//
//  TileModel.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 28/11/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "TileModel.h"

bool TileModel::initialized = false;

Appearance* TileModel::blank = NULL;
Appearance* TileModel::selected = NULL;
Appearance* TileModel::possible = NULL;

TileModel::TileModel()
{
    if (!initialized)
    {
        GLfloat a[4] = {0,0,0,1};
        
        GLfloat b[4] = {0,1,0,1};
        GLfloat c[4] = {1,1,0,1};
        
        blank = new Appearance(a);
        selected = new Appearance(b);
        possible = new Appearance(c);
        
        initialized = true;
        
        GLfloat xy0[2] = {0,0};
        GLfloat xy[2] = {TILE_SIZE,TILE_SIZE};
        model = new Rectangle(xy0,xy);
        app = blank;
    }
}

void TileModel::draw(GLint color)
{
    glPushMatrix();
    
    switch (color)
    {
        case 0:
            app = blank;
            break;
            
        case 1:
            app = selected;
            break;
            
        case 2:
            app = possible;
            break;
            
        default:
            break;
    }
    
    app->apply();
    
    glTranslated(0, 0, TILE_SIZE);
    glRotated(-90, 1, 0, 0);
    model->draw();
    
    glPopMatrix();
}