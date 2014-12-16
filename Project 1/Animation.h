//
//  Animation.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 27/10/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__Animation__
#define __Project_1__Animation__

#include <iostream>

#include <vector>

#include <cmath>

#include "GraphicalObject.h"

#include "GraphicalMath.h"

#include "GraphicalException.h"

#include "Coordinate.h"

_BUILD_GRAPHICAL_EXCEPTION(AnimateException, GraphicalException);

typedef struct AnimationPreviousState {
    unsigned int stage;
    float angle;
} AnimationPreviousState;

class Animation : public GraphicalObject {
    
protected:
    
    bool _hidden;
    
    bool _animating;
    
    float _timeElapsed;
    
    float _span;
    
    Coordinate3D *_lastAnimationResult;
    
    float _lastRotation;
    
    AnimationPreviousState _ps;

	Animation() {
		_span = 0;
        
        _lastAnimationResult = nullptr;
        
        _lastRotation = 0;
        
        _animating = false;
        
        _ps.stage = 0;
        _ps.angle = 0;
	}
    
    Animation(std::string id) : GraphicalObject(id) {
        _span = 0;
        
        _lastAnimationResult = nullptr;
        
        _lastRotation = 0;
        
        _animating = false;
        
        _ps.stage = 0;
        _ps.angle = 0;
    }
    
public:
    
    Animation(std::string id, float span) : GraphicalObject(id) {
        _span = span;
        
        _lastAnimationResult = nullptr;
        
        _lastRotation = 0;
        
        _animating = false;
        
        _ps.stage = 0;
        _ps.angle = 0;
    }
    
    virtual void animate(float delta);
    
    Coordinate3D * getLastAnimationResult() {
        return _lastAnimationResult;
    }
    
    float getLastRotation() {
        return _lastRotation;
    }
    
    void reset() {
        _lastAnimationResult = nullptr;

        _lastRotation = 0;
        _timeElapsed = 0;

		_ps.stage = 0;
        _ps.angle = 0;
    }
    
    bool getAnimating() {
        return _animating;
    }
    
    virtual void start() {
        this->reset();
        
        this->resume();
    }
    
    void resume() {
        _animating = true;
    }
    
    void pause() {
        _animating = false;
    }
    
    virtual void stop() {
        this->reset();
        
        this->pause();
    }
    
    void setHidden(bool h) {
        _hidden = h;
    }
    
    bool getHidden() {
        return _hidden;
    }
    
};

class LinearAnimation : public Animation {
    
    std::vector<Coordinate3D> _controlPoints;
    
public:
    
    LinearAnimation(std::string id, float span) : Animation(id, span) {
        
    }
    
    void addControlPoint(Coordinate3D cp) {
        _controlPoints.push_back(cp);
    }
    
    bool removeControlPoint(Coordinate3D cp) {
        for (int i = 0; i < _controlPoints.size(); i++)
            if (_controlPoints[i] == cp) {
                _controlPoints.erase(_controlPoints.begin() + i);
                
                return true;
            }
        
        return false;
    }
    
    void animate(float delta);
    
};

class CircularAnimation : public Animation {
    
    Coordinate3D _center;
    
    float _radius;
    
    float _startAngle;
    
    float _rotationAngle;
    
    Coordinate3D _distanceToCentralPoint(float currentAngle) {
        return Coordinate3D(cos(currentAngle), 0, sin(currentAngle)) * Coordinate3D(_radius, _radius, _radius);
    }
    
public:
    
    CircularAnimation(std::string id, float span, Coordinate3D center, float radius, float startAngle, float rotationAngle) : Animation(id, span) {
        _center = center;
        
        _radius = radius;
        
        _startAngle = startAngle;
        
        _rotationAngle = rotationAngle;
    }
    
    void animate(float delta);
    
};

class CompositeAnimation : public Animation {
    
    int _currentAnimation;
    
    bool _currentAnimationSetup;
    
    std::vector<Animation *> _animations;
    
    std::vector<std::string> _animationRefs;

	void init() {
		_currentAnimation = 0;
        
        _currentAnimationSetup = false;
	}
    
public:
    
    CompositeAnimation(std::string id) : Animation(id) {
        init();
	}
    
    CompositeAnimation(std::string id, std::vector<Animation *> animations) : Animation(id) {
		init();

        _animations = animations;
    }
    
    CompositeAnimation(std::string id, std::vector<std::string> animationRefs) : Animation(id) {
		init();

        _animationRefs = animationRefs;
    }
    
    void addAnimation(Animation *a) {
        _animations.push_back(a);
    }
    
    void addAnimationRef(std::string ar) {
        _animationRefs.push_back(ar);
    }
    
    std::vector<std::string> getAnimationRefs() {
        return _animationRefs;
    }
    
    void start() {
        _currentAnimation = 0;
        
		_currentAnimationSetup = false;

        Animation::start();
    }
    
    void stop() {
        _currentAnimation = 0;

		_currentAnimationSetup = false;
        
        Animation::stop();
    }
    
    void animate(float delta);
    
};

#endif /* defined(__Project_1__Animation__) */
