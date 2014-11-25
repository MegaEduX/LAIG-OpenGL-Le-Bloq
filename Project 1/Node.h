//
//  Node.h
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 23/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#ifndef __Project_1__Node__
#define __Project_1__Node__

#include <stdio.h>

#include <typeinfo>
#include <string>
#include <vector>

#include "Transform.h"

#include "GraphicalObject.h"

#include "Primitive.h"

#include "Animation.h"

#define NO_TRANSFORM_MATRIX 0

class Node : public GraphicalObject {
    
    std::vector<Transform *> _transforms;
    
    std::vector<Primitive *> _primitives;
    
    std::vector<Node *> _descendants;
    
    std::string _appearanceRef;
    
    std::string _animationRef;
    
    std::vector<std::string> _descendantNodeRefs;
    
    Node *_parent;
    
    Appearance *_appearance;
    
    Animation *_animation;
    
    bool _inheritedAppearance;
    
    bool _usesDisplayList;
    
    int _displayListId;
    
    int _delayListCreationCounter;
    
    float _matrix[4][4];
    
public:
    
    Node() : GraphicalObject() {
        init();
    }
    
    Node(std::string anId) : GraphicalObject(anId) {
        init();
    }
    
    void init() {
        _inheritedAppearance = false;
        
        _usesDisplayList = false;
        
        _displayListId = -1;
        
        _delayListCreationCounter = 10;
        
        _appearance = nullptr;
        
        _animation = nullptr;
    }
    
    std::vector<Transform *> getTransforms() {
        return _transforms;
    }
    
    void addTransform(Transform *transform) {
        _transforms.push_back(transform);
    }
    
    void removeTransform(Transform *child) {
        //	Removed for now.
    }
    
    void setTransformationMatrix() {
        glLoadIdentity();
        
		for (int i = 0; i < _transforms.size(); i++)
           _transforms[i]->apply();
        
        glGetFloatv(GL_MODELVIEW_MATRIX, &_matrix[0][0]);
    }
    
    std::vector<Primitive *> getPrimitives() {
        return _primitives;
    }
    
    void addPrimitive(Primitive *primitive) {
        _primitives.push_back(primitive);
    }
    
    void removePrimitive(Primitive *child) {
        //	Removed for now.
    }
    
    void setAppearance(Appearance *appearance) {
        _appearance = appearance;
    }
    
    Appearance* getAppearance() {
        if (_inheritedAppearance)
            return _parent->getAppearance();
        
        return _appearance;
    }
    
    void setAnimation(Animation *animation) {
        _animation = animation;
    }
    
    Animation *getAnimation() {
        //  I don't think it can be inherit...
        
        return _animation;
    }
    
    void setAppearanceRef(std::string ar) {
        _appearanceRef = ar;
    }
    
    std::string getAppearanceRef() {
        return _appearanceRef;
    }
    
    void setAnimationRef(std::string ar) {
        _animationRef = ar;
    }
    
    std::string getAnimationRef() {
        return _animationRef;
    }
    
    void addNodeRef(std::string nr) {
        _descendantNodeRefs.push_back(nr);
    }
    
    void removeNodeRef(std::string nr) {
		//	Perhaps it's needed.

        /*	std::vector<std::string>::iterator position = std::find(_descendantNodeRefs.begin(), _descendantNodeRefs.end(), nr);
        
        if (position != _descendantNodeRefs.end())
            _descendantNodeRefs.erase(position);	*/
    }
    
    std::vector<std::string> getNodeRefs() {
        return _descendantNodeRefs;
    }
    
    void addDescendant(Node *d) {
        _descendants.push_back(d);
    }
    
    void removeDescendant(Node *d) {
        //	Removed for now.
    }
    
    std::vector<Node *> getDescendants() {
        return _descendants;
    }
    
    void setParent(Node *p) {
        _parent = p;
    }
    
    void setInheritedAppearance(bool e) {
        _inheritedAppearance = e;
    }
    
