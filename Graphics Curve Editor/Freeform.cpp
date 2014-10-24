//
//  Freeform.cpp
//  Graphics Curve Editor
//
//  Created by Jon Atkins on 10/22/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#include "Freeform.h"

void Freeform::drawControlPoints(bool isSelectedCurve, int selectedControlPoint) {
    glBegin(GL_POINTS);
    if (isSelectedCurve) {
        for (int i = 0; i < numControlPoints(); i++) {
            printf("selected control point (in drawControlPoints) is == %d\n", selectedControlPoint);
            if ((selectedControlPoint == i) ||
                selectedControlPoint == controlPoints.size()) {
                printf("here\n");
                glColor3d(POINT_HIGHLIGHT_COLOR);
            }
            else {
                glColor3d(POINT_COLOR);
            }
            glVertex2d(controlPoints[i].x, controlPoints[i].y);
        }
    }
    else if (!isSelectedCurve) {
        glColor3d(POINT_COLOR);
        for (int i = 0; i < numControlPoints(); i++) {
                    glVertex2d(controlPoints[i].x, controlPoints[i].y);
        }


    }

    glEnd();
}

void Freeform::addControlPoint(float2 p) {
    controlPoints.push_back(p);
}

bool Freeform::isEmpty() {
    return controlPoints.empty();
}

int Freeform::numControlPoints() {
    if (controlPoints.empty())
        return 0;
    return (int)controlPoints.size();
}

int Freeform::deleteControlPoint(float2 clickLocation, float radius, int selectedControlPoint) {
    for (int i = 0; i < controlPoints.size(); i++) {
        if(clickLocation.withinRange(controlPoints[i], radius)) {
            controlPoints.erase(controlPoints.begin() + i);
            //fix the selected index problem
            if (i < selectedControlPoint) {
                return selectedControlPoint - 1;
//                selectedControlPoint--;
            }
            else if (i == selectedControlPoint) {
                return - 1;
//                selectedControlPoint = -1;
            }
            //if all were selected
            else if (selectedControlPoint == controlPoints.size() + 1) {
                return selectedControlPoint;
//                selectedControlPoint--;
            }
            return true;
        }
    }
    return false;
}

float2 Freeform::getControlPoint(int index) {
    return controlPoints[index];
}

char Freeform::getType() {
    return type;
}

void Freeform::draw() {
    glLineWidth(DEFAULT_LINE_WIDTH);
    glBegin(GL_LINE_STRIP);
    for (float f = 0; f < 1; f += (1/(float)PRECISION)){
//        printf("drawing point\n");
        float2 pt = getPoint(f);
        glVertex2d(pt.x, pt.y);
    }
    glEnd();
}

bool Freeform::onLine(float2 clickPosition, float radius) {
    for (float t = 0.0; t < (float)numControlPoints() - 1; t += 1/PRECISION) {
        float2 target = getPoint(t);
        if (clickPosition.withinRange(target, radius)) {
            return true;
        }
    }
    return false;
}