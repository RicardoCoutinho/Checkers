//
//  Scale.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 02/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Scale__
#define __CGFLib_1__Scale__

#include <iostream>
#include <string>

#include "Transform.h"

using namespace std;

class Scale : public Transform {
private:
    GLfloat factor[3];
    
public:
    Scale(GLfloat* factorxyz);
    
    GLfloat* getFactor();
        
    void setFactor(GLfloat* xyz);
    void setFactor(GLfloat x, GLfloat y, GLfloat z);
    
    void print();
    
    void apply();
};

#endif /* defined(__CGFLib_1__Scale__) */
