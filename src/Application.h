#ifndef __CGFLib_1__Application__
#define __CGFLib_1__Application__

#include "YAFScene.h"
#include "Interface.h"

#include <stdexcept>
#include <string>

class Application
/// Main class for an Application where you can add Scenes, Interfaces and manage other aspects of the Application.
{
public:
    
    Application();
    ~Application();
    void init(int*, char**); ///< Initial method, should be called from main and have (argc, argv) passed through
    void run();				 ///< Main Application loop; should be called after initializing and setting the active Scene and Interface using _setScene()_ and _setInterface()_
    
    void setScene(YAFScene* gls);			///< Associates the provided Scene with the Application, and initializes it
    void setInterface(Interface* gli);	///< Associates the provided Interface with the Application and the previously associated Scene, and initializes it
    
    int getMainWindow();			///< Returns the OpenGL handle to the main Application window
    
    static void snapshot();			///< Takes a snapshot of the Application window and stores it in PNG format in the working directory, with a timestamp.
    
    static float xy_aspect;			///< Aspect ratio of the Application window
    static int width;				///< Width of the Application window
    static int height;				///< Height of the Application window
    static int vpx, vpy, vpw, vph;	///< Viewport coordinates and dimensions within the Application window, excluding the Interface area.
    
    static unsigned long getTime();			///< Returns the current time in milliseconds to be used in time-based updates and other actions. The time base may vary from platform to platform, can be from a specific date, or from the start of the Application.
    
    void forceRefresh();			///< Forces the Application to refresh, including updating the viewports and corresponding projection matrices
    
    static Application *activeApp;
    
// ----
    
    
    void enableGamemode() {
        if (!app_interface->gamemode) {
            int width = glutGet(GLUT_SCREEN_WIDTH);
            int height = glutGet(GLUT_SCREEN_HEIGHT);
            char* mode;
            
            asprintf(&mode, "%dx%d:32", width, height);
            glutGameModeString(mode);
            if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
                app_interface->gamemode = true;
                glutEnterGameMode();
                
            }
            
        }
        
    };
    
    
    void activate();
    
    static int app_window;
    
    YAFScene* app_scene;
    
    Interface* app_interface;
    
    static bool refreshRequested;
    
    void static gluiIdleFunction(void);		///< Static idle handler to be registered in GLUT/GLUI. It is responsible to route execution to any handlers specific of the active Application, Scene and/or Interface.
    void static reshape(int, int);			///< Static reshape handler to be registered in GLUT/GLUI. It is responsible to handle reshape in terms of Application, and to update the active camera of the active Scene.
    void static display();					///< Static display handler to be registered in GLUT/GLUI. It is responsible to route execution to the active Scene's Scene::display() handler.
    void environmentInit();					///< Called at the end of init(), it sets the default OpenGL parameters, such as culling, depth testing, etc. (which can later be overriden by Scene::init() ).
    void updateScene();						///<
};

class GLexception: public std::runtime_error
/// Utility class to handle exceptions specific to the library
{
public:
    GLexception(const std::string& what_str): runtime_error(what_str) {}
    
};

#endif /* defined(__CGFLib_1__Application__) */
