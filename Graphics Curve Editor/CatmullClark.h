//
//  CatmullClark.h
//  Graphics Curve Editor
//
//  Created by Jon Atkins on 10/28/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef __Graphics_Curve_Editor__CatmullClark__
#define __Graphics_Curve_Editor__CatmullClark__ 

#include <stdio.h>
#include "Freeform.h"
#include "assert.h"
#include <vector>

const int NUM_SUBDIVISIONS = 3;

class CatmullClark : public Freeform {
public:
    CatmullClark();
    void draw();
    float2 getPoint(float t);
    bool onLine(float2 point, float radius);
    void drawFilled();
private:
    void divideRecursive(int counter);
    void divide();
    /*returns the new drawPoint instead of the control/drawPoint at current index */
    float2 getNewPoint(int index);
    /*returns the midPoint of a given section (section 0 is first section), returns (-1, -1) for last section) */
    float2 getMidPoint(int section);
    
    std::vector<float2> drawPoints;
};

#endif /* defined(__Graphics_Curve_Editor__CatmullClark__) */
