//
//  ANFLoader.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 14/10/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__ANFLoader__
#define __Project_1__ANFLoader__

#include <iostream>

#include "ANFResult.h"

class ANFLoader {
    
    ANFLoader() {};
    
    ANFLoader(ANFLoader const&);
    
    void operator=(ANFLoader const&);
    
    std::string _path;
    
public:
    
    static ANFLoader& getInstance() {
        static ANFLoader instance;
        
        return instance;
    }
    
    void setANFPath(std::string path) {
        _path = path;
    }
    
    ANFResult* loadANF();
    
};

#endif /* defined(__Project_1__ANFLoader__) */
