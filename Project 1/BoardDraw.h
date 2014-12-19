//
//  BoardDraw.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 08/12/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__BoardDraw__
#define __Project_1__BoardDraw__

#include <iostream>

#include "LeBloq.h"

#include "Coordinate.h"

#include "Primitive.h"

class BoardDraw {
    
    PieceNode *_pieceNode;
    
    Coordinate3D _boardPos;
    
    int _squareSize;
    
    float _squareSeparation;
    
    LeBloqState _state;
    
public:
    
    BoardDraw(PieceNode *pieceNode, Coordinate3D boardPos, int squareSize, float squareSeparation) {
        _pieceNode = pieceNode;
        
        _boardPos = boardPos;
        
        _squareSize = squareSize;
        
        _squareSeparation = squareSeparation;
        
        _state = LeBloq::getInstance().getCurrentGameState();
    }
    
    void setOverride(LeBloqState state) {
        _state = state;
    }
    
    void draw() {
        std::vector<LeBloqPiece> pieces = _state.getBoard().getPieces();
        
        for (LeBloqPiece piece : pieces) {
            Coordinate3D drawPos = _boardPos;
            
            int diff = _squareSize + _squareSeparation;
            
            drawPos.x += piece.position.x * diff;
            drawPos.z += piece.position.y * diff;    //  Yes, the z/y thing is -correct-.
            
            glPushMatrix();
            
            {
                
                glTranslated(drawPos.x, drawPos.y, drawPos.z);
                //  glTranslated(-1.5, -1.5, -1.5);
                
                
                _pieceNode->setPiece(piece);
                _pieceNode->draw();
                
            }
            
            glPopMatrix();
        }
        
        _state = LeBloq::getInstance().getCurrentGameState();
    }
    
};

#endif /* defined(__Project_1__BoardDraw__) */
