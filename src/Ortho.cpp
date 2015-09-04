//
//  Ortho.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 27/09/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Ortho.h"

Ortho::Ortho(int ID, string ids, GLfloat* pos, GLfloat znear, GLfloat zfar, GLfloat left, GLfloat right, GLfloat top, GLfloat bottom)
        : Camera(ID,ids,pos,znear,zfar)
{
    setLeft(left);
    setRight(right);
    setTop(top);
    setBottom(bottom);
}
Ortho::~Ortho() {}


GLfloat Ortho::getLeft() {return left;}
GLfloat Ortho::getRight() {return right;}
GLfloat Ortho::getTop() {return top;}
GLfloat Ortho::getBottom() {return bottom;}


void Ortho::setLeft(GLfloat left) {this->left = left;}
void Ortho::setRight(GLfloat right) {this->right = right;}
void Ortho::setTop(GLfloat top) {this->top = top;}
void Ortho::setBottom(GLfloat bottom) {this->bottom = bottom;}


void Ortho::print()
{
    cout << "- Camera - Ortho" << endl;
    cout << "| id: " << getID() << endl;
    cout << "| ids: " << getIds() << endl;
    cout << "| near: " << getZNear() << endl;
    cout << "| far: " << getZFar() << endl;
    cout << "| left: " << getLeft() << endl;
    cout << "| right: " << getRight() << endl;
    cout << "| top: " << getTop() << endl;
    cout << "| down: " << getBottom() << endl;
}


void Ortho::updateProjectionMatrix(GLint width, GLint height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(left, right, bottom, top, getZNear(), getZFar());
}

void Ortho::applyView()
{    
	if (getMode()==EXAMINE_MODE)
	{
		glTranslatef(getPos()[0],getPos()[1], getPos()[2]);
		// glTranslatef(0, 0, position[2]); // or this, if we ignore panning
        
		glRotatef(getRotation()[0], 1.f, 0.f, 0.f);
		glRotatef(getRotation()[1], 0.f, 1.f, 0.f);
		glRotatef(getRotation()[2], 0.f, 0.f, 1.f);
        
	}
	else
	{
		glRotatef(getRotation()[0], 1.f, 0.f, 0.f);
		glRotatef(getRotation()[1], 0.f, 1.f, 0.f);
		glRotatef(getRotation()[2], 0.f, 0.f, 1.f);
        
		glTranslatef(getPos()[0], getPos()[1], getPos()[2]);
	}
    
}

