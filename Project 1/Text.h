//
//  Text.h
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#ifndef __Project_1__Text__
#define __Project_1__Text__

#include <iostream>

#include "Primitive.h"

class Text : public Primitive {
    
    std::string _text;
    
    Coordinate3D _pos;
    
    kColorRGB _col;
    
    void *_glutFont;
    
public:
    
    Text(std::string text, Coordinate3D position, kColorRGB color, void *glutFont) {
        _text = text;
        
        _pos = position;
        _col = color;
        
        _glutFont = glutFont;
    }
    
    void draw();
    
};

#endif /* defined(__Project_1__Text__) */
