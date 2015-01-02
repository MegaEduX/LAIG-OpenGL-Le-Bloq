//
//  Table.cpp
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#include "Table.h"

void Table::draw() {
    glPushMatrix();
    
    {
        glTranslatef(0.1,0,0.1);
        glScalef(0.3,3.5,0.3);
        
        cube->draw();
    }
    
    glPopMatrix();
    
    glPushMatrix();
    
    {
        glTranslatef(0.1,0,2.6);
        glScalef(0.3,3.5,0.3);
        
        cube->draw();
    }
    
    glPopMatrix();
    
    glPushMatrix();
    
    {
        glTranslatef(4.6,0,0.1);
        glScalef(0.3,3.5,0.3);
        
        cube->draw();
    }
    
    glPopMatrix();
    
    glPushMatrix();
    
    {
        glTranslatef(4.6,0,2.6);
        glScalef(0.3,3.5,0.3);
        
        cube->draw();
    }
    
    glPopMatrix();
    
    glPushMatrix();
    
    {
        glTranslatef(0,3.5,0);
        glScalef(5,0.3,3);
        
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        cube->draw();
    }
    
    glPopMatrix();
}
