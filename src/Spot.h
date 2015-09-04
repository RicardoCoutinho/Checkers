//
//  Spot.h
//  CGFLib-1
// 
//  Created by José Ricardo de Sousa Coutinho on 01/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Spot__
#define __CGFLib_1__Spot__

#include <iostream>
#include <string>

#include "Light.h"

using namespace std;

class Spot : public Light {
private:
    GLfloat angle;
    GLfloat exponent;
    GLfloat direction[3];
    
public:
    Spot(string ids, bool enabled, GLfloat* location, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLfloat angle, GLfloat exponent, GLfloat* direction);
    ~Spot();
    
    GLfloat getAngle();
    GLfloat getExponent();
    GLfloat* getDirection();
    
    void setAngle(GLfloat);
    void setExponent(GLfloat);
    void setDirection(GLfloat* xyz);
    void setDirection(GLfloat x, GLfloat y, GLfloat z);
    
    void print();
    
    void init();
    void update();
    void draw();
};

#endif /* defined(__CGFLib_1__Spot__) */
