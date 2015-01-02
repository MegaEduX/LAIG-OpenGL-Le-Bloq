//
//  Text.cpp
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#include "Text.h"

void Text::draw() {
    glPushMatrix();
    
    {
        glColor3f(_col.r, _col.g, _col.b);
        glRasterPos3f(_pos.x, _pos.y, _pos.z);
        
        for (int i = 0; i < _text.length(); i++)
            glutBitmapCharacter(_glutFont, _text[i]);
        
        glColor3f(1.0f, 1.0f, 1.0f);
    }
    
    glPopMatrix();
}
