//
//  LeBloqBoard.h
//  Project 1
//
//  Created by Eduardo Almeida on 29/11/14.
//  Copyright (c) 2014 Eduardo Almeida. All rights reserved.
//

#ifndef __Project_1__LeBloqBoard__
#define __Project_1__LeBloqBoard__

#include <iostream>

#include <vector>

#include "Coordinate.h"

#include "LeBloqPiece.h"

#include "GraphicalException.h"

_BUILD_GRAPHICAL_EXCEPTION(LeBloqUnknownPieceException, LeBloqException);

class LeBloqBoard {
    
    std::vector<std::vector<int>> _boardRepresentation;
    
    char _figurePieceOrientation(Coordinate2D);
    
    void _removePieceFromBoard(std::vector<std::vector<int>> &, Coordinate2D);
    
public:
    
    LeBloqBoard() {
        
    }
    
    LeBloqBoard(std::vector<std::vector<int>> boardRepresentation) {
        _boardRepresentation = boardRepresentation;
    }
    
    std::vector<std::vector<int>> getBoardRepresentation() {
        return _boardRepresentation;
    }
    
    std::vector<LeBloqPiece> getPieces();
    
};

#endif /* defined(__Project_1__LeBloqBoard__) */
