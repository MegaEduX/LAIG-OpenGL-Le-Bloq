//
//  Plane.h
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#ifndef __Project_1__Plane__
#define __Project_1__Plane__

#include <iostream>

#include "Primitive.h"

class Plane : public Primitive {
    
    int _parts;
    
public:
    
    Plane(int parts) : Primitive() {
        _parts = parts;
    }
    
    void draw();
    
};

#endif /* defined(__Project_1__Plane__) */
