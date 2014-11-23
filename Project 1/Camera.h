//
//  Camera.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 27/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__Camera__
#define __Project_1__Camera__

#include <iostream>

#include "GraphicalObject.h"

#include "Coordinate.h"

#include "CGFcamera.h"

class Camera : public GraphicalObject, public CGFcamera {
    
    bool _enabled;
    
protected:
    
    void _setup();
    
public:
    
    static bool defaultCameraExists;
    
    Camera(std::string anId) : GraphicalObject(anId) {
        
    }
    
    bool getEnabled() {
        return _enabled;
    }
    
    bool setEnabled(bool setting) {
        if (setting) {
            if (defaultCameraExists)
                return false;
            
            defaultCameraExists = true;
            
            _enabled = true;
            
            return true;
        } else {
            if (!_enabled)
                return false;
            
            defaultCameraExists = false;
            
            _enabled = false;
            
            return true;
        }
        
        return false;
    }
    
    virtual void updateProjectionMatrix(int, int) {
        
    }
    
    virtual void applyView() {
        
    }
    
};

class PerspectiveCamera : public Camera {
    
    float _near;
    float _far;
    float _angle;
    
    Coordinate3D _position;
    Coordinate3D _target;
    
public:
    
    PerspectiveCamera(std::string anId, float near, float far, float angle, Coordinate3D position, Coordinate3D target) : Camera(anId) {
        _near = near;
        _far = far;
        _angle = angle;
        
        _position = position;
        _target = target;
    }
    
    void updateProjectionMatrix(int, int);
    void applyView();
    
};

class OrthographicCamera : public Camera {
    
    char _axis;
    
    float _near;
    float _far;
    float _left;
    float _right;
    float _top;
    float _bottom;
    
public:
    
    OrthographicCamera(std::string anId, char axis, float near, float far, float left, float right, float top, float bottom) : Camera(anId) {
        _axis = axis;
        
        _near = near;
        _far = far;
        _left = left;
        _right = right;
        _top = top;
        _bottom = bottom;
    }
    
    void updateProjectionMatrix(int, int);
    
    void applyView();
    
};

#endif /* defined(__Project_1__Camera__) */
