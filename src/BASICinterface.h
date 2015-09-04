#ifndef BASICinterface_H
#define BASICinterface_H

#include "Interface.h"
#include "Globals.h"
#include "YAFScene.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <unistd.h>
#else
#include <GL/glut.h>
#endif
#include <GL/glui.h>

class BASICinterface: public Interface
{
public:
    bool gamemode;
    
	BASICinterface();

    void initGUI();
	void processGUI(GLUI_Control *ctrl);
    
    virtual void processMouse(int button, int state, int x, int y);
    void performPicking(int x, int y);
    void processHits(GLint hits, GLuint buffer[]);

    GLint lightID;
	GLint nextID;
    
    //Set up an ortho projection with surface size width, height
    void switchToOrtho()
    {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, Application::width, Application::height, 0, 0, 1);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
    };
    
    void switchBack()
    {
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    };
};
#endif