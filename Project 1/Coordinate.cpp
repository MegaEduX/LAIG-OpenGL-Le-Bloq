//
//  Coordinate.cpp
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 01/10/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#include <iostream>

#include "Coordinate.h"

float* Coordinate2D::getFloatVector() {
    float *f = (float *) malloc(2 * sizeof(float));
    
    f[0] = x;
    f[1] = y;
    
    return f;
}

float* Coordinate2D::vectorToFloatVector(std::vector<Coordinate2D> fv) {
    float *f = (float *) malloc(fv.size() * 2 * sizeof(float));
    
    for (int i = 0, j = 0; j < fv.size(); ) {
        f[i++] = fv[j].x;
        f[i++] = fv[j++].y;
    }
    
    return f;
}

float* Coordinate3D::getFloatVector() {
    float *f = (float *) malloc(4 * sizeof(float));
    
    f[0] = x;
    f[1] = y;
    f[2] = z;
    f[3] = 1.0;
    
	//	#warning This might be why lights aren't working - CHECK IT!
    
    return f;
}

float* Coordinate3D::getRawFloatVector() {
    float *f = (float *) malloc(3 * sizeof(float));
    
    f[0] = x;
    f[1] = y;
    f[2] = z;
    
    return f;
}

float* Coordinate3D::vectorToFloatVector(std::vector<Coordinate3D> fv) {
    float *f = (float *) malloc(fv.size() * 3 * sizeof(float));
    
    for (int i = 0, j = 0; j < fv.size(); ) {
        f[i++] = fv[j].x;
        f[i++] = fv[j].y;
        f[i++] = fv[j++].z;
    }
    
    return f;
}
