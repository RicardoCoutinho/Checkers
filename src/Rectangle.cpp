//
//  Rectangle.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 02/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Rectangle.h"

Rectangle::Rectangle(GLfloat* xy1, GLfloat* xy2)
{
    setXY1(xy1);
    setXY2(xy2);
}

GLfloat* Rectangle::getXY1() {return xy1;}
GLfloat* Rectangle::getXY2() {return xy2;}

void Rectangle::setXY1(GLfloat* xy)
{
    this->xy1[0] = xy[0];
    this->xy1[1] = xy[1];
}
void Rectangle::setXY1(GLfloat x, GLfloat y)
{
    this->xy1[0] = x;
    this->xy1[1] = y;
}
void Rectangle::setXY2(GLfloat* xy)
{
    this->xy2[0] = xy[0];
    this->xy2[1] = xy[1];
}
void Rectangle::setXY2(GLfloat x, GLfloat y)
{
    this->xy2[0] = x;
    this->xy2[1] = y;
}

void Rectangle::print()
{
    cout << "| | - Rectangle" << endl;
    cout << "| | | - xy1: {" << getXY1()[0] << ", "<< getXY1()[1] << "}" << endl;
    cout << "| | | - xy2: {" << getXY2()[0] << ", "<< getXY2()[1] << "}" << endl;
}

void Rectangle::draw()
{
    glPushMatrix();
    
    glBegin(GL_QUADS);
        glNormal3f(0,0,1);
    
        glTexCoord2f(0,0);
        glVertex2fv(xy1);
    
        glTexCoord2f(1,0);
        glVertex2f(xy2[0],xy1[1]);
    
        glTexCoord2f(1,1);
        glVertex2fv(xy2);
    
        glTexCoord2f(0,1);
        glVertex2f(xy1[0],xy2[1]);
    
    glEnd();
    
    glPopMatrix();
}