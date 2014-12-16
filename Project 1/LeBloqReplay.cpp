//
//  LeBloqReplay.cpp
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 30/11/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#include <cereal/archives/json.hpp>
#include <cereal/types/stack.hpp>

#include "LeBloqReplay.h"

std::string LeBloqReplay::createReplayData(std::stack<LeBloqState> states) {
    std::stringstream ss;
    
    {
        
        cereal::JSONOutputArchive oarchive(ss);
        
        oarchive(states);
        
    }
    
    return ss.str();
}

std::stack<LeBloqState> LeBloqReplay::loadReplayData(std::string replay) {
    std::stack<LeBloqState> output;
    
    std::istringstream stream(replay);
    
    {
        cereal::JSONInputArchive iarchive(stream);
        
        iarchive(output);
    }
    
    return output;
}
