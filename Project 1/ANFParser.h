//
//  ANFParser.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 23/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__ANFParser__
#define __Project_1__ANFParser__

#include <iostream>

#include <vector>

#include "tinyxml.h"

#include "GraphicalEngine.h"

#include "ANFResult.h"

#include "GraphicalException.h"

_BUILD_GRAPHICAL_EXCEPTION(ANFParserException, GraphicalException);
_BUILD_GRAPHICAL_EXCEPTION(ANFFileLoadParserException, ANFParserException);
_BUILD_GRAPHICAL_EXCEPTION(ANFGlobalsParserException, ANFParserException);
_BUILD_GRAPHICAL_EXCEPTION(ANFNodeParserException, ANFParserException);
_BUILD_GRAPHICAL_EXCEPTION(ANFAppearanceParserException, ANFParserException);
_BUILD_GRAPHICAL_EXCEPTION(ANFTextureParserException, ANFParserException);
_BUILD_GRAPHICAL_EXCEPTION(ANFCameraParserException, ANFParserException);
_BUILD_GRAPHICAL_EXCEPTION(ANFLightParserException, ANFParserException);
_BUILD_GRAPHICAL_EXCEPTION(ANFAnimationParserException, ANFParserException);

class ANFParser {
    
    TiXmlDocument *_doc;
    
    std::string _basePath;
    
    void _setBasePathFromANFPath(std::string anfPath);
    
    void parseGlobals(TiXmlElement *);
    
    Graph* parseGraph(TiXmlElement *);
    Node *parseNode(TiXmlElement *);
    
    std::vector<Transform *> parseTransforms(TiXmlElement *);
    std::vector<Primitive *> parsePrimitives(TiXmlElement *);
    std::vector<Appearance *> parseAppearances(TiXmlElement *);
    std::vector<Texture *> parseTextures(TiXmlElement *);
    std::vector<Camera *> parseCameras(TiXmlElement *);
    std::vector<Light *> parseLights(TiXmlElement *);
    std::vector<Animation *> parseAnimations(TiXmlElement *);
    
    Component* parseComponent(TiXmlElement *);
    Texture* parseTexture(TiXmlElement *);
    
public:
    
    ANFParser(std::string path);
    
    ANFResult* parse();
    
};

#endif /* defined(__Project_1__ANFParser__) */
