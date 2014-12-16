//
//  Primitive.cpp
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 23/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifdef _WIN32

#include <GL/glew.h>
#include <GL/glut.h>

#else

#include <GLUT/GLUT.h>

#endif

#include <vector>

#include "Primitive.h"

#include "GraphicalMath.h"

#include "Global.h"

#include "LeBloq.h"

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

void Sphere::draw() {
    gluQuadricTexture(_quad, (GLboolean) true);
    
    gluQuadricNormals(_quad, (Globals::getInstance().getDrawingSettings()->getSmooth() ? GLU_SMOOTH : GLU_FLAT));
    
    gluQuadricOrientation(_quad, GLU_OUTSIDE);
    
    gluSphere(_quad, _radius, _slices, _stacks);
}

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
    
    for(i = 0; i <= _slices; i++) {
        phi = 2.0 * M_PI * (double)i / (double)_slices; //o angulo vai de 0 a 360
        
        for(j = 0; j <= _loops; j++) {
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

void Patch::draw() {
    glPushMatrix();
    
    {
        kCullingOrder co = Globals::getInstance().getCullingSettings()->getCullingOrder();
        kCullingFace cf = Globals::getInstance().getCullingSettings()->getCullingFace();
        
        Globals::getInstance().setCullingSettings(new CullingSettings(cf, kCullingOrderClockWise));
        
        glEnable(GL_AUTO_NORMAL);
        
        float *points = Coordinate3D::vectorToFloatVector(_controlPoints);
        
        glMap2f(GL_MAP2_VERTEX_3, 0.0,
                1.0, 3, _order + 1, 0.0,
                1.0, 3 * (_order + 1), _order + 1,
                points);
        
        std::vector<Coordinate2D> tc;
        
        switch (_order) {
                
            case 1:
                
                tc.push_back(Coordinate2D(0.0, 1.0));
                tc.push_back(Coordinate2D(1.0, 1.0));
                
                tc.push_back(Coordinate2D(0.0, 0.0));
                tc.push_back(Coordinate2D(1.0, 0.0));
                
                break;
                
            case 2:
                
                tc.push_back(Coordinate2D(0.0, 1.0));
                tc.push_back(Coordinate2D(0.5, 1.0));
                tc.push_back(Coordinate2D(1.0, 1.0));
                
                tc.push_back(Coordinate2D(0.0, 0.5));
                tc.push_back(Coordinate2D(0.5, 0.5));
                tc.push_back(Coordinate2D(1.0, 0.5));
                
                tc.push_back(Coordinate2D(0.0, 0.0));
                tc.push_back(Coordinate2D(0.5, 0.0));
                tc.push_back(Coordinate2D(1.0, 0.0));
                
                break;
                
            case 3:
                
                tc.push_back(Coordinate2D(0.0,          1.0));
                tc.push_back(Coordinate2D(1.0 / 3.0,    1.0));
                tc.push_back(Coordinate2D(2.0 / 3.0,    1.0));
                tc.push_back(Coordinate2D(1.0,          1.0));
                
                tc.push_back(Coordinate2D(0.0,          2.0 / 3.0));
                tc.push_back(Coordinate2D(1.0 / 3.0,    2.0 / 3.0));
                tc.push_back(Coordinate2D(2.0 / 3.0,    2.0 / 3.0));
                tc.push_back(Coordinate2D(1.0,          2.0 / 3.0));
                
                tc.push_back(Coordinate2D(0.0,          1.0 / 3.0));
                tc.push_back(Coordinate2D(1.0 / 3.0,    1.0 / 3.0));
                tc.push_back(Coordinate2D(2.0 / 3.0,    1.0 / 3.0));
                tc.push_back(Coordinate2D(1.0,          1.0 / 3.0));
                
                tc.push_back(Coordinate2D(0.0,          0.0));
                tc.push_back(Coordinate2D(1.0 / 3.0,    0.0));
                tc.push_back(Coordinate2D(2.0 / 3.0,    0.0));
                tc.push_back(Coordinate2D(1.0,          0.0));
                
                break;
                
            default:
                
                throw new InvalidDrawException("Invalid draw order.");
                
                break;
        }
        
        glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0,
                1.0, 2, (_order + 1), 0.0,
                1.0, (_order + 1) * 2, (_order + 1),
                Coordinate2D::vectorToFloatVector(tc));
        
        glEnable(GL_MAP2_VERTEX_3);
        glEnable(GL_MAP2_NORMAL);
        glEnable(GL_MAP2_TEXTURE_COORD_2);
        
        glMapGrid2f(_parts.x, 0.0, 1.0, _parts.y, 0.0, 1.0);
        
        glShadeModel(GL_SMOOTH);
        
        glEvalMesh2((_compute == kPatchComputeFill ? GL_FILL : (_compute == kPatchComputeLine ? GL_LINE : GL_POINT)), 0, _parts.x, 0, _parts.y);
        
        glDisable(GL_AUTO_NORMAL);
        
        Globals::getInstance().setCullingSettings(new CullingSettings(cf, co));
    }
    
    glPopMatrix();
}

void Flag::draw() {
    if (_appWait) {
        _appWait--;
        
        return;
    }
    
    glPushMatrix();
    
    {
        
        if (_shader == nullptr)
            _shader = new Shader(_texture->getTexture(),
                                 Globals::getInstance().getShadingSettings()->getVertPath(),
                                 Globals::getInstance().getShadingSettings()->getFragPath());
        
        _shader->bind(0.05, Globals::getInstance().getShadingSettings()->getWind());
        
        glActiveTexture(GL_TEXTURE0);
        
        _texture->apply();
        
        _plane->draw();
        
        _shader->unbind();
    }
    
    glPopMatrix();
}

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

void ScoreView::draw() {
    //
    //  A 2x2 rectangle with the score.
    //
    
    glPushMatrix();
    
    {
        _rectangle = new Rectangle(Coordinate2D(0, 0), Coordinate2D(4, 4));
        
        _rectangle->draw();
        
        Text text = Text(std::to_string(LeBloq::getInstance().getCurrentGameState().getBoard().getScoringForPlayer(1)), Coordinate3D(1, 0, 1), {.r = 1, .g = 0, .b = 0}, GLUT_BITMAP_HELVETICA_18);
        
        text.draw();
        
        text = Text(std::to_string(LeBloq::getInstance().getCurrentGameState().getBoard().getScoringForPlayer(2)), Coordinate3D(2, 0, 1), {.r = 1, .g = 0, .b = 0}, GLUT_BITMAP_HELVETICA_18);
        
        text.draw();
    }
    
    glPopMatrix();
}

void Text::draw() {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    
    glPushMatrix();
    
    {
        glColor3f(_col.r, _col.g, _col.b);
        glRasterPos3f(_pos.x, _pos.y, _pos.z);
        
        for (int i = 0; i < _text.length(); i++)
            glutBitmapCharacter(_glutFont, _text[i]);
    }
    
    glPopMatrix();
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}
