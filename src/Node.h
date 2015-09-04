//
//  Node.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 02/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Node__
#define __CGFLib_1__Node__

#include <iostream>
#include <vector>
#include <string>

#include "Appearance.h"
#include "Animation.h"
#include "LinearAnimation.h"
#include "Transform.h"
#include "Primitive.h"
#include "Ref.h"

using namespace std;

class Node : public Ref {
private:
	GLuint id_dplObject;
	bool displaylist;
public:
    vector<Node*> nodes;
    vector<Transform*> transforms;
    Appearance* app;
	Animation* anim;
    vector<Primitive*> primitives;
    
    GLfloat matrix[16];
    
	Node(int ID, string ids);
    Node(int ID, string ids, bool displaylist);

	void initDpl();
	void displayDpl();
	void generateGeometry(bool);
    
	GLuint getIdDPL();
	void setIdDPL(GLuint);	
	bool getDisplaylist();
	void setDisplaylist(bool);

    bool operator() (Node*,Node*);
    
    void addLinkTo(Node*);
    void addTransformation(Transform*);
    void addPrimitive(Primitive*);
    
    void init();
    void applyTransformations();
    void applyAppearance();
	void applyAnimation();
	void applyEvaluators(Primitive*);
    void drawPrimitives();
	void draw();
    
    void apply();
	void update(unsigned long millis);
};

#endif /* defined(__CGFLib_1__Node__) */
