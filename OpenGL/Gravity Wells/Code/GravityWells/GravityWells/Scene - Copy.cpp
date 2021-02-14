#include <string>
#include "Scene.h"
#include "MySphere.h"
#include "Circle.h"
#include "MyCylinder.h"

#define PI  (float)3.1415926

using std::string;
using namespace gxbase;

Scene::Scene(void)
{
}

Scene::~Scene(void)
{
	_textureManager.Destroy();
	delete [] _sphere;
	delete [] _ballPhysics;
}

void Scene::ExtractFrustrum(void){
	float   proj[16];
	float   modl[16];
	float   clip[16];
	float   t;

	/* Get the current PROJECTION matrix from OpenGL */
	glGetFloatv( GL_PROJECTION_MATRIX, proj );

	/* Get the current MODELVIEW matrix from OpenGL */
	glGetFloatv( GL_MODELVIEW_MATRIX, modl );

	/* Combine the two matrices (multiply projection by modelview) */
	clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
	clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
	clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
	clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

	clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
	clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
	clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
	clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

	clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
	clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
	clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
	clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

	clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
	clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
	clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
	clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];

	/* Extract the numbers for the RIGHT plane */
	_frustum[0][0] = clip[ 3] - clip[ 0];
	_frustum[0][1] = clip[ 7] - clip[ 4];
	_frustum[0][2] = clip[11] - clip[ 8];
	_frustum[0][3] = clip[15] - clip[12];

	/* Normalize the result */
	t = sqrt( _frustum[0][0] * _frustum[0][0] + _frustum[0][1] * _frustum[0][1] + _frustum[0][2] * _frustum[0][2] );
	_frustum[0][0] /= t;
	_frustum[0][1] /= t;
	_frustum[0][2] /= t;
	_frustum[0][3] /= t;

	/* Extract the numbers for the LEFT plane */
	_frustum[1][0] = clip[ 3] + clip[ 0];
	_frustum[1][1] = clip[ 7] + clip[ 4];
	_frustum[1][2] = clip[11] + clip[ 8];
	_frustum[1][3] = clip[15] + clip[12];

	/* Normalize the result */
	t = sqrt( _frustum[1][0] * _frustum[1][0] + _frustum[1][1] * _frustum[1][1] + _frustum[1][2] * _frustum[1][2] );
	_frustum[1][0] /= t;
	_frustum[1][1] /= t;
	_frustum[1][2] /= t;
	_frustum[1][3] /= t;

	/* Extract the BOTTOM plane */
	_frustum[2][0] = clip[ 3] + clip[ 1];
	_frustum[2][1] = clip[ 7] + clip[ 5];
	_frustum[2][2] = clip[11] + clip[ 9];
	_frustum[2][3] = clip[15] + clip[13];

	/* Normalize the result */
	t = sqrt( _frustum[2][0] * _frustum[2][0] + _frustum[2][1] * _frustum[2][1] + _frustum[2][2] * _frustum[2][2] );
	_frustum[2][0] /= t;
	_frustum[2][1] /= t;
	_frustum[2][2] /= t;
	_frustum[2][3] /= t;

	/* Extract the TOP plane */
	_frustum[3][0] = clip[ 3] - clip[ 1];
	_frustum[3][1] = clip[ 7] - clip[ 5];
	_frustum[3][2] = clip[11] - clip[ 9];
	_frustum[3][3] = clip[15] - clip[13];

	/* Normalize the result */
	t = sqrt( _frustum[3][0] * _frustum[3][0] + _frustum[3][1] * _frustum[3][1] + _frustum[3][2] * _frustum[3][2] );
	_frustum[3][0] /= t;
	_frustum[3][1] /= t;
	_frustum[3][2] /= t;
	_frustum[3][3] /= t;

	/* Extract the FAR plane */
	_frustum[4][0] = clip[ 3] - clip[ 2];
	_frustum[4][1] = clip[ 7] - clip[ 6];
	_frustum[4][2] = clip[11] - clip[10];
	_frustum[4][3] = clip[15] - clip[14];

	/* Normalize the result */
	t = sqrt( _frustum[4][0] * _frustum[4][0] + _frustum[4][1] * _frustum[4][1] + _frustum[4][2] * _frustum[4][2] );
	_frustum[4][0] /= t;
	_frustum[4][1] /= t;
	_frustum[4][2] /= t;
	_frustum[4][3] /= t;

	/* Extract the NEAR plane */
	_frustum[5][0] = clip[ 3] + clip[ 2];
	_frustum[5][1] = clip[ 7] + clip[ 6];
	_frustum[5][2] = clip[11] + clip[10];
	_frustum[5][3] = clip[15] + clip[14];

	/* Normalize the result */
	t = sqrt( _frustum[5][0] * _frustum[5][0] + _frustum[5][1] * _frustum[5][1] + _frustum[5][2] * _frustum[5][2] );
	_frustum[5][0] /= t;
	_frustum[5][1] /= t;
	_frustum[5][2] /= t;
	_frustum[5][3] /= t;

}

