//
//  MainScene.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 24/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__MainScene__
#define __Project_1__MainScene__

#include <stdio.h>

#include "CGFscene.h"
#include "CGFshader.h"

#include "ANFResult.h"

#include "GraphicalEngine.h"

#include "BoardDraw.h"

#include "LeBloqReplay.h"

#include "Global.h"

typedef enum {
    kACSUnchecked,
    kACSDisabled,
    kACSEnabled
} kACS;

_BUILD_GRAPHICAL_EXCEPTION(MainSceneCreationException, GraphicalException);

class Interface;

class MainScene : public CGFscene {
    
    double _lastUpdateValue;
    
    ANFResult *_anf;
    
    BoardDraw *_bd;
    
    PieceNode *_bdn;
    
    PieceNode *_marker;
    
    void _setupFromANF();
    
    void _animateLatestPlay();
    
    void _computeAIPlay();
    
    Camera *_lastGoodCamera;
    
    bool _criticalSection;
    
    bool _loadedMatrixes;
    
    bool _interfaceLocked;
    
    void _createTransformationMatrixes(Node *n);
    
    Appearance *_p1Appearance;
    Appearance *_p2Appearance;
    
    Appearance *_blankAppearance;
    
    Appearance *_scrubWhite;
    Appearance *_scrubBlack;
    
    Interface *_interface;
    
    AnimatedRotation *_animatedRotation;
    
    kACS _acsState;
    
    Camera *_acs1, *_acs2;
    
    LeBloqReplay *_currentReplay;
    
    int _wac;
    
public:
    
    MainScene(ANFResult *);
    
    void init();
    void display();
    
    void displayBoard();
    void displayPieces();
    void displayReplay();
    
    void update(unsigned long);
    
    void reloadANF();
    
    void setInterface(Interface *i) {
        _interface = i;
    }
    
    PieceNode *getMarker() {
        return _marker;
    }
    
    void loadReplay(LeBloqReplay *);
    void stopReplay();
    
    LeBloqReplay *getCurrentReplay() {
        return _currentReplay;
    }
    
    bool getInterfaceLock() {
        return _interfaceLocked;
    }
    
    ~MainScene();
    
};

#endif /* defined(__Project_1__MainScene__) */
