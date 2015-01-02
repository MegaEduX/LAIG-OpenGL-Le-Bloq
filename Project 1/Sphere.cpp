//
//  Sphere.cpp
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#include "Sphere.h"

void Sphere::draw() {
    gluQuadricTexture(_quad, (GLboolean) true);
    
    gluQuadricNormals(_quad, (Globals::getInstance().getDrawingSettings()->getSmooth() ? GLU_SMOOTH : GLU_FLAT));
    
    gluQuadricOrientation(_quad, GLU_OUTSIDE);
    
    gluSphere(_quad, _radius, _slices, _stacks);
}
