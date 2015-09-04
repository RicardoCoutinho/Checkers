//
//  PieceModel.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 28/11/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "PieceModel.h"

PieceModel::PieceModel()
{
    model = new Cylinder(0.7,0.7,PIECE_HEIGHT,20,1);
}

void PieceModel::draw()
{
    glPushMatrix();
    
    glTranslatef(0.92 , PIECE_HEIGHT , 0.9);
    glRotatef(90, 1, 0, 0);
    model->draw();
    
    glPopMatrix();
}