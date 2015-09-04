//
//  Omni.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 01/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Omni__
#define __CGFLib_1__Omni__

#include <iostream>
#include <string>

#include "Light.h"

using namespace std;

class Omni : public Light {
private:
    
public:
    Omni(string ids, bool enabled, GLfloat* location, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular);
    ~Omni();
    
    void print();
    
    void init();
    void update();
    void draw();
};

#endif /* defined(__CGFLib_1__Omni__) */
