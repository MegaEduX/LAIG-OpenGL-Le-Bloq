//
//  Primitive.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 23/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__Primitive__
#define __Project_1__Primitive__

#include <stdio.h>

#include "CGFobject.h"

#include "Coordinate.h"

#include "GraphicalObject.h"

#include "GraphicalException.h"

#include "Animation.h"

#include "Texture.h"

#include "Shader.h"

#include "Global.h"

_BUILD_GRAPHICAL_EXCEPTION(InvalidDrawException, GraphicalException);

class Primitive : GraphicalObject {
    
protected:
    
    GLUquadric *_quad;
    
    Coordinate2D _texCoords;
    
public:
    
    Primitive() {
        _quad = gluNewQuadric();
    }
    
    virtual void draw() {
        
    }
    
    void setTextureCoordinates(Coordinate2D crd) {
        _texCoords = crd;
    }
    
};

#endif /* defined(__Project_1__Primitive__) */
