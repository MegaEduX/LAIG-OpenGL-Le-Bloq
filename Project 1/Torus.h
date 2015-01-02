//
//  Torus.h
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#ifndef __Project_1__Torus__
#define __Project_1__Torus__

#include <iostream>

#include "Primitive.h"

class Torus : public Primitive {
    
    float _inner;
    float _outer;
    
    unsigned int _slices;
    unsigned int _loops;
    
public:
    
    Torus(float inner, float outer, unsigned int slices, unsigned int loops) : Primitive() {
        _inner = inner;
        _outer = outer;
        _slices = slices;
        _loops = loops;
    }
    
    float getInner() {
        return _inner;
    }
    
    float getOuter() {
        return _outer;
    }
    
    unsigned int getSlices() {
        return _slices;
    }
    
    unsigned int getLoops() {
        return _loops;
    }
    
    void draw();
    
};

#endif /* defined(__Project_1__Torus__) */
