//
//  Flag.cpp
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#include "Flag.h"

void Flag::draw() {
    if (_appWait) {
        _appWait--;
        
        return;
    }
    
    glPushMatrix();
    
    {
        
        if (_shader == nullptr)
            _shader = new Shader(_texture->getTexture(),
                                 Globals::getInstance().getShadingSettings()->getVertPath(),
                                 Globals::getInstance().getShadingSettings()->getFragPath());
        
        _shader->bind(0.05, Globals::getInstance().getShadingSettings()->getWind());
        
        glActiveTexture(GL_TEXTURE0);
        
        _texture->apply();
        
        _plane->draw();
        
        _shader->unbind();
    }
    
    glPopMatrix();
}