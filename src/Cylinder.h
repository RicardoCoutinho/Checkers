//
//  Cylinder.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 02/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Cylinder__
#define __CGFLib_1__Cylinder__

#include <iostream>
#include <string>

#include "Primitive.h"

using namespace std;

class Cylinder : public Primitive {
private:
    GLfloat base;
    GLfloat top;
    GLfloat height;
    GLint slices;
    GLint stacks;
    
public:
    Cylinder(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks);
    
    GLfloat getBase();
    GLfloat getTop();
    GLfloat getHeight();
    GLint getSlices();
    GLint getStacks();

    void setBase(GLfloat);
    void setTop(GLfloat);
    void setHeight(GLfloat);
    void setSlices(GLint);
    void setStacks(GLint);

    void print();
    
    void draw();
};

#endif /* defined(__CGFLib_1__Cylinder__) */
