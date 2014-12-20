//
//  LeBloqReplay.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 30/11/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__LeBloqReplay__
#define __Project_1__LeBloqReplay__

#include <iostream>

#include "LeBloqTile.h"
#include "LeBloqState.h"
#include "LeBloqPiece.h"

#include "GraphicalException.h"

#include "StackReverse.h"

_BUILD_GRAPHICAL_EXCEPTION(NoPlayedPiecesException, GraphicalException);

class LeBloqReplay {
    
    int _playCount = 0;
    
    LeBloqState _previousState;
    
    std::stack<LeBloqState> _replayData;
    
public:
    
    LeBloqReplay(std::stack<LeBloqState> replayData) {
        _replayData = reverseStack(replayData);
    }
    
    LeBloqPiece getPlayedPiece() {
        if (!_playCount)
            throw new NoPlayedPiecesException("No pieces were played so far!");
            
        std::vector<LeBloqPiece> pieces = _replayData.top().getBoard().getPieces();
        
        if (_playCount == 1)
            return pieces[0];
        
        LeBloqBoard stateDiff = _replayData.top().getBoard() - _previousState.getBoard();
            
        return stateDiff.getPieces()[0];
    }
    
    std::vector<LeBloqTile> getScoredTiles() {
        if (_playCount < 4)
            return std::vector<LeBloqTile>();
        
        LeBloqBoard stateDiff = _replayData.top().getBoard() - _previousState.getBoard();
        
        return stateDiff.getScoredTiles();
    }
    
    LeBloqState getCurrentState() {
        return _replayData.top();
    }
    
    void advance() {
        _previousState = _replayData.top();
        
        _replayData.pop();
        
        _playCount++;
    }
    
    static std::string createReplayData(std::stack<LeBloqState>);
    
    static std::stack<LeBloqState> loadReplayData(std::string);
    
};

#endif /* defined(__Project_1__LeBloqReplay__) */