void Scene::GetOGLPos(int x, int y){
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

}

void Scene::OnCreate(int viewportHeight, int viewportWidth){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)viewportWidth / (GLdouble)viewportHeight, 0.1, 40.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0,0, viewportWidth, viewportHeight);
	glEnable(GL_DEPTH_TEST);
	// set the background clear colour to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// set the shade model to smooth (Gouraud shading)
	glShadeModel(GL_SMOOTH);
	// remove back faces
	glEnable(GL_CULL_FACE);

	_angle = 0.0f;

	_eyeZ = -2.0f;
	_centreZ = -10.0f;
	_eyeX = 0.0f;
	_centreX = 0.0f;
	_eyeY = 2.0f;
	_centreY = 0.0f;

	_screenCentreX = viewportWidth/2;
	_screenCentreY = viewportHeight/2;

	//Mouse code
	GLint viewport[4];					// Where The Viewport Values Will Be Stored
	glGetIntegerv(GL_VIEWPORT, viewport);			// Retrieves The Viewport Values (X, Y, Width, Height)

	GLdouble modelview[16];					// Where The 16 Doubles Of The Modelview Matrix Are To Be Stored
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);		// Retrieve The Modelview Matrix

	GLdouble projection[16];				// Where The 16 Doubles Of The Projection Matrix Are To Be Stored
	glGetDoublev(GL_PROJECTION_MATRIX, projection);		// Retrieve The Projection Matrix

	POINT mouse;						// Stores The X And Y Coords For The Current Mouse Position
	GetCursorPos(&mouse);					// Gets The Current Cursor Coordinates (Mouse Coordinates)
	ScreenToClient(_hwnd, &mouse);

	_mousePosX = (int)mouse.x;					// Holds The Mouse X Coordinate
	_mousePosY = (int)mouse.y;					// Holds The Mouse Y Coordinate

	mouse.x = viewportWidth/2;
	mouse.y = viewportHeight/2;

	_mousePosY = _screenCentreY;			// Subtract The Current Mouse Y Coordinate From The Screen Height.
	_mousePosX = _screenCentreX;

	//SetCursorPos(_centreX, _centreY);

	//for (int i = 0; i < 1000; i++){
	//	_sphere[i].Create(Vector3f(0.0f, 0.7f, -5.0f), Vector3f(0.5f, 0.5f, 0.5f), true);
	//	_ballPhysics[i].Create(_sphere[i].GetPosition(), _sphere[i].GetRadius());
	//}
	_ballAmount = 1000;
	_sphere = new MySphere[_ballAmount];
	_ballPhysics = new BallPhysics[_ballAmount];
	float ballRadius = 0.5f;
	float floorRadius = ballRadius * 250;
	float floorArea = PI * (floorRadius*floorRadius);
	float spacing = floorArea/_ballAmount;
	spacing = sqrt(spacing);
	float tempZ = floorRadius-(spacing/2);
	float rowDist = 2 * sqrt((floorRadius*floorRadius) - (tempZ*tempZ));
	float c = (rowDist/2)/spacing;
	float tempX =c *-spacing;
	for (int i = 0; i < _ballAmount; i++)
	{
		_sphere[i].Create(Vector3f(tempX, 0.7f, tempZ), Vector3f(ballRadius, ballRadius, ballRadius), true);
		_ballPhysics[i].Create(_sphere[i].GetPosition(), _sphere[i].GetRadius());
		tempX+= spacing;
		if (tempX > (rowDist/2)){
			tempZ -= spacing;
			rowDist = 2 * sqrt((floorRadius*floorRadius)-(tempZ*tempZ));
			c = (rowDist/2)/spacing;
			tempX =c *-spacing;
		}
	}

	_circle.Create(Vector3f(0.0f, 0.5f, 0.0f), Vector3f(0.5f, floorRadius, 0.5f), false);
	_gravityWell.Create(Vector3f(0.0f, 0.6f, 0.0f), Vector3f(0.5f, 1.0f, 0.5f), false);
	_myCylinder.Create(Vector3f(0.0f, 0.5f, 0.0f), Vector3f(10.0f, floorRadius, 0.5f), false);

	_test = 0;
	_leftMouseButtonDown = _rightMouseButtonDown = false;
	ExtractFrustrum();

	_textureManager = _textureManager.GetSingleton();
	string tex1 = "images\\ball_8.jpg";
	string tex2 = "images\\floor.jpg";
	string tex3 = "images\\wall.jpg";
	GLuint result = _textureManager.LoadTexture(tex1,"CLAMP");
	for (int i = 0; i < _ballAmount; i++)
	{
		_sphere[i].SetTextureEnabledStatus(true);
		_sphere[i].SetTextureID(result);
	}
	result = _textureManager.LoadTexture(tex2, "REPEAT");
	_circle.SetTextureEnabledStatus(true);
	_circle.SetTextureID(result);
	result = _textureManager.LoadTexture(tex3, "REPEAT");
	_myCylinder.SetTextureEnabledStatus(true);
	_myCylinder.SetTextureID(result);
}

