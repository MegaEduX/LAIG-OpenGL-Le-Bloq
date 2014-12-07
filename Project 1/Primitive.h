//
//  Primitive.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 23/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__Primitive__
#define __Project_1__Primitive__

#include <stdio.h>

#include "CGFobject.h"

#include "Coordinate.h"

#include "GraphicalObject.h"

#include "GraphicalException.h"

#include "Animation.h"

#include "Texture.h"

#include "Shader.h"

#include "Global.h"

_BUILD_GRAPHICAL_EXCEPTION(InvalidDrawException, GraphicalException);

typedef enum {
    
    kPatchComputePoint,
    kPatchComputeLine,
    kPatchComputeFill
    
} kPatchCompute;

class Primitive : GraphicalObject {
    
protected:
    
    GLUquadric *_quad;
    
    Coordinate2D _texCoords;
    
public:
    
    Primitive() {
        _quad = gluNewQuadric();
    }
    
    virtual void draw() {
        
    }
    
    void setTextureCoordinates(Coordinate2D crd) {
        _texCoords = crd;
    }
    
};

class Rectangle : public Primitive {
    
    Coordinate2D _point1;
    Coordinate2D _point2;
    
public:
    
    Rectangle(Coordinate2D p1, Coordinate2D p2) : Primitive() {
        _point1 = p1;
        _point2 = p2;
    }
    
    void draw();
    
};

class Triangle : public Primitive {
    
    Coordinate3D _point1;
    Coordinate3D _point2;
    Coordinate3D _point3;
    
public:
    
    Triangle(Coordinate3D p1, Coordinate3D p2, Coordinate3D p3) : Primitive() {
        _point1 = p1;
        _point2 = p2;
        _point3 = p3;
    }
    
    void draw();
    
};

class UnitCube : public Primitive {
    
public:
    
    UnitCube() {
        
    }
    
    void draw();
    
};

class Cylinder : public Primitive {
    
    float _base;
    float _top;
    float _height;
    
    unsigned int _slices;
    unsigned int _stacks;
    
public:
    
    Cylinder(float base, float top, float height, unsigned int slices, unsigned int stacks) : Primitive() {
        _base = base;
        _top = top;
        _height = height;
        
        _slices = slices;
        _stacks = stacks;
    }
    
    float getBase() {
        return _base;
    }
    
    float getTop() {
        return _top;
    }
    
    float getHeight() {
        return _height;
    }
    
    unsigned int getSlices() {
        return _slices;
    }
    
    unsigned int getStacks() {
        return _stacks;
    }
    
    void draw();
    
};

class Sphere : public Primitive {
    
    float _radius;
    
    unsigned int _slices;
    unsigned int _stacks;
    
public:
    
    Sphere(float radius, unsigned int slices, unsigned int stacks) : Primitive() {
        _radius = radius;
        
        _slices = slices;
        _stacks = stacks;
        
        _quad = gluNewQuadric();
    }
    
    ~Sphere() {
        gluDeleteQuadric(_quad);
    }
    
    float getRadius() {
        return _radius;
    }
    
    unsigned int getSlices() {
        return _slices;
    }
    
    unsigned int getStacks() {
        return _stacks;
    }
    
    void draw();
    
};

class Torus : public Primitive {
    
    float _inner;
    float _outer;
    
    unsigned int _slices;
    unsigned int _loops;
    
public:
    
    Torus(float inner, float outer, unsigned int slices, unsigned int loops) : Primitive() {
        _inner = inner;
        _outer = outer;
        _slices = slices;
        _loops = loops;
    }
    
    float getInner() {
        return _inner;
    }
    
    float getOuter() {
        return _outer;
    }
    
    unsigned int getSlices() {
        return _slices;
    }
    
    unsigned int getLoops() {
        return _loops;
    }
    
    void draw();
    
};

class Plane : public Primitive {
    
    int _parts;
    
public:
    
    Plane(int parts) : Primitive() {
        _parts = parts;
    }
    
    void draw();
    
};

class Patch : public Primitive {
    
    int _order;
    
    Coordinate2D _parts;
    
    kPatchCompute _compute;
    
    std::vector<Coordinate3D> _controlPoints;
    
public:
    
    Patch(int order, Coordinate2D parts, kPatchCompute compute) : Primitive() {
        _order = order;
        
        _parts = parts;
        
        _compute = compute;
    }
    
    void addControlPoint(Coordinate3D cp) {
        _controlPoints.push_back(cp);
    }
    
    bool removeControlPoint(Coordinate3D cp) {
        for (int i = 0; i < _controlPoints.size(); i++)
            if (_controlPoints[i] == cp) {
                _controlPoints.erase(_controlPoints.begin() + i);
                
                return true;
            }
        
        return false;
    }
    
    void draw();
    
};

class Vehicle : public Primitive {
    
public:
    
    void draw();
    
};

class Flag : public Primitive {
    
    Texture *_texture;
    
    Shader *_shader;
    
    Plane *_plane;
    
    unsigned int _appWait;
    
public:
    
    Flag(Texture *tex) : Primitive() {
        _texture = tex;
        
        _plane = new Plane(25);
        
        _shader = nullptr;
        
        _appWait = 15;
    }
    
    void draw();
    
};

class Table : public Primitive {
    
    UnitCube *cube = new UnitCube();
    
public:
    
    Table() {
        
    }
    
    ~Table() {
        delete cube;
    }
    
    void draw();
    
};

#endif /* defined(__Project_1__Primitive__) */
