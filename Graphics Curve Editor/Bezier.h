//
//  Bezier.h
//  Graphics Curve Editor
//
//  Created by Jon Atkins on 10/23/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef __Graphics_Curve_Editor__Bezier__
#define __Graphics_Curve_Editor__Bezier__

#include <stdio.h>
#include "Freeform.h"

class Bezier : public Freeform {
public:
    Bezier();
    static double bernstein(int i, int n, double t);
    float2 getPoint(float t);
};


#endif /* defined(__Graphics_Curve_Editor__Bezier__) */
