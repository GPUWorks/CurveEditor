//
//  Lagrange.h
//  Graphics Curve Editor
//
//  Created by Jon Atkins on 10/23/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef __Graphics_Curve_Editor__Lagrange__
#define __Graphics_Curve_Editor__Lagrange__

#include <stdio.h>
#include "Freeform.h"

class Lagrange : public Freeform {
public:
    Lagrange();
    float L(int i, float t);
    void addControlPoint(float2 p);
    float2 getPoint(float t);
    int deleteControlPoint(float2 clickLocation, float radius, int selectedControlPoint);
    void moveSelectedControlPoint(float x, float y, int selectedControlPoint);
private:
    std::vector<float> knots;
    void recalculateKnots();
    
};

#endif /* defined(__Graphics_Curve_Editor__Lagrange__) */
