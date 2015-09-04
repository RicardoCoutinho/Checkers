//
//  Textures.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 01/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Textures__
#define __CGFLib_1__Textures__

#include <iostream>
#include <string>
#include <iomanip>
#include <map>

#include "Texture.h"

using namespace std;

class Textures {
private:
    map<string,Texture*> textureMap;
    
public:
    Textures();
    ~Textures();
    
    Texture* getTexture(string);
    bool addTexture(Texture*);
    
    void print();
};


#endif /* defined(__CGFLib_1__Textures__) */
