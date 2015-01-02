//
//  Torus.cpp
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#include "Torus.h"

void Torus::draw() {
    glRotated(90, 1, 0, 0);
    
    unsigned int i, j;
    double phi;
    double theta;
    
    double ***vertex = (double ***) malloc((_slices + 1) * sizeof(double **));
    
    for (unsigned int i = 0; i < _slices + 1; i++) {
        double **loops = (double **) malloc((_loops + 1) * sizeof(double *));
        
        for (unsigned int j = 0; j < _loops + 1; j++) {
            double *xyz = (double *) malloc(3 * sizeof(double));
            
            loops[j] = xyz;
        }
        
        vertex[i] = loops;
    }
    
    double ***textureVertex = (double ***) malloc((_slices + 1) * sizeof(double **));
    
    for (unsigned int i = 0; i < _slices + 1; i++) {
        double **loops = (double **) malloc((_loops + 1) * sizeof(double *));
        
        for (unsigned int j = 0; j < _loops + 1; j++) {
            double *xyz = (double *) malloc(3 * sizeof(double));
            
            loops[j] = xyz;
        }
        
        textureVertex[i] = loops;
    }
    
    double ***normalVertex = (double ***) malloc((_slices + 1) * sizeof(double **));
    
    for (unsigned int i = 0; i < _slices + 1; i++) {
        double **loops = (double **) malloc((_loops + 1) * sizeof(double *));
        
        for (unsigned int j = 0; j < _loops + 1; j++) {
            double *xyz = (double *) malloc(3 * sizeof(double));
            
            loops[j] = xyz;
        }
        
        normalVertex[i] = loops;
    }
    
    double *p1,*p2,*p3,*p4;
    double *v1,*v2,*v3,*v4;
    double *n1,*n2,*n3,*n4;
    
    double R = _outer + 0.5 * _inner; //distancia do centro do torus ao centro do tubo <-- needed cause maths
    
    //limites senao da asneira pois o vertex tem de ter espaÁos finitos
    
    if (_slices > 50)
        _slices = 50;  //slices e o numero de pontos de cada loop
    
    if (_loops > 50)
        _loops = 50;  //numero de circunferencias a desenhar
    
    //Vertices serao armazenados aqui para uso a seguir
    
    for (i = 0; i <= _slices; i++) {
        phi = 2.0 * M_PI * (double)i / (double)_slices; //o angulo vai de 0 a 360
        
        for (j = 0; j <= _loops; j++) {
            theta = 2.0 * M_PI *  (double)j / (double)_loops; //o angulo vai de 0 a 360
            vertex[i][j][0] = (double) (R + _inner*cos(theta))*cos(phi) ;//x
            vertex[i][j][1] = (double) _inner * sin(theta);//y
            vertex[i][j][2] = (double) (R + _inner*cos(theta))*sin(phi);//z
            
            textureVertex[i][j][1] = (double) ((acos(vertex[i][j][1] / R) / (/*2 **/0.5* M_PI))) ; //texture coord u
            textureVertex[i][j][0] = (double) ((acos(vertex[i][j][0] / (R + _inner*cos(theta))) / (/*2 **/ 0.5*M_PI))) ; //texture coord v
            
            double tx = -sin(theta);
            double ty = 0;
            double tz = cos(theta);
            
            double sx = cos(theta) * (-sin(phi));
            double sy = cos(phi);
            double sz = sin(theta) * (-sin(phi));
            
            double nx = ty*sz - tz*sy;
            double ny = tz*sx - tx*sz;
            double nz = tx*sy - ty*sx;
            
            double length = sqrt(nx*nx + ny*ny + nz*nz);
            nx /= length;
            ny /= length;
            nz /= length;
            
            normalVertex[i][j][0] = nx;
            normalVertex[i][j][1] = ny;
            normalVertex[i][j][2] = nz;
            
        }
    }
    
    if (Globals::getInstance().getDrawingSettings()->getSmooth()) {
        for (i = 0; i < _slices; i++){
            for (j = 0; j < _loops; j++) {
                if (j <= _loops) {
                    p1 = vertex[i][j];
                    p2 = vertex[i][j+1];
                    p3 = vertex[i+1][j+1];
                    p4 = vertex[i+1][j];
                    
                    v1 = textureVertex[i][j];
                    v2 = textureVertex[i][j+1];
                    v3 = textureVertex[i+1][j+1];
                    v4 = textureVertex[i+1][j];
                    
                    n1 = normalVertex[i][j];
                    n2 = normalVertex[i][j+1];
                    n3 = normalVertex[i+1][j+1];
                    n4 = normalVertex[i+1][j];
                    
                    glBegin(GL_QUADS);
                    
                    {
                        glNormal3dv(n1); glTexCoord2dv(v1); glVertex3dv(p1);
                        glNormal3dv(n2); glTexCoord2dv(v2); glVertex3dv(p2);
                        glNormal3dv(n3); glTexCoord2dv(v3); glVertex3dv(p3);
                        glNormal3dv(n4); glTexCoord2dv(v4); glVertex3dv(p4);
                    }
                    
                    glEnd();
                }
            }
        }
    } else {
        for (i = 0;i < _slices;i++) {
            for (j = 0;j < _loops; j++) {
                if (j <= _loops) {
                    p1 = vertex[i][j];
                    p2 = vertex[i][j+1];
                    p3 = vertex[i+1][j+1];
                    p4 = vertex[i+1][j];
                    
                    v1 = textureVertex[i][j];
                    v2 = textureVertex[i][j+1];
                    v3 = textureVertex[i+1][j+1];
                    v4 = textureVertex[i+1][j];
                    
                    glBegin(GL_QUADS);
                    
                    {
                        double Nx = (normalVertex[i][j+1][1] - normalVertex[i+1][j+1][1])*(normalVertex[i+1][j+1][2] - normalVertex[i][j][2]) - (normalVertex[i][j+1][2] - normalVertex[i+1][j+1][2])*(normalVertex[i+1][j+1][1] - normalVertex[i][j][1]);         //      UyVz - UzVy
                        double Ny = (normalVertex[i][j+1][2] - normalVertex[i+1][j+1][2])*(normalVertex[i+1][j+1][0] - normalVertex[i][j][0]) - (normalVertex[i][j+1][0] - normalVertex[i+1][j+1][0])*(normalVertex[i+1][j+1][2] - normalVertex[i][j][2]);         //      UzVx - UxVz
                        double Nz = (normalVertex[i][j+1][0] - normalVertex[i+1][j+1][0])*(normalVertex[i+1][j+1][1] - normalVertex[i][j][1]) - (normalVertex[i][j+1][1] - normalVertex[i+1][j+1][1])*(normalVertex[i+1][j+1][0] - normalVertex[i][j][0]);         //      UxVy - UyVx
                        double lenght = sqrt(Nx*Nx + Ny*Ny + Nz+Nz);
                        Nx = Nx / lenght;
                        Ny = Ny / lenght;
                        Nz = Nz / lenght;
                        
                        glNormal3d(Nx, Ny, Nz);
                        
                        glTexCoord2dv(v1); glVertex3dv(p1);
                        glTexCoord2dv(v2); glVertex3dv(p2);
                        glTexCoord2dv(v3); glVertex3dv(p3);
                        glTexCoord2dv(v4); glVertex3dv(p4);
                    }
                    
                    glEnd();
                }
            }
        }
    }
    
    for (unsigned int i = 0; i < _slices + 1; i++) {
        for (unsigned int j = 0; j < _loops + 1; j++)
            free(vertex[i][j]);
        
        free(vertex[i]);
    }
    
    free(vertex);
    
    for (unsigned int i = 0; i < _slices + 1; i++) {
        for (unsigned int j = 0; j < _loops + 1; j++)
            free(textureVertex[i][j]);
        
        free(textureVertex[i]);
    }
    
    free(textureVertex);
    
    for (unsigned int i = 0; i < _slices + 1; i++) {
        for (unsigned int j = 0; j < _loops + 1; j++)
            free(normalVertex[i][j]);
        
        free(normalVertex[i]);
    }
    
    free(normalVertex);
}
