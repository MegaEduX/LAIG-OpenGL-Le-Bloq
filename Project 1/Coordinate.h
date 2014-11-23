//
//  Coordinate.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 23/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__Coordinate__
#define __Project_1__Coordinate__

#include <stdio.h>

#include <vector>

class Coordinate {
    
public:
    
    virtual float *getFloatVector() {
        return NULL;
    }
    
};

class Coordinate2D : Coordinate {
    
public:
    
    Coordinate2D() {
        x = 0, y = 0;
    }
        
    Coordinate2D(float xCoord, float yCoord) {
        x = xCoord, y = yCoord;
    }
    
    float x, y;
    
    float *getFloatVector();
    
    static float* vectorToFloatVector(std::vector<Coordinate2D> fv);
    
    bool operator==(const Coordinate2D &other) const {
        return (x == other.x && y == other.y);
    }
    
};

class Coordinate3D : Coordinate {
    
public:
    
    Coordinate3D() {
        x = 0, y = 0, z = 0;
    }
    
    Coordinate3D(float xCoord, float yCoord, float zCoord) {
        x = xCoord, y = yCoord, z = zCoord;
    }
    
    float x, y, z;
    
    float *getFloatVector();
    float *getRawFloatVector();
    
    static float* vectorToFloatVector(std::vector<Coordinate3D> fv);
    
    bool operator==(const Coordinate3D &other) const {
        return (x == other.x && y == other.y && z == other.z);
    }
    
    friend inline Coordinate3D operator+(Coordinate3D lhs, const Coordinate3D &rhs) {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        lhs.z += rhs.z;
        
        return lhs;
    }
    
    friend inline Coordinate3D operator-(Coordinate3D lhs, const Coordinate3D &rhs) {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        lhs.z -= rhs.z;
        
        return lhs;
    }
    
    friend inline Coordinate3D operator*(Coordinate3D lhs, const Coordinate3D &rhs) {
        lhs.x *= rhs.x;
        lhs.y *= rhs.y;
        lhs.z *= rhs.z;
        
        return lhs;
    }
    
    friend inline Coordinate3D operator/(Coordinate3D lhs, const Coordinate3D &rhs) {
        lhs.x /= rhs.x;
        lhs.y /= rhs.y;
        lhs.z /= rhs.z;
        
        return lhs;
    }
    
};

#endif /* defined(__Project_1__Coordinate__) */
