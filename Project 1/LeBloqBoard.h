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

#include <cereal/types/vector.hpp>

#include "Coordinate.h"

#include "LeBloqTile.h"
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
    
    LeBloqBoard operator-(LeBloqBoard rhs) {
        std::vector<std::vector<int>> boardRep;
        
        for (int col = 0; col < _boardRepresentation.size(); col++) {
            auto line = _boardRepresentation[col];
            
            for (int p = 0; p < line.size(); p++) {
                auto piece = line[p];
                
                if (rhs.getBoardRepresentation()[col][p] != piece) {
                    if (rhs.getBoardRepresentation()[col][p] != 0)
                        boardRep[col][p] = rhs.getBoardRepresentation()[col][p];
                    else
                        boardRep[col][p] = piece;
                }
            }
        }
        
        return LeBloqBoard(boardRep);
    }
    
    std::vector<LeBloqPiece> getPieces();
    
    std::vector<LeBloqTile> getScoredTiles();
    
    template <class Archive> void serialize(Archive &archive) {
        archive(_boardRepresentation);
    };
    
};

#endif /* defined(__Project_1__LeBloqBoard__) */
