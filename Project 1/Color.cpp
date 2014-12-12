//
//  Color.cpp
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 30/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#include <iostream>

#include "Color.h"

float *color_to_float_vec(kColorRGB col) {
    float *f = (float *)malloc(4 * sizeof(float));
    
    f[0] = col.r;
    f[1] = col.g;
    f[2] = col.b;
    f[3] = col.a;
    
    return f;
}

kColorRGB color_red() {
    kColorRGB color;
    
    color.r = 1.0f;
    color.g = 0.0f;
    color.b = 0.0f;
    color.a = 1.0f;
    
    return color;
}

kColorRGB color_green() {
    kColorRGB color;
    
    color.r = 0.0f;
    color.g = 1.0f;
    color.b = 0.0f;
    color.a = 1.0f;
    
    return color;
}


kColorRGB color_blue() {
    kColorRGB color;
    
    color.r = 0.0f;
    color.g = 0.0f;
    color.b = 1.0f;
    color.a = 1.0f;
    
    return color;
}

kColorRGB color_black() {
    kColorRGB color;
    
    color.r = 0.0f;
    color.g = 0.0f;
    color.b = 0.0f;
    color.a = 1.0f;
    
    return color;
}

kColorRGB color_white() {
    kColorRGB color;
    
    color.r = 1.0f;
    color.g = 1.0f;
    color.b = 1.0f;
    color.a = 1.0f;
    
    return color;
}
