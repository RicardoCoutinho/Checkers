//
//  Lighting.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 01/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Lighting__
#define __CGFLib_1__Lighting__

#include <iostream>
#include <string>
#include <iomanip>
#include <map>

#include "Light.h"
#include "Omni.h"
#include "Spot.h"

using namespace std;

class Lighting {
private:
    bool doublesided;
    bool local;
    bool enabled;
    GLfloat ambient[4];
    
    GLenum nextLight;
    map<string,Light*> lightMap;

public:
    Lighting(bool doublesided, bool local, bool enabled, GLfloat* ambient);
    ~Lighting();
    
    bool getDoublesided();
    bool getLocal();
    bool getEnabled();
    GLfloat* getAmbient();
    map<string,Light*> getLights();
    
    void setDoublesided(bool);
    void setLocal(bool);
    void setEnabled(bool);
    void setAmbient(GLfloat* rgba);
    void setAmbient(GLfloat,GLfloat,GLfloat,GLfloat);
    
    void enable();
    void disable();
    
    Light* getLight(string);
    bool addLight(Light*);
    
    void print();
    
    void init();
    void run();
};

#endif /* defined(__CGFLib_1__Lighting__) */
