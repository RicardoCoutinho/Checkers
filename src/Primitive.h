//
//  Primitive.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 02/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Primitive__
#define __CGFLib_1__Primitive__

#include <iostream>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <unistd.h>
#else
#include <GL/glut.h>
#endif
#include <GL/glui.h>

class Primitive {
public:

    virtual void print();    
    virtual void draw();
};

#endif /* defined(__CGFLib_1__Primitive__) */
