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
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < numControlPoints(); i++) {
        glVertex2d(controlPoints[i].x, controlPoints[i].y);
    }
    glEnd();
}

float2 Polyline::getPoint(float t) {
    printf("error: calling Polyline::getPoint\n");
    if (1) {
        exit(1);
    }
    return float2();
}