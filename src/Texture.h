//
//  Texture.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 01/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Texture__
#define __CGFLib_1__Texture__

#include <iostream>
#include <string>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <unistd.h>
#else
#include <GL/glut.h>
#endif
#include <GL/glui.h>

using namespace std;

class Texture {
private:
    string ids;
    string file;
    
    GLint width; // recebe valor do loadRGBImage
    GLint height; // recebe valor do loadRGBImage
    GLuint texID; // recebe valor do glGenTexture

public:
    Texture(string ids, string file);
    ~Texture();
    
    string getIds();
    string getFile();
    GLint getWidth();
    GLint getHeight();
    GLuint getTexID();
    
    void setIds(string);
    void setFile(string);
    void setWidth(GLint);
    void setHeight(GLint);
    void setTexID(GLuint);
    
    bool operator() (Texture*, Texture*);
    
    void print();
    
    void loadTexture();
    void apply();
};

#endif /* defined(__CGFLib_1__Texture__) */