    void setUseDisplayList(bool u) {
        _usesDisplayList = true;
    }
    
    bool getUseDisplayList() {
        return _usesDisplayList;
    }
    
    void draw(DrawingSettings *ds) {
        glPushMatrix();
        
        {
            bool skipCache = false;
            
            if (_delayListCreationCounter) {
                _delayListCreationCounter--;
                
                skipCache = true;
            }
            
            if (_animation != nullptr && _animation->getAnimating()) {
                skipCache = true;
                
                if (_animation->getLastAnimationResult() != nullptr)
                    glTranslated(_animation->getLastAnimationResult()->x,
                                 _animation->getLastAnimationResult()->y,
                                 _animation->getLastAnimationResult()->z);
                
                for (int i = 0; i < _transforms.size(); i++)
                    if (dynamic_cast<Scale *>(_transforms[i]))
                        _transforms[i]->apply();
                
                for (int i = 0; i < _transforms.size(); i++)
                    if (dynamic_cast<Rotate *>(_transforms[i]))
                        _transforms[i]->apply();
                
                if (_animation->getLastRotation() != 0)
                    glRotatef(_animation->getLastRotation(), 0, 1, 0);
            }
            
            if ( ! (Globals::getInstance().getDrawingSettings()->useDisplayLists()) )
                skipCache = true;
            
            if (_usesDisplayList && _displayListId != -1 && !skipCache)
                glCallList(_displayListId);
            else {
                bool createList = false;
                
                if (!skipCache) {
                    if (( createList = (_usesDisplayList && _displayListId == -1) )) {
                        _displayListId = glGenLists(1);
                        
                        glNewList(_displayListId, GL_COMPILE);
                    }
                    
                    glMultMatrixf(&_matrix[0][0]);
                }
                
                if (!(Globals::getInstance().getDrawingSettings()->useDisplayLists()))
                    glMultMatrixf(&_matrix[0][0]);
                
                glBindTexture(GL_TEXTURE_2D, 0);
                
                if (getAppearance() != nullptr) {
                    if (getAppearance()->getTexture() != nullptr)
                        getAppearance()->setTextureWrap(Coordinate2D(getAppearance()->getTexture()->getTexLength().s,
                                                                     getAppearance()->getTexture()->getTexLength().t));
                    getAppearance()->apply();
                }
                
                for (int i = 0; i < _primitives.size(); i++) {
                    if (getAppearance() != nullptr && getAppearance()->getTexture() != nullptr)
                        _primitives[i]->setTextureCoordinates(Coordinate2D(getAppearance()->getTexture()->getTexLength().s,
                                                                           getAppearance()->getTexture()->getTexLength().t));
                    
                    _primitives[i]->draw();
                }
                
                for (int i = 0; i < _descendants.size(); i++) {
                    _descendants[i]->setParent(this);
                    
                    _descendants[i]->draw(ds);
                }
                
                if (!skipCache) {
                    if (createList)
                        glEndList();
                    
                    if (_usesDisplayList)
                        glCallList(_displayListId);
                }
            }
        }
        
        glPopMatrix();
    }
    
};

class Graph : public GraphicalObject {
    
    std::vector<Node *> _nodes;
    
    Node *_rootNode;
    
    std::string _rootNodeRef;
    
public:
    
    std::vector<Node *> getNodes() {
        return _nodes;
    }
    
    void addNode(Node *aNode) {
        _nodes.push_back(aNode);
    }
    
    void removeNode(Node *aNode) {
        //	Removed for now.
    }
    
    void setRootNodeRef(std::string nr) {
        _rootNodeRef = nr;
    }
    
    std::string getRootNodeRef() {
        return _rootNodeRef;
    }
    
    void setRootNode(Node *n) {
        _rootNode = n;
    }
    
    Node* getRootNode() {
        return _rootNode;
    }
    
};

#endif /* defined(__Project_1__Node__) */
