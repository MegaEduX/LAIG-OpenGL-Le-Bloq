//
//  Triangle.cpp
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#include "Triangle.h"

void Triangle::draw() {
    float p1p2 = sqrt(pow((_point2.x - _point1.x), 2) + pow((_point2.y - _point1.y), 2) + pow((_point2.z - _point1.z), 2)); //a
    float p2p3 = sqrt(pow((_point3.x - _point2.x), 2) + pow((_point3.y - _point2.y), 2) + pow((_point3.z - _point2.z), 2)); //b
    float p3p1 = sqrt(pow((_point1.x - _point3.x), 2) + pow((_point1.y - _point3.y), 2) + pow((_point1.z - _point3.z), 2)); //c
    
    float alfa = acos((pow(p2p3, 2) + pow(p3p1, 2) - pow(p1p2, 2)) / (2 * p2p3 * p3p1)); //ang entre b e c
    float beta = acos((pow(p1p2, 2) + pow(p3p1, 2) - pow(p2p3, 2)) / (2 * p1p2 * p3p1)); //ang entre a e c
    float sigma = acos((pow(p2p3, 2) + pow(p1p2, 2) - pow(p3p1, 2)) / (2 * p1p2 * p2p3)); //ang entre a e b
    
    //calc normais
    
    float Nx = (_point2.y - _point3.y) * (_point3.z - _point1.z) - (_point2.z - _point3.z) * (_point3.y - _point1.y);         //      UyVz - UzVy
    float Ny = (_point2.z - _point3.z) * (_point3.x - _point1.x) - (_point2.x - _point3.x) * (_point3.z - _point1.z);         //      UzVx - UxVz
    float Nz = (_point2.x - _point3.x) * (_point3.y - _point1.y) - (_point2.y - _point3.y) * (_point3.x - _point1.x);         //      UxVy - UyVx
    
    float lenght = sqrt(Nx*Nx + Ny*Ny + Nz+Nz);
    
    //normalizaÁ„o das normais (sim isto soa estranho eu sei)
    
    Nx = Nx / lenght;
    Ny = Ny / lenght;
    Nz = Nz / lenght;
    
    if (p3p1 > p2p3 && p3p1 > p1p2) {
        glPushMatrix();
        
        {
            glBegin(GL_TRIANGLES);
            
            {
                if (Globals::getInstance().getDrawingSettings()->getSmooth())
                    
                {
                    
                    glNormal3f(Nx, Ny, Nz);
                    
                    glTexCoord2f(0, 0);
                    glVertex3f(_point1.x, _point1.y, _point1.z); // ponto do ang alfa
                    
                    glTexCoord2f(p3p1, 0);
                    glVertex3f(_point2.x, _point2.y, _point2.z); // ponto do ang beta
                    
                    glTexCoord2f(p3p1 - p1p2 * cos(beta), p1p2 * sin(beta));
                    glVertex3f(_point3.x, _point3.y, _point3.z); // ponto do ang sigma
                    
                } else {
                    
                    glNormal3f(Nx, Ny, Nz);
                    glTexCoord2f(0, 0);
                    glVertex3f(_point1.x, _point1.y, _point1.z); // ponto do ang alfa
                    
                    glNormal3f(Nx, Ny, Nz);
                    glTexCoord2f(p3p1, 0);
                    glVertex3f(_point2.x, _point2.y, _point2.z); // ponto do ang beta
                    
                    glNormal3f(Nx, Ny, Nz);
                    glTexCoord2f(p3p1 - p1p2 * cos(beta), p1p2 * sin(beta));
                    glVertex3f(_point3.x, _point3.y, _point3.z); // ponto do ang sigma
                    
                }
                
                glEnd();
            }
            
            glPopMatrix();
        }
        
        if (p1p2 > p2p3 && p1p2 > p3p1) {
            glPushMatrix();
            
            {
                glBegin(GL_TRIANGLES);
                
                {
                    if(!(Globals::getInstance().getDrawingSettings()->getSmooth())) {
                        
                        glNormal3f(Nx, Ny, Nz);
                        
                        glTexCoord2f(p1p2 - p2p3 * cos(sigma), p2p3 * sin(sigma));
                        glVertex3f(_point1.x, _point1.y, _point1.z); // ponto do ang alfa
                        
                        glTexCoord2f(0, 0);
                        glVertex3f(_point2.x, _point2.y, _point2.z); // ponto do ang beta
                        
                        glTexCoord2f(p2p3, 0);
                        glVertex3f(_point3.x, _point3.y, _point3.z); // ponto do ang sigma
                        
                    } else {
                        
                        glNormal3f(Nx, Ny, Nz);
                        glTexCoord2f(p1p2 - p2p3 * cos(sigma), p2p3 * sin(sigma));
                        glVertex3f(_point1.x, _point1.y, _point1.z); // ponto do ang alfa
                        
                        glNormal3f(Nx, Ny, Nz);
                        glTexCoord2f(0, 0);
                        glVertex3f(_point2.x, _point2.y, _point2.z); // ponto do ang beta
                        
                        glNormal3f(Nx, Ny, Nz);
                        glTexCoord2f(p2p3, 0);
                        glVertex3f(_point3.x, _point3.y, _point3.z); // ponto do ang sigma
                        
                    }
                    
                    glEnd();
                }
                
                glPopMatrix();
            }
            
            if(p2p3 > p1p2 && p2p3 > p3p1) {
                glPushMatrix();
                
                {
                    glBegin(GL_TRIANGLES);
                    
                    {
                        
                        if (!(Globals::getInstance().getDrawingSettings()->getSmooth())) {
                            glNormal3f(Nx, Ny, Nz);
                            
                            glTexCoord2f(p2p3, 0);
                            glVertex3f(_point1.x, _point1.y, _point1.z); // ponto do ang alfa
                            
                            glTexCoord2f(p2p3 - p3p1 * cos(alfa), p3p1 * sin(alfa));
                            glVertex3f(_point2.x, _point2.y, _point2.z); // ponto do ang beta
                            
                            glTexCoord2f(0 , 0);
                            glVertex3f(_point3.x, _point3.y, _point3.z); // ponto do ang sigma
                            
                        } else {
                            
                            glNormal3f(Nx, Ny, Nz);
                            glTexCoord2f(p2p3, 0);
                            glVertex3f(_point1.x, _point1.y, _point1.z); // ponto do ang alfa
                            
                            glNormal3f(Nx, Ny, Nz);
                            glTexCoord2f(p2p3 - p3p1 * cos(alfa), p3p1 * sin(alfa));
                            glVertex3f(_point2.x, _point2.y, _point2.z); // ponto do ang beta
                            
                            glNormal3f(Nx, Ny, Nz);
                            glTexCoord2f(0 , 0);
                            glVertex3f(_point3.x, _point3.y, _point3.z); // ponto do ang sigma
                            
                        }
                    }
                    
                    glEnd();
                }
                
                glPopMatrix();
            }
        }
    }
}
