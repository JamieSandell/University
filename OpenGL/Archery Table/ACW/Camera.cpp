#include "Camera.h"

Camera::Camera(void)
{
	//glRotated(90, 0, 0, 1);         //Audience view
	//gluLookAt(0.0f, 120.0f, 0.0f,
	//	120.0f, 120.0f, -1.0f,
	//	0.0f, 1.0f, 0.0f);

	//gluLookAt(60.0f, 100.0f, 250.0f, // Plan View
	//	60.0f, 100.0f, -1.0f,
	//	0.0f, 1.0f, 0.0f); 

	//glRotated(0, 1, 0, 0);         //Front View
	//gluLookAt(60.0f, 0.0f, 0.0f,
	//	60.0f, 255.0f, -1.0f,
	//	0.0f, 1.0f, 0.0f);


	// plan view
	//gluLookAt(0,1275,4000, 0,1275,0, 0,1,0);

	_currentCamera = 0; // 0 for 1, 1 for 2, 2 for 3 0 == plan view, 1 == side view, 3 == disc view
	_planViewRow1.SetVector(0, 1275.0, 4000);
	_planViewRow2.SetVector(0, 1275.0, 0.0);
	_planViewRow3.SetVector(0.0, 1.0, 0.0);

	_sideViewRow1.SetVector(0.0, 1200.0, 3000.0);
	_sideViewRow2.SetVector(0.0, 1200.0, 0.0);
	_sideViewRow3.SetVector(0.0, 1.0, 0.0);

	_discViewRow1.SetVector(600.0, 0.0, 1000.0);
	_discViewRow2.SetVector(600.0, 1200.0, 0.0);
	_discViewRow3.SetVector(0.0, 1.0, 0.0);

	_vectorOfCamera.push_back(&_planViewRow1); // Add each row for gluLookAt
	_vectorOfCamera.push_back(&_planViewRow2);
	_vectorOfCamera.push_back(&_planViewRow3);
	_rotation = false;
}

Camera::~Camera(void)
{
}

// Change the current camera
void Camera::ChangeCurrentCamera(const Vector3d &input)
{
		switch (_currentCamera)
		{
		case 0: // plan view


			_currentCamera = 1; // side view
			_rotation = true;
			_rotationNumbers.push_back(90); // glRotated(90, 0, 0, 1);
			_rotationNumbers.push_back(0);
			_rotationNumbers.push_back(0);
			_rotationNumbers.push_back(1);
			break;
		case 1: // side view
			_discViewRow1.SetVector(input.X(), input.Y(), 1000.0); // TODO://
			// Change this so it follows the disc, add a view method that is called and updated in the
			// Draw method

			_currentCamera = 2; // disc view
			_rotation = false;
			break;
		case 2: // disc view
			_currentCamera = 0; // plan view
			_rotation = false;


			break;
		default: // Shouldn't be here
			break;
		}
}

vector <Vector3d*> Camera::GetCurrentCamera() const
{
	return _vectorOfCamera;
}
vector<double> Camera::GetRotationNumbers() const
{
	return _rotationNumbers;
}

bool Camera::GetRotationStatus() const
{
	return _rotation;
}
void Camera::ViewCamera(const Vector3d &input)
{
	switch(_currentCamera)
	{
	case 0: // plan view
		_vectorOfCamera.clear(); // Empty the vector
		_vectorOfCamera.push_back(&_planViewRow1); // Add each row for gluLookAt
		_vectorOfCamera.push_back(&_planViewRow2);
		_vectorOfCamera.push_back(&_planViewRow3);
		gluLookAt(_planViewRow1.X(), _planViewRow1.Y(), _planViewRow1.Z(),
			_planViewRow2.X(), _planViewRow2.Y(), _planViewRow2.Z(),
			_planViewRow3.X(), _planViewRow3.Y(), _planViewRow3.Z());
		break;
	case 1: // side view
		_vectorOfCamera.clear();
		_vectorOfCamera.push_back(&_sideViewRow1); // Add each row for gluLookAt
		_vectorOfCamera.push_back(&_sideViewRow2);
		_vectorOfCamera.push_back(&_sideViewRow3);
		gluLookAt(_sideViewRow1.X(),input.Y(), _sideViewRow1.Z(),
			_sideViewRow2.X(), input.Y(), _sideViewRow2.Z(),
			_sideViewRow3.X(), _sideViewRow3.Y(), _sideViewRow3.Z());
		break;
	case 2: // Disc view
		_discViewRow1.SetVector(input.X(), input.Y(), 1000.0);
		_discViewRow2.SetVector(input.X(), input.Y(), 0.0);
		_vectorOfCamera.clear(); // Empty the vector
		_vectorOfCamera.push_back(&_discViewRow1); // Add each row for gluLookAt
		_vectorOfCamera.push_back(&_discViewRow2);
		_vectorOfCamera.push_back(&_discViewRow3);
		gluLookAt(_discViewRow1.X(), _discViewRow1.Y(), _discViewRow1.Z(),
			_discViewRow2.X(), _discViewRow2.Y(), _discViewRow2.Z(),
			_discViewRow3.X(), _discViewRow3.Y(), _discViewRow3.Z());
		break;
	}
}