#pragma once
#include <vector>
#include "GXBase.h"
#include "Text.h"

using namespace gxbase;

class Hud : public GLWindow
{
public:
	Hud(void);
	~Hud(void);

	inline void CloseWindow(void){Close();};//The Hude inherits from GLWindow, which automatically creates
		// a window, use this to close that window.
	void DrawText(void);
	inline void ResetPerspectiveProjection(void){
			glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	};
	inline void SetOrthographicProjection(void){
		// switch to projection mode
		glMatrixMode(GL_PROJECTION);
		// save previous matrix which contains the 
		//settings for the perspective projection
		glPushMatrix();
			// reset matrix
			glLoadIdentity();
			// set a 2D orthographic projection
			gluOrtho2D(0,_windowX,0,_windowY);
			//glOrtho(0, 500, 0, 500);
			// invert the y axis, down is positive
			//glScalef(1, -1, 1);
			// mover the origin from the bottom left corner
			// to the upper left corner
			//glTranslatef(0, -480, 0);
			glMatrixMode(GL_MODELVIEW);
	};
	//inline void SetGLWindow(const GLWindow &glWindow){_glWindow=glWindow;};
	inline void SetText(const std::vector<Text> &text){_text=text;};
	inline void SetWindowDimensions(int x, int y){_windowX=x;_windowY=y;};

private:
	std::vector<Text> _text;
	//GLWindow _glWindow;
	int _windowX, _windowY;
};
