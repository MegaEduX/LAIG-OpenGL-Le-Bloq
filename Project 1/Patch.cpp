//
//  Patch.cpp
//  Project 1
//
//  Created by Eduardo Almeida on 02/01/15.
//  Copyright (c) 2015 Eduardo Almeida. All rights reserved.
//

#include "Patch.h"

void Patch::draw() {
    glPushMatrix();
    
    {
        kCullingOrder co = Globals::getInstance().getCullingSettings()->getCullingOrder();
        kCullingFace cf = Globals::getInstance().getCullingSettings()->getCullingFace();
        
        Globals::getInstance().setCullingSettings(new CullingSettings(cf, kCullingOrderClockWise));
        
        glEnable(GL_AUTO_NORMAL);
        
        float *points = Coordinate3D::vectorToFloatVector(_controlPoints);
        
        glMap2f(GL_MAP2_VERTEX_3, 0.0,
                1.0, 3, _order + 1, 0.0,
                1.0, 3 * (_order + 1), _order + 1,
                points);
        
        std::vector<Coordinate2D> tc;
        
        switch (_order) {
                
            case 1:
                
                tc.push_back(Coordinate2D(0.0, 1.0));
                tc.push_back(Coordinate2D(1.0, 1.0));
                
                tc.push_back(Coordinate2D(0.0, 0.0));
                tc.push_back(Coordinate2D(1.0, 0.0));
                
                break;
                
            case 2:
                
                tc.push_back(Coordinate2D(0.0, 1.0));
                tc.push_back(Coordinate2D(0.5, 1.0));
                tc.push_back(Coordinate2D(1.0, 1.0));
                
                tc.push_back(Coordinate2D(0.0, 0.5));
                tc.push_back(Coordinate2D(0.5, 0.5));
                tc.push_back(Coordinate2D(1.0, 0.5));
                
                tc.push_back(Coordinate2D(0.0, 0.0));
                tc.push_back(Coordinate2D(0.5, 0.0));
                tc.push_back(Coordinate2D(1.0, 0.0));
                
                break;
                
            case 3:
                
                tc.push_back(Coordinate2D(0.0,          1.0));
                tc.push_back(Coordinate2D(1.0 / 3.0,    1.0));
                tc.push_back(Coordinate2D(2.0 / 3.0,    1.0));
                tc.push_back(Coordinate2D(1.0,          1.0));
                
                tc.push_back(Coordinate2D(0.0,          2.0 / 3.0));
                tc.push_back(Coordinate2D(1.0 / 3.0,    2.0 / 3.0));
                tc.push_back(Coordinate2D(2.0 / 3.0,    2.0 / 3.0));
                tc.push_back(Coordinate2D(1.0,          2.0 / 3.0));
                
                tc.push_back(Coordinate2D(0.0,          1.0 / 3.0));
                tc.push_back(Coordinate2D(1.0 / 3.0,    1.0 / 3.0));
                tc.push_back(Coordinate2D(2.0 / 3.0,    1.0 / 3.0));
                tc.push_back(Coordinate2D(1.0,          1.0 / 3.0));
                
                tc.push_back(Coordinate2D(0.0,          0.0));
                tc.push_back(Coordinate2D(1.0 / 3.0,    0.0));
                tc.push_back(Coordinate2D(2.0 / 3.0,    0.0));
                tc.push_back(Coordinate2D(1.0,          0.0));
                
                break;
                
            default:
                
                throw new InvalidDrawException("Invalid draw order.");
                
                break;
        }
        
        glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0,
                1.0, 2, (_order + 1), 0.0,
                1.0, (_order + 1) * 2, (_order + 1),
                Coordinate2D::vectorToFloatVector(tc));
        
        glEnable(GL_MAP2_VERTEX_3);
        glEnable(GL_MAP2_NORMAL);
        glEnable(GL_MAP2_TEXTURE_COORD_2);
        
        glMapGrid2f(_parts.x, 0.0, 1.0, _parts.y, 0.0, 1.0);
        
        glShadeModel(GL_SMOOTH);
        
        glEvalMesh2((_compute == kPatchComputeFill ? GL_FILL : (_compute == kPatchComputeLine ? GL_LINE : GL_POINT)), 0, _parts.x, 0, _parts.y);
        
        glDisable(GL_AUTO_NORMAL);
        
        Globals::getInstance().setCullingSettings(new CullingSettings(cf, co));
    }
    
    glPopMatrix();
}