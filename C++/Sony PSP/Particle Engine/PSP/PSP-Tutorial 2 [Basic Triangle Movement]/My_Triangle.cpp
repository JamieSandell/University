#include "My_Triangle.h"
My_Triangle::My_Triangle(void)	{}
My_Triangle::~My_Triangle(void)	{}

void My_Triangle::Initalise()
{
	// Set Background colour
	sceGuClearColor(0xff050505);
	
	// Create View array and Display array
	int view[4] = {2048, 2048, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT};
	float disp[6] = {
			-6.0f,
			6.0f,
			-3.0f*((float)SCEGU_SCR_HEIGHT*2)/(float)SCEGU_SCR_WIDTH,
			3.0f*((float)SCEGU_SCR_HEIGHT*2)/(float)SCEGU_SCR_WIDTH,
			-10.0f,
			10.0f};

	// Pass to Camera
	_camera = Camera3D(view,disp);


	// Basic Triangle Points
	_array[0] = Vector3(-50,0,0);
	_array[1] = Vector3(0,100,0);
	_array[2] = Vector3(50,0,0);
	// Colour Triangle Points
	_colour_array[0].Vector = _array[0];
	_colour_array[0].Col.Set(Colour::Green());
	_colour_array[1].Vector = _array[1];
	_colour_array[1].Col.Set(Colour::Blue());
	_colour_array[2].Vector = _array[2];
	_colour_array[2].Col.Set(Colour::Red());
	// Texture Triangle Points
	_texture_array[0].Vector = _array[0];
	_texture_array[0].Tex = Vector2(0,0);
	_texture_array[1].Vector = _array[1];
	_texture_array[1].Tex = Vector2(0.5f,1);
	_texture_array[2].Vector = _array[2];
	_texture_array[2].Tex = Vector2(1,0);
	// Full Triangle Points
	_full_array[0].Vector = _array[0];
	_full_array[0].Col.Set(Colour::Green());
	_full_array[0].Tex = Vector2(0,0);
	_full_array[1].Vector = _array[1];
	_full_array[1].Col.Set(Colour::Blue());
	_full_array[1].Tex = Vector2(0.5f,1);
	_full_array[2].Vector = _array[2];
	_full_array[2].Col.Set(Colour::Red());
	_full_array[2].Tex = Vector2(1,0);

	sceGumSetMatrixStack(Matrix(), 8, 8, 32, 0);

	// Update the Camera Position
	_camera.Set(Vector3(0, 0, 100), Vector3( 0, 0, 0 ), 0, 0);
	_camera.Update();
	_mode = Col;
	_tex.Load_Texture(File("test.gim"));
	// Begin Timer (Throw away float)
	_timer.Tick();

}
void My_Triangle::Idle()
{
	float dt = _timer.Tick();
	// Select Camera or Mode Control
	if (Controller::Select())
		_camera_enabled = !_camera_enabled;
	// Camera Control Mode
	if (_camera_enabled)
	{
		if (Controller::D_Left())
			_camera.MoveLeft(1);
			//_trans.SelfAdd(Vector3(-1,0,0));
		if (Controller::D_Right())
			_camera.MoveRight(1);
			//_trans.SelfAdd(Vector3(1,0,0));
		if (Controller::D_Up())
			_camera.MoveUp(1);
			//_trans.SelfAdd(Vector3(0,1,0));
		if (Controller::D_Down())
			_camera.MoveDown(1);
		if (Controller::Triangle())
			_camera.MoveIn(1);
		if (Controller::Cross())
			_camera.MoveOut(1);
	}
	// Mode Control Mode
	else
	{
		// Movement
		if (Controller::D_Left())
			_trans.SelfAdd(Vector3(-1,0,0));
		if (Controller::D_Right())
			_trans.SelfAdd(Vector3(1,0,0));
		if (Controller::D_Up())
			_trans.SelfAdd(Vector3(0,1,0));
		if (Controller::D_Down())
			_trans.SelfAdd(Vector3(0,-1,0));
		// Mode
		if (Controller::Square())
			_mode = Col;
		if (Controller::Triangle())
			_mode = Tex;
		if (Controller::Circle())
			_mode = Full;
		if (Controller::Cross())
			_mode = Basic;
	}
}

void My_Triangle::Render()
{
	_camera.Update();
	// Set Some Debug Text to title the Application
	sceGuDebugPrint(0, 30, Colour::Red(), 
				"PSP-Tutorial 2: Basic Triangle");

	unsigned long long  urLongNum = sceKernelGetSystemTimeWide();
	SceUInt64 t = sceKernelGetSystemTimeWide();
	float time = urLongNum;
	time /= 1000000.0f;
	char strLong[50];
	sprintf(strLong, "Time: %f(s)", time);

	sceGuDebugPrint(0, 50, Colour::Red(),
					strLong);
	_timer.Print_to_Screen(0,100);
	//Set Colour to Green
	sceGuColor(0xff00ff00);

	sceGumPushMatrix();
		sceGumTranslate((const ScePspFVector3 *)&_trans);
		//Draw the array above defined
		switch (_mode)
		{
		case Basic:
			sceGuColor(Colour::Green());
			sceGumDrawArray(	SCEGU_PRIM_TRIANGLES,
								VER_FORM,
								3,
								NULL,
								(ScePspFVector3*)_array);
			break;
		case Col:
			sceGuColor(Colour().White());
			sceGumDrawArray(	SCEGU_PRIM_TRIANGLES,
								V_CV,
								3,
								NULL,
								(ScePspFVector3*)_colour_array);
			break;
		case Tex:
			sceGuColor(Colour().White());
			_tex.Enable();
			sceGumDrawArray(	SCEGU_PRIM_TRIANGLES,
								V_TV,
								3,
								NULL,
								(ScePspFVector3*)_texture_array);
			_tex.Disable();
			break;
		case Full:
			sceGuColor(Colour().White());
			_tex.Enable();
			sceGumDrawArray(	SCEGU_PRIM_TRIANGLES,
								V_TCV,
								3,
								NULL,
								(ScePspFVector3*)_full_array);
			_tex.Disable();
			break;
		}

	sceGumPopMatrix();
}