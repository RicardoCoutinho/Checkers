//
//  Patch.h
//  CGFLib-1

#ifndef __CGFLib_1__Patch__
#define __CGFLib_1__Patch__

#include <iostream>
#include <string>

#include "Primitive.h"

using namespace std;

class Patch : public Primitive {
private:
    GLint order;    
	GLint partsU;
	GLint partsV;
	string compute;
	vector <vector<GLfloat> > controlpoints;
    
public:
    Patch(GLint order, GLint partsU, GLint partsV, string compute, vector <vector<GLfloat> >  controlpoints);

    void print();    
    void draw();
};

#endif /* defined(__CGFLib_1__Patch__) */
