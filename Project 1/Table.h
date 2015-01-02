//
//  Table.h
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#ifndef __Project_1__Table__
#define __Project_1__Table__

#include <iostream>

#include "Primitive.h"

#include "UnitCube.h"

class Table : public Primitive {
    
    UnitCube *cube = new UnitCube();
    
public:
    
    Table() {
        
    }
    
    ~Table() {
        delete cube;
    }
    
    void draw();
    
};

#endif /* defined(__Project_1__Table__) */
