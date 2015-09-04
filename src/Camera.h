//
//  Camera.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 27/09/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Camera__
#define __CGFLib_1__Camera__

#include <iostream>
#include <string>

#include "Ref.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <unistd.h>
#else
#include <GL/glut.h>
#endif
#include <GL/glui.h>

enum CAMERA_MODE { EXAMINE_MODE, WALK_MODE, TARGET_MODE };

using namespace std;

class Camera : public Ref {
private:
    GLfloat pos[3];
    GLfloat zNear;
    GLfloat zFar;
    
    GLfloat rotation[3]; // = {0.0,0.0,0.0};
    
    CAMERA_MODE mode;
    
public:
    Camera(int ID, string ids, GLfloat* pos, GLfloat znear, GLfloat zfar);
    ~Camera();
    
    GLfloat* getPos();
    GLfloat getZNear();
    GLfloat getZFar();
    GLfloat* getRotation();
    CAMERA_MODE getMode();
    
    void setPos(GLfloat* xyz);
    void setPos(GLfloat x, GLfloat y, GLfloat z);
    void setPosX(GLfloat x);
    void setPosY(GLfloat y);
    void setPosZ(GLfloat z);
    void setZNear(GLfloat);
    void setZFar(GLfloat);
    
    
    bool operator() (Camera*, Camera*);
    
    virtual void print();
    

    void setExamineMode();
    void setWalkMode();
    
    
    virtual bool rotateTo(GLint axis, GLfloat angle, GLfloat increment = 0.5f);
    virtual bool rotate(GLint axis, GLfloat angle);
    virtual bool setRotation(GLint axis, GLfloat angle);
    virtual bool moveTo(GLint axis, GLfloat value, GLfloat increment=0.5f);
    virtual bool translate(GLint axis, GLfloat value);
    
    virtual void applyView() = 0;
         
    virtual void updateProjectionMatrix(GLint width, GLint height) = 0;
    							
};

#endif /* defined(__CGFLib_1__Camera__) */
