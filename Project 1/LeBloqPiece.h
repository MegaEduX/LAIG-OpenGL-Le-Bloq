//
//  LeBloqPiece.h
//  Project 1
//
//  Created by Eduardo Almeida on 29/11/14.
//  Copyright (c) 2014 Eduardo Almeida. All rights reserved.
//

#ifndef __Project_1__LeBloqPiece__
#define __Project_1__LeBloqPiece__

#include "Coordinate.h"

class LeBloqPiece {
    
public:
    
    Coordinate2D position;
    
    int type;
    
    char orientation;
    
    LeBloqPiece(Coordinate2D p, int t, int o) {
        position = p;
        
        type = t;
        
        orientation = o;
    }
    
};

#endif /* defined(__Project_1__LeBloqPiece__) */
