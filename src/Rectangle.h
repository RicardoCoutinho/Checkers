//
//  Rectangle.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 02/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Rectangle__
#define __CGFLib_1__Rectangle__

#include <iostream>
#include <string>

#include "Primitive.h"

using namespace std;

class Rectangle : public Primitive {
private:
    GLfloat xy1[2];
    GLfloat xy2[2];

public:
    Rectangle(GLfloat* xy1, GLfloat* xy2);
    
    GLfloat* getXY1();
    GLfloat* getXY2();

    void setXY1(GLfloat* xy1);
    void setXY1(GLfloat x, GLfloat y);
    void setXY2(GLfloat* xy2);
    void setXY2(GLfloat x, GLfloat y);

    void print();
    
    void draw();
};

#endif /* defined(__CGFLib_1__Rectangle__) */
