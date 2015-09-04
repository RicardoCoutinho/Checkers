//
//  Rotate.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 02/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Rotate__
#define __CGFLib_1__Rotate__

#include <iostream>
#include <string>

#include "Transform.h"

enum ROTATE_AXIS { ROTATE_X=1, ROTATE_Y=2, ROTATE_Z=3 };

using namespace std;

class Rotate : public Transform {
private:
    GLint axis[3];
    GLfloat angle;
    
public:
    Rotate(GLint* axis, GLfloat);
    
    GLint* getAxis();
    GLfloat getAngle();
    
    void setAxis(GLint* xyz);
    void setAngle(GLfloat);
        
    void print();
    
    void apply();
};

#endif /* defined(__CGFLib_1__Rotate__) */
