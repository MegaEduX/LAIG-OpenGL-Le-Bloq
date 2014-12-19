//
//  LeBloq.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 27/11/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
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
    
    kLeBloqGameTypePlayerVsAI_Easy,
    kLeBloqGameTypePlayerVsAI_Hard,
    kLeBloqGameTypePlayerVsPlayer,
    kLeBloqGameTypeAIVsAI
    
} kLeBloqGameType;

class LeBloq {
    
    std::stack<LeBloqState> _gameStates;
    
    SocketClient *_conn;
    
    int _boardSizeX;
    
    int _boardSizeY;
    
    int _gameStart;
    int _turnStart;
    
    LeBloqState _parseOK(std::string);
    
    int _checkWinner();
    
    kLeBloqGameType _gameType;
    
    LeBloq() {
        _conn = new SocketClient(kDefaultAddress, kDefaultPort);
        
        _gameType = kLeBloqGameTypePlayerVsAI_Easy;
    }
    
    LeBloq(LeBloq const &);
    
    void operator=(LeBloq const &);
    
public:
    
    static LeBloq& getInstance() {
        static LeBloq instance;
        
        return instance;
    }
    
    void setGameType(kLeBloqGameType gt) {
        _gameType = gt;
    }
    
    kLeBloqGameType getGameType() {
        return _gameType;
    }
    
    LeBloqState newGame(int boardSizeX, int boardSizeY);
    
    LeBloqState getCurrentGameState();
    
    LeBloqState getPreviousGameState();
    
    std::stack<LeBloqState> getGameStates() {
        return _gameStates;
    }
    
    Coordinate2D getBoardSize() {
        return Coordinate2D(_boardSizeX, _boardSizeY);
    }
    
    unsigned int getGameTimeElapsed() {
        return (unsigned int) time(NULL) - _gameStart;
    }
    
    unsigned int getTurnTimeElapsed() {
        return (unsigned int) time(NULL) - _turnStart;
    }
    
    void undo() {
        _gameStates.pop();
    }
    
    LeBloqState performPlay();
    
    LeBloqState performPlay(LeBloqPiece);
    
    LeBloqState performPlay(int pieceType, char pieceOrientation, Coordinate2D piecePos);
    
    LeBloqState performPlayAI();
    
    LeBloqPiece workingPiece;
    
};

#endif /* defined(__Project_1__LeBloq__) */
