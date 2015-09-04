//
//  LinearAnimation.h
//  CGFLib-1
//

#ifndef __CGFLib_1__LinearAnimation__
#define __CGFLib_1__LinearAnimation__

#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <ctime>
#include <math.h>

#include "Animation.h"

using namespace std;

class LinearAnimation : public Animation {
private:

	GLfloat angle;
	    
public:
    bool end;
    
	LinearAnimation(string ids, GLfloat span, string type, GLint ncpt, GLfloat** cpt);
	//~LinearAnimation();

	void init();	
	void reset();
	void update();
	void apply();
    void print();    	
};

#endif /* defined(__CGFLib_1__LinearAnimation__) */
