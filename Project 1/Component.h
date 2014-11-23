//
//  Component.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 29/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef Project_1_Component_h
#define Project_1_Component_h

typedef enum {
    kComponentTypeAmbient,
    kComponentTypeDiffuse,
    kComponentTypeSpecular
} kComponentType;

class Component {
    
    kComponentType _componentType;
    
    kColorRGB _color;
    
public:
    
    Component(kComponentType type, kColorRGB color) {
        _componentType = type;
        
        _color = color;
    }
    
    kComponentType getType() {
        //  Crashes here sometimes!
        
        return _componentType;
    }
    
    kColorRGB getColor() {
        return _color;
    }
    
};

#endif
