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

#include "Interface.h"

#define NO_ANF_CAMERAS    0

#define DRAW_AXIS         1

#define ENABLE_PICKING    1

#define DEFAULT_NAME    - 1

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
    
    _marker = nullptr;
    
    _lastUpdateValue = 0;
    
    _p1Appearance = new Appearance(1.0f);
    _p2Appearance = new Appearance(1.0f);
    _defaultAppearance = new Appearance(1.0f);
    
    _p1Appearance->addComponent(new Component(kComponentTypeAmbient, color_red()));
    _p1Appearance->addComponent(new Component(kComponentTypeDiffuse, color_red()));
    _p1Appearance->addComponent(new Component(kComponentTypeSpecular, color_red()));
    
    _p2Appearance->addComponent(new Component(kComponentTypeAmbient, color_blue()));
    _p2Appearance->addComponent(new Component(kComponentTypeDiffuse, color_blue()));
    _p2Appearance->addComponent(new Component(kComponentTypeSpecular, color_blue()));
    
    _defaultAppearance->addComponent(new Component(kComponentTypeAmbient, color_white()));
    _defaultAppearance->addComponent(new Component(kComponentTypeDiffuse, color_white()));
    _defaultAppearance->addComponent(new Component(kComponentTypeSpecular, color_white()));
    
    _setupFromANF();
    
    setUpdatePeriod(20);
}

void MainScene::update(unsigned long t) {
    double diff = (t - _lastUpdateValue) / 1000;
    
    _lastUpdateValue = t;
    
    for (int i = 0; i < _anf->animations.size(); i++)
        _anf->animations[i]->animate(diff);
    
    if (_marker && _marker->getAnimation())
        _marker->getAnimation()->animate(diff);
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

void MainScene::animateLatestPlay() {
    if (_marker) {
        Coordinate3D drawPos(30, 55, 30);
        Coordinate3D markerPos(50, 55, 22);
        
        int diff = 2 + 0.5;
        
        LeBloqBoard currentBoard = LeBloq::getInstance().getCurrentGameState().getBoard();
        LeBloqBoard latestBoard = LeBloq::getInstance().getPreviousGameState().getBoard();
        LeBloqBoard difference = currentBoard - latestBoard;
        
        LeBloqPiece p = difference.getPieces()[0];
        
        drawPos.x += p.position.x * diff;
        drawPos.z += p.position.y * diff;
        
        drawPos = drawPos - markerPos;
        
        LinearAnimation *ani = new LinearAnimation(1.0f);
        
        Coordinate3D stp = Coordinate3D(0, 0, 0);   //  replace with starting point
        Coordinate3D endp = drawPos;                //  replace with ending point
        
        ani->addControlPoint(stp);
        ani->addControlPoint(stp + Coordinate3D(0, 5, 0));
        ani->addControlPoint(endp + Coordinate3D(0, 5, 0));
        ani->addControlPoint(endp);
        
        ani->start();
        
        _marker->setAnimation(ani);
    }
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
    
    glMultMatrixf(_interface->getRotation());
    glTranslatef(0.0f, *(_interface->getZoom()), *(_interface->getZoom()));
    
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
    
    if (!LeBloq::getInstance().getCurrentGameState().getPlaying()) {
        
        Text *test = new Text("Game Over, Player 2 -> You SUCK!", Coordinate3D(0.0f, 0.0f, 0.0f), {.r = 0.0f, .g = 1.0f, .b = 0.0f}, GLUT_BITMAP_TIMES_ROMAN_24);
        
        test->draw();
        
    } else {
        
        if (_bd == nullptr) {
            _bdn = nullptr;
            
            for (Node *n : _anf->graphs[0]->getNodes()) {
                if (dynamic_cast<PieceNode *>(n)) {
                    _bdn = (PieceNode *) n;
                    
                    break;
                }
            }
            
            if (!_bdn) {
                std::cout << "This can not happen! Throw an exception here!" << std::endl;
                
                return;
            }
            
            _bd = new BoardDraw(_bdn, Coordinate3D(0.0, 0.0, 0.0), 2, 0.5); //  arbitrary values
        }
        
        bool animating = false;
        
        if (_marker && _marker->getAnimation() && _marker->getAnimation()->getAnimating()) {
            _bd->setOverride(LeBloq::getInstance().getPreviousGameState());
            
            animating = true;
        }
        
        if (!animating) {
            switch (LeBloq::getInstance().getGameType()) {
                case kLeBloqGameTypeAIVsAI:
                    
                    LeBloq::getInstance().performPlayAI();
                    
                    animateLatestPlay();
                    
                    break;
                    
                case kLeBloqGameTypePlayerVsAI_Easy:
                case kLeBloqGameTypePlayerVsAI_Hard:
                    
                    if (LeBloq::getInstance().getCurrentGameState().getPlayer() != 1) {
                        LeBloq::getInstance().performPlayAI();
                        
                        animateLatestPlay();
                    }
                    
                    break;
                    
                default:
                    
                    break;
            }
        }
        
        if (_marker == nullptr)
            _marker = new PieceNode(*_bdn);
        
        _marker->setPiece(LeBloq::getInstance().workingPiece);
        
        glPushMatrix();
        
        {
            //    where the piece will be placed
            //  this needs to stop being hardcoded
            
            glTranslated(50, 55, 22);
            
            _marker->draw();
        }
        
        glPopMatrix();
        
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
            
            std::vector<LeBloqTile> tiles = LeBloq::getInstance().getCurrentGameState().getBoard().getScoredTiles();
            
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
                            
                            _defaultAppearance->apply();
                            
                            for (LeBloqTile tile : tiles)
                                if (tile.position.x == r && tile.position.y == c) {
                                    if (tile.scoringPlayer == 1)
                                        _p1Appearance->apply();
                                    else if (tile.scoringPlayer == 2)
                                        _p2Appearance->apply();
                                    
                                    break;
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
        
        glPushMatrix();
        
        {
            ScoreView *scoreView = new ScoreView(0);
            
            scoreView->draw();
        }
        
        glPopMatrix();
        
        delete obj;
        
    }
    
#endif
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glutSwapBuffers();
    
    _criticalSection = false;
}

MainScene::~MainScene() {
    
}
