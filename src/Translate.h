//
//  Translate.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 02/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Translate__
#define __CGFLib_1__Translate__

#include <iostream>
#include <string>

#include "Transform.h"

using namespace std;

class Translate :public Transform {
private:
    GLfloat to[3];
    
public:
    Translate(GLfloat* toxyz);
    
    GLfloat* getTo();
    
    void setTo(GLfloat* to);
    void setTo(GLfloat x, GLfloat y, GLfloat z);
    
    void print();
    
    void apply();
};

#endif /* defined(__CGFLib_1__Translate__) */
