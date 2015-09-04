//
//  Scale.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 02/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Scale.h"

Scale::Scale(GLfloat* factor)
{
    setFactor(factor);
}

GLfloat* Scale::getFactor() {return factor;}

void Scale::setFactor(GLfloat* factor)
{
    this->factor[0] = factor[0];
    this->factor[1] = factor[1];
    this->factor[2] = factor[2];
}

void Scale::setFactor(GLfloat x, GLfloat y, GLfloat z)
{
    this->factor[0] = x;
    this->factor[1] = y;
    this->factor[2] = z;
}

void Scale::print()
{
    cout << "| | - Scale :: ";
    cout << "factor: {" << getFactor()[0] << ", "<< getFactor()[1] << ", " << getFactor()[2] << "}" << endl;
}

void Scale::apply()
{
    glScalef(factor[0], factor[1], factor[2]);
}