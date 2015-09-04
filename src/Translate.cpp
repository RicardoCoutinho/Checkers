//
//  Translate.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 02/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Translate.h"

Translate::Translate(GLfloat* to)
{
    setTo(to);
}


GLfloat* Translate::getTo() {return to;}


void Translate::setTo(GLfloat* xyz)
{
    this->to[0] = xyz[0];
    this->to[1] = xyz[1];
    this->to[2] = xyz[2];
}
void Translate::setTo(GLfloat x, GLfloat y, GLfloat z)
{
    this->to[0] = x;
    this->to[1] = y;
    this->to[2] = z;
}


void Translate::print()
{
    cout << "| | - Translate :: ";
    cout << "to: {" << getTo()[0] << ", "<< getTo()[1] << ", " << getTo()[2] << "}" << endl;
}

void Translate::apply()
{
    glTranslatef(to[0], to[1], to[2]);
}