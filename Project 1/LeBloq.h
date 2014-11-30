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

#include "LeBloqState.h"

_BUILD_GRAPHICAL_EXCEPTION(LeBloqBoardCreationException, LeBloqException);
_BUILD_GRAPHICAL_EXCEPTION(LeBloqBoardPlayException, LeBloqException);

typedef enum {
    
    kLeBloqGameTypePlayerVsAI,
    kLeBloqGameTypePlayerVsPlayer,
    kLeBloqGameTypeAIVsAI
    
} kLeBloqGameType;

class LeBloq {
    
    std::stack<LeBloqState> _gameStates;
    
    SocketClient *_conn;
    
    int _boardSizeX;
    
    int _boardSizeY;
    
    LeBloqState _parseOK(std::string);
    
    int _checkWinner();
    
    kLeBloqGameType _gameType;
    
public:
    
    LeBloq() {
        _conn = new SocketClient("127.0.0.1", 60001);
        
        _gameType = kLeBloqGameTypePlayerVsAI;
    }
    
    LeBloq(kLeBloqGameType gameType) {
        _conn = new SocketClient("127.0.0.1", 60001);
        
        _gameType = gameType;
    }
    
    LeBloq(kLeBloqGameType gameType, std::string host, int port) {
        _conn = new SocketClient(host, port);
        
        _gameType = gameType;
    }
    
    LeBloqState newGame(int boardSizeX, int boardSizeY);
    
    LeBloqState getCurrentGameState();
    
    std::stack<LeBloqState> getGameStates() {
        return _gameStates;
    }
    
    LeBloqState performPlay(int pieceType, char pieceOrientation, Coordinate2D piecePos);
    
};

#endif /* defined(__Project_1__LeBloq__) */
