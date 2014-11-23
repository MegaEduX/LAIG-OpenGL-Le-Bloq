//
//  Light.cpp
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 27/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#include "Light.h"

#include "CGFlight.h"
#include "CGFapplication.h"

void Light::enable() {
    _cachedLight->enable();
    
    _enabled = true;
}

void Light::disable() {
    _cachedLight->disable();
    
    _enabled = false;
}

void Light::draw() {
    if (!_built) {
        build();
        
        _built = true;
    }
    
    if (_enabled)
        if (_marker)
            _cachedLight->draw();
}

void Light::build() {
    if (_enabled)
        enable();
    else
        disable();
}

void SpotlightLight::build() {
    float *direction = (float *) malloc(3 * sizeof(float));
    
    float *dirbase = direction;
    
    for (int i = 0; i < 3; i++) {
        (* direction) = (* _target.getFloatVector()) - (* _position.getFloatVector());
        
        direction++;
    }
    
    direction = dirbase;
    
    _cachedLight = new CGFlight(_glLightId, _position.getFloatVector(), direction);
    
    _setComponents();
    
    _cachedLight->setAngle(_angle);
    
    glLightf(_glLightId, GL_SPOT_EXPONENT, _exponent);
    
    Light::build();
}

void Light::_setComponents() {
    _cachedLight->setAmbient(color_to_float_vec(getComponent(kComponentTypeAmbient)->getColor()));
    _cachedLight->setDiffuse(color_to_float_vec(getComponent(kComponentTypeDiffuse)->getColor()));
    _cachedLight->setSpecular(color_to_float_vec(getComponent(kComponentTypeSpecular)->getColor()));
}

void OmnidirectionalLight::build() {
    _cachedLight = new CGFlight(_glLightId, _position.getFloatVector());
    
    _setComponents();
    
    Light::build();
}
