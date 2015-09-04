//
//  Plane.h
//  CGFLib-1

#ifndef __CGFLib_1__Plane__
#define __CGFLib_1__Plane__

#include <iostream>
#include <string>

#include "Primitive.h"

using namespace std;

class Plane : public Primitive {
private:
    GLint divisions;
    
public:
    Plane(GLint divisons);   
    
	GLint getDivisions();
	void setDivisions(GLint);
    
    void print();    
    void draw();
};

#endif /* defined(__CGFLib_1__Plane__) */
