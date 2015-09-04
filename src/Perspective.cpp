//
//  Perspective.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 27/09/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Perspective.h"

Perspective::Perspective(int ID, string ids, GLfloat* pos, GLfloat znear, GLfloat zfar, GLfloat angle, GLfloat* target)
                : Camera(ID,ids,pos,znear,zfar)
{
    setAngle(angle);
    setTarget(target);
}
Perspective::~Perspective() {}


GLfloat Perspective::getAngle() {return angle;}
GLfloat* Perspective::getTarget() {return this->target;}


void Perspective::setAngle(GLfloat angle) {this->angle = angle;}
void Perspective::setTarget(GLfloat* target)
{
    this->target[0] = target[0];
    this->target[1] = target[1];
    this->target[2] = target[2];
}
void Perspective::setTarget(GLfloat x, GLfloat y, GLfloat z)
{
    this->target[0] = x;
    this->target[1] = y;
    this->target[2] = z;
}


void Perspective::print()
{
    cout << "- Camera - Perspective" << endl;
    cout << "| ID: " << getID() << endl;
    cout << "| ids: " << getIds() << endl;
    cout << "| pos: {" << getPos()[0] << ", "<< getPos()[1]<< ", " << getPos()[2] << "}" << endl;
    cout << "| near: " << getZNear() << endl;
    cout << "| far: " << getZFar() << endl;
    cout << "| angle: " << getAngle() << endl;
    cout << "| target: {" << getTarget()[0] << ", "<< getTarget()[1] << ", " << getTarget()[2] << "}" << endl;
}

void Perspective::updateProjectionMatrix(GLint width, GLint height)
{    
    float aspect= (float)width / (float)height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(angle, aspect, getZNear(), getZFar());
}

void Perspective::applyView()
{
    
    gluLookAt(
              getPos()[0],      getPos()[1],    getPos()[2],
              getTarget()[0],   getTarget()[1], getTarget()[2],
              0,                1,              0
              );
    
    glRotatef(getRotation()[0], 1.f, 0.f, 0.f);
    glRotatef(getRotation()[1], 0.f, 1.f, 0.f);
    glRotatef(getRotation()[2], 0.f, 0.f, 1.f);
}


