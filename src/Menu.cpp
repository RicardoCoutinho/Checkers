//
//  Menu.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 02/01/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#include "Menu.h"
#include <cmath>
#define _USE_MATH_DEFINES

Menu::Menu()
{
    t1 = "EMERGO";
    t2 = "click to start";
    
    l1 = t1.length();
    l2 = t2.length();
    
    GLfloat xy1[2] = {-50,-50};
    GLfloat xy2[2] = {50,50};
    
    window = new Rectangle(xy1, xy2);
}

void Menu::draw()
{
    glLoadName(101);
    
    glPushMatrix();
    
    glDisable(GL_LIGHTING);
    glColor4f(0,0,0,0.5);
    
    glRotatef(-90,1,0,0);
    glTranslatef(0,0,1);
    
    window->draw();
    
    glTranslatef(-3, -1, 1);
    glScalef(0.01, 0.01, 0.01);
    glLineWidth(5);
    
    glPushMatrix();
    
    for (int i=0; i<l1; i++)
    {
        glColor4f(1, 1, 0,1);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, t1[i]);
        
    }
    
    glPopMatrix();
    
    
    glPushMatrix();
    
    glLineWidth(2);
    glTranslatef(50, -300, 0);
    glScalef(0.5, 0.5, 0.5);
    
    for (int i=0; i<l2; i++)
    {
        glColor4f(1, 1, 0,1);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, t2[i]);
        
    }
    
    glPopMatrix();
    
    glEnable(GL_LIGHTING);
    glPopMatrix();
}