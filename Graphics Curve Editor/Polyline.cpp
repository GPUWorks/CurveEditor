//
//  Polyline.cpp
//  Graphics Curve Editor
//
//  Created by Jon Atkins on 10/23/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#include "Polyline.h"

//bool isBetween(float2 a, float2 b, float2 c) {
//    float crossproduct = (c.y - a.y) * (b.x - a.x) - (c.x - a.x) * (b.y - a.y);
//    if abs(crossproduct) > epsilon : return False   # (or != 0 if using integers)
//        
//        dotproduct = (c.x - a.x) * (b.x - a.x) + (c.y - a.y)*(b.y - a.y)
//        if dotproduct < 0 : return False
//            
//            squaredlengthba = (b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y)
//            if dotproduct > squaredlengthba: return False
//                
//                return True
//}

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
    printf("error: calling Polyline::getPoint\n");
    if (1) {
        exit(1);
    }
    return float2();
}

//loops through
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