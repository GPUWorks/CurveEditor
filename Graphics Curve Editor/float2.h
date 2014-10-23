//
//  float2.h
//  Graphics Class 9-18
//
//  Created by Jon Atkins on 9/25/14.
//  Copyright (c) 2014 AIT. All rights reserved.
//

#ifndef Graphics_Class_9_18_float2_h
#define Graphics_Class_9_18_float2_h

#pragma once

#include <math.h>
#include <iostream>
#include <cstdlib>

class float2
{
public:
    float x;
    float y;
    
    float2()
    {
        x = 0.0f;
        y = 0.0f;
    }
    
    float2(float x, float y):x(x),y(y){}
    
    float2 operator-() const
    {
        return float2(-x, -y);
    }
    
    float2 operator+(const float2& addOperand) const
    {
        return float2(x + addOperand.x, y + addOperand.y);
    }
    
    float2 operator-(const float2& operand) const
    {
        return float2(x - operand.x, y - operand.y);
    }
    
    float2 operator*(const float2& operand) const
    {
        return float2(x * operand.x, y * operand.y);
    }
    
    float2 operator*(float operand) const
    {
        return float2(x * operand, y * operand);
    }
    
    void operator-=(const float2& a)
    {
        x -= a.x;
        y -= a.y;
    }
    
    void operator+=(const float2& a)
    {
        x += a.x;
        y += a.y;
    }
    
    void operator*=(const float2& a)
    {
        x *= a.x;
        y *= a.y;
    }
    
    void operator*=(float a)
    {
        x *= a;
        y *= a;
    }
    
    float norm()
    {
        return sqrtf(x*x+y*y);
    }
    
    float norm2()
    {
        return x*x+y*y;
    }
    
    float2 normalize()
    {
        float oneOverLength = 1.0f / norm();
        x *= oneOverLength;
        y *= oneOverLength;
        return *this;
    }
    
    static float2 random()
    {
        return float2(
                      ((float)rand() / RAND_MAX) * 2 - 1,
                      ((float)rand() / RAND_MAX) * 2 - 1);
    }
    
    
    
    //checks if the point is within the given range of the given radius (circular range)
    bool withinRange(float2 target, float radius) {
        float2 diff = target - *this;
        float distanceSqrd = (diff.x * diff.x) + (diff.y * diff.y);
        std::cout << "distance == " << distanceSqrd << std::endl;
        std::cout << "radius == " << radius << std::endl;
        
        if (distanceSqrd <= radius * radius) {
//            std::cout << "Within Range\n\n\n\n";
            return true;
        }
        return false;
    }
};


#endif
