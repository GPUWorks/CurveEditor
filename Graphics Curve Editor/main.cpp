//
//  main.cpp
//  Graphics Curve Editor
//
//  Created by Jon Atkins on 10/22/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <assert.h>

#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#include <vector>
#include "float2.h"

#include "Bezier.h"
#include "Lagrange.h"
#include "Polyline.h"

float timeElapsed = 0;

const float WINDOW_WIDTH = 600;
const float WINDOW_HEIGHT = 600;

//distance allowed from object for click to be recognized
const float CLICK_PRECISION = .05;
//const int NUM_CIRCLES = 10;
const int MIN_CONTROL_POINTS = 2;

//default drawing colors
#define HIGHLIGHT_COLOR .0, .0, .8
#define BEZIER_COLOR .9, .9, .1
#define LAGRANGE_COLOR .1, .9, .1
#define POLYLINE_COLOR .9, .1, .1

//array of valid inputs mean things table:
bool validCurveTypes[256];
void initializevalidCurveTypes() {
    for(int i = 0; i < 256; i++) {
        validCurveTypes[i] = false;
    }
    validCurveTypes[BEZIER] = true;
    validCurveTypes[LAGRANGE] = true;
    validCurveTypes[POLYLINE] = true;
    //    validCurveTypes[CATMULL_CLARK] = true;
    //    validCurveTypes[CATMULL_ROM] = true;
    //    validCurveTypes[HERMITE] = true;
    //    validCURVETYPES[B_SPLINES] = true;
}

//will hold the type of curve that is currently being drawn
char currentCurveType;

enum state {waiting, drawing, addingControlPoints, deletingControlPoints};

state systemMode = waiting;

std::vector<Freeform*> curves;
int selectedCurve = -1;
int selectedControlPoint = - 1;

/* Pixel Conversion Functions */
float pixelToXCoord(int x) {
    return (float)x * 2.0/WINDOW_WIDTH - 1.0;
}

float pixelToYCoord(int y) {
    return -(float)y * 2.0/WINDOW_HEIGHT + 1.0;
}

//makes sure that every time a new curve is selected, the selectedControlPoint is reset
void setSelectedCurve(int newSelectedCurve) {
    if (newSelectedCurve != selectedCurve) {
        selectedCurve = newSelectedCurve;
        selectedControlPoint = -1;
    }
}

//--------------------------------------------------------
// Display callback that is responsible for updating the screen
//--------------------------------------------------------
void onDisplay() {
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);        	// clear color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear screen
    glLineWidth(2);
    
    //draw the Curves
    if(!curves.empty()) {
        for (int i = 0; i < curves.size(); i++) {
            if (i == selectedCurve) {
                glColor3d(HIGHLIGHT_COLOR);
            }
            else if (!curves[i]->isEmpty()) {
//                printf("here\n");
                if(curves[i]->getType() == 'b')
                    glColor3d(BEZIER_COLOR);
                else if (curves[i]->getType() == 'l')
                    glColor3d(LAGRANGE_COLOR);
                else if (curves[i]->getType() == 'p')
                    glColor3d(POLYLINE_COLOR);
            }
            if(curves[i]->numControlPoints() > 0)
                curves[i]->draw();
        }
    }
    //draw control points
    glPointSize(5.0);
    glColor3d(POINT_COLOR);
    printf("selectedControlPoint now is %d\n", selectedControlPoint);
    if(!curves.empty()) {
        for (int i = 0; i < curves.size(); i++) {
            bool isSelected = (selectedCurve == i);
            if (!curves[i]->isEmpty())
                curves[i]->drawControlPoints(isSelected, selectedControlPoint);
        }
    }
    glutSwapBuffers();
}

void onIdle(){
    timeElapsed = glutGet(GLUT_ELAPSED_TIME);
    glutPostRedisplay();
    
}

