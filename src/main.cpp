#include <iostream>
#include <exception>

#include "Application.h"
#include "YAFScene.h"
#include "BASICinterface.h"

#include "Board.h"


using std::cout;
using std::exception;


int main(int argc, char* argv[]) {

    
	Application app = Application();

	try {
        app.init(&argc, argv);
        
        #ifdef __APPLE__
        char file[] = "config.yaf";
        #else
        char file[] = "..\\data\\config.yaf";
        #endif
        
        YAFScene* scene = new YAFScene(file);
        Interface* interface = new BASICinterface();
        
		app.setScene(scene);
		app.setInterface(interface);
		
		app.run();
	}
	catch(GLexception& ex) {
		cout << "Error: " << ex.what();
		return -1;
	}
	catch(exception& ex) {
		cout << "Unexpected error: " << ex.what();
		return -1;
	}


    
    //Board* board = new Board();
    //board->start();
    
    
	return 0;
}
