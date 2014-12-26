//
//  Interface.cpp
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 02/10/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#include <map>

#include "Interface.h"

#include "Global.h"

#include "Animation.h"

#include "LeBloq.h"
#include "LeBloqReplay.h"

//  Picking Buffer

#define BUFSIZE 256

GLuint selectBuf[256];

void Interface::initGUI() {
    int id = 0;
    
    GLUI_Panel *lightsPanel = addPanel(const_cast<char *>(std::string("Lights").c_str()), 1);
    
    id = 10;
    
	for (int i = 0; i < _result->lights.size(); i++) {
		Light *l = _result->lights[i];

        GLUI_Checkbox *checkbox = addCheckboxToPanel(lightsPanel, const_cast<char *>(l->getId().c_str()), nullptr, id);
        
        checkbox->set_int_val(l->getEnabled() ? 1 : 0);
        
        id++;
    }
    
    addColumn();
    
    id = 500;
    
    GLUI_Panel *levelPanel = addPanel(const_cast<char *>(std::string("Difficulty").c_str()), 1);
    
    _difficultyRadioGroup = addRadioGroupToPanel(levelPanel);
    
    _difficultyRadioGroup->set_id(id);
    
    GLUI_RadioButton *PvAI_Easy = addRadioButtonToGroup(_difficultyRadioGroup, const_cast<char *>(std::string("Player vs AI (Easy)").c_str()));
    
    PvAI_Easy->set_int_val(1);
    
    GLUI_RadioButton *PvAI_Hard = addRadioButtonToGroup(_difficultyRadioGroup, const_cast<char *>(std::string("Player vs AI (Hard)").c_str()));
    
    PvAI_Hard->set_int_val(0);
    
    GLUI_RadioButton *PvP = addRadioButtonToGroup(_difficultyRadioGroup, const_cast<char *>(std::string("Player vs Player").c_str()));
    
    PvP->set_int_val(0);
    
    GLUI_RadioButton *AIvAI = addRadioButtonToGroup(_difficultyRadioGroup, const_cast<char *>(std::string("AI vs AI").c_str()));
    
    AIvAI->set_int_val(0);
    
    addColumn();
    
    id = 600;
    
    GLUI_Panel *gcPanel = addPanel(const_cast<char *>(std::string("Control").c_str()), 1);
    
    addButtonToPanel(gcPanel, const_cast<char *>(std::string("New Game").c_str()), id++);
    
    addButtonToPanel(gcPanel, const_cast<char *>(std::string("Undo Move").c_str()), id++);
    
    GLUI_Panel *rcPanel = addPanel(const_cast<char *>(std::string("Replays").c_str()), 1);
    
    addButtonToPanel(rcPanel, const_cast<char *>(std::string("Load Replay").c_str()), id++);
    
    addButtonToPanel(rcPanel, const_cast<char *>(std::string("Save Replay").c_str()), id++);
    
    addColumn();
    
    id = 700;
    
    GLUI_Panel *ccPanel = addPanel(const_cast<char *>(std::string("Camera Control").c_str()), 1);
    
    GLUI_Rotation *rot = addRotationToPanel(ccPanel, const_cast<char *>(std::string("Board").c_str()), _liveRotation);
    
    rot->set_spin(1.0f);
    
    rot->reset();
    
    GLUI_Translation *zoom = addTranslationToPanel(ccPanel, const_cast<char *>(std::string("Zoom").c_str()), GLUI_TRANSLATION_Y, _liveZoom);
    
    zoom->set_speed(0.2f);
}

void Interface::processGUI(GLUI_Control *ctrl) {
    if (ctrl->user_id == -1)
        return;
    
    if (ctrl->user_id < 10) {
        
        DrawingSettings *ds = Globals::getInstance().getDrawingSettings();
        
        ds->setMode((kDrawingMode) ctrl->user_id);
        
        ds->apply();
        
        Globals::getInstance().setDrawingSettings(ds);
        
    } else if (ctrl->user_id < 100) {
        
        int lightPos = (int)(ctrl->user_id - 10);
        
        if (_result->lights.size() <= lightPos)
            throw new LightNotFoundException("Light not found!");
        
        _result->lights[lightPos]->toggle();
        
    } else if (ctrl->user_id < 200) {
        
        int camPos = (int)(ctrl->user_id - 100);
        
        if (_result->cameras.size() <= camPos)
            throw new CameraNotFoundException("Camera not found!");
        
		for (int i = 0; i < _result->cameras.size(); i++) {
			Camera *c = _result->cameras[i];
			
            if (c->getEnabled()) {
                c->setEnabled(false);
                
                break;
            }
		}
        
        _result->cameras[camPos]->setEnabled(true);
        
    } else if (ctrl->user_id < 300) {
            
        int aniPos = (int)(ctrl->user_id - 200);
            
        if (_result->animations.size() <= aniPos)
            throw new AnimationNotFoundException("Animation not found!");
            
        _result->animations[aniPos]->start();
        
    } else if (ctrl->user_id == 300)
        
        Globals::getInstance().getShadingSettings()->setWind(ctrl->int_val);
    
    else if (ctrl->user_id == 400)
        
        Globals::getInstance().getDrawingSettings()->setUseDisplayLists(ctrl->int_val ? true : false);
    
    else if (ctrl->user_id < 600) {
        
        _selectedDifficulty = _difficultyRadioGroup->get_int_val();
        
        std::cout << "Selected Difficulty: " << _selectedDifficulty << std::endl;
        
    } else if (ctrl->user_id < 700) {
        
        switch (ctrl->user_id) {
                
            case 600:
                
                LeBloq::getInstance().setGameType((kLeBloqGameType) _difficultyRadioGroup->get_int_val());
                LeBloq::getInstance().newGame(10, 10);
                
                break;
                
            case 601:
                
                if (LeBloq::getInstance().getGameStates().size())
                    LeBloq::getInstance().undo();
                
                break;
                
            case 602:
                
                //  Load Replay
                
                try {
                    
                }
                
                break;
                
            case 603: {
                
                //  Save Replay
                
                try {
                    
                    std::string replayData = LeBloqReplay::createReplayData(LeBloq::getInstance().getGameStates());
                    
                    std::cout << "Save As: ";
                    
                    std::string outputFilePath;
                    
                    std::cin >> outputFilePath;
                    
                    std::ofstream out(outputFilePath);
                    
                    out << replayData;
                    
                    out.close();
                    
                } catch (std::exception exception) {
                    
                    std::cout << "An error has occoured while exporting the current game." << std::endl;
                    
                }
                
                break;
                
            }
                
            default:
                
                break;
        }
        
        //  game control
        
        std::cout << "game control" << std::endl;
        
    } else if (ctrl->user_id < 800) {
        
        //  camera control
        
        std::cout << "camera control" << std::endl;
        
        //  float ballRotation[16];
        
        //  _cameraRotationControl->get_float_array_val(ballRotation);
        
        std::cout << "rot" << std::endl;
        
    } else
        
        throw new InternalInconsistencyException("Unknown ctrl->user_id!");
}

