//
//  ReferenceParser.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 30/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__ReferenceParser__
#define __Project_1__ReferenceParser__

#include <stdio.h>

#include "ANFResult.h"

#include "GraphicalEngine.h"

_BUILD_GRAPHICAL_EXCEPTION(ReferenceParserException, GraphicalException);

class ReferenceParser {
    
public:
    
    static void parseReferences(ANFResult *);
    
};

#endif /* defined(__Project_1__ReferenceParser__) */
