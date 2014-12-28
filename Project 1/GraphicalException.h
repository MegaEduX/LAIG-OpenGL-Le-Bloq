//
//  GraphicalException.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 27/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef Project_1_GraphicalException_h
#define Project_1_GraphicalException_h

class GraphicalException {
    
    std::string _description;
    
    int _code;
    
public:
    
    GraphicalException(std::string description, int code = 1) {
        _description = description;
        
        _code = 1;
    }
    
    std::string getDescription() {
        return _description;
    }
    
    int getCode() {
        return _code;
    }
    
};

#define _BUILD_GRAPHICAL_EXCEPTION(name, superclass)    class name : public superclass {    \
                                                            public: \
                                                                name(std::string description, int code = 1) : superclass(description, code) {  \
                                                                        \
                                                                }   \
                                                                name(int code = 1) : superclass("", code) { \
                                                                        \
                                                                }   \
                                                        };

_BUILD_GRAPHICAL_EXCEPTION(LeBloqException, GraphicalException);

#endif
