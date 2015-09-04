//
//  Animation.h
//  CGFLib-1
//

#ifndef __CGFLib_1__Animation__
#define __CGFLib_1__Animation__

#include <iostream>
#include <string>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <unistd.h>
#else
#include <GL/glut.h>
#endif
#include <GL/glui.h>

using namespace std;

class Animation {
public:
    string ids;
	GLfloat span;
	string type;
	
    GLint cp; // current control point
    GLfloat xyz[3];
    GLint ncpt;
    GLfloat** cpt;
    
    GLint loop;
    bool reset;
	GLfloat startTime;
    GLfloat time;
    
	Animation(string ids, GLfloat span, string type, GLint ncpt, GLfloat** cpt);
    ~Animation();

	string getIds();
    GLfloat getSpan();
    string getType();
    GLint getCp();
    GLfloat* getXYZ();
    GLint getNCpt();
    GLfloat** getCpt();
    
    bool getLoop();
    bool getReset();
    GLfloat getStartTime();
    GLfloat getTime();
    
	void setIds(string);
    void setSpan(GLfloat);
	void setType(string);
    void setCp(GLint cp);
    void setXYZ(GLfloat* xyz); void setX(GLfloat); void setY(GLfloat); void setZ(GLfloat);
    void setNCpt(GLint ncpt);
	void setCpt(GLfloat** cpt);
    
    void setLoop(bool);
    void setReset(bool);
    void setStartTime(GLfloat);
    void setTime(GLfloat);
	
    void nextCp();
    
	virtual void print(){};
    virtual void init(){};
	virtual void apply(){};
};

#endif /* defined(__CGFLib_1__Animation__) */