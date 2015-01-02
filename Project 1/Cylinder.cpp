//
//  Cylinder.cpp
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#include "Cylinder.h"

void Cylinder::draw() {
    glPushMatrix();
    
    {
        gluQuadricTexture(_quad, (GLboolean) true);
        
        gluQuadricNormals(_quad, (Globals::getInstance().getDrawingSettings()->getSmooth() ? GLU_SMOOTH : GLU_FLAT));
        
        gluQuadricOrientation(_quad, GLU_OUTSIDE);
        
        //  Base Disk
        
        gluDisk(_quad, 0, _base, _slices, _stacks);
        
        //  Actual Cylinder
        
        gluCylinder(_quad, _base, _top, _height, _slices, _stacks);
        
        //  Top Disk
        
        glTranslatef(0, 0, (float) _height);    //  Why am I doing this on the z coordinate? I have no idea!
        
        gluDisk(_quad, 0, _base, _slices, _stacks);
    }
    
    glPopMatrix();
}
