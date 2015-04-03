////
////  BezierDigit.h
////  curve_modeler
////
////  Created by Jayce Rudig-Leathers on 10/22/14.
////  Copyright (c) 2014 Leathers. All rights reserved.
////
//#pragma once
//#ifndef __curve_modeler__BezierDigit__
//#define __curve_modeler__BezierDigit__
//
//#include <stdio.h>
//#include "Bezier.h"
//
//#endif /* defined(__curve_modeler__BezierDigit__) */
//
//const int SCALING_FACTOR = 8;
//
//class BezierDigit {
//private:
//    std::vector<std::vector<double>> controlPoints;
//public:
//    BezierDigit();
//    BezierDigit(int i);
//    
//    std::vector<std::vector<double>> getCPS(){
//        return controlPoints;
//    }
//    
//    std::vector<std::vector<double>> getScaledCPS() {
//        std::vector<std::vector<double>> scaledCPS(4, std::vector<double>(8));
//        for (int j = 0; j < 4; j++) {
//            for (int i = 0; i < 8; i++) {
//                scaledCPS[j][i] = controlPoints[j][i] / SCALING_FACTOR;
//            }
//        }
//        return scaledCPS;
//    }
//    
//    void drawModel(float width, float height, float2 offset){
//        std::vector<std::vector<double>> digitCPS = getScaledCPS();
//        std::vector<Bezier*> digitCurves;
//        glColor3b(0, 0, 0);
//        glLineWidth(2);
//        for(int i = 0; i < 4; i++)
//        {
//            digitCurves.push_back(new Bezier(digitCPS[i], width, height));
//            digitCurves.at(i)->translate(offset);
//            digitCurves.at(i)->drawModel();
//        }
//    }
//    
//
//    
//    
//};
