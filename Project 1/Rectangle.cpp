//
//  Rectangle.cpp
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#include "Rectangle.h"

void Rectangle::draw() {
    float texSizeS = abs((long) (_point1.x - _point2.x)) / _texCoords.x;
    float texSizeT = abs((long) (_point1.y - _point2.y)) / _texCoords.y;
    
    glPushMatrix();
    
    {
        int xSize = (int) abs((long) (_point2.x - _point1.x));
        int ySize = (int) abs((long) (_point2.y - _point1.y));
        
        glTranslated(_point1.x, _point1.y, 0);
        glScaled(xSize, ySize, 1);
        
        glPushMatrix();
        
        {
            glBegin(GL_QUADS);
            
            {
                glTexCoord2d(0, 0);
                glVertex3d(0, 0, 0);
                
                glTexCoord2d(texSizeS, 0);
                glVertex3d(1, 0, 0);
                
                glTexCoord2d(texSizeS, texSizeT);
                glVertex3d(1, 1, 0);
                
                glTexCoord2d(0, texSizeT);
                glVertex3d(0, 1, 0);
            }
            
            glEnd();
        }
        
        glPopMatrix();
    }
    
    glPopMatrix();
}