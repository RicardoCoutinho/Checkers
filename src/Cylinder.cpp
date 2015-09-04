//
//  Cylinder.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 02/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Cylinder.h"

Cylinder::Cylinder(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks)
{
    setBase(base);
    setTop(top);
    setHeight(height);
    setSlices(slices);
    setStacks(stacks);
}


GLfloat Cylinder::getBase() {return base;}
GLfloat Cylinder::getTop() {return top;}
GLfloat Cylinder::getHeight() {return height;}
GLint Cylinder::getSlices() {return slices;}
GLint Cylinder::getStacks() {return stacks;}


void Cylinder::setBase(GLfloat base) {this->base = base;}
void Cylinder::setTop(GLfloat top) {this->top = top;}
void Cylinder::setHeight(GLfloat height) {this->height = height;}
void Cylinder::setSlices(GLint slices) {this->slices = slices;}
void Cylinder::setStacks(GLint stacks) {this->stacks = stacks;}

void Cylinder::print()
{
    cout << "| | - Cylinder" << endl;
    cout << "| | | - base: " << getBase() << endl;
    cout << "| | | - top: " << getTop() << endl;
    cout << "| | | - height: " << getHeight() << endl;
    cout << "| | | - slices: " << getSlices() << endl;
    cout << "| | | - stacks: " << getStacks() << endl;
}

void Cylinder::draw()
{
    glPushMatrix();
    
    GLUquadric *quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricOrientation(quadric,GLU_OUTSIDE);

    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluQuadricTexture( quadric, GL_TRUE );
    
    gluCylinder(quadric, base, top, height, slices, stacks);
    
    glRotatef(180,1,0,0);
    gluDisk(quadric, 0, base, slices, 1);
    glRotatef(180,1,0,0);
    glTranslatef(0, 0, height);
    gluDisk(quadric, 0, top, slices, 1);
    glTranslatef(0, 0, -height);
    
    gluDeleteQuadric(quadric);
    
    glPopMatrix();
}