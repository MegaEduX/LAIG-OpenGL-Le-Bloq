//
//  ANFResult.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 24/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

/*
 *  This is a data-only class, which is why we felt no need to include getters/setters.
 */

#ifndef Project_1_ANFResult_h
#define Project_1_ANFResult_h

#include "Global.h"

#include "Appearance.h"

#include "Texture.h"

#include "Camera.h"

#include "Light.h"

#include "Animation.h"

class Graph;

class ANFResult {
    
public:
    
    //  Globals *globals;
    
    std::vector<Graph *> graphs;
    
    std::vector<Appearance *> appearances;
    
    std::vector<Texture *> textures;
    
    std::vector<Camera *> cameras;
    
    std::vector<Light *> lights;
    
    std::vector<Animation *> animations;
    
};

#endif
