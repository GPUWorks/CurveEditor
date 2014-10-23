//
//  Polyline.h
//  Graphics Curve Editor
//
//  Created by Jon Atkins on 10/23/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef __Graphics_Curve_Editor__Polyline__
#define __Graphics_Curve_Editor__Polyline__

#include <stdio.h>
#include "Freeform.h"

class Polyline : public Freeform {
public:
    Polyline();
    void draw();
    float2 getPoint(float t);
    bool onLine(float2 clickPosition, float radius);
//    bool deleteControlPoint(float2 clickLocation, float radius);
private:
//    bool isOnLine(float2 p);
};

#endif /* defined(__Graphics_Curve_Editor__Polyline__) */
