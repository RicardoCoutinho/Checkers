#include "Interface.h"
#include "YAFScene.h"
#include "Application.h"
#include <GL/glui.h>

#define MOUSE_ROTATE_FACTOR 0
#define MOUSE_PAN_FACTOR 0
#define MOUSE_ZOOM_FACTOR 0

//#define MOUSE_ROTATE_FACTOR 0.5
//#define MOUSE_PAN_FACTOR 0.05
//#define MOUSE_ZOOM_FACTOR 0.5

#define CG_CGFcamera_AXIS_X 0
#define CG_CGFcamera_AXIS_Y 1
#define CG_CGFcamera_AXIS_Z 2

int Interface::modifiers=0;

Interface::Interface() {
    gamemode = false;
}

Interface::~Interface() {
}

Interface * Interface::activeInterface=NULL;

void Interface::setScene(YAFScene* sc)
{
	scene=sc;
}

float Interface::getDisplacementY()
{
    return displacementY;
}


void Interface::init(int parent) {
    
	//glui_window = GLUI_Master.create_glui_subwindow(parent, GLUI_SUBWINDOW_LEFT);
	GLUI_Master.set_glutKeyboardFunc(Interface::preprocessKeyboard);
    
	GLUI_Master.set_glutMouseFunc(Interface::preprocessMouse);
	glutMotionFunc(Interface::preprocessMouseMoved);
	glutPassiveMotionFunc(Interface::preprocessPassiveMouseMoved);
	displacementX = 0;
	displacementY = 0;
    
	pressing_left=false;
	pressing_right=false;
	pressing_middle=false;
    
	prev_X = 0;
	prev_Y = 0;
}

void Interface::initGUI()
{
}


GLUI_Checkbox* Interface::addCheckbox(char* name, int* value, int id )
{
	return glui_window->add_checkbox(name, value, id, Interface::preprocessGUI);
}

GLUI_Checkbox* Interface::addCheckboxToPanel(GLUI_Panel *p,char* name, int* value,int id )
{
	return glui_window->add_checkbox_to_panel(p,name, value,id,Interface::preprocessGUI);
}

GLUI_Button* Interface::addButton(char* name,int id)
{
	return glui_window->add_button(name, id, Interface::preprocessGUI);
}

GLUI_Button* Interface::addButtonToPanel(GLUI_Panel *p,char* name, int id  )
{
	return glui_window->add_button_to_panel(p,name, id, Interface::preprocessGUI);
}

void Interface::addColumn()
{
	glui_window->add_column();
}

void Interface::addColumnToPanel(GLUI_Panel *p)
{
	glui_window->add_column_to_panel(p);
}

GLUI_EditText* Interface::addEditText(char* name, char* var, int id )
{
	return glui_window->add_edittext(name,GLUI_EDITTEXT_STRING, var,id,Interface::preprocessGUI);
}

GLUI_EditText* Interface::addEditText(char* name, int* var, int id  )
{
	return glui_window->add_edittext(name,GLUI_EDITTEXT_INT, var,id,Interface::preprocessGUI);
}

GLUI_EditText* Interface::addEditText(char* name, float* var, int id  )
{
	return glui_window->add_edittext(name,GLUI_EDITTEXT_FLOAT, var,id,Interface::preprocessGUI);
}

GLUI_EditText* Interface::addEditTextToPanel(GLUI_Panel *p,char* name, char* var, int id  )
{
	return glui_window->add_edittext_to_panel(p,name,GLUI_EDITTEXT_FLOAT, var,id,Interface::preprocessGUI);
}

GLUI_EditText* Interface::addEditTextToPanel(GLUI_Panel *p,char* name, int* var, int id )
{
	return glui_window->add_edittext_to_panel(p,name,GLUI_EDITTEXT_FLOAT, var,id,Interface::preprocessGUI);
}

GLUI_EditText* Interface::addEditTextToPanel(GLUI_Panel *p,char* name, float* var, int id  )
{
	return glui_window->add_edittext_to_panel(p,name,GLUI_EDITTEXT_FLOAT, var,id,Interface::preprocessGUI);
}

