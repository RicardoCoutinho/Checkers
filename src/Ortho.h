//
//  Ortho.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 27/09/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Ortho__
#define __CGFLib_1__Ortho__

#include <iostream>
#include <string>

#include "Camera.h"

using namespace std;

class Ortho : public Camera {
private:
    GLfloat left;
    GLfloat right;
    GLfloat top;
    GLfloat bottom;
    
public:
    Ortho(int ID, string ids, GLfloat* pos, GLfloat znear, GLfloat zfar, GLfloat left, GLfloat right, GLfloat top, GLfloat bottom);
    ~Ortho();
    
    GLfloat getLeft();
    GLfloat getRight();
    GLfloat getTop();
    GLfloat getBottom();
    
    void setLeft(GLfloat);
    void setRight(GLfloat);
    void setTop(GLfloat);
    void setBottom(GLfloat);
    
    void print();
    
    void updateProjectionMatrix(GLint width, GLint height);
    
    void applyView();
};

#endif /* defined(__CGFLib_1__Ortho__) */
