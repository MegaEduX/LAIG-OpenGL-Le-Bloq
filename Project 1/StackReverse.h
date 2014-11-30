//
//  StackReverse.h
//  Project 1
//
//  Created by Eduardo Almeida on 30/11/14.
//  Copyright (c) 2014 Eduardo Almeida. All rights reserved.
//

#ifndef Project_1_StackReverse_h
#define Project_1_StackReverse_h

#include <iostream>

#include <stack>

template <typename T>

std::stack<T> reverseStack(std::stack<T> stackToReverse) {
    std::stack<T> returnStack;
    
    while (stackToReverse.size()) {
        returnStack.push(stackToReverse.top());
        
        stackToReverse.pop();
    }
    
    return returnStack;
}

#endif
