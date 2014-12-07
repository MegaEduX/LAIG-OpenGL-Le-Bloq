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

#include "LeBloqPiece.h"

#define kDefaultAddress "127.0.0.1"
#define kDefaultPort    60001

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
    
    LeBloq() {
        _conn = new SocketClient(kDefaultAddress, kDefaultPort);
        
        _gameType = kLeBloqGameTypePlayerVsAI;
    }
    
    LeBloq(LeBloq const &);
    
    void operator=(LeBloq const &);
    
public:
    
    static LeBloq& getInstance() {
        static LeBloq instance;
        
        return instance;
    }
    
    /*  
     
     LeBloq(kLeBloqGameType gameType) {
        _conn = new SocketClient(kDefaultAddress, kDefaultPort);
        
        _gameType = gameType;
    }
    
    LeBloq(kLeBloqGameType gameType, std::string host, int port) {
        _conn = new SocketClient(host, port);
        
        _gameType = gameType;
    }   
     
     */
    
    void setGameType(kLeBloqGameType gt) {
        _gameType = gt;
    }
    
    kLeBloqGameType getGameType() {
        return _gameType;
    }
    
    LeBloqState newGame(int boardSizeX, int boardSizeY);
    
    LeBloqState getCurrentGameState();
    
    std::stack<LeBloqState> getGameStates() {
        return _gameStates;
    }
    
    LeBloqState performPlay();
    
    LeBloqState performPlay(LeBloqPiece);
    
    LeBloqState performPlay(int pieceType, char pieceOrientation, Coordinate2D piecePos);
    
    LeBloqPiece workingPiece;
    
};

#endif /* defined(__Project_1__LeBloq__) */
