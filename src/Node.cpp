//
//  Node.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 02/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Node.h"

#define FOR(i, n) for(unsigned int i = 0; i < n ; ++i)

Node::Node(int ID, string ids) : Ref(ID,ids)
{
    nodes.clear();
    transforms.clear();
    app = NULL;
	anim = NULL;
    primitives.clear();
	displaylist = false;
}

//EXAME:Displaylist constructor Node com displaylist
Node::Node(int ID, string ids, bool displaylist) : Ref(ID,ids)
{
	this->displaylist = displaylist;
    nodes.clear();
    transforms.clear();
    app = NULL;
	anim = NULL;
    primitives.clear();
}

//EXAME:Displaylist inicializador do objecto para a displaylist
void Node::initDpl()
{
	id_dplObject = glGenLists(1);
	glNewList(id_dplObject, GL_COMPILE);
}

//EXAME:Displaylist chamada da displaylist
void Node::displayDpl()
{
	 //glClear(GL_COLOR_BUFFER_BIT);
	 glCallList(id_dplObject);
	 //glFlush();
}

//EXAME:Displaylist Desenha a displaylist
void Node::generateGeometry(bool check)
{
	if (displaylist && !check) 
	{
		initDpl();
	}

	FOR(i, this->primitives.size()) 
		this->primitives[i]->draw();

	FOR(i, this->nodes.size()) 
		this->nodes[i]->generateGeometry(displaylist || check);		

	if (displaylist && !check) 
	{
		glEndList();
	}
}

GLuint Node::getIdDPL()
{
	return id_dplObject;
}

void Node::setIdDPL(GLuint id_dplObject)
{
	this->id_dplObject = id_dplObject;
}
bool Node::getDisplaylist()
{
	return displaylist;
}

void Node::setDisplaylist(bool displaylist)
{
	this->displaylist = displaylist;
}

bool Node::operator() (Node* a, Node* b) {return (a->getIds().compare(b->getIds()));}

void Node::addLinkTo(Node* node)
{
    nodes.push_back(node);
}

void Node::addTransformation(Transform* transform)
{
    transforms.push_back(transform);
}

void Node::addPrimitive(Primitive* primitive)
{	
    primitives.push_back(primitive);
}

void Node::applyTransformations()
{
    vector<Transform*>::iterator it, ite;
    it = transforms.begin();
    ite = transforms.end();
    
    for (; it != ite; it++)
    {
        (*it)->apply();
    }
}

void Node::applyAppearance()
{
    if (app != NULL) 
	{
        app->apply();
    }
}

//EXAME:Animation aplica a animation
void Node::applyAnimation()
{
    if (anim != NULL) 
	{				
        ((LinearAnimation *)anim)->apply();
    }
}

//EXAME:Evaluators aplica os evaluators
void Node::applyEvaluators(Primitive* primitive)
{	
	glPushMatrix();

	primitive->draw();

	glPopMatrix();
}

////EXAME:Draw desenha as displaylists e aplica as animações, se houver primitivas feitas com evaluators desenha-as também
void Node::draw() 
{
	glPushMatrix();
    applyTransformations();
    applyAppearance();
	applyAnimation();

	FOR(i, this->nodes.size()) {
		if(this->nodes[i]->getDisplaylist()) {
			glCallList(this->nodes[i]->getIdDPL());
		} else {
			this->nodes[i]->draw();
		}
	}

	FOR(i, this->primitives.size()) {
		this->primitives[i]->draw();
	}

	glPopMatrix();
}

void Node::drawPrimitives()
{
	glPushMatrix();
    vector<Primitive*>::iterator it, ite;
    it = primitives.begin();
    ite = primitives.end();
    
    for (; it != ite; it++)
    {
        (*it)->draw();
    }
	glPopMatrix();
}

void Node::init()
{
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    
    //applyTransformations();
    
    //glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
}

void Node::apply()
{
    //glMultMatrixf(matrix);
    
    applyTransformations();
    applyAppearance();
	applyAnimation();
    drawPrimitives();
}

//EXAME:Animation faz um update a animation para ela se mover
void Node::update(unsigned long millis)
{
	if (anim != NULL) 
	{			
		glPushMatrix();
		applyAnimation();		
	}

	FOR(i, this->nodes.size())
		this->nodes[i]->update(millis);

	if (anim != NULL) 
		glPopMatrix();
}