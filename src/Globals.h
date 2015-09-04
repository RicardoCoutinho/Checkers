//
//  Globals.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 26/09/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Globals__
#define __CGFLib_1__Globals__

#include <iostream>
#include <string>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <unistd.h>
#else
#include <GL/glut.h>
#endif
#include <GL/glui.h>

using namespace std;

class Globals {
private:
    GLfloat background[4];
    GLenum drawmode;
    GLenum shading;
    GLenum cullface;
    GLenum cullorder;
    
public:
    Globals(GLfloat* background, GLenum drawmode, GLenum shading, GLenum cullface, GLenum cullorder);
    ~Globals();
    
    GLfloat* getBackground();
    GLenum getDrawmode();
    GLenum getShading();
    GLenum getCullface();
    GLenum getCullorder();
    
    void setBackground(GLfloat* rgba);
    void setBackground(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setDrawmode(GLenum);
    void setShading(GLenum);
    void setCullface(GLenum);
    void setCullorder(GLenum);

	void applyDrawmode();
    
    void print();
    
    void init();
    void run();
};

#endif /* defined(__CGFLib_1__Globals__) */
