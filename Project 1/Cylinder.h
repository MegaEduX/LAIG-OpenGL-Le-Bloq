//
//  Cylinder.h
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#ifndef __Project_1__Cylinder__
#define __Project_1__Cylinder__

#include <iostream>

#include "Primitive.h"

class Cylinder : public Primitive {
    
    float _base;
    float _top;
    float _height;
    
    unsigned int _slices;
    unsigned int _stacks;
    
public:
    
    Cylinder(float base, float top, float height, unsigned int slices, unsigned int stacks) : Primitive() {
        _base = base;
        _top = top;
        _height = height;
        
        _slices = slices;
        _stacks = stacks;
    }
    
    float getBase() {
        return _base;
    }
    
    float getTop() {
        return _top;
    }
    
    float getHeight() {
        return _height;
    }
    
    unsigned int getSlices() {
        return _slices;
    }
    
    unsigned int getStacks() {
        return _stacks;
    }
    
    void draw();
    
};


#endif /* defined(__Project_1__Cylinder__) */
