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

_BUILD_GRAPHICAL_EXCEPTION(MainSceneCreationException, GraphicalException);

class Interface;

class MainScene : public CGFscene {
    
    double _lastUpdateValue;
    
    ANFResult *_anf;
    
    BoardDraw *_bd;
    
    void _setupFromANF();
    
    Camera *_lastGoodCamera;
    
    bool _criticalSection;
    
    bool _loadedMatrixes;
    
    void _createTransformationMatrixes(Node *n);
    
    Appearance *_p1Appearance;
    
    Appearance *_p2Appearance;
    
    Appearance *_defaultAppearance;
    
    Interface *_interface;
    
public:
    
    MainScene(ANFResult *);
    
    void init();
    void display();
    
    void update(unsigned long);
    
    void reloadANF();
    
    void setInterface(Interface *i) {
        _interface = i;
    }
    
    ~MainScene();
    
};

#endif /* defined(__Project_1__MainScene__) */
