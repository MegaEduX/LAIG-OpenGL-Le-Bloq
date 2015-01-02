//
//  SocketClient.cpp
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 27/11/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#define SOCKETS_ENABLED 1

#include "SocketClient.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

char nclient[64];

#if SOCKETS_ENABLED

SocketClient::SocketClient(std::string host, int port) {
    struct sockaddr_in server;
    
    if ((_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        throw new SocketCreationException("Stream Socket Open Failure.");
    
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    
    struct hostent *hp = gethostbyname(host.c_str());
    
    if (hp == NULL)
        throw new SocketCreationException("DNS Query Failure.");
    
    memcpy((char *)&server.sin_addr, (char *)hp->h_addr, hp->h_length);
    
    if (connect(_sockfd, (struct sockaddr *)&server, sizeof server) < 0)
        throw new SocketCreationException("Connection Failure.");
}

void SocketClient::write(std::string data) {
    if (::write(_sockfd, data.c_str(), strlen(data.c_str()) + 1) < 0)
        throw new SocketWriteException("Write Failure.");
}

std::string SocketClient::read() {
    char *buf = (char *) malloc(4096 * sizeof(char));
    
    ::read(_sockfd, buf, 4096);
    
    std::string cppbuf = buf;
    
    std::string cleansed = cppbuf.substr(0, cppbuf.find(".", 0));
    
    return cleansed;
}

SocketClient::~SocketClient() {
    close(_sockfd);
}

#else

SocketClient::SocketClient(std::string host, int port) {}

void SocketClient::write(std::string data) {}

std::string SocketClient::read() {
    return "";
}

SocketClient::~SocketClient() {}

#endif
