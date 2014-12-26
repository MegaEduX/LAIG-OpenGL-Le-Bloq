//
//  Global.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 23/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__Global__
#define __Project_1__Global__

#include <iostream>

#include "Color.h"

#include "CGFobject.h"

#include "GraphicalException.h"

#include "Coordinate.h"

#include "Transform.h"

_BUILD_GRAPHICAL_EXCEPTION(GlobalSettingsApplyException, GraphicalException);
_BUILD_GRAPHICAL_EXCEPTION(DrawingSettingsApplyException, GlobalSettingsApplyException);
_BUILD_GRAPHICAL_EXCEPTION(CullingSettingsApplyException, GlobalSettingsApplyException);
_BUILD_GRAPHICAL_EXCEPTION(LightingSettingsApplyException, GlobalSettingsApplyException);

class Global {
    
public:
    
    virtual void apply() {
        
    }
    
};

//
//  Drawing Settings
//

typedef enum {
    kDrawingModeFill,
    kDrawingModeLine,
    kDrawingModePoint
} kDrawingMode;

typedef enum {
    kDrawingShadingFlat,
    kDrawingShadingGouraud
} kDrawingShading;

class DrawingSettings {
    
    kDrawingMode _mode;
    
    kDrawingShading _shading;
    
    kColorRGB _background;
    
    bool _useDL;
    
public:
    
    DrawingSettings(kDrawingMode mode, kDrawingShading shading, kColorRGB background) {
        _mode = mode;
        _shading = shading;
        _background = background;
        
        _useDL = true;
    }
    
    void apply();
    
    kDrawingMode getMode() {
        return _mode;
    }
    
    void setMode(kDrawingMode mode) {
        _mode = mode;
    }
    
    bool useDisplayLists() {
        return _useDL;
    }
    
    void setUseDisplayLists(bool dl) {
        _useDL = dl;
        
    }
    
    bool getSmooth() {
        return (_shading == kDrawingShadingGouraud);
    }
};

//
//  Culling Settings
//

typedef enum {
    kCullingFaceNone,
    kCullingFaceBack,
    kCullingFaceFront,
    kCullingFaceBoth
} kCullingFace;

typedef enum {
    kCullingOrderCounterClockWise,
    kCullingOrderClockWise
} kCullingOrder;

class CullingSettings {
    
    kCullingFace _face;
    
    kCullingOrder _order;
    
public:
    
    CullingSettings(kCullingFace face, kCullingOrder order) {
        _face = face;
        _order = order;
    }
    
    void apply();
    
    kCullingFace getCullingFace() {
        return _face;
    }
    
    kCullingOrder getCullingOrder() {
        return _order;
    }
};

//
//  Lighting Setings
//

class LightingSettings {
    
    bool _doubleSided;
    bool _local;
    bool _enabled;
    
    kColorRGB _ambient;
    
public:
    
    LightingSettings(bool doubleSided, bool local, bool enabled, kColorRGB ambient) {
        _doubleSided = doubleSided;
        _local = local;
        _enabled = enabled;
        
        _ambient = ambient;
    }
    
    void apply();
};

//
//  Global Settings Holder
//

class ShadingSettings {
    
    std::string _fragPath;
    std::string _vertPath;
    
    unsigned int _wind;
    
public:
    
    ShadingSettings(std::string fragPath, std::string vertPath) {
        _fragPath = fragPath;
        _vertPath = vertPath;
        
        _wind = 0;
    }
    
    std::string getFragPath() {
        return _fragPath;
    }
    
    std::string getVertPath() {
        return _vertPath;
    }
    
    void setWind(unsigned int w) {
        _wind = w;
    }
    
    unsigned int getWind() {
        return _wind;
    }
    
};

class LeBloqSettings {
    
public:
    
    Coordinate3D marker;
    Coordinate3D boardDraw;
    
    std::vector<Transform *> transforms;
};

class Globals {
    
    std::string _basePath;
    
    DrawingSettings *_ds;
    CullingSettings *_cs;
    LightingSettings *_ls;
    ShadingSettings *_es;
    LeBloqSettings *_lbs;
    
    Globals() {};
    
    Globals(Globals const&);
    
    void operator=(Globals const&);
    
public:
    
    static Globals& getInstance() {
        static Globals instance;
        
        return instance;
    }
    
    void setDrawingSettings(DrawingSettings *ds) {
        _ds = ds;
    }
    
    void setCullingSettings(CullingSettings *cs) {
        _cs = cs;
    }
    
    void setLightingSettings(LightingSettings *ls) {
        _ls = ls;
    }
    
    void setShadingSettings(ShadingSettings *es) {
        _es = es;
    }
    
    void setLeBloqSettings(LeBloqSettings *lbs) {
        _lbs = lbs;
    }
    
    DrawingSettings *getDrawingSettings() {
        return _ds;
    }
    
    CullingSettings *getCullingSettings() {
        return _cs;
    }
    
    LightingSettings *getLightingSettings() {
        return _ls;
    }
    
    ShadingSettings *getShadingSettings() {
        return _es;
    }
    
    LeBloqSettings *getLeBloqSettings() {
        return _lbs;
    }
    
    void setBasePath(std::string bp) {
        _basePath = bp;
    }
    
    std::string getBasePath() {
        return _basePath;
    }
    
    void applyAllSettings();
    
};

#endif /* defined(__Project_1__Global__) */
