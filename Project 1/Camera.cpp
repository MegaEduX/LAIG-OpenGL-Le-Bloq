//
//  Camera.cpp
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 27/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#include "Camera.h"

#include "CGFcamera.h"
#include "CGFapplication.h"

bool Camera::defaultCameraExists = false;

void Camera::_setup() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void PerspectiveCamera::updateProjectionMatrix(int w, int h) {
    _setup();
    
    float aspect = (float) w / (float) h;
    
    gluPerspective(_angle, aspect, _near, _far);
}

void PerspectiveCamera::applyView() {
    if (mode == EXAMINE_MODE) {
        gluLookAt(position[0], position[1], position[2], target[0], target[1], target[2], 0, 1, 0);
        
        glRotatef(rotation[0], 1.f, 0.f, 0.f);
        glRotatef(rotation[1], 0.f, 1.f, 0.f);
        glRotatef(rotation[2], 0.f, 0.f, 1.f);
    } else {
        glRotatef(rotation[0], 1.f, 0.f, 0.f);
        glRotatef(rotation[1], 0.f, 1.f, 0.f);
        glRotatef(rotation[2], 0.f, 0.f, 1.f);
        
        glTranslatef(position[0], position[1], position[2]);
    }
}

void OrthographicCamera::applyView() {
    if(_axis == 'x')
        glRotatef(-90, 0, 1, 0);
    else if (_axis == 'y')
        glRotatef(90, 1, 0, 0);
    
    //  Not needed if _axis == 'z'
}

void OrthographicCamera::updateProjectionMatrix(int w, int h) {
    _setup();
    
    float aspect = (float) w / (float) h;
    
    glOrtho(_left * aspect, _right * aspect, _bottom, _top, _near, _far);
}
