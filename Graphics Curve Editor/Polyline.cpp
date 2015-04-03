//
//  Polyline.cpp
//  Graphics Curve Editor
//
//  Created by Jon Atkins on 10/23/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#include "Polyline.h"

Polyline::Polyline() {
    type = POLYLINE;
}

void Polyline::draw() {
    glLineWidth(DEFAULT_LINE_WIDTH);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < numControlPoints(); i++) {
        glVertex2d(controlPoints[i].x, controlPoints[i].y);
    }
    glEnd();
}

float2 Polyline::getPoint(float t) {
    fprintf(stderr, "error: calling Polyline::getPoint\n");
    if (1) {
        exit(1);
    }
    return float2();
}

//loops through sections between control points and checks every point there.
bool Polyline::onLine(float2 point, float radius) {
    float2 slope;
    for (int section = 0; section < numControlPoints() - 1; section++) {
        slope = controlPoints[section + 1] - controlPoints[section];
        for (float t = 0; t < 1; t += 1/PRECISION) {
            if (point.withinRange(slope * t, radius))
                return true;
        }
    }
    return false;
}

void Polyline::drawFilled() {
    glBegin(GL_POLYGON);
    for (int i = 0; i < numControlPoints(); i++) {
        glVertex2d(getControlPoint(i).x, getControlPoint(i).y);
    }
    glEnd();
}