#include "Server.h"
#include <string>
#include <vector>
#include "MyWindow.h"

using std::string;
using std::vector;

MyWindow::MyWindow(void)
{
}

MyWindow::~MyWindow(void)
{
}

void MyWindow::OnCreate(){
	_hud.SetWindowDimensions(Width(), Height());
	_hud.CloseWindow();

	_scene.SetHWND(GetSafeHwnd());
	_scene.OnCreate(Height(), Width());
	SetFullscreen(true);
}

void MyWindow::OnDisplay(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_scene.Update((float)App::GetDeltaTime());
	_scene.Draw();
	_hud.SetText(_scene.GetText());
	_hud.DrawText();
	SwapBuffers();
}

void MyWindow::OnResize(int width, int height){

	GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, aspectRatio, 0.1, 40.0);
	glMatrixMode(GL_MODELVIEW);
}
