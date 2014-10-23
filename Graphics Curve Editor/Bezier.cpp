//
//  Bezier.cpp
//  Graphics Curve Editor
//
//  Created by Jon Atkins on 10/23/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#include "Bezier.h"
#include <assert.h>

Bezier::Bezier() {
    type = BEZIER;
}

double Bezier::bernstein(int i, int n, double t) {
    if(n == 1) {
        if(i == 0) return 1-t;
        if(i == 1) return t; return 0;
    }
    if(i < 0 || i > n) return 0; return (1 - t) * bernstein(i, n-1, t) + t * bernstein(i-1, n-1, t);
}

float2 Bezier::getPoint(float t) {
    float2 r(0.0, 0.0);
    
    int n = (int)controlPoints.size();
    for (int i = 0; i < n; i++) {
        float weight = bernstein(i, n- 1, t);
        r += controlPoints[i] * weight;
    }
    
    return r;
}