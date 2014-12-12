//
//  Color.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 26/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef Project_1_Color_h
#define Project_1_Color_h

typedef struct {
    float r;
    float g;
    float b;
    float a;
} kColorRGB;

float *color_to_float_vec(kColorRGB);

kColorRGB color_red();
kColorRGB color_green();
kColorRGB color_blue();
kColorRGB color_black();
kColorRGB color_white();

#endif
