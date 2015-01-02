//
//  UnitCube.cpp
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#include "UnitCube.h"

void UnitCube::draw() {
    glPushMatrix();
    
    {
        glTranslatef(0,0,1);
        glNormal3f(0,0,1);
        glBegin(GL_QUADS);
        
        glTexCoord2f(0, 0);
        glVertex2d(0, 0);
        
        glTexCoord2f(_texCoords.x, 0);
        glVertex2d(1, 0);
        
        glTexCoord2f(_texCoords.x, _texCoords.y);
        glVertex2d(1, 1);
        
        glTexCoord2f(0, _texCoords.y);
        glVertex2d(0, 1);
        glEnd();
    }
    
    glPopMatrix();
    
    glPushMatrix();
    
    {
        glRotatef(180,1,0,0);
        glTranslatef(0,-1,0);
        glNormal3f(0,0,1);
        glBegin(GL_QUADS);
        
        glTexCoord2f(0, 0);
        glVertex2d(0, 0);
        
        glTexCoord2f(_texCoords.x, 0);
        glVertex2d(1, 0);
        
        glTexCoord2f(_texCoords.x, _texCoords.y);
        glVertex2d(1, 1);
        
        glTexCoord2f(0, _texCoords.y);
        glVertex2d(0, 1);
        glEnd();
    }
    
    glPopMatrix();
    
    glPushMatrix();
    
    {
        glRotatef(90,1,0,0);
        glNormal3f(0,0,1);
        glBegin(GL_QUADS);
        
        glTexCoord2f(0, 0);
        glVertex2d(0, 0);
        
        glTexCoord2f(_texCoords.x, 0);
        glVertex2d(1, 0);
        
        glTexCoord2f(_texCoords.x, _texCoords.y);
        glVertex2d(1, 1);
        
        glTexCoord2f(0, _texCoords.y);
        glVertex2d(0, 1);
        glEnd();
    }
    
    glPopMatrix();
    
    glPushMatrix();
    
    {
        glRotatef(270,0,1,0);
        glNormal3f(0,0,1);
        glBegin(GL_QUADS);
        
        glTexCoord2f(0, 0);
        glVertex2d(0, 0);
        
        glTexCoord2f(_texCoords.x, 0);
        glVertex2d(1, 0);
        
        glTexCoord2f(_texCoords.x, _texCoords.y);
        glVertex2d(1, 1);
        
        glTexCoord2f(0, _texCoords.y);
        glVertex2d(0, 1);
        glEnd();
    }
    
    glPopMatrix();
    
    glPushMatrix();
    
    {
        glTranslatef(0,1,1);
        glRotatef(270,1,0,0);
        glNormal3f(0,0,1);
        glBegin(GL_QUADS);
        
        glTexCoord2f(0, 0);
        glVertex2d(0, 0);
        
        glTexCoord2f(_texCoords.x, 0);
        glVertex2d(1, 0);
        
        glTexCoord2f(_texCoords.x, _texCoords.y);
        glVertex2d(1, 1);
        
        glTexCoord2f(0, _texCoords.y);
        glVertex2d(0, 1);
        glEnd();
    }
    
    glPopMatrix();
    
    glPushMatrix();
    
    {
        glTranslatef(1,0,1);
        glRotatef(90,0,1,0);
        glNormal3f(0,0,1);
        glBegin(GL_QUADS);
        
        glTexCoord2f(0, 0);
        glVertex2d(0, 0);
        
        glTexCoord2f(_texCoords.x, 0);
        glVertex2d(1, 0);
        
        glTexCoord2f(_texCoords.x, _texCoords.y);
        glVertex2d(1, 1);
        
        glTexCoord2f(0, _texCoords.y);
        glVertex2d(0, 1);
        glEnd();
    }
    
    glPopMatrix();
}
