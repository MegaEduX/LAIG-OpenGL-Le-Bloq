//
//  GraphicalObject.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 25/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__GraphicalObject__
#define __Project_1__GraphicalObject__

#include <iostream>

class GraphicalObject {
    
    std::string _id;
    
public:
    
    GraphicalObject() {
        _id = "";
    }
    
    GraphicalObject(std::string anId) {
        _id = anId;
    }
    
    std::string getId() {
        return _id;
    }
    
    void setId(std::string anId) {
        _id = anId;
    }
    
};

#endif /* defined(__Project_1__GraphicalObject__) */
