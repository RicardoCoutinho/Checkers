//
//  TileModel.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 28/11/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__TileModel__
#define __CGFLib_1__TileModel__

#define TILE_SIZE 1.9125

#include <iostream>
#include "Rectangle.h"
#include "Appearance.h"

using namespace std;

class TileModel{
private:
    Rectangle* model;
    
    static bool initialized;
    static Appearance* blank;
    static Appearance* selected;
    static Appearance* possible;
    
public:
    TileModel();
    Appearance* app;
    
    void draw(GLint color);
};

#endif /* defined(__CGFLib_1__TileModel__) */
