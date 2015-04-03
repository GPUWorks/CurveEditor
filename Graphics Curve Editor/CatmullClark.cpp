//
//  CatmullClark.cpp
//  Graphics Curve Editor
//
//  Created by Jon Atkins on 10/28/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#include "CatmullClark.h"

CatmullClark::CatmullClark() {
    type = CATMULL_CLARK;
}

void CatmullClark::draw() {
    divide();
    glLineWidth(DEFAULT_LINE_WIDTH);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < drawPoints.size(); i++) {
        glVertex2d(drawPoints[i].x, drawPoints[i].y);
    }
    glEnd();
}

float2 CatmullClark::getPoint(float t) {
    fprintf(stderr, "error: calling CatmullClark::getPoint\n");
    if (1) {
        exit(1);
    }
    return float2();
}

//loops through sections between control points and checks every point there.
bool CatmullClark::onLine(float2 point, float radius) {
    float2 slope;
    for (int section = 0; section < drawPoints.size() - 1; section++) {
        slope = drawPoints[section + 1] - drawPoints[section];
        for (float t = 0; t < 1; t += 1/PRECISION) {
            if (point.withinRange(slope * t, radius)) {
                return true;
            }
        }
    }
    return false;
}

void CatmullClark::divide() {
    drawPoints.clear();
    drawPoints = controlPoints;
    divideRecursive(NUM_SUBDIVISIONS);
}

void CatmullClark::divideRecursive(int counter) {
    if (counter <= 0) {
        return;
    }
    
    int numTimes = (int)drawPoints.size();
    std::vector<float2> newDrawPoints;
    for (int section = 0; section < numTimes; section++) {
        float2 newPoint = getNewPoint(section);
        float2 midPoint = getMidPoint(section);
        
        newDrawPoints.push_back(newPoint);
        if(midPoint != SENTINEL_FLOAT2)
            newDrawPoints.push_back(midPoint);
        
    }
    drawPoints.clear();
    drawPoints = newDrawPoints;
    divideRecursive(counter - 1);
}

float2 CatmullClark::getMidPoint(int section) {
    if (section == drawPoints.size() - 1)
        return SENTINEL_FLOAT2;
    else {
        float2 slope = drawPoints.at(section + 1) - drawPoints.at(section);
        float2 midPoint = drawPoints[section] + (slope * .5);
        return midPoint;
    }
}

float2 CatmullClark::getNewPoint(int index) {
    if (index == 0 || index == drawPoints.size() - 1)
        return drawPoints[index];
    else {
        float2 midPoint1 = getMidPoint(index - 1);
        float2 midPoint2 = getMidPoint(index);
        assert (midPoint1 != SENTINEL_FLOAT2);
        assert (midPoint2 != SENTINEL_FLOAT2);
        float2 newPoint = (drawPoints[index] * .5) + (midPoint1 * .25) + (midPoint2 * .25);
        return newPoint;
    }
}

void CatmullClark::drawFilled() {
    glBegin(GL_POLYGON);
    for (int i = 0; i < drawPoints.size(); i++) {
        glVertex2d(drawPoints[i].x, drawPoints[i].y);
    }
    glEnd();
}
