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

#define NO_ANF_TEST_MODE    0
#define NO_ANF_CAMERAS      0

#define DRAW_AXIS           1

#define kPickingTest        1

#if kPickingTest

#define NUM_ROWS            12
#define NUM_COLS            12

#endif

MainScene::MainScene(ANFResult *result) {
    _anf = result;
    
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
    
    /*  for (int i = 0; i < _anf->animations.size(); i++)
        _anf->animations[i]->start();   */
    
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
    
    //  CGFscene::activeCamera->applyView();
    
#endif
    
#if DRAW_AXIS
    
    axis.draw();
    
#endif
    
#if NO_ANF_TEST_MODE
    
	Vehicle *veic = new Vehicle();

	veic -> draw();
	
	/*
     
    Rectangle *rect = new Rectangle(Coordinate2D(1, 2), Coordinate2D(7, 5));
    
    rect -> draw();
    
    Triangle *trg = new Triangle(Coordinate3D(5, 5, 1), Coordinate3D(2, 1, 1), Coordinate3D(8, 5, 1));
    
    trg -> draw();
    
    Sphere *sph = new Sphere(5, 20, 20);
    
    sph->draw();
    
    Torus *torus = new Torus(2, 3, 30, 10);
    
    torus->draw();
    
    delete rect;
    
    delete trg;
    
    delete sph;
    
    delete torus;
     
    */
    
#else
    
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
            n->draw(Globals::getInstance().getDrawingSettings());
        }
        
        glPopMatrix();
    }
    
#endif
    
#if kPickingTest
    
    Rectangle *obj = new Rectangle(Coordinate2D(0, 0), Coordinate2D(2, 2));

    glPushMatrix();
    
    {
        glRotated(-90, 0, 0, 1);
        
        glTranslated(-2, 2, 2);
        
        glPushName(-1);     //  Default Name
        
        for (int i=0; i< 3;i++) {
            glPushMatrix();
            glTranslatef(i*5,0,0);
            glLoadName(i*500);		//replaces the value on top of the name stack
            obj->draw();
            glPopMatrix();
        }
        
        for (int r = 0; r < NUM_ROWS; r++) {
            glPushMatrix();
            
            {
                glTranslatef(0, r * 2.2, 0);
                glLoadName(r);
                
                for (int c=0; c < NUM_COLS; c++) {
                    glPushMatrix();
                    
                    {
                        glTranslatef(0, 0, (c + 1) * 2.2);
                        glRotatef(90, 0, 1, 0);
                        glPushName(c);
                        
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
