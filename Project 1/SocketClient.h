//
//  SocketClient.h
//  Project 1
//
//  Created by Eduardo Almeida on 27/11/14.
//  Copyright (c) 2014 Eduardo Almeida. All rights reserved.
//

#ifndef __Project_1__SocketClient__
#define __Project_1__SocketClient__

#include <iostream>

#include "GraphicalException.h"

_BUILD_GRAPHICAL_EXCEPTION(SocketCreationException, GraphicalException);
_BUILD_GRAPHICAL_EXCEPTION(SocketWriteException, GraphicalException);
_BUILD_GRAPHICAL_EXCEPTION(SocketReadException, GraphicalException);

class SocketClient {
    
    int _sockfd;
    
public:
    
    
    SocketClient(std::string host, int port);
    
    std::string read();
    
    void write(std::string);
    
    ~SocketClient();
    
};

#endif /* defined(__Project_1__SocketClient__) */
