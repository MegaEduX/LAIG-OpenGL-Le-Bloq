//
//  Plane.cpp
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#include "Plane.h"

static const GLfloat _planeControlPoints[4][3] = {
    { -3.0, 0.0,  3.0 },
    {  3.0, 0.0,  3.0 },
    { -3.0, 0.0, -3.0 },
    {  3.0, 0.0, -3.0 }
};

static const GLfloat _planeNormalComponents[4][3] = {
    { 0.0, 0.0, 1.0 },
    { 0.0, 0.0, 1.0 },
    { 0.0, 0.0, 1.0 },
    { 0.0, 0.0, 1.0 }
};

static const GLfloat _planeTexturePoints[4][2] = {
    { 0.0, 0.0 },
    { 0.0, 1.0 },
    { 1.0, 0.0 },
    { 1.0, 1.0 }
};

void Plane::draw() {
    //  Partially stolen from http://stackoverflow.com/a/20825713/243506
    
    glPushMatrix();
    
    {
        //  Simpler CW/CCW fix.
        
        glRotated(180, 0, 0, 1);
        glRotated(90, 0, 1, 0);
        
        glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3.0, 2.0, 0.0, 1.0, 3.0 * 2.0, 2.0, &_planeControlPoints[0][0]);
        glMap2f(GL_MAP2_NORMAL, 0.0, 1.0, 3.0, 2.0, 0.0, 1.0, 3.0 * 2.0, 2.0, &_planeNormalComponents[0][0]);
        glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2.0, 2.0, 0.0, 1.0, 2.0 * 2.0, 2.0, &_planeTexturePoints[0][0]);
        
        glEnable(GL_MAP2_VERTEX_3);
        glEnable(GL_MAP2_NORMAL);
        glEnable(GL_MAP2_COLOR_4);
        glEnable(GL_MAP2_TEXTURE_COORD_2);
        
        glMapGrid2f(_parts, 0.0, 1.0, _parts, 0.0, 1.0);
        
        glEvalMesh2(GL_FILL, 0, _parts, 0, _parts);
        
        glDisable(GL_AUTO_NORMAL);
    }
    
    glPopMatrix();
}