GLUI_Listbox* Interface::addListbox(char* name, int* var, int id )
{
	return glui_window->add_listbox(name,var,id,Interface::preprocessGUI);
}

GLUI_Listbox* Interface::addListboxToPanel(GLUI_Panel *p,char* name, int* var, int id)
{
	return glui_window->add_listbox_to_panel(p,name,var,id,Interface::preprocessGUI);
}

GLUI_Panel* Interface::addPanel(char* name, int type )
{
	return glui_window->add_panel(name,type);
}

GLUI_Panel* Interface::addPanelToPanel(GLUI_Panel *p,char* name, int type)
{
	return glui_window->add_panel_to_panel(p,name,type);
}

GLUI_RadioButton* Interface::addRadioButtonToGroup(GLUI_RadioGroup * group, char * name)
{
	return glui_window->add_radiobutton_to_group(group,name);
}

GLUI_RadioGroup* Interface::addRadioGroup(int *var, int id )
{
	return glui_window->add_radiogroup(var,id,Interface::preprocessGUI);
    
}

GLUI_RadioGroup* Interface::addRadioGroupToPanel(GLUI_Panel *p,int *var, int id)
{
	return glui_window->add_radiogroup_to_panel(p,var,id,Interface::preprocessGUI);
    
}

GLUI_Rollout* Interface::addRollout(char *name, int open, int type )
{
	return glui_window->add_rollout(name,open,type);
}

GLUI_Rollout* Interface::addRolloutToPanel(GLUI_Panel* p,char *name, int open, int type )
{
	return glui_window->add_rollout_to_panel(p,name,open,type);
}

void Interface::addSeparator()
{
	return glui_window->add_separator();
}

void Interface::addSeparatorToPanel(GLUI_Panel *p)
{
	return glui_window->add_separator_to_panel(p);
}

GLUI_Rotation* Interface::addRotation(char* name, float* var, int id)
{
	return glui_window->add_rotation(name,var,id,Interface::preprocessGUI);
}

GLUI_Rotation* Interface::addRotationToPanel(GLUI_Panel *p,char* name, float* var, int id)
{
	return glui_window->add_rotation_to_panel(p,name,var,id,Interface::preprocessGUI);
}


GLUI_Spinner* Interface::addSpinner(char* name, int type, int* var, int id)
{
	return glui_window->add_spinner(name,type,var,id,Interface::preprocessGUI);
}

GLUI_Spinner* Interface::addSpinnerToPanel(GLUI_Panel* p,char* name, int type, int* var, int id )
{
	return glui_window->add_spinner_to_panel(p,name,type,var,id,Interface::preprocessGUI);
}

GLUI_StaticText* Interface::addStaticText(char* name)
{
	return glui_window->add_statictext(name);
}

GLUI_StaticText* Interface::addStaticTextToPanel(GLUI_Panel *p,char* name)
{
	return glui_window->add_statictext_to_panel(p,name);
}

GLUI_Translation* Interface::addTranslationToPanel(GLUI_Panel* p,char* name, int type, float* var, int id)
{
	return glui_window->add_translation_to_panel(p,name,type,var,id,Interface::preprocessGUI);
}

GLUI_Translation* Interface::addTranslation(char* name, int type, float* var, int id)
{
	return glui_window->add_translation(name,type,var,id,Interface::preprocessGUI);
}

void Interface::preprocessKeyboard(unsigned char key, int x, int y)
{
	modifiers=glutGetModifiers();
	activeInterface->processKeyboard(key,x,y);
}

void Interface::preprocessMouse(int button, int state, int x, int y) {
	modifiers=glutGetModifiers();
	activeInterface->processMouse(button, state, x,y);
}

void Interface::preprocessMouseMoved(int x, int y) {
	activeInterface->processMouseMoved(x,y);
}

void Interface::preprocessPassiveMouseMoved(int x, int y)
{
	activeInterface->processPassiveMouseMoved(x,y);
}

void Interface::syncVars()
{
	/****************************************************************/
	/*            This demonstrates GLUI::sync_live()               */
	/*   We change the value of a variable that is 'live' to some   */
	/*   control.  We then call sync_live, and the control          */
	/*   associated with that variable is automatically updated     */
	/*   with the new value.  This frees the programmer from having */
	/*   to always remember which variables are used by controls -  */
	/*   simply change whatever variables are necessary, then sync  */
	/*   the live ones all at once with a single call to sync_live  */
	/****************************************************************/
    
	//glui_window->sync_live();
}

