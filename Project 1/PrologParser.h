//
//  PrologParser.h
//  Project 1
//
//  Created by Eduardo Almeida on 27/11/14.
//  Copyright (c) 2014 Eduardo Almeida. All rights reserved.
//

#ifndef __Project_1__PrologParser__
#define __Project_1__PrologParser__

#include <iostream>
#include <vector>

class PrologParser {

public:
    
    static std::string boardRepresentationToProlog(std::vector<std::vector<int>>);
    
    static std::vector<std::vector<int>> prologToBoardRepresentation(std::string, int);
    
};

#endif /* defined(__Project_1__PrologParser__) */
