//
//  LeBloq.h
//  Project 1
//
//  Created by Eduardo Almeida on 27/11/14.
//  Copyright (c) 2014 Eduardo Almeida. All rights reserved.
//

#ifndef __Project_1__LeBloq__
#define __Project_1__LeBloq__

#include <iostream>
#include <vector>
#include <stack>

#include "SocketClient.h"

#include "Coordinate.h"

#include "GraphicalException.h"

_BUILD_GRAPHICAL_EXCEPTION(LeBloqException, GraphicalException);

_BUILD_GRAPHICAL_EXCEPTION(LeBloqBoardCreationException, LeBloqException);
_BUILD_GRAPHICAL_EXCEPTION(LeBloqBoardPlayException, LeBloqException);

class LeBloqPiece {
    
    Coordinate2D position;
    
    int type;
    
};

class LeBloqBoard {
    
    std::vector<std::vector<int>> _boardRepresentation;
    
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

class LeBloqState {
    
    LeBloqBoard _board;
    
    int _player;
    
    bool _playing;
    
public:
    
    LeBloqState(LeBloqBoard b, int p, bool r) {
        _board = b;
        _player = p;
        _playing = r;
    }
    
    LeBloqBoard getBoard() {
        return _board;
    }
    
    int getPlayer() {
        return _player;
    }
    
    bool getPlaying() {
        return _playing;
    }
    
};

class LeBloq {
    
    std::stack<LeBloqState> _gameStates;
    
    SocketClient *_conn;
    
    int _boardSizeX;
    
    int _boardSizeY;
    
    LeBloqState _parseOK(std::string);
    
public:
    
    LeBloq() {
        _conn = new SocketClient("127.0.0.1", 60001);
    }
    
    LeBloq(std::string host, int port) {
        _conn = new SocketClient(host, port);
    }
    
    LeBloqState newGame(int boardSizeX, int boardSizeY);
    
    LeBloqState getCurrentGameState();
    
    LeBloqState performPlay(int pieceType, char pieceOrientation, Coordinate2D piecePos);
    
};

#endif /* defined(__Project_1__LeBloq__) */
