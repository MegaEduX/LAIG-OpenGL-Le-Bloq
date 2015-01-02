//
//  ScoreView.cpp
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#include "ScoreView.h"

#include "Global.h"

#include "LeBloq.h"

#include "MainScene.h"

#include "LeBloqReplay.h"

void ScoreView::draw() {
    //
    //  A 10x10 rectangle with the score.
    //
    
    glPushMatrix();
    
    {
        LeBloqBoard b = LeBloq::getInstance().getCurrentGameState().getBoard();
        
        if (Globals::getInstance().getMainScene()->getCurrentReplay() != nullptr) {
            try {
                b = Globals::getInstance().getMainScene()->getCurrentReplay()->getCurrentState().getBoard();
            } catch (...) {
                b = Globals::getInstance().getMainScene()->getCurrentReplay()->getPreviousState().getBoard();
            }
        }
        
        Text text = Text(std::to_string(b.getScoringForPlayer(1)), Coordinate3D(1, 2.5, 2), {.r = 1, .g = 0, .b = 0}, GLUT_BITMAP_HELVETICA_18);
        
        text.draw();
        
        text = Text(std::to_string(b.getScoringForPlayer(2)), Coordinate3D(6, 2.5, 2), {.r = 1, .g = 0, .b = 0}, GLUT_BITMAP_HELVETICA_18);
        
        text.draw();
    }
    
    glPopMatrix();
}