//function to be called when a key is pressed down
void onKeyBoard(unsigned char key, int x, int y) {
    std::cout << key << " key pressed\n";
    if (validCurveTypes[key]) {
        if (systemMode != drawing) {
            //add new curve
            Freeform *c;
            if (key == BEZIER) {
                c = new Bezier();
            }
            else if (key == LAGRANGE) {
                c = new Lagrange();
            }
            else if (key == POLYLINE) {
                c = new Polyline();
            }
            curves.push_back(c);
            setSelectedCurve((int)curves.size() - 1);
            systemMode = drawing;
        }
        
        //        else if (systemMode == drawing) {
        //            std::cout << "here" << std::endl;
        //            assert (selectedCurve >= 0);
        //            if (key == curves[selectedCurve]->getType()) {
        //                //keep drawing
        //            }
        //            else {
        //                std::cout << "please don't press two keys at once\n" << std::endl;
        //            }
        //        }
        
    }
    else if (key == ' ') {
        assert (selectedCurve >= -1);
        setSelectedCurve((selectedCurve + 1) % curves.size());
    }
    else if (key == 'a') {
        systemMode = addingControlPoints;
    }
    else if(key == 'd') {
        systemMode = deletingControlPoints;
    }
    else if (key == 'c') {
        curves.clear();
        systemMode = waiting;
    }
    else
        std::cout << "That key is unsupported\n";
    
    
    //    std::cout << "after onKeyboard: mode is currently: " << systemMode << std::endl;
    
    glutPostRedisplay();
}

//when the key is released (if it is the right one?? - do I need it to be)
void onKeyBoardRelease(unsigned char key, int x, int y) {
        std::cout << key << " released" << std::endl;
//    if (validKeyInputs[key]) {
    if (validCurveTypes[key] || key == 'd') {
        //        std::cout << "OnKeyBoardRelease: mode is currently: " << systemMode << std::endl;
        if (!curves.empty()) {
            assert(selectedCurve >= 0);
            if (curves[selectedCurve]->numControlPoints() < MIN_CONTROL_POINTS)
                curves.erase(curves.begin() + selectedCurve);
        }
    }
    systemMode = waiting;
}

void onMouse(int button, int state, int x, int y) {
    printf("click registered\n");
    float2 coord = float2(pixelToXCoord(x), pixelToYCoord(y));
    if (systemMode == waiting) {
        //select curves or control points
        if (systemMode == GLUT_DOWN) {
            bool isControlPoint = false;
            for (int i = 0; i < curves.size(); i++) {
                for (int j = 0; j < curves[i]->numControlPoints(); j++) {
                    if (coord.withinRange(curves[i]->getControlPoint(j), CLICK_PRECISION)) {
                        isControlPoint = true;
                        printf("selectedControlPoint == %d\n", selectedControlPoint);
                        //for consistency
                        setSelectedCurve(i);
//                        selectedCurve = i;
                        selectedControlPoint = j;
                    }
                }
            }
            //select curves
            if (!isControlPoint) {
                for (int i = 0; i < curves.size(); i++) {
                    if (curves[i]->onLine(coord, CLICK_PRECISION))
                        setSelectedCurve(i);
                }
            }
        }
    }
    else if (systemMode == drawing || systemMode == addingControlPoints) {
        
        if ((button == GLUT_LEFT_BUTTON || GLUT_RIGHT_BUTTON) && state == GLUT_DOWN) {
            assert (!curves.empty());
            if (selectedCurve >= 0) {
                curves[selectedCurve]->addControlPoint(coord);
            }
        }
    }
    else if (systemMode == deletingControlPoints) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            //no way to check if this worked
            selectedControlPoint = curves[selectedCurve]->deleteControlPoint(coord, CLICK_PRECISION, selectedControlPoint);
        }
    }
    
//        //probably get rid of selected control points when curve is deselected
//        if (state == GLUT_UP && selectedControlPoint > -1) {
//            for (int i = 0; i < curves.size(); i++) {
//                printf("resetting selected Control Point\n");
//                selectedControlPoint = -1;
//            }
//        }
    
    glutPostRedisplay();
}

//--------------------------------------------------------
// The entry point of the application
//--------------------------------------------------------
int main(int argc, char *argv[]) {
    
    initializevalidCurveTypes();
    
    glutInit(&argc, argv);                 		// GLUT initialization
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);				// Initial resolution of window
    glutInitWindowPosition(100, 100);            // Initial location of window
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);    // Image = 8 bit R,G,B + double buffer + depth buffer
    
    glutCreateWindow("Curve Editor");        	// Window is born with name
    glutIdleFunc(onIdle);
    glutDisplayFunc(onDisplay);                	// Register event handlers
    glutKeyboardFunc(onKeyBoard);
    glutKeyboardUpFunc(onKeyBoardRelease);
    glutMouseFunc(onMouse);
    
    glutMainLoop();                    			// Event loop  
    
    return 0;
}