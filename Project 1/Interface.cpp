//
//  Interface.cpp
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 02/10/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#include "Interface.h"

#include "Global.h"

#include "Animation.h"

void Interface::initGUI() {
    GLUI_Panel *drawingPanel = addPanel(const_cast<char *>(std::string("Drawing Style").c_str()), 1);
    
    int id = 0;
    
    addButtonToPanel(drawingPanel, const_cast<char *>(std::string("Point").c_str()), kDrawingModePoint);
    
    addButtonToPanel(drawingPanel, const_cast<char *>(std::string("Line").c_str()), kDrawingModeLine);
    
    addButtonToPanel(drawingPanel, const_cast<char *>(std::string("Fill").c_str()), kDrawingModeFill);
    
    addColumn();
    
    GLUI_Panel *lightsPanel = addPanel(const_cast<char *>(std::string("Lights").c_str()), 1);
    
    id = 10;
    
	for (int i = 0; i < _result->lights.size(); i++) {
		Light *l = _result->lights[i];

        GLUI_Checkbox *checkbox = addCheckboxToPanel(lightsPanel, const_cast<char *>(l->getId().c_str()), nullptr, id);
        
        checkbox->set_int_val(l->getEnabled() ? 1 : 0);
        
        id++;
    }
    
    addColumn();
    
    GLUI_Panel *camerasPanel = addPanel(const_cast<char *>(std::string("Camera").c_str()), 1);
    
    id = 100;
    
	for (int i = 0; i < _result->cameras.size(); i++) {
		Camera *c = _result->cameras[i];

        addButtonToPanel(camerasPanel, const_cast<char *>(c->getId().c_str()), id);
        
        id++;
    }
    
    addColumn();
    
    GLUI_Panel *animatePanel = addPanel(const_cast<char *>(std::string("Animate").c_str()), 1);
    
    id = 200;
    
    for (int i = 0; i < _result->animations.size(); i++) {
        Animation *a = _result->animations[i];
        
        if (!a->getHidden())
            addButtonToPanel(animatePanel, const_cast<char *>(a->getId().c_str()), id);
        
        id++;
    }
    
    addColumn();
    
    id = 300;
    
    GLUI_Panel *windPanel = addPanel(const_cast<char *>(std::string("Wind").c_str()), 1);
    
    GLUI_Spinner *spinner = addSpinnerToPanel(windPanel, const_cast<char *>(std::string("Wind").c_str()), 2, NULL, id);
    
    spinner->set_int_limits(0, 9);
    
    spinner->set_int_val(0);
    
    addColumn();
    
    id = 400;
    
    GLUI_Panel *dpPanel = addPanel(const_cast<char *>(std::string("Display Lists").c_str()), 1);
    
    GLUI_Checkbox *checkbox = addCheckboxToPanel(dpPanel, const_cast<char *>("Use"), nullptr, id);
    
    checkbox->set_int_val(1);
}

void Interface::processGUI(GLUI_Control *ctrl) {
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
        
    } else if (ctrl->user_id == 300)
        
        Globals::getInstance().getShadingSettings()->setWind(ctrl->int_val);
    
    else if (ctrl->user_id == 400)
        
        Globals::getInstance().getDrawingSettings()->setUseDisplayLists(ctrl->int_val ? true : false);

    else {
        
        int aniPos = (int)(ctrl->user_id - 200);
        
        if (_result->animations.size() <= aniPos)
            throw new AnimationNotFoundException("Animation not found!");
        
        _result->animations[aniPos]->start();
    }
}
