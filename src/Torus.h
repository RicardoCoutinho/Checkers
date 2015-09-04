#ifndef __CGFLib_1__Torus__
#define __CGFLib_1__Torus__

#include <iostream>
#include <string>

#include "Primitive.h"

using namespace std;

class Torus : public Primitive {
private:
   GLfloat inner;
   GLfloat outer;
   GLint slices;
   GLint loops;

public:
    Torus(GLfloat inner, GLfloat outer, GLint slices, GLint loops);
    
    GLfloat getInner();
    GLfloat getOuter();
    GLint getSlices();
    GLint getLoops();

    void setInner(GLfloat);
    void setOuter(GLfloat);
    void setSlices(GLint);
    void setLoops(GLint);

    void print();
    
    void draw();

};

#endif /* defined(__CGFLib_1__Torus__) */
