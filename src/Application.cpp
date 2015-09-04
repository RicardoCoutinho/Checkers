#ifndef NO_SHADERS
#include <GL/glew.h>
#endif

#include "Application.h"

#include "version.h"

#include <stdlib.h>
using namespace std;

#include "imagetools.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <unistd.h>
#else
#include <GL/glut.h>
#endif
#include <GL/glui.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif

#define CG_GLAPP_DISPLAY_MODE GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA|GLUT_ALPHA
#define CG_GLAPP_INIT_WIDTH 800
#define CG_GLAPP_INIT_HEIGHT 600
#define CG_GLAPP_INIT_POSX 0
#define CG_GLAPP_INIT_POSY 0
#define CG_GLAPP_REDBITS 8
#define CG_GLAPP_BLUEBITS 8
#define CG_GLAPP_GREENBITS 8

#if __APPLE__
struct timeval _time_start;
#endif

bool gamemode = false;

int Application::app_window = 0;

float Application::xy_aspect = 0;

Application * Application::activeApp = NULL;

int Application::width = 0;
int Application::height = 0;
int Application::vpx = 0;
int Application::vpy = 0;
int Application::vpw = 0;
int Application::vph = 0;

bool Application::refreshRequested=false;



Application::Application() {
    
#if __APPLE__
    gettimeofday(&_time_start, NULL);
#endif
    
	Application::app_window = NULL;
	Application::app_scene = NULL;
    app_interface = NULL;
    
	activate();
}

void Application::activate()
{
	Application::activeApp=this;
}

void Application::setScene(YAFScene* gls)
{
	app_scene = gls;
	app_scene->init();
}

void Application::setInterface(Interface* gli)
{
	app_interface = gli;
	
	app_interface->setScene(app_scene);
	app_scene->setInterface(app_interface);
	
	app_interface->init(Application::app_window);
	app_interface->initGUI();
	
	Interface::setActiveInterface(gli);
}

int Application::getMainWindow()
{
	return Application::app_window;
}


Application::~Application() {
}

void Application::init(int* argc, char** argv) {
    
	try {
		glutInit(argc, argv);
		glutInitDisplayMode(CG_GLAPP_DISPLAY_MODE);
        
		Application::width = CG_GLAPP_INIT_WIDTH;
		Application::height = CG_GLAPP_INIT_HEIGHT;
		glutInitWindowSize(Application::width, Application::height);
		glutInitWindowPosition(CG_GLAPP_INIT_POSX, CG_GLAPP_INIT_POSY);
        
		Application::app_window = glutCreateWindow(argv[0]);
        
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable( GL_BLEND ); glClearColor(0.0,0.0,0.0,0.0);
        
		glutDisplayFunc(Application::display);
		GLUI_Master.set_glutIdleFunc(Application::gluiIdleFunction);
		GLUI_Master.set_glutReshapeFunc(Application::reshape);
        
		environmentInit();
        
#ifndef NO_SHADERS
		glewInit();
#endif
	}
	catch(std::exception&) {
		throw GLexception("Application::init failed");
	}
    
	return;
}

void Application::run() {
	activate();
    
	glutMainLoop();
    
	return;
}

void Application::display() {
	if (refreshRequested)
	{
		reshape(Application::width, Application::height );
		refreshRequested=false;
	}
    
	YAFScene *sc=Application::activeApp->app_scene;
	sc->checkUpdate();
	sc->display();
}

/* GLUI IDLE FUNCTION
 * This function may have to be re-implemented
 */
void Application::gluiIdleFunction()
{
	/* According to GLUT, the current window may be
	 * undefined when idle is called back.
	 */
	if (glutGetWindow()!=Application::app_window) glutSetWindow(Application::app_window);
    
	Application::activeApp->app_interface->syncVars();
    
	glutPostRedisplay();
    
	return;
}

/* ENVIRONMENT INITIALIZATION FUNCTION
 * This function may have to be re-implemented
 */
void Application::environmentInit() {}

void Application::reshape(int w, int h)
{
	Application::width = w;
	Application::height = h;
    
	GLUI_Master.get_viewport_area( &vpx, &vpy, &vpw, &vph );
	glViewport( vpx, vpy, vpw, vph );
	Application::xy_aspect = (float)vpw / (float)vph;
    
	// Inicializacoes da matriz de visualizacao
	activeApp->app_scene->cameras->getCamera(activeApp->app_scene->camID)->updateProjectionMatrix(vpw,vph);
    
	glutPostRedisplay();
}

void Application::forceRefresh()
{
	refreshRequested=true;
}


void Application::snapshot() {
	takeSnapshot(Application::width, Application::height);
}

unsigned long Application::getTime() {
#ifdef _WIN32
    return GetTickCount();
#elif __APPLE__
    struct timeval time_now;
    gettimeofday(&time_now, NULL);
    return (time_now.tv_sec - _time_start.tv_sec ) * 1000 + (time_now.tv_usec / 1000 ) ;
#else
    // glutGet(GLUT_ELAPSED_TIME) was deprecated due to potential to overflow
    struct timespec stime;
    clock_gettime(CLOCK_MONOTONIC, &stime);
    
    return ((stime.tv_sec) * 1000 + stime.tv_nsec/1000000); 
#endif
}

