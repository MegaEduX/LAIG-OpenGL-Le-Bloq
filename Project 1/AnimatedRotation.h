//
//  AnimatedRotation.h
//  Project 1
//
//  Created by Eduardo Almeida on 22/12/14.
//  Copyright (c) 2014 Eduardo Almeida. All rights reserved.
//

#ifndef __Project_1__AnimatedRotation__
#define __Project_1__AnimatedRotation__

#include <iostream>

#include "GraphicalObject.h"

#include "CGFobject.h"

#include "Coordinate.h"

class AnimatedRotation : public GraphicalObject {
    
    int _angle, _current;
    
    int _ticks, _elapsed;
    
    Coordinate3D _rotAxis;
    
public:
    
    AnimatedRotation(float angle, Coordinate3D axis, int ticks) {
        _angle = angle;
        _ticks = ticks;
        
        _elapsed = 0;
        _current = 0.0f;
        
        _rotAxis = axis;
    }
    
    void apply() {
        if (_ticks == _elapsed)
            return;
        
        _current += _angle / (float) _ticks;
        
        _elapsed++;
        
        glRotated(_current, _rotAxis.x, _rotAxis.y, _rotAxis.z);
    }
    
    bool getDone() {
        return (_ticks == _elapsed);
    }
    
};

#endif /* defined(__Project_1__AnimatedRotation__) */
