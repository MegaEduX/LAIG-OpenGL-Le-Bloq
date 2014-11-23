//
//  Appearance.cpp
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 26/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#include "Appearance.h"

#include "CGFapplication.h"

void Appearance::build() {
    if (!getComponent(kComponentTypeAmbient) || !getComponent(kComponentTypeDiffuse) || !getComponent(kComponentTypeSpecular))
        throw new AppearanceBuilderException("Color component missing! All of ambient, diffuse and specular are required to build an appearance object.");
    
    _cachedAppearance = new CGFappearance(color_to_float_vec(getComponent(kComponentTypeAmbient)->getColor()),
                                          color_to_float_vec(getComponent(kComponentTypeDiffuse)->getColor()),
                                          color_to_float_vec(getComponent(kComponentTypeSpecular)->getColor()),
                                          _shininess);
    
    if (_texture) {
        _cachedAppearance->setTexture(_texture->getTexture());
        
        //  _cachedAppearance->setTextureWrap(_texture->getTexLength().s, _texture->getTexLength().t);
        
        //  I gotta do something with the tex length still.
        
        _cachedAppearance->setTextureWrap(GL_REPEAT, GL_REPEAT);
    }
}
