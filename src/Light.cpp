//
//  Light.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 01/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Light.h"

GLfloat _x_tmp_0[3] = {CG_GLIGHT_DEFAULT_COLOR};
Appearance* Light::default_light_material = new Appearance(_x_tmp_0);
GLfloat Light::background_ambient[4] = {CG_GLIGHT_DEFAULT_BACKGROUND_AMBIENT};

Light::Light(string ids, bool enabled, GLfloat* location, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular)
{
    setIds(ids); 
    setEnabled(enabled);
    setLocation(location);
    setAmbient(ambient);
    setDiffuse(diffuse);
    setSpecular(specular);
    
    setKc(CG_GLIGHT_DEFAULT_KC);
    setKl(CG_GLIGHT_DEFAULT_KL);
    setKq(CG_GLIGHT_DEFAULT_KQ);
    
    set_GLREF(-1);
    
    material = default_light_material;
}
Light::~Light() {}


string Light::getIds() {return ids;}
bool Light::getEnabled() {return enabled;}
GLfloat* Light::getLocation() {return location;}
GLfloat* Light::getAmbient() {return ambient;}
GLfloat* Light::getDiffuse() {return diffuse;}
GLfloat* Light::getSpecular() {return specular;}
GLfloat Light::getKc() {return kc;}
GLfloat Light::getKl() {return kl;}
GLfloat Light::getKq() {return kq;}
GLenum Light::get_GLREF() {return _GLREF;}
Appearance* Light::getMaterial() {return material;}


void Light::setIds(string ids) {this->ids = ids;}
void Light::setEnabled(bool enabled) {this->enabled = enabled;}
void Light::setLocation(GLfloat* xyzo)
{
    this->location[0] = xyzo[0];
    this->location[1] = xyzo[1];
    this->location[2] = xyzo[2];
    this->location[3] = xyzo[3];
}
void Light::setLocation(GLfloat x, GLfloat y, GLfloat z, GLfloat o)
{
    this->location[0] = x;
    this->location[1] = y;
    this->location[2] = z;
    this->location[3] = o;
}
void Light::setAmbient(GLfloat* rgba)
{
    this->ambient[0] = rgba[0];
    this->ambient[1] = rgba[1];
    this->ambient[2] = rgba[2];
    this->ambient[3] = rgba[3];
}
void Light::setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    this->ambient[0] = r;
    this->ambient[1] = g;
    this->ambient[2] = b;
    this->ambient[3] = a;
}
void Light::setDiffuse(GLfloat* rgba)
{
    this->diffuse[0] = rgba[0];
    this->diffuse[1] = rgba[1];
    this->diffuse[2] = rgba[2];
    this->diffuse[3] = rgba[3];
}
void Light::setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    this->diffuse[0] = r;
    this->diffuse[1] = g;
    this->diffuse[2] = b;
    this->diffuse[3] = a;
}
void Light::setSpecular(GLfloat* rgba)
{
    this->specular[0] = rgba[0];
    this->specular[1] = rgba[1];
    this->specular[2] = rgba[2];
    this->specular[3] = rgba[3];
}
void Light::setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    this->specular[0] = r;
    this->specular[1] = g;
    this->specular[2] = b;
    this->specular[3] = a;
}

void Light::setKc(float f) { kc = f; }
void Light::setKl(float f) { kl = f; }
void Light::setKq(float f) { kq = f; }

void Light::set_GLREF(GLenum _GLREF) {this->_GLREF = _GLREF;}
void Light::setMaterial(Appearance* material) {this->material = material;}


bool* Light::controlEnabled() {return &(this->enabled);}

bool Light::operator() (Light* a, Light* b) {return (a->getIds().compare(b->getIds()));}


void Light::print()
{
    cout << "- Light - Base" << endl;
    cout << "| id: " << getIds() << endl;
    cout << "| enabled: " << getEnabled() << endl;
    cout << "| location: {"
            << location[0] << ", "
            << location[1] << ", "
            << location[2] << "}" << endl;
    cout << "| ambient: {"
            << ambient[0] << ", "
            << ambient[1] << ", "
            << ambient[2] << ", "
            << ambient[3] << "}" << endl;
    cout << "| diffuse: {"
            << diffuse[0] << ", "
            << diffuse[1] << ", "
            << diffuse[2] << ", "
            << diffuse[3] << "}" << endl;
    cout << "| specular: {"
            << specular[0] << ", "
            << specular[1] << ", "
            << specular[2] << ", "
            << specular[3] << "}" << endl;
}

// --------------------------------------------------------------

void Light::init()
{
    if (enabled)
		glEnable(_GLREF);
	else
		glDisable(_GLREF);
}

void Light::update()
{
	if (enabled)
		glEnable(_GLREF);
	else
		glDisable(_GLREF);
    
    
    glLightfv(_GLREF, GL_POSITION, location);
    
    glLightfv(_GLREF, GL_AMBIENT, ambient);
    glLightfv(_GLREF, GL_DIFFUSE, diffuse);
    glLightfv(_GLREF, GL_SPECULAR, specular);
    
    glLightf(_GLREF, GL_CONSTANT_ATTENUATION, kc);
    glLightf(_GLREF, GL_LINEAR_ATTENUATION, kl);
    glLightf(_GLREF, GL_QUADRATIC_ATTENUATION, kq);
    
}

void Light::draw()
{
	update();
    
	material->apply();
    
    glTranslatef(location[0], location[1], location[2]);
    
    quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
        
    gluSphere(quadric, CG_GLIGHT_DEFAULT_RADIUS, CG_GLIGHT_DEFAULT_SLICES, CG_GLIGHT_DEFAULT_STACKS);
        
    gluDeleteQuadric(quadric);
}

