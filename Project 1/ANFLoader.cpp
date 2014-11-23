//
//  ANFLoader.cpp
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 14/10/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#include "ANFLoader.h"

#include "ANFParser.h"

#include "ReferenceParser.h"

ANFResult* ANFLoader::loadANF() {
    ANFResult *result = nullptr;
    
    try {
        
        ANFParser *parser = new ANFParser(_path);
        
        result = parser->parse();
        
        ReferenceParser::parseReferences(result);
        
    } catch (ANFFileLoadParserException *exception) {
        
        throw exception;
    
    } catch (ANFGlobalsParserException *exception) {
        
        std::cout << "ANF Globals Parser Exception: " << exception->getDescription() << std::endl;
        
        exit(EXIT_FAILURE);
        
    } catch (ANFNodeParserException *exception) {
        
        std::cout << "ANF Node Parser Exception: " << exception->getDescription() << std::endl;
        
        exit(EXIT_FAILURE);
        
    } catch (RotateException *exception) {
        
        std::cout << "Rotate Exception: " << exception->getDescription() << std::endl;
        
        exit(EXIT_FAILURE);
        
    } catch (ANFParserException *exception) {
        
        std::cout << "ANF Parser Exception: " << exception->getDescription() << std::endl;
        
        exit(EXIT_FAILURE);
        
    } catch (GraphicalException *exception) {
        
        std::cout << "Generic Graphical Exception: " << exception->getDescription() << std::endl;
        
        exit(EXIT_FAILURE);
        
    }
    
    return result;
}
