//
//  Lighting.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 01/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Lighting.h"

Lighting::Lighting(bool doublesided, bool local, bool enabled, GLfloat* ambient)
{
    setDoublesided(doublesided);
    setLocal(local);
    setEnabled(enabled);
    setAmbient(ambient);
    
    nextLight = GL_LIGHT0; //0x4000;
    
    lightMap.clear();
}
Lighting::~Lighting()
{
    map<string,Light*>::iterator it,ite;
    it = lightMap.begin();
    ite = lightMap.end();
    
    for (; it != ite; it++)
    {
        delete it->second;
    }
}

bool Lighting::getDoublesided() {return doublesided;}
bool Lighting::getLocal() {return local;}
bool Lighting::getEnabled() {return enabled;}
GLfloat* Lighting::getAmbient() {return ambient;}
map<string,Light*> Lighting::getLights() {return lightMap;}

void Lighting::setDoublesided(bool doublesided) {this->doublesided = doublesided;}
void Lighting::setLocal(bool local) {this->local = local;}
void Lighting::setEnabled(bool enabled) {this->enabled = enabled;}
void Lighting::setAmbient(GLfloat* ambient)
{
    this->ambient[0] = ambient[0];
    this->ambient[1] = ambient[1];
    this->ambient[2] = ambient[2];
    this->ambient[3] = ambient[3];
}
void Lighting::setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    this->ambient[0] = r;
    this->ambient[1] = g;
    this->ambient[2] = b;
    this->ambient[3] = a;
}

void Lighting::enable() {enabled = true;}
void Lighting::disable() {enabled = false;}

Light* Lighting::getLight(string ids)
{
    if (lightMap.count(ids))
    {
        return lightMap[ids];
    }
    
    return NULL;
}
bool Lighting::addLight(Light* light)
{
    if (nextLight >= GL_LIGHT0 && nextLight <= GL_LIGHT7)
    {
        light->set_GLREF(nextLight);
        this->lightMap.insert(pair<string,Light*>(light->getIds(),light));
        
        nextLight++;
        
        return true;
    }
    
    return false;
}

void Lighting::print() {
    map<string,Light*>::iterator it,ite;
    it = lightMap.begin();
    ite = lightMap.end();
    
    cout << "--- Lighting ---" << endl;
    for (; it != ite; it++)
    {
        it->second->print();
        cout << endl;
    }
}

void Lighting::init( )
{
    if (enabled)
        glEnable(GL_LIGHTING);
    else
        glDisable(GL_LIGHTING);
 
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, doublesided);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, local);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
        
    map<string,Light*>::iterator it,ite;
    it = lightMap.begin();
    ite = lightMap.end();
    
    for (; it != ite; it++)
    {
        it->second->init();
    }

}

void Lighting::run()
{
    map<string,Light*>::iterator it,ite;
    it = lightMap.begin();
    ite = lightMap.end();
    
    for (; it != ite; it++)
    {
        it->second->draw();
    }
}
