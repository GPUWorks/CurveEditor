//
//  Lagrange.cpp
//  Graphics Curve Editor
//
//  Created by Jon Atkins on 10/23/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#include "Lagrange.h"

Lagrange::Lagrange() {
    type = LAGRANGE;
}

float Lagrange::L(int i, float t) {
    float f = 1.0;
    for (int j = 0; j < numControlPoints(); j++) {
        if (j != i) {
            f *= (t - knots[j])/(knots[i] - knots[j]);
        }
    }
    return f;
}
void Lagrange::addControlPoint(float2 p) {
    controlPoints.push_back(p);
    knots.push_back(1);
    recalculateKnots();
}

void Lagrange::recalculateKnots() {
    int n = (int)knots.size();
    for (int i = 0; i < n; i++) {
        knots[i] = (float)i/(n - 1);
    }
}

float2 Lagrange::getPoint(float t) {
    float2 r = float2(0, 0);
    for (int i = 0; i < numControlPoints(); i++) {
        r += controlPoints[i] * L(i, t);
    }
    
    return r;
}

//returns the new selected control point
int Lagrange::deleteControlPoint(float2 clickLocation, float radius, int selectedControlPoint) {
    for (int i = 0; i < controlPoints.size(); i++) {
        if(clickLocation.withinRange(controlPoints[i], radius)) {
            controlPoints.erase(controlPoints.begin() + i);
            knots.pop_back();
            recalculateKnots();
            //fix the selected index problem
            if (i < selectedControlPoint) {
                return selectedControlPoint - 1;
            }
            else if (i == selectedControlPoint) {
                return - 1;
            }
            //if all were selected
            else if (selectedControlPoint == controlPoints.size() + 1) {
                return selectedControlPoint;
            }
            return true;
        }
    }
    return false;
}