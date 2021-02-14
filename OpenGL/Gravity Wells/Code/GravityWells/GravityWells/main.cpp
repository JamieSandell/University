#include <winsock2.h>
#include "Server.h"
#include "GXBase.h"
#include "MyWindow.h"

using namespace gxbase;

class MyApp :public App {
public:

	MyWindow _w;
	MyApp();

};

MyApp::MyApp(){

}

// this is the single instance of our application
//
static MyApp _gravityWells;