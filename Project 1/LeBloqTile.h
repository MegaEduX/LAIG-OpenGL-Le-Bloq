//
//  LeBloqTile.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 30/11/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef Project_1_LeBloqTile_h
#define Project_1_LeBloqTile_h

#include <iostream>

#include "Coordinate.h"

class LeBloqTile {
    
public:
    
    Coordinate2D position;
    
    int scoringPlayer;
    
    LeBloqTile(Coordinate2D pos, int sp) {
        position = pos;
        
        scoringPlayer = sp;
    }
    
};

#endif
