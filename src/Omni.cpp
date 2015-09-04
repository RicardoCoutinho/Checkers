//
//  Omni.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 01/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Omni.h"

Omni::Omni(string ids, bool enabled, GLfloat* location, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular)
            : Light(ids,enabled,location,ambient,diffuse,specular) {}
Omni::~Omni() {}

void Omni::print()
{
    cout << "- Light - Omni" << endl;
    cout << "| id: " << getIds() << endl;
    cout << "| enabled: " << getEnabled() << endl;
    cout << "| location: {"
    << getLocation()[0] << ", "
    << getLocation()[1] << ", "
    << getLocation()[2] << "}" << endl;
    cout << "| ambient: {"
    << getAmbient()[0] << ", "
    << getAmbient()[1] << ", "
    << getAmbient()[2] << ", "
    << getAmbient()[3] << "}" << endl;
    cout << "| diffuse: {"
    << getDiffuse()[0] << ", "
    << getDiffuse()[1] << ", "
    << getDiffuse()[2] << ", "
    << getDiffuse()[3] << "}" << endl;
    cout << "| specular: {"
    << getSpecular()[0] << ", "
    << getSpecular()[1] << ", "
    << getSpecular()[2] << ", "
    << getSpecular()[3] << "}" << endl;
}

void Omni::init()
{
    Light::init();
}

void Omni::update()
{
    Light::update();
}

void Omni::draw()
{
    glPushMatrix();
    
	update();
    
	getMaterial()->apply();
    
    glTranslatef(getLocation()[0], getLocation()[1], getLocation()[2]);
    
    /*
    quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
        
    gluSphere(quadric, CG_GLIGHT_DEFAULT_RADIUS, CG_GLIGHT_DEFAULT_SLICES, CG_GLIGHT_DEFAULT_STACKS);
        
    gluDeleteQuadric(quadric);
    */
    
    glPopMatrix();
}
