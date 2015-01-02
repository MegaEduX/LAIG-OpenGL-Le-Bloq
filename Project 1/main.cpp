//
//  main.cpp
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 23/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#include <iostream>

#include "CGFapplication.h"

#include "ANFLoader.h"

#include "ANFParser.h"

#include "MainScene.h"

#include "Interface.h"

#include "LeBloq.h"
#include "LeBloqReplay.h"

#define kUseDefaultPath 1

int main(int argc, const char * argv[]) {
    
    try {
        
        LeBloq::getInstance().newGame(10, 10);
        
    } catch (SocketCreationException *exception) {
        
        cout << "Couldn't connect to SICStus Le Bloq. Proceeding anyway..." << endl;
        
    }
    
    ANFResult *result = nullptr;
    
#if kUseDefaultPath
    
    ANFLoader::getInstance().setANFPath("/Users/MegaEduX/proj3-test/Final/1stScene.anf");
    
    result = ANFLoader::getInstance().loadANF();

#else
    
    while (true) {
        
        try {
            
            std::cout << "(Absolute/Relative) Path to ANF file: ";
            
            std::string anfPath;
            
            std::cin >> anfPath;
            
            ANFLoader::getInstance().setANFPath(anfPath);
            
            result = ANFLoader::getInstance().loadANF();
            
            break;
            
        } catch (ANFFileLoadParserException *exception) {
            
            std::cout << "Failed to load ANF file." << std::endl;
            
        }
        
    }
    
#endif
    
    try {
        
        CGFapplication app = CGFapplication();
        
        app.init(&argc, (const_cast<char **>(argv)));
        
        MainScene *scene = new MainScene(result);
        
        Interface *interface = new Interface(scene, result);
        
        scene->setInterface(interface);
        
        app.setScene(scene);
        app.setInterface(interface);
        
        app.run();
        
    } catch (MainSceneCreationException &ex) {
        
        cout << "Scene Creation Exception: " << ex.getDescription();
        
        return EXIT_FAILURE;
        
    } catch (GLexception& ex) {
        
        cout << "OpenGL Exception: " << ex.what();
        
        return EXIT_FAILURE;
        
    } catch (GraphicalException &ex) {
        
        cout << "Graphical Engine Exception: " << ex.getDescription();
        
        return EXIT_FAILURE;
    
    } catch (exception& ex) {
        
        cout << "Unexpected Exception: " << ex.what();
        
        return EXIT_FAILURE;
        
    }
    
    return EXIT_SUCCESS;
}
