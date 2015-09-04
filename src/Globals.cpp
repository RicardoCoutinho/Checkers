//
//  Globals.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 26/09/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Globals.h"

Globals::Globals(GLfloat* background, GLenum drawmode, GLenum shading, GLenum cullface, GLenum cullorder)
{
    setBackground(background);
    setDrawmode(drawmode);
    setShading(shading);
    setCullface(cullface);
    setCullorder(cullorder);
}
Globals::~Globals() {}

GLfloat* Globals::getBackground(){return background;}
GLenum Globals::getDrawmode(){return drawmode;}
GLenum Globals::getShading(){return shading;}
GLenum Globals::getCullface(){return cullface;}
GLenum Globals::getCullorder(){return cullorder;}

void Globals::setBackground(GLfloat* rgba){
    this->background[0] = rgba[0];
    this->background[1] = rgba[1];
    this->background[2] = rgba[2];
    this->background[3] = rgba[3];
}
void Globals::setBackground(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    this->background[0] = r;
    this->background[1] = g;
    this->background[2] = b;
    this->background[3] = a;
}
void Globals::setDrawmode(GLenum drawmode){this->drawmode = drawmode;} // GL_POINT , GL_LINE , GL_FILL
void Globals::setShading(GLenum shading){this->shading = shading;} // GL_FLAT , GL_SMOOTH
void Globals::setCullface(GLenum cullface){this->cullface = cullface;} // none , GL_FRONT , GL_BACK , GL_FRONT_AND_BACK
void Globals::setCullorder(GLenum cullorder){this->cullorder = cullorder;} // GL_CW , GL_CCW


void Globals::print() {
    cout << "--- Globals ---" << endl;
    cout << "| background: {"
                << background[0] << ", "
                << background[1] << ", "
                << background[2] << ", "
                << background[3] << "}" << endl;
    cout << "| drawmode: " << drawmode << endl;
    cout << "| shading: " << shading << endl;
    cout << "| cullface: " << cullface << endl;
    cout << "| cullorder: " << cullorder << endl << endl;
}

void Globals::init()
{
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    
    glNormal3f(0,1,0);
    glEnable(GL_NORMALIZE);
    
    //glEnable(GL_RESCALE_NORMAL);
    
    glClearColor( // background color
                 background[0],
                 background[1],
                 background[2],
                 background[3]
                );
    
    glShadeModel(shading); // shading model
    
	applyDrawmode();
    
    if (cullface)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(cullface); // cullface
    }
    
    glFrontFace(cullorder); // cullorder
}

void Globals::run()
{
    
}

void Globals::applyDrawmode()
{
	glPolygonMode(GL_FRONT_AND_BACK, drawmode); // drawmode
}