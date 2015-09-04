#include <stdio.h>
#include <string.h>

#include "BASICinterface.h"

// buffer to be used to store the hits during picking
#define BUFSIZE 256
GLuint selectBuf[BUFSIZE];

BASICinterface::BASICinterface():Interface()
{
    lightID = 10;
	nextID = lightID;
}

void BASICinterface::initGUI()
{
    /*
	//Panels
    //GLUI_Panel* panelGlobals = addPanel( (char*) "Globals GUI", 1 );
    //GLUI_Panel* panelDrawmode = addPanelToPanel(panelGlobals, (char*) "Drawmode GUI" , 1);
    
    
	//GLUI_Panel* panelLighting = addPanel( (char*) "Lighting GUI" , 1);
    GLUI_Panel* panelLights = addPanelToPanel(panelLighting, (char*) "Lights GUI" , 1);
    
	GLUI_Panel* panelCameras = addPanel( (char*) "Cameras GUI" , 1);
	 	    
    
    //Wireframe , ID = 2    
    GLUI_RadioGroup* drawBox = addRadioGroupToPanel(panelDrawmode,NULL,2);
    
	addRadioButtonToGroup(drawBox, (char*) "Fill");
	addRadioButtonToGroup(drawBox, (char*) "Lines");
	addRadioButtonToGroup(drawBox, (char*) "Points");
     
    
    //Lights panel , ID = 0
    GLUI_Checkbox lightBox[8];
    
    map<string,Light*> lights = scene->lighting->getLights();
    map<string,Light*>::iterator lt,lte;
    lt = lights.begin();
    lte = lights.end();
    
    int* enabled;
    string str;
    char* cstr;
    
    for (int i=0; lt != lte; lt++, i++)
    {
        str = lt->second->getIds();
        cstr = new char[str.length() + 1 ];
        strcpy(cstr, str.c_str());
        
        enabled = (int*) (lt->second->controlEnabled());
        lightBox[i] = *addCheckboxToPanel(panelLights, cstr, enabled, nextID);        
		lightBox[i].set_int_val(lt->second->getEnabled());
        nextID++;
        delete [] cstr;
    }
    nextID++;
    
    //Cameras panel , ID = 1
    GLUI_Listbox* cameraBox;
    cameraBox = addListboxToPanel(panelCameras, (char*) "Active Camera ",
                                  &(scene->camID), // numero da camera activa
                                  2);
    
    map<string,Camera*> cameras = scene->cameras->getCameras();
    map<string,Camera*>::iterator ct,cte;
    ct = cameras.begin();
    cte = cameras.end();    
    
    for (int i=0; ct != cte; ct++, i++)
    {
        str = ct->second->getIds();
        cstr = new char[str.length() + 1 ];
        strcpy(cstr, str.c_str());
        
        cameraBox->add_item(ct->second->getID(), cstr);
                
        delete [] cstr;         
    }
    nextID++;
     */
}

void BASICinterface::processGUI(GLUI_Control *ctrl)
{
	if(ctrl->get_id() == 2)
	{
		switch(ctrl->get_int_val())
		{
		case 0:
			this->scene->globals->setDrawmode(GL_FILL);
			break;
		case 1:
			this->scene->globals->setDrawmode(GL_LINE);
			break;
		case 2:
			this->scene->globals->setDrawmode(GL_POINT);
			break;
		}
	}
}

void BASICinterface::processMouse(int button, int state, int x, int y)
{
    Interface::processMouse(button,state, x, y);
    
	// do picking on mouse press (GLUT_DOWN)
	// this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
		performPicking(x,y);
    }
    
    if (!scene->board->menu && scene->board->lastPicked!=-1)
    {
        
    }
}

void BASICinterface::performPicking(int x, int y)
{
    //get the actual projection matrix values on an array of our own to multiply with pick matrix later
	GLfloat projmat[16];
	glGetFloatv(GL_PROJECTION_MATRIX,projmat);
    
    // get current viewport and use it as reference for
	// setting a small picking window of 5x5 pixels around mouse coordinates for picking
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
    
	// Sets the buffer to be used for selection and activate selection mode
	glSelectBuffer (BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);
    
    // Initialize the picking name stack
	glInitNames();
    glPushName(0xffffffff);
    
	// The process of picking manipulates the projection matrix
	// so we will be activating, saving and manipulating it
	glMatrixMode(GL_PROJECTION);
    
	//store current projmatrix to restore easily in the end with a pop
	glPushMatrix ();
    
	// reset projection matrix
	glLoadIdentity();
    
	// this is multiplied in the projection matrix
	gluPickMatrix ((GLdouble) x, (GLdouble) (Application::height - y), 5.0, 5.0, viewport);
    
	// multiply the projection matrix stored in our array to ensure same conditions as in normal render
	glMultMatrixf(projmat);
    
	// force scene drawing under this mode
	// only the names of objects that fall in the 5x5 window will actually be stored in the buffer
    scene->drawPicking();
    
	// restore original projection matrix
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();
    
	glFlush();
    
	// revert to render mode, get the picking results and process them
	GLint hits;
	hits = glRenderMode(GL_RENDER);
	processHits(hits, selectBuf);
}

void BASICinterface::processHits (GLint hits, GLuint buffer[])
{
    if (!scene->board->isGameover() || scene->board->replay)
        return;
    
	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *selected=NULL;
	GLuint nselected;
    
	// iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
	for (int i=0;i<hits;i++) {
		int num = *ptr; ptr++;
		GLuint z1 = *ptr; ptr++;
		ptr++;
		if (z1 < mindepth && num>0) {
			mindepth = z1;
			selected = ptr;
			nselected=num;
		}
		for (int j=0; j < num; j++)
			ptr++;
	}
	
    if (scene->board->menu)
    {
        scene->board->menu = false;
        return;
    }
    
	// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
	if (selected!=NULL)
	{
		// this should be replaced by code handling the picked object's ID's (stored in "selected"),
		// possibly invoking a method on the scene class and passing "selected" and "nselected"
		/*
        printf("Picked ID's: ");
		for (int i=0; i<nselected; i++)
        {
			printf("%d ",selected[i]);
        }
		printf("\n");
        */
        
        scene->board->play(selected[0]);
	}
	else
    {
		scene->board->clear_picked();
        scene->board->clear_possible();
        scene->board->setPlaceable();
        //printf("Nothing selected while picking \n");
    }
    
}
