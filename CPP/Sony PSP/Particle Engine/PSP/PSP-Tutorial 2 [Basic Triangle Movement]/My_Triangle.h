#pragma once
#include "C:\SEED TFS\PSPDev Kit\PSPFramework.h"
#include "C:\SEED TFS\PSPDev Kit\PSPFramework.Utilities.h"
#include "C:\SEED TFS\PSPDev Kit\PSPFramework.Maths.h"
class My_Triangle :
	public App
{
public:
	My_Triangle(void);
	~My_Triangle(void);

	void Initalise();
	void Idle();
	void Render();

private:
	enum View_Mode{
		Basic,
		Col,
		Tex,
		Full
	};
	bool _camera_enabled;
	View_Mode _mode;
	Camera3D _camera;

	Vector3 _trans;

	Vector3 _array[3];
	Vector_CV _colour_array[3];
	Texture _tex;
	Vector_TV _texture_array[3];
	Vector_TCV _full_array[3];
	Timer _timer;
};