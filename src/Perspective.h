//
//  Perspective.h
//  CGFLib-1
// 
//  Created by José Ricardo de Sousa Coutinho on 27/09/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Perspective__
#define __CGFLib_1__Perspective__

#include <iostream>
#include <string>

#include "Camera.h"

using namespace std;

class Perspective : public Camera {
private:
    GLfloat angle;
    GLfloat target[3];
    
public:
    Perspective(int ID, string ids, GLfloat* pos, GLfloat znear, GLfloat zfar, GLfloat angle, GLfloat* target);
    ~Perspective();
    
    GLfloat getAngle();
    GLfloat* getTarget();

    void setAngle(GLfloat);
    void setTarget(GLfloat* xyz);
    void setTarget(GLfloat x, GLfloat y, GLfloat z);
    
    void print();
    
    void updateProjectionMatrix(GLint width, GLint height);
    
    void applyView();
};

#endif /* defined(__CGFLib_1__Perspective__) */
