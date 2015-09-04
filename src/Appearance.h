//
//  Appearance.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 01/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Appearance__
#define __CGFLib_1__Appearance__

#include <iostream>
#include <string>

#include "Texture.h"


using namespace std;

class Appearance {
private:
    string ids;
    GLfloat emissive[4];
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;
    
    string textureref;
    GLenum texlength_s; // s wrap
    GLenum texlength_t; // t wrap
    
    Texture* texture;
    
    GLint materialType;
    GLint color[4];
    bool privateTexture;
    
public:
    Appearance(string ids, GLfloat* emissive, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLfloat shininess);
    Appearance(string ids, GLfloat* emissive, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLfloat shininess, string textureref, GLenum texlength_s, GLenum texlength_t);
    Appearance(GLfloat* color);
    ~Appearance();
    
    string getIds();
    GLfloat* getEmissive();
    GLfloat* getAmbient();
    GLfloat* getDiffuse();
    GLfloat* getSpecular();
    GLfloat getShininess();
    string getTextureref();
    GLenum getTexlength_s();
    GLenum getTexlength_t();
    Texture* getTexture();
    
    void setIds(string);
    void setEmissive(GLfloat* rgba);
    void setEmissive(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setAmbient(GLfloat* rgba);
    void setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setDiffuse(GLfloat* rgba);
    void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setSpecular(GLfloat* rgba);
    void setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setShininess(GLfloat);
    void setTextureref(string);
    void setTexlength_s(GLenum);
    void setTexlength_t(GLenum);
    void setTexture(Texture* tex);
    
    bool operator() (Appearance*, Appearance*);
    
    void print();
    
    void setTexture(string);						///< Loads the texture specified by filename and stores it
    
    void apply();									///< Applies the material (makes it active for whatever is rendered next)
};


#endif /* defined(__CGFLib_1__Appearance__) */