void Interface::preprocessGUI(GLUI_Control *ctrl)
{
	activeInterface->processGUI(ctrl);
}



// Default handlers (to be overriden by sub-class)

void Interface::processKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
            /*
		case 'w':
			//scene->cameras->getCamera(scene->camID)->setWalkMode();
			break;
		case 'e':
			//scene->cameras->getCamera(scene->camID)->setExamineMode();
			break;
            */
		case 's':
			Application::snapshot();
			break;
            
        case 48:
            scene->appearances->getAppearance("floor")->setTexture(scene->textures->getTexture("board0"));
            break;
        case 49:
            scene->appearances->getAppearance("floor")->setTexture(scene->textures->getTexture("board1"));
            break;
        case 50:
            scene->appearances->getAppearance("floor")->setTexture(scene->textures->getTexture("board2"));
            break;
            
            
        case 'q':
            if (!scene->board->menu) scene->camID = 30;
            break;
        case 'w':
            if (!scene->board->menu) scene->camID = 31;
            break;
        case 'e':
            if (!scene->board->menu) scene->camID = 32;
            break;
        case 'r':
            if (!scene->board->menu) scene->camID = 33;
            break;
            
        case 'u':
            if (scene->board->menu || scene->board->gameover!=0) return;
            if ( scene->board->replay || (scene->board->placementsLeft[0]==12 && scene->board->placementsLeft[0]==12 )) ;
            else
            {
                scene->board->undo();
            }
            break;
            
        case 'i':
            if (scene->board->menu || scene->board->gameover==0) return;
            if (scene->board->gameover!=0 && scene->board->replay == 0)
            {
                scene->board->replay = true;
                scene->board->reset();
                scene->board->start_time = 0;
                scene->board->actual_time = 0;
                scene->board->actual_play = 0;
                scene->board->itplay = scene->board->plays.begin();
                
                scene->board->replayGame();
            }
            break;
            
		case 27:		// tecla de escape termina o programa
			exit(0);
			break;
	}
}

void Interface::processMouse(int button, int state, int x, int y) {
    
	
	prev_X = x;
	prev_Y = y;
    
	pressing_left = (button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN);
	pressing_right = (button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN);
	pressing_middle = (button == GLUT_MIDDLE_BUTTON) && (state == GLUT_DOWN);
    
	glutPostRedisplay();
	
}

void Interface::processMouseMoved(int x, int y) {
	
	// pedido de refrescamento da janela
	displacementX = x- prev_X;
	displacementY = y- prev_Y;
    
	if(pressing_left && modifiers==0)
	{
		scene->cameras->getCamera(scene->camID)->rotate(CG_CGFcamera_AXIS_X, displacementY*MOUSE_ROTATE_FACTOR);
		scene->cameras->getCamera(scene->camID)->rotate(CG_CGFcamera_AXIS_Y, displacementX*MOUSE_ROTATE_FACTOR);
	}
	else if(pressing_right && modifiers==0)
	{
		scene->cameras->getCamera(scene->camID)->translate(CG_CGFcamera_AXIS_X, displacementX*MOUSE_PAN_FACTOR);
		scene->cameras->getCamera(scene->camID)->translate(CG_CGFcamera_AXIS_Y, -displacementY*MOUSE_PAN_FACTOR);
	}
	else if(pressing_middle || (pressing_left && modifiers & GLUT_ACTIVE_CTRL))
	{
		scene->cameras->getCamera(scene->camID)->translate(CG_CGFcamera_AXIS_Z, displacementY*MOUSE_ZOOM_FACTOR);
	}
    
	prev_X = x;
	prev_Y = y;
    
	glutPostRedisplay();
    
}

void Interface::processPassiveMouseMoved(int x, int y) {
    
	// pedido de refrescamento da janela
	glutPostRedisplay();
}

void Interface::processGUI(GLUI_Control *ctrl)
{ 
}

