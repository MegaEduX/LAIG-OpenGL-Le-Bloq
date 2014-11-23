//
//  GraphicalMath.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 28/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef Project_1_GraphicalMath_h
#define Project_1_GraphicalMath_h

#include <math.h>

#include "Coordinate.h"

#ifndef M_PI

#define M_PI 3.1415926535

#endif

inline double rad_to_deg(double rad) {
    return rad * (180.0 / M_PI);
}

inline double deg_to_rad(double deg) {
    return deg * (M_PI / 180.0);
}

#endif
