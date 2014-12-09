//
//  LeBloqBoard.cpp
//  Project 1
//
//  Created by Eduardo Almeida on 29/11/14.
//  Copyright (c) 2014 Eduardo Almeida. All rights reserved.
//

#include "LeBloqBoard.h"

#define ORIENT_H    'h'
#define ORIENT_V    'v'

#define PIECE_1_B   3
#define PIECE_1_S   2

#define PIECE_2_B   4
#define PIECE_2_S   2

#define PIECE_3_B   4
#define PIECE_3_S   3

char LeBloqBoard::_figurePieceOrientation(Coordinate2D coord) {
    int type = _boardRepresentation[coord.y][coord.x];
    
    if (_boardRepresentation[coord.y][coord.x + 3] == type)             //  Width  = 4
        
        return ORIENT_H;
    
    else if (_boardRepresentation[coord.y][coord.x + 2] == type) {      //  Width  = 3
        
        if (_boardRepresentation[coord.y + 3][coord.x] == type)         //  Height = 4
            return ORIENT_V;
        else                                                            //  Height = 2
            return ORIENT_H;
        
    } else {                                                            //  Width  = 2
        
        if (_boardRepresentation[coord.y + 3][coord.x] == type)         //  Height = 4
            return ORIENT_V;
        else                                                            //  Height = 3
            return ORIENT_V;
        
    }
}

void LeBloqBoard::_removePieceFromBoard(std::vector<std::vector<int>> &board, Coordinate2D coord) {
    int pieceType = board[coord.y][coord.x];
    
    char orient = _figurePieceOrientation(coord);
    
    int width, height;
    
    switch (pieceType) {
            
        case 1:
            
            width  = (orient == ORIENT_H ? PIECE_1_B : PIECE_1_S);
            height = (orient == ORIENT_H ? PIECE_1_S : PIECE_1_B);
            
            break;
            
        case 2:
            
            width  = (orient == ORIENT_H ? PIECE_2_B : PIECE_2_S);
            height = (orient == ORIENT_H ? PIECE_2_S : PIECE_2_B);
            
            break;
            
        case 3:
            
            width  = (orient == ORIENT_H ? PIECE_3_B : PIECE_3_S);
            height = (orient == ORIENT_H ? PIECE_3_S : PIECE_3_B);
            
            break;
            
        default:
            
            throw new LeBloqUnknownPieceException("Unknown Piece Type!");
            
            break;
            
    }
    
    for (; height; height--, coord.y++) { //  ¯\_(ツ)_/¯
        //  std::cout << "[¯\\_(ツ)_/¯] height: " << height << ", x: " << coord.x << ", y: " << coord.y << "[¯\\_(ツ)_/¯]" << std::endl;
    
        for (int i = coord.x; i < coord.x + width; i++) {
            //  std::cout << "[¯\\_(ツ)_/¯] x: " << coord.x << ", y: " << coord.y << ", i: " << i << "[¯\\_(ツ)_/¯]" << std::endl;
            
            board[coord.y][i] = 0;
        }
    }
}

std::vector<LeBloqPiece> LeBloqBoard::getPieces() {
    std::vector<LeBloqPiece> pieces;
    
    auto boardRep = _boardRepresentation;   //  Let's create a copy and mess with it.
    
    for (int i = 0; i < boardRep.size(); i++) {
        auto line = boardRep[i];
        
        for (int j = 0; j < line.size(); j++, line = boardRep[i]) {
            auto piece = line[j];
            
            if (piece > 0 && piece < 4) {
                
                //
                //  We're forcibly at the (0, 0) of the piece,
                //  let's just figure out it's orientation and
                //  then remove it from the array.
                //
                
                char orientation = _figurePieceOrientation(Coordinate2D(j, i));
                
                _removePieceFromBoard(boardRep, Coordinate2D(j, i));
                
                pieces.push_back(LeBloqPiece(Coordinate2D(j, i), piece, orientation));
                
            }
        }
    }
    
    return pieces;
}

std::vector<LeBloqTile> LeBloqBoard::getScoredTiles() {
    std::vector<LeBloqTile> tiles;
    
    for (int i = 0; i < _boardRepresentation.size(); i++) {
        auto line = _boardRepresentation[i];
        
        for (int j = 0; j < line.size(); j++, line = _boardRepresentation[i]) {
            auto tile = line[j];
            
            if (tile > 3)
                tiles.push_back(LeBloqTile(Coordinate2D(j, i), tile - 4));
        }
        
    }
    
    return tiles;
}
