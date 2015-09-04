//
//  Triangle.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 02/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Triangle__
#define __CGFLib_1__Triangle__

#include <iostream>
#include <string>

#include "Primitive.h"

using namespace std;

class Triangle : public Primitive {
private:
    GLfloat xyz1[3];
    GLfloat xyz2[3];
    GLfloat xyz3[3];

public:
    Triangle(GLfloat* xyz1, GLfloat* xyz2, GLfloat* xyz3);
    
    GLfloat* getXYZ1();
    GLfloat* getXYZ2();
    GLfloat* getXYZ3();

    void setXYZ1(GLfloat* xyz);
    void setXYZ1(GLfloat x, GLfloat y, GLfloat z);
    void setXYZ2(GLfloat* xyz);
    void setXYZ2(GLfloat x, GLfloat y, GLfloat z);
    void setXYZ3(GLfloat* xyz);
    void setXYZ3(GLfloat x, GLfloat y, GLfloat z);

    void print();
    
    void draw();
};

#endif /* defined(__CGFLib_1__Triangle__) */
