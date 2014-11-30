//
//  LeBloqTile.h
//  Project 1
//
//  Created by Eduardo Almeida on 30/11/14.
//  Copyright (c) 2014 Eduardo Almeida. All rights reserved.
//

#ifndef Project_1_LeBloqTile_h
#define Project_1_LeBloqTile_h

#include <iostream>

#include "Coordinate.h"

class LeBloqTile {
    
    Coordinate2D _position;
    
    int _scoringPlayer;
    
public:
    
    LeBloqTile(Coordinate2D pos, int scoringPlayer) {
        _position = pos;
        
        _scoringPlayer = scoringPlayer;
    }
    
};

#endif
