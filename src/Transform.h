//
//  Transform.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 02/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Transform__
#define __CGFLib_1__Transform__

#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <unistd.h>
#else
#include <GL/glut.h>
#endif
#include <GL/glui.h>

using namespace std;

class Transform {
    
public:
    virtual void print() = 0;
    virtual void apply() = 0;
};

#endif /* defined(__CGFLib_1__Transform__) */
