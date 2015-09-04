//
//  PieceModel.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 28/11/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__PieceModel__
#define __CGFLib_1__PieceModel__

#define PIECE_HEIGHT 0.2

#include <iostream>
#include "Cylinder.h"

using namespace std;

class PieceModel{
private:
    Cylinder* model;
public:
    PieceModel();
    
    void draw();
};

#endif /* defined(__CGFLib_1__PieceModel__) */
