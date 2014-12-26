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
    
    _animatedRotation = nullptr;
    
    _lastUpdateValue = 0;
    
    _acsState = kACSUnchecked;
    
    _p1Appearance = new Appearance(1.0f);
    _p2Appearance = new Appearance(1.0f);
    //_defaultAppearance = new Appearance(1.0f);
    
    _p1Appearance->addComponent(new Component(kComponentTypeAmbient, color_red()));
    _p1Appearance->addComponent(new Component(kComponentTypeDiffuse, color_red()));
    _p1Appearance->addComponent(new Component(kComponentTypeSpecular, color_red()));
    
    _p2Appearance->addComponent(new Component(kComponentTypeAmbient, color_blue()));
    _p2Appearance->addComponent(new Component(kComponentTypeDiffuse, color_blue()));
    _p2Appearance->addComponent(new Component(kComponentTypeSpecular, color_blue()));
    
    //_defaultAppearance->addComponent(new Component(kComponentTypeAmbient, color_white()));
    //_defaultAppearance->addComponent(new Component(kComponentTypeDiffuse, color_white()));
    //_defaultAppearance->addComponent(new Component(kComponentTypeSpecular, color_white()));
    
    //  _defaultAppearance->setTexture(defaultTex);
    
    for (Appearance *appr : _anf->appearances)
        if (appr->getId() == "tile") {
            _defaultAppearance = appr;
            
            std::cout << "def appr set!" << std::endl;
        }
    
    /*for (Texture *tex : _anf->textures)
        if (tex->getId() == "field") {
            _defaultAppearance->setTexture(tex);
            
            break;
        }*/
    
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
    
#warning Disabled while the camera isn't fixed.
    
    /*  if (_animatedRotation)
        _animatedRotation->apply(); */
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

void MainScene::_animateLatestPlay() {
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
        
        _animatedRotation = new AnimatedRotation(180.0f, Coordinate3D(0, 1, 0), 60);
        
        _marker->setAnimation(ani);
    }
}

void MainScene::_computeAIPlay() {
    LeBloq::getInstance().performPlayAI();
    
    LeBloqBoard b = LeBloq::getInstance().getCurrentGameState().getBoard() - LeBloq::getInstance().getPreviousGameState().getBoard();
    
    LeBloq::getInstance().workingPiece = b.getPieces()[0];
    
    _animateLatestPlay();
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
    
    if (_acsState == kACSUnchecked) {
        for (Camera *cam : _anf->cameras) {
            if (cam->getId() == "Player 1")
                _acs1 = cam;
            else if (cam->getId() == "Player 2")
                _acs2 = cam;
        }
        
        _acsState = ((_acs1 != nullptr && _acs2 != nullptr) ? kACSEnabled : kACSDisabled);
        
        std::cout << "ACS State: " << _acsState << std::endl;
    }
    
    if (_acsState == kACSEnabled)
        if (!(_marker && _marker->getAnimation() && _marker->getAnimation()->getAnimating())) {
            _acs1->setEnabled(LeBloq::getInstance().getCurrentGameState().getPlayer() == 1);
            _acs2->setEnabled(LeBloq::getInstance().getCurrentGameState().getPlayer() == 2);
            
            //  Yes, I am aware this is here twice.
            
            _acs1->setEnabled(LeBloq::getInstance().getCurrentGameState().getPlayer() == 1);
            _acs2->setEnabled(LeBloq::getInstance().getCurrentGameState().getPlayer() == 2);
        }
    
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
        
        std::string message = "";
        
        if (LeBloq::getInstance().getCurrentGameState().getPlayer() < 3)
            message = "Congratulations, Player " + std::to_string(LeBloq::getInstance().getCurrentGameState().getPlayer()) + "!";
        else
            message = "It's a Tie!";
            
        Text *endText = new Text(message, Coordinate3D(60, 60, 60), {.r = 0.0f, .g = 1.0f, .b = 0.0f}, GLUT_BITMAP_TIMES_ROMAN_24);
        
        endText->draw();
        
        delete endText;
        
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
            
            _bd = new BoardDraw(_bdn, Coordinate3D(0.0, 0.0, 0.0), 2, 0); //  arbitrary values
        }
        
        bool animating = false;
        
        if (_marker && _marker->getAnimation() && _marker->getAnimation()->getAnimating()) {
            _bd->setOverride(LeBloq::getInstance().getPreviousGameState());
            
            animating = true;
        }
        
        if (!animating) {
            switch (LeBloq::getInstance().getGameType()) {
                case kLeBloqGameTypeAIVsAI:
                    
                    _computeAIPlay();
                    
                    break;
                    
                case kLeBloqGameTypePlayerVsAI_Easy:
                case kLeBloqGameTypePlayerVsAI_Hard:
                    
                    if (LeBloq::getInstance().getCurrentGameState().getPlayer() != 1)
                        _computeAIPlay();
                    
                    break;
                    
                default:
                    
                    break;
            }
        }
        
        if (_marker == nullptr)
            _marker = new PieceNode(*_bdn);
        
        _marker->setPiece(LeBloq::getInstance().workingPiece);
        
        glPopMatrix();
        
        if (Globals::getInstance().getLeBloqSettings() == nullptr)
            throw new MainSceneCreationException("Le Bloq settings not found!");
        
        glPushMatrix();
        
        {
            Coordinate3D markerPos = Globals::getInstance().getLeBloqSettings()->marker;
            
            glTranslated(markerPos.x, markerPos.y, markerPos.z);
            
            _marker->draw();
        }
        
        glPopMatrix();
        
        glPushMatrix();
        
        {
            Coordinate3D boardDraw = Globals::getInstance().getLeBloqSettings()->boardDraw;
            
            glTranslated(boardDraw.x, boardDraw.y, boardDraw.z);
            
            _bd->draw();
        }
        
        glPopMatrix();
        
        _defaultAppearance->apply();
        
        Rectangle *obj = new Rectangle(Coordinate2D(0, 0), Coordinate2D(2, 2));
        
        glPushMatrix();
        
        {
            for (Transform *t : Globals::getInstance().getLeBloqSettings()->transforms)
                t->apply();
            
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
                    //  glTranslatef(0, r * 2.2, 0);
                    glTranslatef(0, r * 2, 0);
                    glLoadName(r);
                    
                    for (int c = 0; c < LeBloq::getInstance().getBoardSize().y; c++) {
                        glPushMatrix();
                        
                        {
                            //  glTranslatef(0, 0, (c + 1) * 2.2);
                            glTranslatef(0, 0, (c + 1) * 2);
                            glRotatef(90, 0, 1, 0);
                            glPushName(c);
                            
                            _defaultAppearance->apply();
                            
                            for (LeBloqTile tile : tiles)
                                if (tile.position.x == r && tile.position.y == c) {
                                    
#warning For some reason, color isn't being changed correctly.
                                    
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
        
        delete obj;
        
    }
    
#endif
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glutSwapBuffers();
    
    _criticalSection = false;
}

MainScene::~MainScene() {
    
}
