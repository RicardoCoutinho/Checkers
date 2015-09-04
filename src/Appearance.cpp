//
//  Appearance.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 01/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Appearance.h"

#define CG_GLMAT_COLOR 0
#define CG_GLMAT_MATERIAL 1
#define CG_GLMAT_TEXTURE 2

#include "imagetools.h"
#include "Application.h"

Appearance::Appearance(string ids, GLfloat* emissive, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLfloat shininess)
{
    setIds(ids);
    setEmissive(emissive);
    setAmbient(ambient);
    setDiffuse(diffuse);
    setSpecular(specular);
    setShininess(shininess);
    
    materialType = CG_GLMAT_MATERIAL;
    
	texture=NULL;
}
Appearance::Appearance(string ids, GLfloat* emissive, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLfloat shininess, string textureref, GLenum texlength_s, GLenum texlength_t)
{
    setIds(ids);
    setEmissive(emissive);
    setAmbient(ambient);
    setDiffuse(diffuse);
    setSpecular(specular);
    setShininess(shininess);
    
    cout << endl << "THIS IS --->> " << textureref << endl;
    
    setTextureref(textureref);
    setTexlength_s(texlength_s);
    setTexlength_t(texlength_t);
    
    materialType = CG_GLMAT_TEXTURE;
    
	texture=NULL;
}
Appearance::Appearance(GLfloat* c)
{
	color[0] = c[0];
	color[1] = c[1];
	color[2] = c[2];
	color[3] = c[3];
    
	materialType = CG_GLMAT_COLOR;
    
	texture=NULL;
	privateTexture=false;
}

Appearance::~Appearance()
{
    if (texture!=NULL && privateTexture==true)
		delete(texture);
}


string Appearance::getIds() {return ids;}
GLfloat* Appearance::getEmissive() {return emissive;}
GLfloat* Appearance::getAmbient() {return ambient;}
GLfloat* Appearance::getDiffuse() {return diffuse;}
GLfloat* Appearance::getSpecular() {return specular;}
GLfloat Appearance::getShininess() {return shininess;}
string Appearance::getTextureref() {return textureref;}
GLenum Appearance::getTexlength_s() {return texlength_s;}
GLenum Appearance::getTexlength_t() {return texlength_t;}
Texture* Appearance::getTexture() {return texture;}


void Appearance::setIds(string ids) {this->ids = ids;}
void Appearance::setEmissive(GLfloat* rgba)
{
    this->emissive[0] = rgba[0];
    this->emissive[1] = rgba[1];
    this->emissive[2] = rgba[2];
    this->emissive[3] = rgba[3];
}
void Appearance::setEmissive(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    this->emissive[0] = r;
    this->emissive[1] = g;
    this->emissive[2] = b;
    this->emissive[3] = a;
}
void Appearance::setAmbient(GLfloat* rgba)
{
    this->ambient[0] = rgba[0];
    this->ambient[1] = rgba[1];
    this->ambient[2] = rgba[2];
    this->ambient[3] = rgba[3];
}
void Appearance::setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    this->ambient[0] = r;
    this->ambient[1] = g;
    this->ambient[2] = b;
    this->ambient[3] = a;
}
void Appearance::setDiffuse(GLfloat* rgba)
{
    this->diffuse[0] = rgba[0];
    this->diffuse[1] = rgba[1];
    this->diffuse[2] = rgba[2];
    this->diffuse[3] = rgba[3];
}
void Appearance::setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    this->diffuse[0] = r;
    this->diffuse[1] = g;
    this->diffuse[2] = b;
    this->diffuse[3] = a;
}
void Appearance::setSpecular(GLfloat* rgba)
{
    this->specular[0] = rgba[0];
    this->specular[1] = rgba[1];
    this->specular[2] = rgba[2];
    this->specular[3] = rgba[3];
}
void Appearance::setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    this->specular[0] = r;
    this->specular[1] = g;
    this->specular[2] = b;
    this->specular[3] = a;
}
void Appearance::setShininess(GLfloat shininess) {this->shininess = shininess;}
void Appearance::setTextureref(string textureref) {this->textureref = textureref;}
void Appearance::setTexlength_s(GLenum texlength_s) {this->texlength_s = texlength_s;}
void Appearance::setTexlength_t(GLenum texlength_t) {this->texlength_t = texlength_t;}
void Appearance::setTexture(Texture* tex) {this->texture = tex;}


bool Appearance::operator() (Appearance* a, Appearance* b) {return (a->getIds().compare(b->getIds()));}


void Appearance::print()
{
    cout << "- Appearance :: ";
    cout << "| id: " << getIds() << endl;
    cout << "| emissive: {"
    << emissive[0] << ", "
    << emissive[1] << ", "
    << emissive[2] << ", "
    << emissive[3] << "}" << endl;
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
    cout << "| shininess: " << shininess << endl;
    cout << "| textureref: " << textureref << endl;
    cout << "| texlength_s: " << texlength_s << endl;
    cout << "| texlength_t: " << texlength_t << endl;
}


void Appearance::apply()
{
    //glDisable(GL_COLOR_MATERIAL);
    
    if (materialType == CG_GLMAT_COLOR)
    {
        glColorMaterial(GL_FRONT, GL_AMBIENT);
        glColorMaterial(GL_FRONT, GL_DIFFUSE);
        glColorMaterial(GL_FRONT, GL_SPECULAR);
        glColorMaterial(GL_FRONT, GL_SHININESS);
        
        glColor4f(color[0],color[1],color[2],color[3]);
        
        glEnable (GL_COLOR_MATERIAL);
        
    }
    else
    {
        glMaterialfv(GL_FRONT, GL_SPECULAR,  specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   diffuse);
        glMaterialfv(GL_FRONT, GL_AMBIENT,   ambient);
        
        glColor4f(0,0,0,1);
        
        glEnable (GL_COLOR_MATERIAL);
        
    }
    
	if (texture != NULL)
	{
		glEnable(GL_TEXTURE_2D);
		texture->apply();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texlength_s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texlength_t);
	}
    else
    {
        glDisable(GL_TEXTURE_2D);
    }
		
}



