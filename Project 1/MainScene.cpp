//
//  MainScene.cpp
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 24/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#include "MainScene.h"

#include "GraphicalEngine.h"

#include "CGFapplication.h"

#include "ANFLoader.h"

#define NO_ANF_CAMERAS        0

#define DRAW_AXIS             1

#define ENABLE_PICKING        1

#define DEFAULT_NAME        - 1

#if ENABLE_PICKING

#endif

MainScene::MainScene(ANFResult *result) {
    _anf = result;
    
    _bd = nullptr;
    
    _criticalSection = false;
    
    if (!_anf || _anf == nullptr)
        throw new MainSceneCreationException("ANFResult* must not be null.");
    
    _lastGoodCamera = nullptr;
}

void MainScene::init() {
    //
    //  Default Normal
    //
    
    glNormal3f(0, 0, 1);
    
    _loadedMatrixes = false;
    
    _lastUpdateValue = 0;
    
    _setupFromANF();
    
    setUpdatePeriod(20);
}

void MainScene::update(unsigned long t) {
    double diff = (t - _lastUpdateValue) / 1000;
    
    _lastUpdateValue = t;
    
    for (int i = 0; i < _anf->animations.size(); i++)
        _anf->animations[i]->animate(diff);
}

void MainScene::_setupFromANF() {
    /*
     *  Apply the Global Settings...
     */
    
    Globals::getInstance().applyAllSettings();
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void MainScene::_createTransformationMatrixes(Node *n) {
    n->setTransformationMatrix();
    
	for (int i = 0; i < n->getDescendants().size(); i++)
        _createTransformationMatrixes(n->getDescendants()[i]);
}

void MainScene::reloadANF() {
    while (_criticalSection) {
        //  Waiting...
    }
    
    _criticalSection = true;
    
    _anf = ANFLoader::getInstance().loadANF();
    
    _setupFromANF();
    
    _criticalSection = false;
}

void MainScene::display() {
    if (_criticalSection)
        return;
    
    _criticalSection = true;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    Globals::getInstance().applyAllSettings();
    
#if NO_ANF_CAMERAS
    
    CGFscene::activeCamera->applyView();
    
#else
    
    bool foundCamera = false;
    
	for (int i = 0; i < _anf->cameras.size(); i++) {
		Camera *c = _anf->cameras[i];
		
        if (c->getEnabled()) {
            foundCamera = true;
            
            if (c == _lastGoodCamera)
                break;
            
            c->updateProjectionMatrix(1.0, 1.0);
            
            _lastGoodCamera = c;
            
            CGFscene::activeCamera = c;
            
            CGFapplication::activeApp->forceRefresh();  //  If I don't do this, then I need to resize the window for changes to apply.
            
            break;
        }
	}
    
    if (!foundCamera)
        throw new MainSceneCreationException("Camera not found!");
    
#endif
    
#if DRAW_AXIS
    
    axis.draw();
    
#endif
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    
    CGFscene::activeCamera->applyView();
    
	for (int i = 0; i < _anf->lights.size(); i++)
        _anf->lights[i]->draw();
    
    if (!_loadedMatrixes) {
        _createTransformationMatrixes(_anf->graphs[0]->getRootNode());
        
        _loadedMatrixes = true;
    }
    
	for (int i = 0; i < _anf->graphs.size(); i++) {
        Node *n = _anf->graphs[i]->getRootNode();
        
        glPushMatrix();
        
        {
            n->draw();
        }
        
        glPopMatrix();
    }
    
#if ENABLE_PICKING
    
    if (_bd == nullptr) {
        PieceNode *bdn = nullptr;
        
        for (Node *n : _anf->graphs[0]->getNodes()) {
            if (dynamic_cast<PieceNode *>(n)) {
                bdn = (PieceNode *) n;
                
                break;
            }
        }
        
        if (!bdn) {
            std::cout << "This can not happen! Throw an exception here!" << std::endl;
            
            return;
        }
        
        _bd = new BoardDraw(bdn, Coordinate3D(1.5, 1.5, 1.5), 2, 0.5); //  arbitrary values
    }
    
    glPushMatrix();
    
    {
        glTranslated(30, 55, 30);
        
        _bd->draw();
    }
    
    glPopMatrix();
    
    Rectangle *obj = new Rectangle(Coordinate2D(0, 0), Coordinate2D(2, 2));

    glPushMatrix();
    
    {
        glRotated(-90, 0, 0, 1);
        glTranslated(-57.5, 30, 30);
        
        glPushName(DEFAULT_NAME);
        
        for (int i = 0; i < 3; i++) {
            glPushMatrix();
            
            {
                glTranslatef(0, i * 5, -5);
                glRotatef(90, 0, 1, 0);
                
                glLoadName(i * 500);		//  Replaces the value on top of the name stack
                
                obj->draw();
            }
            
            glPopMatrix();
        }
        
        auto tiles = LeBloq::getInstance().getCurrentGameState().getBoard().getScoredTiles();
        
        for (int r = 0; r < LeBloq::getInstance().getBoardSize().x; r++) {
            glPushMatrix();
            
            {
                glTranslatef(0, r * 2.2, 0);
                glLoadName(r);
                
                for (int c = 0; c < LeBloq::getInstance().getBoardSize().y; c++) {
                    glPushMatrix();
                    
                    {
                        glTranslatef(0, 0, (c + 1) * 2.2);
                        glRotatef(90, 0, 1, 0);
                        glPushName(c);
                        
                        for (LeBloqTile tile : tiles)
                            if (tile.position.x == r && tile.position.y == c) {
                                if (tile.scoringPlayer == 1) {
                                    //  Set Red (hypothetical) Color
                                } else {
                                    //  Set Blue (hypothetical) Color
                                }
                            }
                        
                        obj->draw();
                        
                        glPopName();
                    }
                    
                    glPopMatrix();
                }
            }
            
            glPopMatrix();
        }
    }
    
    glPopMatrix();
    
    delete obj;
    
#endif
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glutSwapBuffers();
    
    _criticalSection = false;
}

MainScene::~MainScene() {
    
}
