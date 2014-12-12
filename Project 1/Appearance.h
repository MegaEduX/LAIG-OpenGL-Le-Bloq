//
//  Appearance.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 26/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__Appearance__
#define __Project_1__Appearance__

#include <iostream>
#include <vector>

#include "Color.h"
#include "Texture.h"
#include "GraphicalObject.h"
#include "Component.h"
#include "GraphicalException.h"
#include "Coordinate.h"

#include "CGFappearance.h"

_BUILD_GRAPHICAL_EXCEPTION(AppearanceBuilderException, GraphicalException);

class Appearance : public GraphicalObject {
    
    float _shininess;
    
    Texture *_texture;
    
    std::string _textureRef;
    
    std::vector<Component *> _components;
    
    CGFappearance *_cachedAppearance;
    
    void build();
    
public:
    
    Appearance(float shininess) : GraphicalObject() {
        _shininess = shininess;
        
        _cachedAppearance = nullptr;
    }
    
    Appearance(std::string id, float shininess) : GraphicalObject(id) {
        _shininess = shininess;

		_texture = nullptr;
		
		_cachedAppearance = nullptr;
    }
    
    Appearance(std::string id, float shininess, Texture *texture) : GraphicalObject(id) {
		_shininess = shininess;

        _texture = texture;

		_cachedAppearance = nullptr;
    }
    
    float getShininess() {
        return _shininess;
    }
    
    Texture* getTexture() {
		if (_texture != nullptr)
			return _texture;

		return nullptr;
    }
    
    void setTexture(Texture *tex) {
        _texture = tex;
        
        _cachedAppearance = nullptr;
    }
    
    void setTextureWrap(Coordinate2D wrap) {
        if (_cachedAppearance != nullptr)
            _cachedAppearance->setTextureWrap(wrap.x, wrap.y);
    }
    
    std::string getTextureRef() {
        return _textureRef;
    }
    
    void setTextureRef(std::string textureRef) {
        _textureRef = textureRef;
    }
    
    std::vector<Component *> getComponents() {
        return _components;
    }
    
    Component* getComponent(kComponentType ct) {
		for (int i = 0; i < _components.size(); i++)
            if (_components[i]->getType() == ct)
                return _components[i];
        
        return nullptr;
    }
    
    void addComponent(Component *component) {
        _components.push_back(component);
        
        _cachedAppearance = nullptr;
    }
    
    void removeComponent(Component *child) {
        //	Removed for now.
    }
    
    CGFappearance* getAppearance() {
        /*if (!_cachedAppearance)*/
            build();
        
        return _cachedAppearance;
    }
    
    void apply() {
        CGFappearance *appr = getAppearance();
        
        if (appr == nullptr)
            throw new AppearanceBuilderException("Couldn't get CGFappearance object.");
            
        appr->apply();
    }
};

#endif /* defined(__Project_1__Appearance__) */
