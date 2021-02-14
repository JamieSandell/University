#include "GXBase.h"
#include "MyWindow.h"

using namespace gxbase;

class MyApp :public App {
public:

	MyWindow w;
	MyApp();

};

MyApp::MyApp() : w(-90){

}

// this is the single instance of our application
//
static MyApp tut5;
