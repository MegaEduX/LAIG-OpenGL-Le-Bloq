//
//  Global.cpp
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 23/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#include "Global.h"

void DrawingSettings::apply() {
    switch (_mode) {
            
        case kDrawingModeFill:
            
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            
            break;
            
        case kDrawingModeLine:
            
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            
            break;
            
        case kDrawingModePoint:
            
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            
            break;
            
        default:
            
            throw new GlobalSettingsApplyException("Unknown drawing mode!");
            
            break;
            
    }
    
    switch (_shading) {
        case kDrawingShadingFlat:
            
            glShadeModel(GL_FLAT);
            
            break;
            
        case kDrawingShadingGouraud:
            
            glShadeModel(GL_SMOOTH);
            
            break;
            
        default:
            
            throw new GlobalSettingsApplyException("Unknown shading mode!");
            
            break;
    }
    
    glClearColor(_background.r, _background.g, _background.b, _background.a);
}

void CullingSettings::apply() {
    switch (_order) {
            
        case kCullingOrderCounterClockWise:
            
            glFrontFace(GL_CCW);
            
            break;
            
        case kCullingOrderClockWise:
            
            glFrontFace(GL_CW);
            
            break;
            
        default:
            
            throw new CullingSettingsApplyException("Invalid Culling Order!");
            
            break;
            
    }
    
    if (_face != kCullingFaceNone) {
        glEnable(GL_CULL_FACE);
        
        switch (_face) {
                
            case kCullingFaceBack:
                
                glCullFace(GL_BACK);
                
                break;
                
            case kCullingFaceFront:
                
                glCullFace(GL_FRONT);
                
                break;
                
            case kCullingFaceBoth:
                
                glCullFace(GL_FRONT_AND_BACK);
                
                break;
                
            default:
                
                throw new CullingSettingsApplyException("Invalid Culling Face!");
                
                break;
                
        }
    } else
        glDisable(GL_CULL_FACE);
}

void LightingSettings::apply() {
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, _doubleSided);
    
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, _local);
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, color_to_float_vec(_ambient));
    
    if (_enabled)
        glEnable(GL_LIGHTING);
    else
        glDisable(GL_LIGHTING);
}

void Globals::applyAllSettings() {
    this->getDrawingSettings()->apply();
    
    this->getCullingSettings()->apply();
    
    this->getLightingSettings()->apply();
}