void Scene::OnKeyboard(int key, bool down){
	float radius = _gravityWell.GetRadius();
	switch (key){
		case 33: //Page Up
			radius++;
			_gravityWell.Assign(_gravityWell.GetPosition(), Vector3f(radius, radius, radius), _gravityWell.GetTextureEnabledStatus());
			break;
		case 34: //Page Down
			radius--;
			if (radius < 1.0f)
				radius = 1.0f;
			_gravityWell.Assign(_gravityWell.GetPosition(), Vector3f(radius, radius, radius), _gravityWell.GetTextureEnabledStatus());
			break;
		case 27: //Escape
			PostQuitMessage(1);
			break;
		case 36: //Home
			_eyeY--;
			ExtractFrustrum();
			break;
		case 35: //End
			_eyeY++;
			ExtractFrustrum();
			break;
		default:
			break;
	}
	
}

void Scene::OnMouseButton(int mouse, bool down){
	float radius = _gravityWell.GetRadius();
	switch (mouse){
		case 0:
			if(down)
				_leftMouseButtonDown = true;
			else
				_leftMouseButtonDown = false;
			break;
		default:
			break;
	}
}
void Scene::OnMouseMove(int x, int y){
	//if (y>_mousePosY){
	//	_eyeZ++;
	//	_centreZ++;
	//	_mousePosY = _centreY;
	//	//SetCursorPos(_centreX,_centreY);
	//}
	//else if(y<_mousePosY){
	//	_eyeZ--;
	//	_centreZ--;
	//	_mousePosY = _centreY;
	//	//SetCursorPos(_centreX,_centreY);
	//}
	//SetCursorPos(_centreX,_centreY);

}

void Scene::Draw(void) const{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//glPushMatrix();
		gluLookAt(_eyeX, _eyeY, _eyeZ,
			_centreX, _centreY, _centreZ,
			0.0f, 1.0f, 0.0f);
		//glTranslatef(_myCylinder.GetPosition().x(), _myCylinder.GetPosition().y(), _myCylinder.GetPosition().z());
		//glRotatef(_angle, 1.0f, 0.0f, 0.0f);
		//glTranslatef(-_myCylinder.GetPosition().x(), -_myCylinder.GetPosition().y(), -_myCylinder.GetPosition().z());

		glColor3f(1.0f, 1.0f, 0.3f);
		int number = 0;
		for (int i = 0; i < _ballAmount; i++){
			if (SphereInFrustum(_sphere[i].GetPosition(), _sphere[i].GetRadius())){
				glPushMatrix();
					glTranslatef(_sphere[i].GetPosition().x(), _sphere[i].GetPosition().y(), _sphere[i].GetPosition().z());
					glRotatef(_angle, 1.0f, 0.0f, 0.0f);
					_sphere[i].Draw();
					glTranslatef(-_sphere[i].GetPosition().x(), -_sphere[i].GetPosition().y(), -_sphere[i].GetPosition().z());
				glPopMatrix();
				number++;
			}
		}
		glColor3f(1.0f, 0.0f, 0.0f);
		glPushMatrix();
			glTranslatef(_circle.GetPosition().x(), _circle.GetPosition().y(), _circle.GetPosition().z());
			_circle.Draw();
		glPopMatrix();
		glColor3f(0.0f, 1.0f, 0.0f);
		glPushMatrix();
			glTranslatef(_myCylinder.GetPosition().x(), _myCylinder.GetPosition().y(), _myCylinder.GetPosition().z());
		    //glRotatef(_angle, 1.0f, 0.0f, 0.0f);
			_myCylinder.Draw();
			//glTranslatef(-_myCylinder.GetPosition().x(), -_myCylinder.GetPosition().y(), -_myCylinder.GetPosition().z());
		glPopMatrix();
		glColor4f(1.0f, 1.0f, 0.0f, 0.3f);
			glPushMatrix();
			glTranslatef(_eyeX, _gravityWell.GetPosition().y(), _eyeZ-(_gravityWell.GetRadius()));
			//glTranslatef(_gravityWell.GetPosition().x(), _gravityWell.GetPosition().y(), _gravityWell.GetPosition().z());
			//glRotatef(_angle, 1.0f, 0.0f, 0.0f);
			_gravityWell.Draw();
			//glTranslatef(-_myCylinder.GetPosition().x(), -_myCylinder.GetPosition().y(), -_myCylinder.GetPosition().z());
		glPopMatrix();
	//glPopMatrix();
}

