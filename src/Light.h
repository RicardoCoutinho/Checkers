//
//  Light.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 01/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Light__
#define __CGFLib_1__Light__

#define CG_GLIGHT_DEFAULT_COLOR 0.5,0.5,0.5
#define CG_GLIGHT_DEFAULT_BACKGROUND_AMBIENT 0.2,0.2,0.2,1.0
#define CG_GLIGHT_DEFAULT_RADIUS 0.2
#define CG_GLIGHT_DEFAULT_SLICES 8
#define CG_GLIGHT_DEFAULT_STACKS 8
#define CG_GLIGHT_DEFAULT_AMBIENT 0.2,0.2,0.2,1.0
#define CG_GLIGHT_DEFAULT_DIFFUSE 0.5,0.5,0.5,1.0
#define CG_GLIGHT_DEFAULT_SPECULAR 0.4,0.4,0.4,1.0
#define CG_GLIGHT_DEFAULT_KC 2.0
#define CG_GLIGHT_DEFAULT_KL 0.0
#define CG_GLIGHT_DEFAULT_KQ 0.0

#include <iostream>
#include <string>

#include "Appearance.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <unistd.h>
#else
#include <GL/glut.h>
#endif
#include <GL/glui.h>

using namespace std;

class Light {
private:
    string ids;
    bool enabled;
    GLfloat location[4];
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    
    GLfloat kc;
    GLfloat kl;
    GLfloat kq;
        
    GLenum _GLREF;
    
    static float background_ambient[4];
    static Appearance* default_light_material;
    
    Appearance* material;

protected:
    GLUquadric* quadric;
    
public:
    Light(string ids, bool enabled, GLfloat* location, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular);
    ~Light();
    
    string getIds();
    bool getEnabled();
    GLfloat* getLocation();
    GLfloat* getAmbient();
    GLfloat* getDiffuse();
    GLfloat* getSpecular();
    GLfloat getKc();
    GLfloat getKl();
    GLfloat getKq();
    GLenum get_GLREF();
    Appearance* getMaterial();
    
    void setIds(string);
    void setEnabled(bool);
    void setLocation(GLfloat* xyzo);
    void setLocation(GLfloat x, GLfloat y, GLfloat z, GLfloat o);
    void setAmbient(GLfloat* rgba);
    void setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setDiffuse(GLfloat* rgba);
    void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setSpecular(GLfloat* rgba);
    void setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setKc(float);
    void setKl(float);
    void setKq(float);
    void set_GLREF(GLenum);
    void setMaterial(Appearance* material);
    
    bool* controlEnabled();
    
    bool operator() (Light*, Light*);
    
    virtual void print();
    
    virtual void init();
    virtual void update();
    virtual void draw();
    
};

#endif /* defined(__CGFLib_1__Light__) */
