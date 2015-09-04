//
//  Rotate.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 02/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Rotate.h"

Rotate::Rotate(GLint* axis, GLfloat angle)
{
    setAxis(axis);
    setAngle(angle);
}


GLint* Rotate::getAxis() {return axis;}
GLfloat Rotate::getAngle() {return angle;}


void Rotate::setAxis(GLint* axisxyz) {
    this->axis[0] = axisxyz[0];
    this->axis[1] = axisxyz[1];
    this->axis[2] = axisxyz[2];
}
void Rotate::setAngle(GLfloat angle) {this->angle = angle;}


void Rotate::print()
{
    cout << "| | - Rotate :: ";
    //cout << "axis: " << getAxis() << " :: ";
    cout << "angle: " << getAngle() << endl;
}

void Rotate::apply()
{
    glRotatef(angle, axis[0], axis[1], axis[2]);
}