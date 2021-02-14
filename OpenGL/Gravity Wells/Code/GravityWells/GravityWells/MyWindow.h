#pragma once
#include "GXBase.h"
#include "Hud.h"
#include "Scene.h"
#include "Text.h"

using namespace gxbase;

class MyWindow : public GLWindow{
public:
	MyWindow(void);
	~MyWindow(void);

	void OnCreate();
	void OnDisplay();
	inline void OnIdle(){
		Redraw();
		Sleep(25);}
	;
	void OnResize(int width, int height);
	inline void OnKeyboard(int key, bool down){
		_scene.OnKeyboard(key, down);
	}
	inline void OnMouseButton(MouseButton button, bool down){
		_scene.OnMouseButton(button, down);
	};//left = 0, middle = 1, right = 2

private:
	Hud _hud;
	Scene _scene;
};
