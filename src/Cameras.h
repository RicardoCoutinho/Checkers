//
//  Cameras.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 27/09/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Cameras__
#define __CGFLib_1__Cameras__

#include <iostream>
#include <string>
#include <iomanip>
#include <map>

#include "Camera.h"
#include "Perspective.h"
#include "Ortho.h"

using namespace std;

class Cameras {
private:
    string initial;
    
    map<string,Camera*> cameraMap;
    
public:
    Cameras(string initial);
    ~Cameras();
    
    string getInitial();
    Camera* getCamera(string);
    Camera* getCamera(GLint);
    map<string,Camera*> getCameras();
    GLint getSize();
    

    void setInitial(string);
    
    bool addCamera(Camera*);
    
    void print();
};

#endif /* defined(__CGFLib_1__Cameras__) */
