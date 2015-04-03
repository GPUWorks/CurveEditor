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
#include "CatmullClark.h"

float timeElapsed = 0;

const float WINDOW_WIDTH = 600;
const float WINDOW_HEIGHT = 600;

//distance allowed from object for click to be recognized
const float CLICK_PRECISION = .05;
//const int NUM_CIRCLES = 10;
const int MIN_CONTROL_POINTS = 2;

//default drawing colors
#define HIGHLIGHT_COLOR .275, .882, 1
#define BEZIER_COLOR .9, .9, .1
#define LAGRANGE_COLOR .1, .9, .1
#define POLYLINE_COLOR .9, .1, .1
#define CATMULL_CLARK_COLOR 1, .565, .275

//array of valid inputs mean things table:
bool validCurveTypes[256];
void initializevalidCurveTypes() {
    for(int i = 0; i < 256; i++) {
        validCurveTypes[i] = false;
    }
    validCurveTypes[BEZIER] = true;
    validCurveTypes[LAGRANGE] = true;
    validCurveTypes[POLYLINE] = true;
    validCurveTypes[CATMULL_CLARK] = true;
    //    validCurveTypes[CATMULL_ROM] = true;
    //    validCurveTypes[HERMITE] = true;
    //    validCURVETYPES[B_SPLINES] = true;
}

//will hold the type of curve that is currently being drawn
char currentCurveType;

enum state {waiting, drawing, addingControlPoints, deletingControlPoints, draggingControlPoint};

state systemMode = waiting;

std::vector<Freeform*> curves;
int selectedCurve = -1;
int selectedControlPoint = - 1;
float2 currentMousePosition;

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
                if(curves[i]->getType() == BEZIER)
                    glColor3d(BEZIER_COLOR);
                else if (curves[i]->getType() == LAGRANGE)
                    glColor3d(LAGRANGE_COLOR);
                else if (curves[i]->getType() == POLYLINE)
                    glColor3d(POLYLINE_COLOR);
                else if (curves[i]->getType() == CATMULL_CLARK)
                    glColor3d(CATMULL_CLARK_COLOR);
            }
            if(curves[i]->numControlPoints() > 0) {
                if (curves[i]->isFilled())
                    curves[i]->drawFilled();
                curves[i]->draw();
            }
        }
    }
    //draw control points
    glPointSize(5.0);
    glColor3d(POINT_COLOR);
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
            else if (key == CATMULL_CLARK) {
                c = new CatmullClark();
            }
            curves.push_back(c);
            setSelectedCurve((int)curves.size() - 1);
            systemMode = drawing;
        }
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
    else if (key == 'f') {
        curves[selectedCurve]->fill();
//        systemMode = waiting;
    }
    else if (key == 'z') {
        curves.clear();
        systemMode = waiting;
    }
    else
        fprintf(stderr, "That key is unsupported\n");
    
    glutPostRedisplay();
}

void onKeyBoardRelease(unsigned char key, int x, int y) {
    if (validCurveTypes[key] || key == 'd') {
        if (!curves.empty()) {
            assert(selectedCurve >= 0);
            if (curves[selectedCurve]->numControlPoints() < MIN_CONTROL_POINTS)
                curves.erase(curves.begin() + selectedCurve);
        }
    }
    systemMode = waiting;
}

void onMouse(int button, int state, int x, int y) {
    currentMousePosition = float2(pixelToXCoord(x), pixelToYCoord(y));
    
    if (systemMode == waiting) {
        //select curves or control points
        if (systemMode == GLUT_DOWN) {
            //select controlPoints
            bool isControlPoint = false;
            for (int i = 0; i < curves.size(); i++) {
                for (int j = 0; j < curves[i]->numControlPoints(); j++) {
                    if (currentMousePosition.withinRange(curves[i]->getControlPoint(j), CLICK_PRECISION)) {
                        isControlPoint = true;
                        //for consistency
                        setSelectedCurve(i);
                        selectedControlPoint = j;
                        
                        //break out of all loops
                        glutPostRedisplay();
                        return;
                    }
                }
            }
            //select curves
            if (!isControlPoint) {
                selectedControlPoint = -1;
                for (int i = 0; i < curves.size(); i++) {
                    if (curves[i]->onLine(currentMousePosition, CLICK_PRECISION)) {
                        setSelectedCurve(i);
                        selectedControlPoint = curves[i]->numControlPoints();
                    }
                }
            }
        }
    }
    else if (systemMode == drawing || systemMode == addingControlPoints) {
        if ((button == GLUT_LEFT_BUTTON || GLUT_RIGHT_BUTTON) && state == GLUT_DOWN) {
            assert (!curves.empty());
            if (selectedCurve >= 0) {
                curves[selectedCurve]->addControlPoint(currentMousePosition);
            }
        }
    }
    else if (systemMode == deletingControlPoints) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            //no way to check if this worked
            selectedControlPoint = curves[selectedCurve]->deleteControlPoint(currentMousePosition, CLICK_PRECISION, selectedControlPoint);
        }
    }
    
    glutPostRedisplay();
}

void onMouseMotion(int x, int y) {
    float2 coord = float2(pixelToXCoord(x), pixelToYCoord(y));
    float2 distance = currentMousePosition - coord;
    currentMousePosition = coord;
    if (selectedControlPoint > -1 && selectedControlPoint < curves[selectedCurve]->numControlPoints()) {
        curves[selectedCurve]->resetControlPoint(coord, selectedControlPoint);
    }
    else if (selectedControlPoint == curves[selectedCurve]->numControlPoints()) {
        curves[selectedCurve]->translate(distance);
    }
        
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
    glutMotionFunc(onMouseMotion);
    
    glutMainLoop();                    			// Event loop  
    
    return 0;
}