//
//  Shader.h
//  Project 1
//
//  Created by Eduardo Almeida on 12/11/14.
//  Copyright (c) 2014 Eduardo Almeida. All rights reserved.
//

#ifndef __Project_1__Shader__
#define __Project_1__Shader__

#include <iostream>

#include "CGFapplication.h"
#include "CGFshader.h"

class Shader : public CGFshader {
    
    float _elapsed;
    
    CGFtexture *_texture;
    
    GLint _imageLoc;
    GLint _timeLoc;
    GLint _windLoc;
    
public:
    
    Shader(CGFtexture *texture, std::string vertexShaderPath, std::string fragmentShaderPath);
    
    ~Shader();
    
    void bind(float delta, float wind);
    
    void setScale(float s) {
        //  Uh.
    }
    
};

#endif /* defined(__Project_1__Shader__) */
