//
//  Menu.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 02/01/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#ifndef __CGFLib_1__Menu__
#define __CGFLib_1__Menu__

#include <iostream>
#include "Rectangle.h"

class Menu{
public:
    Rectangle* window;
    GLfloat deltaX,deltaY,angle;
    
    string t1, t2;
    int l1,l2;
    
    Menu();
    
    void draw();
    
};

#endif /* defined(__CGFLib_1__Menu__) */
