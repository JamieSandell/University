#pragma once
#include <vector>
#include <windows.h>		// Header File For Windows
#include <stdio.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glut.h>		// Header File For The Glaux Library
#include "Vector3d.h"


using namespace std;

class Camera
{
public:
	Camera(void);
	~Camera(void);

	void ChangeCurrentCamera(const Vector3d &input);
	void ViewCamera(const Vector3d &input);

	vector<double> GetRotationNumbers() const;

	bool GetRotationStatus() const;

	vector<Vector3d*> GetCurrentCamera() const;

private:
	vector <Vector3d*> _vectorOfCamera;
	vector <double> _rotationNumbers;
	Vector3d _planViewRow1;
	Vector3d _planViewRow2;
	Vector3d _planViewRow3;
	Vector3d _sideViewRow1;
	Vector3d _sideViewRow2;
	Vector3d _sideViewRow3;
	Vector3d _discViewRow1;
	Vector3d _discViewRow2;
	Vector3d _discViewRow3;
	int _currentCamera;
	bool _rotation;
};
