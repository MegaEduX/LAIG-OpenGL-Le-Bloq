//
//  Sphere.h
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#ifndef __Project_1__Sphere__
#define __Project_1__Sphere__

#include <iostream>

#include "Primitive.h"

class Sphere : public Primitive {
    
    float _radius;
    
    unsigned int _slices;
    unsigned int _stacks;
    
public:
    
    Sphere(float radius, unsigned int slices, unsigned int stacks) : Primitive() {
        _radius = radius;
        
        _slices = slices;
        _stacks = stacks;
        
        _quad = gluNewQuadric();
    }
    
    ~Sphere() {
        gluDeleteQuadric(_quad);
    }
    
    float getRadius() {
        return _radius;
    }
    
    unsigned int getSlices() {
        return _slices;
    }
    
    unsigned int getStacks() {
        return _stacks;
    }
    
    void draw();
    
};

#endif /* defined(__Project_1__Sphere__) */
