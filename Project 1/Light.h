//
//  Light.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 27/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__Light__
#define __Project_1__Light__

#include <iostream>

#include <vector>

#include "GraphicalObject.h"

#include "Coordinate.h"

#include "Color.h"

#include "CGFlight.h"

#include "Component.h"

static int kLightId = GL_LIGHT0;

class Light : public GraphicalObject {
    
protected:
    
    unsigned int _glLightId;
    
    bool _enabled;
    
    bool _built;
    
    bool _marker;
    
    Coordinate3D _position;
    
    std::vector<Component *> _components;
    
    //  Cached Light
    
    CGFlight *_cachedLight;
    
    void _setComponents();
    
public:
    
    Light(std::string anId, bool enabled, bool marker, Coordinate3D position) : GraphicalObject(anId) {
        _glLightId = kLightId;
        
        kLightId++;
        
        _cachedLight = nullptr;
        
        _enabled = enabled;
        _marker = marker;
        _position = position;
        
        _built = false;
    }
    
    void addComponent(Component *component) {
        _components.push_back(component);
    }
    
    void removeComponent(Component *child) {
        //	Removed for now.
    }
    
    std::vector<Component *> getComponents() {
        return _components;
    }
    
    Component* getComponent(kComponentType type) {
		for (int i = 0; i < _components.size(); i++)
            if (_components[i]->getType() == type)
                return _components[i];
        
        return nullptr;
    }
    
    CGFlight *getLight() {
        if (!_cachedLight)
            build();
        
        return _cachedLight;
    }
    
    bool getEnabled() {
        return _enabled;
    }
    
    int getEnabledLive() {
        return (getEnabled() ? 1 : 0);
    }
    
    void enable();
    void disable();
    
    void toggle() {
        if (_enabled)
            disable();
        else
            enable();
    }
    
    void draw();
    
    virtual void build();
    
};

class OmnidirectionalLight : public Light {
    
public:
    
    OmnidirectionalLight(std::string anId, bool enabled, bool marker, Coordinate3D position) : Light(anId, enabled, marker, position) {
        
    }
    
    void build();
    
};

class SpotlightLight : public Light {
    
    Coordinate3D _target;
    
    char _angle;
    
    float _exponent;
    
public:
    
    SpotlightLight(std::string anId, bool enabled, bool marker, Coordinate3D position, Coordinate3D target, float angle, float exponent) : Light(anId, enabled, marker, position) {
        _target = target;
        
        _angle = angle;
        
        _exponent = exponent;
    }
    
    void build();
    
};

#endif /* defined(__Project_1__Light__) */
