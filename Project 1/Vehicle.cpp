//
//  Vehicle.cpp
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#include "Vehicle.h"

#include "Patch.h"
#include "Torus.h"
#include "Rectangle.h"

static const GLfloat _vehiclePoints[16][3] = {
    { -0.5,  0, -0.5  },
    { -0.5,  0, -0.25 },
    { -0.5,  0, 0.25  },
    { -0.5,  0, 0.5   },
    { -0.25, 0, -0.5  },
    { -0.25, 1, -0.25 },
    { -0.25, 1, 0.25  },
    { -0.25, 0, 0.5   },
    { 0.25,  0, -0.5  },
    { 0.25,  1, -0.25 },
    { 0.25,  1, 0.25  },
    { 0.25,  0, 0.5   },
    { 0.5,   0, -0.5  },
    { 0.5,   0, -0.25 },
    { 0.5,   0, 0.25  },
    { 0.5,   0, 0.5   }
};

void Vehicle::draw() {
    float skyblue[4] = {0.392157, 0.584314, 0.929412};
    
    float ambA[3] = {0.2, 0.2, 0.2};
    float difA[3] = {0.6, 0.6, 0.6};
    float specA[3] = {0.2, 0.2, 0.2};
    
    float shininessA = 10.f;
    
    CGFappearance* tireAppearance;
    tireAppearance = new CGFappearance(ambA,difA,specA,shininessA);
    tireAppearance->setTexture(Globals::getInstance().getBasePath() + "Textures/tire.png");
    
    CGFappearance* mericaAppearance;
    mericaAppearance = new CGFappearance(ambA,difA,specA,shininessA);
    mericaAppearance->setTexture(Globals::getInstance().getBasePath() + "Textures/merica.png");
    
    CGFappearance* engineAppearance;
    engineAppearance = new CGFappearance(ambA,difA,specA,shininessA);
    engineAppearance->setTexture(Globals::getInstance().getBasePath() + "Textures/engine.png");
    
    CGFappearance* baseAppearance;
    baseAppearance = new CGFappearance(skyblue);
    
    glPushMatrix();
    
    {
        glPushMatrix();
        
        {
            Patch *patch = new Patch(3, Coordinate2D(10,10) ,kPatchComputeFill);
            
            for (int i = 0; i < 16; i++)
                patch->addControlPoint(Coordinate3D(_vehiclePoints[i][0], _vehiclePoints[i][1], _vehiclePoints[i][2]));
            
            mericaAppearance->apply();
            
            patch -> draw();
        }
        
        glPopMatrix();
        
        //  Roda 1
        
        glPushMatrix();
        
        {
            
            Torus *tor1 = new Torus(0.1,0.2,10,10);
            
            glTranslatef(0.2,0,0);
            
            glRotatef(90,0,1,0);
            
            tireAppearance->apply();
            
            tor1 -> draw();
        }
        
        glPopMatrix();
        
        //  Roda 2
        
        glPushMatrix();
        
        {
            Torus *tor2 = new Torus(0.1,0.2,10,10);
            
            glTranslatef(-0.2,0,0);
            
            glRotatef(90,0,1,0);
            
            tireAppearance->apply();
            
            tor2 -> draw();
        }
        
        glPopMatrix();
        
        //  Base
        
        glPushMatrix();
        
        {
            Rectangle *rekt = new Rectangle(Coordinate2D(-0.5,-0.5), Coordinate2D(0.5,0.5));
            
            glRotatef(90,1,0,0);
            
            baseAppearance->apply();
            
            rekt -> draw();
        }
        
        glPopMatrix();
        
        //  Wing 1
        
        glPushMatrix();
        
        {
            Torus *wing1 = new Torus(0.1,0.2,10,10);
            
            glTranslatef(0.45,0.25,0);
            
            glRotatef(90,0,0,1);
            
            glScalef(0.4,0.4,2);
            
            engineAppearance->apply();
            
            wing1 -> draw();
        }
        
        glPopMatrix();
        
        //  Wing 2
        
        glPushMatrix();
        
        {
            Torus *wing2 = new Torus(0.1,0.2,10,10);
            
            glTranslatef(-0.45,0.25,0);
            
            glRotatef(90,0,0,1);
            
            glScalef(0.4,0.4,2);
            
            engineAppearance->apply();
            
            wing2 -> draw();
        }
        
        glPopMatrix();
    }
    
    glPopMatrix();
}
