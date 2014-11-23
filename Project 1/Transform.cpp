//
//  Transform.cpp
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 23/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#include "Transform.h"

#include "GraphicalMath.h"

#include "CGFobject.h"

void Translate::apply() {
    glTranslatef(_to.x, _to.y, _to.z);
}

void Rotate::apply() {
    glRotatef(_angle, _axis == 'x' ? 1 : 0, _axis == 'y' ? 1 : 0, _axis == 'z' ? 1 : 0);
}

void Scale::apply() {
    glScalef(_scaleAxis.x, _scaleAxis.y, _scaleAxis.z);
}
