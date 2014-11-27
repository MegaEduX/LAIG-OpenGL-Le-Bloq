//
//  SocketClient.cpp
//  Project 1
//
//  Created by Eduardo Almeida on 27/11/14.
//  Copyright (c) 2014 Eduardo Almeida. All rights reserved.
//

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

SocketClient::SocketClient(std::string host, int port) {
    struct sockaddr_in server;
    
    if ((_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        throw new SocketCreationException("Stream Socket Open Failure.");
    
    /* Connect socket using server name indicated in the command line */
    server.sin_family = AF_INET;
    
    struct hostent *hp = gethostbyname(host.c_str());
    
    if (hp == NULL)
        throw new SocketCreationException("DNS Query Failure.");
    
    memcpy((char *)&server.sin_addr, (char *)hp->h_addr, hp->h_length);
    server.sin_port = htons(port);
    
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
    
    std::cout << "[READ Debug]: " << buf << std::endl;
    
    return std::string(buf);
}

SocketClient::~SocketClient() {
    close(_sockfd);
}
