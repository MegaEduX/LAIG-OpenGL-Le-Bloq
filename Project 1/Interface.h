//
//  Interface.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 02/10/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__Interface__
#define __Project_1__Interface__

#include <iostream>

#include "CGFinterface.h"

#include "GraphicalEngine.h"

#include "ANFResult.h"

#include "MainScene.h"

#include "GraphicalException.h"

_BUILD_GRAPHICAL_EXCEPTION(InterfaceException, GraphicalException);

_BUILD_GRAPHICAL_EXCEPTION(LightNotFoundException, InterfaceException);
_BUILD_GRAPHICAL_EXCEPTION(CameraNotFoundException, InterfaceException);
_BUILD_GRAPHICAL_EXCEPTION(AnimationNotFoundException, InterfaceException);
_BUILD_GRAPHICAL_EXCEPTION(InternalInconsistencyException, InterfaceException);
    
class Interface : public CGFinterface {
    
    MainScene *_scene;
    
    ANFResult *_result;
    
public:
    
    Interface(MainScene *s, ANFResult *r) {
        _scene = s;
        _result = r;
    }
    
    void initGUI();
    
    void processGUI(GLUI_Control *ctrl);
    
};

#endif /* defined(__Project_1__Interface__) */
