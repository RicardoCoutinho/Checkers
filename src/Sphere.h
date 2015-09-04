#ifndef __CGFLib_1__Sphere__
#define __CGFLib_1__Sphere__

#include <iostream>
#include <string>

#include "Primitive.h"

using namespace std;

class Sphere : public Primitive {
private:
	GLfloat radius;
    GLint slices;
    GLint stacks;
    	
public:
    Sphere(GLfloat radius, GLint slices, GLint stacks);

	GLfloat getRadius();
	GLint getSlices();
	GLint getStacks();
    
	void setRadius(GLfloat);
	void setSlices(GLint);
	void setStacks(GLint);
	
    void print();
    
    void draw();
};

#endif /* defined(__CGFLib_1__Sphere__) */
