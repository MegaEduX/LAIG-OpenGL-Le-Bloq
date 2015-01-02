//
//  Patch.h
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#ifndef __Project_1__Patch__
#define __Project_1__Patch__

#include <iostream>

#include "Primitive.h"

typedef enum {
    
    kPatchComputePoint,
    kPatchComputeLine,
    kPatchComputeFill
    
} kPatchCompute;

class Patch : public Primitive {
    
    int _order;
    
    Coordinate2D _parts;
    
    kPatchCompute _compute;
    
    std::vector<Coordinate3D> _controlPoints;
    
public:
    
    Patch(int order, Coordinate2D parts, kPatchCompute compute) : Primitive() {
        _order = order;
        
        _parts = parts;
        
        _compute = compute;
    }
    
    void addControlPoint(Coordinate3D cp) {
        _controlPoints.push_back(cp);
    }
    
    bool removeControlPoint(Coordinate3D cp) {
        for (int i = 0; i < _controlPoints.size(); i++)
            if (_controlPoints[i] == cp) {
                _controlPoints.erase(_controlPoints.begin() + i);
                
                return true;
            }
        
        return false;
    }
    
    void draw();
    
};

#endif /* defined(__Project_1__Patch__) */
