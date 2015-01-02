//
//  Texture.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 26/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__Texture__
#define __Project_1__Texture__

#include <fstream>
#include <iostream>

#include "CGFapplication.h"

#include "CGFtexture.h"

#include "GraphicalException.h"

#define kWorkaroundInteger 10

_BUILD_GRAPHICAL_EXCEPTION(TextureCreationException, GraphicalException);

typedef struct kTexLength {
    float s;
    float t;
} kTexLength;

/*
 *  I am not doing anything with texLength at this time...
 */

class Texture {
    
    int _workaroundCounter;
    
    std::string _id;
    
    std::string _filePath;
    
    kTexLength _texLength;
    
    CGFtexture *_cachedTexture;
    
    void build() {
        std::ifstream f(_filePath);  // New enough C++ library will accept just name
        
        if (!f.is_open())
            throw new TextureCreationException("Texture file couldn't be open for reading! Maybe it doesn't exist at the specified path?");
        
        if (_cachedTexture != nullptr)
            delete _cachedTexture;
        
        try {
            _cachedTexture = new CGFtexture(_filePath);
        } catch (GLexception& ex) {
            std::cout << "Failure to load texture " << _filePath << std::endl;
            
            throw ex;
        }
        
    }
    
public:
    
    Texture(std::string anId, std::string filePath, kTexLength texLength) {
        _id = anId;
        
        _filePath = filePath;
        
        _texLength = texLength;
        
        _cachedTexture = nullptr;
        
        _workaroundCounter = 0;
    }
    
    CGFtexture *getTexture() {
        if (_workaroundCounter < kWorkaroundInteger) {
            
            build();
            
            _workaroundCounter++;
            
        } else if (!_cachedTexture)
            build();
        
        return _cachedTexture;
    }
    
    std::string getId() {
        return _id;
    }
    
    kTexLength getTexLength() {
        return _texLength;
    }
    
    void setTexLength(kTexLength tl) {
        _texLength = tl;
        
        build();
    }
    
    std::string getFilePath() {
        return _filePath;
    }
    
    void setFilePath(std::string fp) {
        _filePath = fp;
        
        build();
    }
    
    void apply() {
        if (_workaroundCounter < kWorkaroundInteger) {
            
            build();
            
            _workaroundCounter++;
            
        } else if (!_cachedTexture)
            build();
        
        _cachedTexture->apply();
    }
    
};

#endif /* defined(__Project_1__Texture__) */
