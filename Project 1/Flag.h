//
//  Flag.h
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#ifndef __Project_1__Flag__
#define __Project_1__Flag__

#include <iostream>

#include "Primitive.h"

#include "Plane.h"

class Flag : public Primitive {
    
    Texture *_texture;
    
    Shader *_shader;
    
    Plane *_plane;
    
    unsigned int _appWait;
    
public:
    
    Flag(Texture *tex) : Primitive() {
        _texture = tex;
        
        _plane = new Plane(25);
        
        _shader = nullptr;
        
        _appWait = 15;
    }
    
    void draw();
    
};

#endif /* defined(__Project_1__Flag__) */
