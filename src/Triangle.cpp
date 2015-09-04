//
//  Triangle.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 02/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Triangle.h"

Triangle::Triangle(GLfloat* xyz1, GLfloat* xyz2, GLfloat* xyz3)
{
    setXYZ1(xyz1);
    setXYZ2(xyz2);
    setXYZ3(xyz3);
}


GLfloat* Triangle::getXYZ1() {return xyz1;}
GLfloat* Triangle::getXYZ2() {return xyz2;}
GLfloat* Triangle::getXYZ3() {return xyz3;}


void Triangle::setXYZ1(GLfloat* xyz)
{
    this->xyz1[0] = xyz[0];
    this->xyz1[1] = xyz[1];
    this->xyz1[2] = xyz[2];
}
void Triangle::setXYZ1(GLfloat x, GLfloat y, GLfloat z)
{
    this->xyz1[0] = x;
    this->xyz1[1] = y;
    this->xyz1[2] = z;
}
void Triangle::setXYZ2(GLfloat* xyz)
{
    this->xyz2[0] = xyz[0];
    this->xyz2[1] = xyz[1];
    this->xyz2[2] = xyz[2];
}
void Triangle::setXYZ2(GLfloat x, GLfloat y, GLfloat z)
{
    this->xyz2[0] = x;
    this->xyz2[1] = y;
    this->xyz2[2] = z;
}
void Triangle::setXYZ3(GLfloat* xyz)
{
    this->xyz3[0] = xyz[0];
    this->xyz3[1] = xyz[1];
    this->xyz3[2] = xyz[2];
}
void Triangle::setXYZ3(GLfloat x, GLfloat y, GLfloat z)
{
    this->xyz3[0] = x;
    this->xyz3[1] = y;
    this->xyz3[2] = z;
}


void Triangle::print()
{
    cout << "| | - Triangle" << endl;
    cout << "| | | - xyz1: {" << getXYZ1()[0] << ", "<< getXYZ1()[1] << ", "<< getXYZ1()[2] << "}" << endl;
    cout << "| | | - xyz2: {" << getXYZ2()[0] << ", "<< getXYZ2()[1] << ", "<< getXYZ2()[2] << "}" << endl;
    cout << "| | | - xyz3: {" << getXYZ3()[0] << ", "<< getXYZ3()[1] << ", "<< getXYZ3()[2] << "}" << endl;
}

void Triangle::draw()
{
        glPushMatrix();
    
        glBegin(GL_TRIANGLES);
            glVertex3fv(xyz1);
            glVertex3fv(xyz2);
            glVertex3fv(xyz3);
        glEnd();
    
        glPopMatrix();
}
