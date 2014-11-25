//
//  Animation.cpp
//  Project 1
//
//  Created by Eduardo Almeida on 27/10/14.
//  Copyright (c) 2014 Eduardo Almeida. All rights reserved.
//

#include "Animation.h"

void Animation::animate(float delta) {
    throw new AnimateException("Unknown animation type!");
}

void LinearAnimation::animate(float delta) {
    if (!_animating)
        return;
    
    if (_timeElapsed >= _span) {
        _animating = false;
        
        return;
    }
    
    if (_controlPoints.size() < 2)
        throw new AnimateException("Insufficient control points!");
    
    _timeElapsed += delta;
    
    float controlPointDelta = _span / (_controlPoints.size() - 1);
    float timeElapsedDelta = _timeElapsed;
    
    int stage = 0;
    
    while (timeElapsedDelta > controlPointDelta) {
        timeElapsedDelta -= controlPointDelta;
        
        stage++;
    }

	if (stage == _controlPoints.size() - 1)
		return;
    
    float currentPointDiff = timeElapsedDelta / controlPointDelta;
    
    Coordinate3D diff = _controlPoints[stage + 1] - _controlPoints[stage];
    Coordinate3D div = Coordinate3D(currentPointDiff, currentPointDiff, currentPointDiff);
    
    diff = diff * div;
    
    Coordinate3D thisLine, prevLine;
    
    if (stage > 0) {
        if (stage != _ps.stage) {
            _ps.stage = stage;
            _ps.angle = _lastRotation;
        }
        
        thisLine = _controlPoints[stage + 1] - _controlPoints[stage];
        prevLine = _controlPoints[stage] - _controlPoints[stage - 1];
    } else {
        thisLine = _controlPoints[1] - _controlPoints[0];
        prevLine = _controlPoints[1] - Coordinate3D(0, 0, 1);
    }

	float dot = thisLine.x * prevLine.x + thisLine.y * prevLine.y ;
    
    float det = thisLine.x * prevLine.y + prevLine.x * thisLine.y ;
    
    _lastRotation = (rad_to_deg(atan2(det,dot)));
    
    while (_lastRotation >= 360.00)
        _lastRotation -= 360.00;

    while (_lastRotation < 0)
        _lastRotation += 360.00;
    
    if (stage >= _controlPoints.size()) {
        _lastAnimationResult = &(_controlPoints[_controlPoints.size() - 1]);
        
        return;
    }
    
    Coordinate3D result = (_controlPoints[stage] + diff);
    
    _lastAnimationResult = new Coordinate3D(result.x, result.y, result.z);
}

void CircularAnimation::animate(float delta) {
    if (!_animating)
        return;
    
    if (_timeElapsed >= _span) {
        _animating = false;
        
        return;
    }
    
    _timeElapsed += delta;
    
    float totalToPerform = _rotationAngle - _startAngle;
    
    float currentAngle = totalToPerform * (_timeElapsed / _span) + _startAngle;
    
    float angleRad = deg_to_rad(currentAngle);
    
    _lastRotation = currentAngle;
    
    Coordinate3D res = _center + _distanceToCentralPoint(angleRad);
    
    _lastAnimationResult = new Coordinate3D(res.x, res.y, res.z);
}

void CompositeAnimation::animate(float delta) {
    if (!_animating)
        return;
    
    if (_currentAnimation == _animations.size()) {
        _animating = false;
        
        return;
    }
    
    if (!_currentAnimationSetup) {
        _animations[_currentAnimation]->start();
        
        _currentAnimationSetup = true;
    }
    
    _animations[_currentAnimation]->animate(delta);
    
    _lastRotation = _animations[_currentAnimation]->getLastRotation();
    _lastAnimationResult = _animations[_currentAnimation]->getLastAnimationResult();
    
    if (!(_animations[_currentAnimation]->getAnimating())) {
        _currentAnimation++;
        
        _currentAnimationSetup = false;
    }
}
