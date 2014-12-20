//
//  LeBloq.cpp
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 27/11/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#include "LeBloq.h"

#include "LeBloqBoard.h"

#include "LeBloqState.h"

#include "PrologParser.h"

LeBloqState LeBloq::_parseOK(std::string answer) {
    answer.erase(0, 3);
    
    answer.pop_back();
    
    std::vector< std::vector<int> > boardRep = PrologParser::prologToBoardRepresentation(answer, _boardSizeX);
    
    LeBloqBoard board = LeBloqBoard(boardRep);
    
    int nextPlayer = (_gameStates.size() ? (getCurrentGameState().getPlayer() == 1 ? 2 : 1) : 2);
    
    int winner = 0;
    
    bool playing = true;
    
    if (_gameStates.size())
        if (( winner = _checkWinner(board) )) {
            nextPlayer = winner;
            
            playing = false;
        }
    
    LeBloqState state = LeBloqState(board, nextPlayer, playing);
    
    _gameStates.push(state);
    
    return state;
}

int LeBloq::_checkWinner(LeBloqBoard board) {
    std::string message = "checkWinner(" + PrologParser::boardRepresentationToProlog(board.getBoardRepresentation()) + "," + std::to_string(_boardSizeX) + "," + std::to_string(_boardSizeY) + ").";
    
    std::cout << "[Check Winner Debug] " << message << std::endl;
    
    _conn->write(message);
    
    int winner = atoi(_conn->read().c_str());
    
    std::cout << "Winner State: " << winner << std::endl;
    
    return winner;
}

LeBloqState LeBloq::newGame(int x, int y) {
    _conn->write("initialize(" + std::to_string(x) + "," + std::to_string(y) + ").");
    
    std::string answer = _conn->read();
    
    if (answer.find("fail") != std::string::npos || answer.find("ok(") == std::string::npos)
        throw new LeBloqBoardCreationException("Unable to create board.");
    
    _boardSizeX = x;
    _boardSizeY = y;
    
    LeBloqState state = _parseOK(answer);
    
    LeBloqState newState(state.getBoard(), 1, true);
    
    _gameStart = (unsigned int) time(NULL);
    _turnStart = _gameStart;
    
    std::cout << newState.getPlayer() << std::endl;
    
    if (_gameStates.size())
        _gameStates.pop();  //  Workaround for an unknown problem.
    
    _gameStates.push(newState);
    
    return newState;
}

LeBloqState LeBloq::getCurrentGameState() {
    return _gameStates.top();
}

LeBloqState LeBloq::getPreviousGameState() {
    LeBloqState cs = getCurrentGameState();
    
    _gameStates.pop();
    
    LeBloqState ret = getCurrentGameState();
    
    _gameStates.push(cs);
    
    return ret;
}

LeBloqState LeBloq::performPlay() {
    return performPlay(workingPiece);
}

LeBloqState LeBloq::performPlay(LeBloqPiece piece) {
    return performPlay(piece.type, piece.orientation, piece.position);
}

LeBloqState LeBloq::performPlay(int pieceType, char pieceOrientation, Coordinate2D piecePos) {
    std::string message = (_gameStates.size() == 1 ? "playFT(" : "play(") + PrologParser::boardRepresentationToProlog(getCurrentGameState().getBoard().getBoardRepresentation()) + "," + std::to_string(pieceType) + "," + pieceOrientation + "," + std::to_string((int) piecePos.x) + "," + std::to_string((int) piecePos.y) + "," + std::to_string(getCurrentGameState().getPlayer()) + "," + std::to_string(_boardSizeX) + "," + std::to_string(_boardSizeY) + ").";
    
    std::string answer;
    
    for (int i = 0; i < 3; i++) {
        _conn->write(message);
        
        answer = _conn->read();
        
        if (answer.find("fail") != std::string::npos || answer.find("ok(") == std::string::npos) {
            if (i == 2)
                throw new LeBloqBoardPlayException("Unable to perform play: " + answer);
        } else
            break;
    }
    
    LeBloqState state = _parseOK(answer);
    
    _turnStart = (unsigned int) time(NULL);
    
    return state;
}

LeBloqState LeBloq::performPlayAI() {
    std::string message = (_gameStates.size() == 1 ? "playAIFT(" : "playAI(") + PrologParser::boardRepresentationToProlog(getCurrentGameState().getBoard().getBoardRepresentation()) + "," + std::to_string(getCurrentGameState().getPlayer()) + "," + std::to_string(_boardSizeX) + "," + std::to_string(_boardSizeY) + ").";
    
    std::string answer;
    
    for (int i = 0; i < 3; i++) {
        _conn->write(message);
        
        answer = _conn->read();
        
        if (answer.find("fail") != std::string::npos || answer.find("ok(") == std::string::npos) {
            if (i == 2)
                throw new LeBloqBoardPlayException("Unable to perform play: " + answer);
        } else
            break;
    }
    
    LeBloqState state = _parseOK(answer);
    
    _turnStart = (unsigned int) time(NULL);
    
    return state;
}
