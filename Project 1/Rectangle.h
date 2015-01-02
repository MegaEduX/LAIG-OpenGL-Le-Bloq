//
//  Rectangle.h
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#ifndef __Project_1__Rectangle__
#define __Project_1__Rectangle__

#include <iostream>

#include "Primitive.h"

class Rectangle : public Primitive {
    
    Coordinate2D _point1;
    Coordinate2D _point2;
    
public:
    
    Rectangle(Coordinate2D p1, Coordinate2D p2) : Primitive() {
        _point1 = p1;
        _point2 = p2;
    }
    
    void draw();
    
};

#endif /* defined(__Project_1__Rectangle__) */