void Scene::SetHWND(HWND handle){
	_hwnd = handle;
}

bool Scene::SphereInFrustum(const Vector3f &spherePosition, float radius)const{
	int p;
	float x = spherePosition.x();
	float y = spherePosition.y();
	float z = spherePosition.z();

	for( p = 0; p < 6; p++ )
		if( _frustum[p][0] * x + _frustum[p][1] * y + _frustum[p][2] * z + _frustum[p][3] <= -radius )
			return false;
	return true;

}

void Scene::Update(float deltaTime){
	//Move Gravity Well
	Vector3f position(_eyeX,_gravityWell.GetPosition().y(),_eyeZ-(_gravityWell.GetRadius()));
	_gravityWell.SetPosition(position);
	//Physics Code
	for (int i = 0; i < _ballAmount; i++)
	{
		if (SphereInFrustum(_sphere[i].GetPosition(), _sphere[i].GetRadius())){
			_ballPhysics[i].GravityWellBallCollision(_gravityWell.GetPosition(), _gravityWell.GetRadius(),
				_gravityWell.GetCurrentState(), _gravityWell.GetForce());
		}
	}
	//Sync the positions
	for (int i = 0; i < _ballAmount; i++)
	{
		_sphere[i].SetPosition(_ballPhysics[i].GetPosition());
	}

	//Mouse Button Code
	if (_leftMouseButtonDown && !_rightMouseButtonDown){
		if (_gravityWell.GetCurrentState()!=1){
			_gravityWell.SetCurrentState(1); //attracting state
			_gravityWell.SetForce(0.0f);
		}
		_gravityWell.SetForce(_gravityWell.GetForce()-0.1f);
	}
	else if(_rightMouseButtonDown && !_leftMouseButtonDown){
		if (_gravityWell.GetCurrentState()!=2){
			_gravityWell.SetCurrentState(2); //Repelling state
			_gravityWell.SetForce(0.0f);
		}
		_gravityWell.SetForce(_gravityWell.GetForce()+0.1f);
	}
	else if(_leftMouseButtonDown && _rightMouseButtonDown){
		_gravityWell.SetForce(0.0f);
		_gravityWell.SetCurrentState(0); //Neutral state
	}

	//Mouse Movement Code
	POINT p;
	GetCursorPos(&p) ;
	if (p.y>_mousePosY){ //centre the mouse position and move forwards along Z axis
		_eyeZ++;
		_centreZ++;
		_mousePosY = _screenCentreY;
		SetCursorPos(_screenCentreX,_screenCentreY);
		ExtractFrustrum();
	}
	else if(p.y<_mousePosY){ //centre the mouse position and move backwards along Z axis
		_eyeZ--;
		_centreZ--;
		_mousePosY = _screenCentreY;
		SetCursorPos(_screenCentreX,_screenCentreY);
		ExtractFrustrum();
	}
	if (p.x>_mousePosX){//centre the mouse position and move right across the X axis
		_eyeX++;
		_centreX++;
		_mousePosX = _screenCentreX;
		SetCursorPos(_screenCentreX,_screenCentreY);
		ExtractFrustrum();
	}
	else if(p.x<_mousePosX){//centre the mouse position and move left across the X axis
		_eyeX--;
		_centreX--;
		_mousePosX = _screenCentreX;
		SetCursorPos(_screenCentreX,_screenCentreY);
		ExtractFrustrum();
	}
}