//
//  Spot.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 01/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Spot.h"

Spot::Spot(string ids, bool enabled, GLfloat* location, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLfloat angle, GLfloat exponent, GLfloat* direction)
        : Light(ids,enabled,location,ambient,diffuse,specular)
{
    setAngle(angle);
    setExponent(exponent);
    setDirection(direction);
}
Spot::~Spot() {}



float Spot::getAngle() {return angle;}
float Spot::getExponent() {return exponent;}
GLfloat* Spot::getDirection() {return direction;}



void Spot::setAngle(GLfloat angle) {this->angle = angle;}
void Spot::setExponent(GLfloat exponent) {this->exponent = exponent;}
void Spot::setDirection(GLfloat* xyz)
{
    this->direction[0] = xyz[0];
    this->direction[1] = xyz[1];
    this->direction[2] = xyz[2];
}
void Spot::setDirection(GLfloat x, GLfloat y, GLfloat z)
{
    this->direction[0] = x;
    this->direction[1] = y;
    this->direction[2] = z;
}


void Spot::print()
{
    cout << "- Light - Spot" << endl;
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
    cout << "| angle: " << angle << endl;
    cout << "| exponent: " << exponent << endl;
    cout << "| direction: {"
            << direction[0] << ", "
            << direction[1] << ", "
            << direction[2] << "}" << endl;
}

void Spot::init()
{
    Light::init();
}

void Spot::update()
{
    Light::update();
    
    glLightfv(get_GLREF(), GL_SPOT_EXPONENT, &exponent);
    glLightf (get_GLREF(), GL_SPOT_CUTOFF, angle);
    glLightfv(get_GLREF(), GL_SPOT_DIRECTION, direction);
}

void Spot::draw()
{
    glPushMatrix();
    
	update();
    
	getMaterial()->apply();
    
    glTranslatef(getLocation()[0], getLocation()[1], getLocation()[2]);
    
    quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
        
    gluSphere(quadric, CG_GLIGHT_DEFAULT_RADIUS, CG_GLIGHT_DEFAULT_SLICES, CG_GLIGHT_DEFAULT_STACKS);
        
    gluDeleteQuadric(quadric);
    
    glPopMatrix();
}