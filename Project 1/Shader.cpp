//
//  Shader.cpp
//  Project 1
//
//  Created by Eduardo Almeida on 12/11/14.
//  Copyright (c) 2014 Eduardo Almeida. All rights reserved.
//

#ifdef _WIN32

#include <GL/glew.h>

#endif

#ifndef FLT_MAX

#define FLT_MAX 4096

#endif

#include "Shader.h"

#include "GraphicalMath.h"

Shader::Shader(CGFtexture *texture, std::string vertexShaderPath, std::string fragmentShaderPath) {
    init(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    
    CGFshader::bind();
    
    _elapsed = 0.0;
    
    _texture = texture;
    
    _imageLoc = glGetUniformLocation(id(), "baseImage");
    
    _timeLoc = glGetUniformLocation(id(), "time");
    
    _windLoc = glGetUniformLocation(id(), "wind");
    
    glUniform1i(_imageLoc, 0);
}

void Shader::bind(float delta, float wind) {
    CGFshader::bind();
    
    _elapsed += delta;
    
    if (_elapsed > FLT_MAX - 1)
        _elapsed = 0;
    
    glUniform1f(_timeLoc, _elapsed);
    glUniform1f(_windLoc, wind);
    
    glActiveTexture(GL_TEXTURE0);
    
    _texture->apply();
    
    glActiveTexture(GL_TEXTURE0);
}

Shader::~Shader() {
    //  delete _texture;
}