void Interface::processMouse(int button, int state, int x, int y) {
    CGFinterface::processMouse(button,state, x, y);
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        performPicking(x, y);
}

void Interface::performPicking(int x, int y) {
    // Sets the buffer to be used for selection and activate selection mode
    glSelectBuffer (BUFSIZE, selectBuf);
    glRenderMode(GL_SELECT);
    
    // Initialize the picking name stack
    glInitNames();
    
    // The process of picking manipulates the projection matrix
    // so we will be activating, saving and manipulating it
    glMatrixMode(GL_PROJECTION);
    
    //store current projmatrix to restore easily in the end with a pop
    glPushMatrix ();
    
    //get the actual projection matrix values on an array of our own to multiply with pick matrix later
    GLfloat projmat[16];
    glGetFloatv(GL_PROJECTION_MATRIX,projmat);
    
    // reset projection matrix
    glLoadIdentity();
    
    // get current viewport and use it as reference for
    // setting a small picking window of 5x5 pixels around mouse coordinates for picking
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    
    // this is multiplied in the projection matrix
    gluPickMatrix ((GLdouble) x, (GLdouble) (CGFapplication::height - y), 5.0, 5.0, viewport);
    
    // multiply the projection matrix stored in our array to ensure same conditions as in normal render
    glMultMatrixf(projmat);
    
    // force scene drawing under this mode
    // only the names of objects that fall in the 5x5 window will actually be stored in the buffer
    scene->display();
    
    // restore original projection matrix
    glMatrixMode (GL_PROJECTION);
    glPopMatrix ();
    
    glFlush();
    
    // revert to render mode, get the picking results and process them
    GLint hits;
    hits = glRenderMode(GL_RENDER);
    processHits(hits, selectBuf);
}

void Interface::processHits(GLint hits, GLuint buffer[]) {
    GLuint *ptr = buffer;
    GLuint mindepth = 0xFFFFFFFF;
    GLuint *selected = NULL;
    GLuint nselected = 0;
    
    // iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
    for (int i=0;i<hits;i++) {
        int num = *ptr; ptr++;
        GLuint z1 = *ptr; ptr++;
        ptr++;
        if (z1 < mindepth && num>0) {
            mindepth = z1;
            selected = ptr;
            nselected=num;
        }
        for (int j=0; j < num; j++)
            ptr++;
    }
    
    if (selected!=NULL) {
        if (nselected == 1) {
            
            if (selected[0] == 500)
                LeBloq::getInstance().workingPiece.toggleType();
            else if (selected[0] == 1000)
                LeBloq::getInstance().workingPiece.toggleOrientation();
                
        } else if (nselected == 2) {
            
            std::cout << "Clicked on Coordinate2D(" << selected[0] << ", " << selected[1] << ")." << std::endl;
            
            LeBloq::getInstance().workingPiece.position = Coordinate2D(selected[0], selected[1]);
            
            try {
                
                LeBloq::getInstance().performPlay();
                
                if (_scene->getMarker()) {
                    Coordinate3D drawPos(30, 55, 30);
                    Coordinate3D markerPos(50, 55, 22);
                    
                    int diff = 2 + 0.5;
                    
                    drawPos.x += selected[0] * diff;
                    drawPos.z += selected[1] * diff;
                    
                    drawPos = drawPos - markerPos;
                    
                    LinearAnimation *ani = new LinearAnimation(1.0f);
                    
                    Coordinate3D stp = Coordinate3D(0, 0, 0);   //  replace with starting point
                    Coordinate3D endp = drawPos;                //  replace with ending point
                    
                    ani->addControlPoint(stp);
                    ani->addControlPoint(stp + Coordinate3D(0, 5, 0));
                    ani->addControlPoint(endp + Coordinate3D(0, 5, 0));
                    ani->addControlPoint(endp);
                    
                    ani->start();
                    
                    _scene->getMarker()->setAnimation(ani);
                }
                
            } catch (LeBloqBoardPlayException *exc) {
                
                std::cout << "Invalid Play!" << std::endl;
                
            }
            
        }
    }
}
