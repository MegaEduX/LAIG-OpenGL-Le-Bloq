//
//  LeBloqPiece.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 29/11/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__LeBloqPiece__
#define __Project_1__LeBloqPiece__

#include "Coordinate.h"

#include "GraphicalException.h"

_BUILD_GRAPHICAL_EXCEPTION(InvalidPieceException, LeBloqException);

class LeBloqPiece {
    
public:
    
    Coordinate2D position;
    
    int type;
    
    char orientation;
    
    LeBloqPiece() {
        position = Coordinate2D();
        
        type = 1;
        
        orientation = 'v';
    }
    
    LeBloqPiece(Coordinate2D p, int t, int o) {
        position = p;
        
        type = t;
        
        orientation = o;
    }
    
    void toggleType() {
        if (type < 3)
            type++;
        else
            type = 1;
    }
    
    void toggleOrientation() {
        orientation = (orientation == 'v' ? 'h' : 'v');
    }
    
    Coordinate3D getDimensions() {
        if (orientation == 'v') {
            
            switch (type) {
                    
                case 1:
                    
                    return Coordinate3D(2, 4, 3);
                    
                case 2:
                    
                    return Coordinate3D(2, 3, 4);
                    
                case 3:
                    
                    return Coordinate3D(3, 2, 4);
                
                default:
                    
                    throw new InvalidPieceException("");
                    
            }
            
        } else if (orientation == 'h') {
            
            switch (type) {
                    
                case 1:
                    
                    return Coordinate3D(3, 4, 2);
                    
                case 2:
                    
                    return Coordinate3D(4, 3, 2);
                    
                case 3:
                    
                    return Coordinate3D(4, 2, 3);
                    
                default:
                    
                    throw new InvalidPieceException("");
                    
            }
            
        } else
            throw new InvalidPieceException("");
    }
    
};

#endif /* defined(__Project_1__LeBloqPiece__) */
