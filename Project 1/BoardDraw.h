//
//  BoardDraw.h
//  Project 1
//
//  Created by Eduardo Almeida on 08/12/14.
//  Copyright (c) 2014 Eduardo Almeida. All rights reserved.
//

#ifndef __Project_1__BoardDraw__
#define __Project_1__BoardDraw__

#include <iostream>

#include "LeBloq.h"

#include "Coordinate.h"

#include "Primitive.h"

class BoardDraw {
    
    Node *_pieceNode;
    
    Coordinate3D _boardPos;
    
    int _squareSize;
    
public:
    
    BoardDraw(Node *pieceNode, Coordinate3D boardPos, int squareSize) {
        _pieceNode =pieceNode;
        
        _squareSize = squareSize;
    }
    
    void draw() {
        auto pieces = LeBloq::getInstance().getCurrentGameState().getBoard().getPieces();
        
        for (LeBloqPiece piece : pieces) {
            Coordinate3D drawPos = _boardPos;
            
            drawPos.x += piece.position.x * _squareSize;
            drawPos.z += piece.position.y * _squareSize;    //  Yes, the z/y thing is -correct-.
            
            glPushMatrix();
            
            {
                glTranslated(drawPos.x, drawPos.y, drawPos.z);
                
                _pieceNode->draw(nullptr);
            }
            
            glPopMatrix();
        }
    }
    
};

#endif /* defined(__Project_1__BoardDraw__) */
