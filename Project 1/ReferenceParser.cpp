//
//  ReferenceParser.cpp
//  Project 1
//
//  Created by Eduardo Almeida and Pedro Santiago on 30/09/14.
//  Copyright (c) 2014 Eduardo Almeida and Pedro Santiago. All rights reserved.
//

#include "ReferenceParser.h"

#include "GraphicalEngine.h"

void ReferenceParser::parseReferences(ANFResult *r) {
    /*
     *  Parse Graphs
     */
    
    {
		for (int i = 0; i < r->graphs.size(); i++) {
			Graph *g = r->graphs[i];

            Node *n = nullptr;
            
			for (int j = 0; j < g->getNodes().size(); j++) {
				Node *temp = g->getNodes()[j];

                if (temp->getId() == g->getRootNodeRef()) {
                    n = temp;
                    
                    break;
                }
			}
            
            if (n)
                g->setRootNode(n);
            else
                throw new ReferenceParserException("Root node not found!");
        }
    }
    
    /*
     *  Parse Graph's Nodes
     */
    
    {
		for (int i = 0; i < r->graphs.size(); i++) {
			Graph *g = r->graphs[i];
			
			for (int j = 0; j < g->getNodes().size(); j++) {
				Node *n = g->getNodes()[j];
                
                //  Grab and set the appearance.
                
                if (n->getAppearanceRef() != "") {
                    if (n->getAppearanceRef() == "inherit")
                        n->setInheritedAppearance(true);
                    else {
						for (int k = 0; k < r->appearances.size(); k++) {
							Appearance *a = r->appearances[k];
							
                            if (a->getId() == n->getAppearanceRef()) {
                                n->setAppearance(a);
                                
                                break;
                            }
						}
                        
                        if (!n->getAppearance())
                            throw new ReferenceParserException("Appearance \"" + n->getAppearanceRef() + "\" not found.");
                    }
                }
                
                //  Grab and set the animation.
                
                if (n->getAnimationRef() != "") {
                    //  I don't think it can be inherit...
                    
                    for (int k = 0; k < r->animations.size(); k++) {
                        Animation *a = r->animations[k];

                        if (a->getId() == n->getAnimationRef()) {
                            n->setAnimation(a);
                            
                            break;
                        }
                    }
                    
                    if (!n->getAnimation())
                        throw new ReferenceParserException("Animation \"" + n->getAnimationRef() + "\" not found.");
                }
                
                //  Set its descendants.
                
				for (int k = 0; k < n->getNodeRefs().size(); k++) {
					std::string nr = n->getNodeRefs()[k];
					
                    bool foundNode = false;

					for (int l = 0; l < g->getNodes().size(); l++) {
						Node *n2 = g->getNodes()[l];
						
                        if (n2 && n2->getId() == nr) {
                            n->addDescendant(n2);
                            
                            if (n->getId() == n2->getId())
                                throw new ReferenceParserException("You are referencing yourself who is then referencing you who is then referencing yourself who is then referencing you who is then referencing yourself... Oops, I crashed already.");
                            
                            foundNode = true;
                            
                            break;
                        }
					}
                    
                    if (!foundNode)
                        throw new ReferenceParserException("Node \"" + nr + "\" not found.");
                }
            }
            
            //  Remove orphan nodes.
            
            std::vector<Node *> toRemove;
            
			for (int x = 0; x < g->getNodes().size(); x++) {
				Node *n = g->getNodes()[x];
				
                if (n != g->getRootNode())
                    toRemove.push_back(n);
			}

			for (int x = 0; x < toRemove.size(); x++)
				g->removeNode(toRemove[x]);
        }
    }
    
    /*
     *  Parse Appearance's Textures
     */
    
    {
		for (int i = 0; i < r->appearances.size(); i++) {
			Appearance *a = r->appearances[i];

			if (a->getTextureRef() != "") {
				for (int j = 0; j < r->textures.size(); j++) {
					Texture *t = r->textures[j];

                    if (t->getId() == a->getTextureRef()) {
                        a->setTexture(t);
                        
                        break;
                    }
				}
                
                if (!a->getTexture())
                    throw new ReferenceParserException("Appearance \"" + a->getTextureRef() + "\" not found.");
            }
		} 
    }
    
    /*
     *  Parse Composite Animations
     */
    
    {
        for (int i = 0; i < r->animations.size(); i++) {
            Animation *a = r->animations[i];
            
            if (dynamic_cast<CompositeAnimation *>(a)) {
                CompositeAnimation *ca = (CompositeAnimation *) a;
                
                for (int j = 0; j < ca->getAnimationRefs().size(); j++) {
                    std::string ar = ca->getAnimationRefs()[j];
                    
                    bool found = false;
                    
                    for (int k = 0; k < r->animations.size(); k++)
                        if (r->animations[k]->getId() == ar) {
                            ca->addAnimation(r->animations[k]);
                            
                            found = true;
                            
                            break;
                        }
                    
                    if (!found)
                        throw new ReferenceParserException("Composite Animation \"" + ar + "\" not found.");
                }
            }
        }
    }
}
