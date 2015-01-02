//
//  Triangle.h
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#ifndef __Project_1__Triangle__
#define __Project_1__Triangle__

#include <iostream>

#include "Primitive.h"

class Triangle : public Primitive {
    
    Coordinate3D _point1;
    Coordinate3D _point2;
    Coordinate3D _point3;
    
public:
    
    Triangle(Coordinate3D p1, Coordinate3D p2, Coordinate3D p3) : Primitive() {
        _point1 = p1;
        _point2 = p2;
        _point3 = p3;
    }
    
    void draw();
    
};

#endif /* defined(__Project_1__Triangle__) */
