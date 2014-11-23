//
//  Transform.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 23/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__Transform__
#define __Project_1__Transform__

#include <iostream>

#include "GraphicalException.h"

_BUILD_GRAPHICAL_EXCEPTION(InvalidTransformException, GraphicalException);
_BUILD_GRAPHICAL_EXCEPTION(RotateException, InvalidTransformException);

class Transform {
    
public:
    
    virtual void apply() {
        throw new InvalidTransformException("Invalid transformation attempted!");
    }
    
};

#include "GraphicalObject.h"

#include "Coordinate.h"

class Translate : public Transform {
    
    Coordinate3D _to;
    
public:
    
    Translate(Coordinate3D dest) {
        _to = dest;
    }
    
    Coordinate3D destination() {
        return _to;
    }
    
    void apply();
    
};

class Rotate : public Transform {
    
    char _axis;
    
    float _angle;
    
public:
    
    Rotate(char axis, float angle) {
        _axis = axis;
        _angle = angle;
        
        if (_axis != 'x' && _axis != 'y' && _axis != 'z')
            throw new RotateException("Invalid Axis.");
    }
    
    char getAxis() {
        return _axis;
    }
    
    float getAngle() {
        return _angle;
    }
    
    void apply();
    
};

class Scale : public Transform {
    
    Coordinate3D _scaleAxis;
    
public:
    
    Scale(Coordinate3D scale) {
        _scaleAxis = scale;
    }
    
    Coordinate3D getScaleAxis() {
        return _scaleAxis;
    }
    
    void apply();
    
};

#endif /* defined(__Project_1__Transform__) */
