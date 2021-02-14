#include "Server.h"
#include <process.h>
#include <string>
#include "Scene.h"
#include "MySphere.h"
#include "Circle.h"
#include "MyCylinder.h"

#define PI  (float)3.1415926

using std::cout;
using std::endl;
using std::string;
using namespace gxbase;

Scene::Scene(void)
{
}

Scene::~Scene(void)
{
	/*CloseHandle(_hThread);
	_hThread=0;*/
	_terminate = true;
	WaitForTermination(_hThread);
	WaitForTermination(_hCheckConnectionThread);
	CloseHandle(_mutexBalls);
	_mutexBalls = NULL;
	CloseHandle(_mutexDelta);
	_mutexDelta = NULL;
	CloseHandle(_mutexPeerGravityWells);
	_textureManager.Destroy();

	//for (vector<MySphere *>::iterator p = _allBalls->begin(); p != _allBalls->end(); ++p){
	//	delete *p;
	//	p = _allBalls->erase(p);
	//}
	//for (vector<BallPhysics *>::iterator p = (*_allBallPhysics).begin(); p != (*_allBallPhysics).end(); ++p){
	//	delete *p;
	//}
	//(*_allBalls).clear();
	//(*_allBallPhysics).clear();
	//(*_allBallPhysics).clear();
	//(*_allBalls).clear();
	_scriptReader.Destroy();
	_server.UninitialiseServer();
}

int Scene::CheckClientForConnection(void){
	while(!_terminate){
		for (unsigned int i = 0; i < _peerIDs.size(); i++)
		{
			if (!_server.IsPeerConnected(_peerIDs[i]))
			{
				string reply = _peerConnection[i].Create(_peerIPs[i], _port);
				if (reply == ""){
					Sleep(100); // Give the server a chance to accept the connection first
					string message = "I " + ToString(_machineID); //Successful connection has been made, send the server our id
					reply = _peerConnection[i].SendMessage2(message);
					Sleep(1000);
					if (reply != "")
						cout << "Sending ID failed, with error: " << reply << "." << endl;
				}
				else
					cout << "Failed To Connect to Peer, with error: " << reply << "." << endl;
			}
		}
		Sleep(100);
	}
	return 0;
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

	_windowHeight = viewportHeight;
	_windowWidth = viewportWidth;

	_eyeZ = -2.0f;
	_centreZ = -10.0f;
	_eyeX = 0.0f;
	_centreX = 0.0f;
	_eyeY = 2.0f;
	_centreY = 0.0f;

	_screenCentreX = viewportWidth/2;
	_screenCentreY = viewportHeight/2;

	_deltaTime = 0.0f;

	_scriptReader.Create("Configuration.txt");
	_scriptReader.ReadScriptFileAndParseIt();

	_peerIPs = _scriptReader.GetPeerIPs();
	_port = _scriptReader.GetPortNumber();
	for (unsigned int i = 0; i < _peerIPs.size(); i++)
	{
		_server.AddAcceptableIP(_peerIPs[i]);
		Client client;
		_peerConnection.push_back(client);
		//_peerConnection[i].Create(_peerIPs[i], _port);
	}
	_server.InitialiseServer();
	_server.Start(_port);

	_peerGravityWells = _scriptReader.GetPeerGravityWells();
	_peerIDs = _scriptReader.GetPeerIDs();
	_machineID = _scriptReader.GetMachineID();

	_floorFriction = _scriptReader.GetFloorFriction();
	_wallElasticity = _scriptReader.GetWallElasticity();

	_allBalls = _scriptReader.GetBalls();
	_allBallPhysics = _scriptReader.GetBallPhysics();

	_ballAmount = _allBalls->size();
	float ballRadius = (*_allBalls)[0]->GetRadius();
	float floorRadius = (_ballAmount*ballRadius);
	_circle = _scriptReader.GetPlanarSurface();
	_myCylinder = _scriptReader.GetWall();
	_gravityWell.Create(Vector3f(0.0f, 0.8f, 0.0f),Vector3f(1.0f,1.0f,1.0f), false);
	_gravityWell.SetColor(Color(1.0f,1.0f,0.0f,0.3f));
	float floorDiameter = (_ballAmount*ballRadius)*2.0f;
	floorRadius = floorDiameter/2.0f;
	floorRadius -= ballRadius*3.0f; // so the balls don't go outside the arena
	float floorArea = PI * (floorRadius*floorRadius);
	//float spacing = floorArea/_ballAmount;
	float spacing = PI * PI*(ballRadius*ballRadius)+(ballRadius*ballRadius);
	spacing = sqrtf(spacing);
	float tempZ = floorRadius-(spacing/2);
	float rowDist = 2 * sqrtf((floorRadius*floorRadius) - (tempZ*tempZ));
	float c = (rowDist/2)/spacing;
	float tempX =c *-spacing;
	Vector3f position;
	float ballY = _circle.GetPosition().y()+ballRadius;

	int currentBall = 0;
	int ballsPerRow = 100;
	int currentRow = 0;
	tempZ = 0.0f;
	spacing = ballRadius*PI;
	tempX = 0.0f;

	for (int i = 0; i < _ballAmount; i++)
	{
		if (currentBall > ballsPerRow-1){
			currentBall = 0;
			currentRow++;
			tempX = 0.0f;
			tempZ = currentRow*spacing;
			tempZ *= -1;
		}
		position.Assign(tempX, ballY, tempZ);
		(*_allBalls)[i]->SetPosition(position);
		(*_allBallPhysics)[i]->SetPosition(position);
		tempX+=spacing;
		currentBall++;
	}

	Vector3f firstBallPosition((*_allBalls)[0]->GetPosition());
	Vector3f lastBallPosition((*_allBalls)[_ballAmount-1]->GetPosition());
	Vector3f diameterDiff(lastBallPosition-firstBallPosition);

	floorRadius = (diameterDiff.CalculateMagnitude()/2)+spacing*2;//+ballRadius*ballRadius;
	Vector3f hWD(floorRadius,floorRadius,floorRadius);
	Vector3f temp(diameterDiff.x()/2,_circle.GetPosition().y(),diameterDiff.z()/2);//(diameterDiff/2);
	_circle.Assign(_circle.GetPosition(), hWD, _circle.GetTextureEnabledStatus());
	hWD.Assign(_myCylinder.GetHeightWidthDepth().x(),hWD.y(),_myCylinder.GetHeightWidthDepth().z());
	_myCylinder.Create(_circle.GetPosition(), hWD, _myCylinder.GetTextureEnabledStatus());

	currentBall = 0;
	int currentLeftBall = 0;
	int currentRightBall = 0;
	int bottomCurrentRow = 0;
	int topCurrentRow = 0;
	tempZ = 0.0f;
	spacing = ballRadius*PI;
	tempX = 0.0f;
	bool left = false;
	bool bottom = true;
	for (int i = 0; i < _ballAmount; i++)
	{
		if (currentBall > ballsPerRow-1){
			currentBall = currentLeftBall = currentRightBall = 0;
			tempX = 0.0f;
			if (bottom)
			{
				bottomCurrentRow++;
				tempZ = bottomCurrentRow*spacing;
				bottom = false;
			}
			else{
				topCurrentRow++;
				bottom = true;
				tempZ = topCurrentRow*spacing*-1;
			}
		}
		position.Assign(tempX, ballY, tempZ);
		(*_allBalls)[i]->SetPosition(position);
		(*_allBallPhysics)[i]->SetPosition(position);
		if (left){
			tempX = (currentLeftBall+1) * spacing * -1;
			left=false;
			currentLeftBall++;
		}
		else{
			tempX = (currentRightBall+1) * spacing;
			left=true;
			currentRightBall++;
		}
		currentBall=currentLeftBall+currentRightBall;
	}

	_gravityWell = _scriptReader.GetGravityWell();

	_gravityWell.SetPosition(Vector3f(_eyeX, _gravityWell.GetPosition().y(), _eyeZ));
	_leftMouseButtonDown = _rightMouseButtonDown = false;
	ExtractFrustrum();

	_mutexBalls=CreateMutexA(NULL,FALSE,"myMutex");
	_mutexDelta=CreateMutexA(NULL,FALSE,"myMutex");

	_terminate = false;
	_hThread = 0;
	Start();
	StartCheckForClientsLoop();
	Resume(_hThread);
	Resume(_hCheckConnectionThread);
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
			break;
		case 35: //End
			_eyeY++;
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
		case 2:
			if(down)
				_rightMouseButtonDown = true;
			else
				_rightMouseButtonDown = false;
			break;
		default:
			break;
	}
}

void Scene::Draw(void)const{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	gluLookAt(_eyeX, _eyeY, _gravityWell.GetPosition().z(),
		_centreX, _centreY, _centreZ,
		0.0f, 1.0f, 0.0f);

	float angle;
	Vector3f axis;
	if (Acquire(_mutexBalls)){
		for (vector<int>::const_iterator i = _sphereID.begin(); i != _sphereID.end(); ++i){
			glPushMatrix();
			glTranslatef((*_allBallPhysics)[(*i)]->GetPosition().x(), (*_allBallPhysics)[(*i)]->GetPosition().y(),
				(*_allBallPhysics)[(*i)]->GetPosition().z());
			if ((*_allBallPhysics)[(*i)]->GetCurrentMovementState()!=0){
				angle = (*_allBallPhysics)[(*i)]->GetOrientationAngle();
				axis = (*_allBallPhysics)[(*i)]->GetOrientationVector();
				glRotatef(angle/PI*180.0f, axis.x(), axis.y(), axis.z());
			}
			(*_allBalls)[(*i)]->Draw();
			glTranslatef(-(*_allBalls)[(*i)]->GetPosition().x(), -(*_allBalls)[(*i)]->GetPosition().y(),
				-(*_allBalls)[(*i)]->GetPosition().z());
			glPopMatrix();
		}
		Release(_mutexBalls);
	}
	glPushMatrix();
	glTranslatef(_circle.GetPosition().x(), _circle.GetPosition().y(), _circle.GetPosition().z());
	_circle.Draw();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(_myCylinder.GetPosition().x(), _myCylinder.GetPosition().y(), _myCylinder.GetPosition().z());
	_myCylinder.Draw();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(_gravityWell.GetPosition().x(), _gravityWell.GetPosition().y(), _gravityWell.GetPosition().z());
	_gravityWell.Draw();
	glPopMatrix();
	////Acquire(_mutexPeerGravityWells);
	//for (unsigned int i = 0; i < (*_peerGravityWells).size(); i++)
	//{
	//	glPushMatrix();
	//	glTranslatef((*_peerGravityWells)[i]->GetPosition().x(), (*_peerGravityWells)[i]->GetPosition().y(), (*_peerGravityWells)[i]->GetPosition().z());
	//	(*_peerGravityWells)[i]->Draw();
	//	glPopMatrix();
	//}
	////Release(_mutexPeerGravityWells);
}

bool Scene::SphereInFrustum(const MySphere &ball)const{
	float radius = ball.GetRadius();
	Vector3f position = ball.GetPosition();
	float x,y,z;
	x = position.x();
	y = position.y();
	z = position.z();
	int p;

	for( p = 0; p < 6; p++ )
		if( _frustum[p][0] * x + _frustum[p][1] * y + _frustum[p][2] * z + _frustum[p][3] <= -radius )
			return false;
	return true;
	//int p;
	//int c = 0;
	//float d;

	//for( p = 0; p < 6; p++ )
	//{
	//	d = frustum[p][0] * x + frustum[p][1] * y + frustum[p][2] * z + frustum[p][3];
	//	if( d <= -radius )
	//		return 0;
	//	if( d > radius )
	//		c++;
	//}
	//return (c == 6) ? 2 : 1;


}

//int Scene::SphereInFrustum( const MySphere &ball) const
//{
//	int p;
//	int c = 0;
//	float d;
//	float radius = ball.GetRadius();
//	Vector3f position = ball.GetPosition();
//	float x,y,z;
//	x = position.x();
//	y = position.y();
//	z = position.z();
//
//	for( p = 0; p < 6; p++ )
//	{
//		d = _frustum[p][0] * x + _frustum[p][1] * y + _frustum[p][2] * z + _frustum[p][3];
//		if( d <= -radius )
//			return 0;
//		if( d > radius )
//			c++;
//	}
//	return (c == 6) ? 2 : 1;
//}

int Scene::Run(void){
	float ballRadius = (*_allBalls)[0]->GetRadius(); //Radius is the same for all the balls so no need
	//											// to store a vector of them
	bool collided;
	Vector3f wallPosition = _myCylinder.GetPosition();
	float wallRadius = _circle.GetRadius();

	float tempDelta = 0.0f;
	vector<int> tempID;
	while(!_terminate){
		if (_timer.UpdateRate())
		{
			tempID.clear();
			if (Acquire(_mutexDelta))
				tempDelta = _deltaTime;
			Release(_mutexDelta);
			for (int i = 0; i < _ballAmount; i++)
			{
				(*_allBallPhysics)[i]->Update(tempDelta, _floorFriction);
				//Sync the positions
				(*_allBalls)[i]->SetPosition((*_allBallPhysics)[i]->GetPosition());
				if (SphereInFrustum(*(*_allBalls)[i])!=false){
					(*_allBallPhysics)[i]->GravityWellBallCollision(_gravityWell.GetPosition(), _gravityWell.GetRadius(),
						_gravityWell.GetCurrentState(), _gravityWell.GetForce());

					tempID.push_back(i);
				}
				(*_allBallPhysics)[i]->BallWallCollision(_myCylinder.GetPosition(), _myCylinder.GetHeightWidthDepth().y(),
					tempDelta, _wallElasticity);
			}
			// See if the balls collide with eachother
			for (vector<int>::iterator i = tempID.begin(); i != tempID.end(); ++i)
			{
				for (vector<int>::iterator j = tempID.begin(); j != tempID.end(); ++j)
				{
					if (j!=i){
						collided = (*_allBallPhysics)[(*i)]->BallBallCollision( (*(*_allBallPhysics)[(*j)]), tempDelta);
						if (collided){
							//Sync the positions
							(*_allBalls)[(*i)]->SetPosition((*_allBallPhysics)[(*i)]->GetPosition());
							(*_allBalls)[(*j)]->SetPosition((*_allBallPhysics)[(*j)]->GetPosition());
						}
					}
				}
			}
			if (Acquire(_mutexBalls)){
				_sphereID = tempID;
			}
			Release(_mutexBalls);
		}
	}
	return 0;
}

HANDLE Scene::Start(void){
	unsigned threadId=0;
	_hThread = (HANDLE)_beginthreadex(
		NULL,		// no security attributes (child cannot inherited handle)
		1024*1024,	// 1MB stack size
		threadFunc,	// code to run on new thread
		this,		// pointer to host application class
		CREATE_SUSPENDED,			// run immediately (could create suspended)
		&threadId	// OUT: returns thread ID
		);
	return _hThread;
}
HANDLE Scene::StartCheckForClientsLoop(void){
	unsigned threadId=0;
	_hCheckConnectionThread = (HANDLE)_beginthreadex(
		NULL,		// no security attributes (child cannot inherited handle)
		1024*1024,	// 1MB stack size
		threadFuncCheckForConnection,	// code to run on new thread
		this,		// pointer to host application class
		CREATE_SUSPENDED,			// run immediately (could create suspended)
		&threadId	// OUT: returns thread ID
		);
	return _hCheckConnectionThread;
}
void Scene::Update(float deltaTime){
	ExtractFrustrum();
	//_sphereID.clear();
	//float ballRadius = (*_allBalls)[0]->GetRadius(); //Radius is the same for all the balls so no need
	////											// to store a vector of them
	//bool collided;
	//Vector3f wallPosition = _myCylinder.GetPosition();
	//float wallRadius = _circle.GetRadius();
	//for (int i = 0; i < _ballAmount; i++)
	//{
	//	(*_allBallPhysics)[i]->Update(deltaTime, _floorFriction);
	//	//Sync the positions
	//	(*_allBalls)[i]->SetPosition((*_allBallPhysics)[i]->GetPosition());
	//	if (SphereInFrustum(*(*_allBalls)[i])!=false){
	//		(*_allBallPhysics)[i]->GravityWellBallCollision(_gravityWell.GetPosition(), _gravityWell.GetRadius(),
	//			_gravityWell.GetCurrentState(), _gravityWell.GetForce());

	//		_sphereID.push_back(i);
	//	}
	//	(*_allBallPhysics)[i]->BallWallCollision(_myCylinder.GetPosition(), _myCylinder.GetHeightWidthDepth().y(),
	//		deltaTime, _wallElasticity);
	//}
	//// See if the balls collide with eachother
	//for (vector<int>::iterator i = _sphereID.begin(); i != _sphereID.end(); ++i)
	//{
	//	for (vector<int>::iterator j = _sphereID.begin(); j != _sphereID.end(); ++j)
	//	{
	//		if (j!=i){
	//			collided = (*_allBallPhysics)[(*i)]->BallBallCollision( (*(*_allBallPhysics)[(*j)]), deltaTime);
	//			if (collided){
	//				//Sync the positions
	//				(*_allBalls)[(*i)]->SetPosition((*_allBallPhysics)[(*i)]->GetPosition());
	//				(*_allBalls)[(*j)]->SetPosition((*_allBallPhysics)[(*j)]->GetPosition());
	//			}
	//		}
	//	}
	//}

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
		_gravityWell.SetPosition(Vector3f(_gravityWell.GetPosition().x(), _gravityWell.GetPosition().y(), _eyeZ));
		_mousePosY = _screenCentreY;
		SetCursorPos(_screenCentreX,_screenCentreY);
		//ExtractFrustrum();
	}
	else if(p.y<_mousePosY){ //centre the mouse position and move backwards along Z axis
		_eyeZ--;
		_centreZ--;
		_gravityWell.SetPosition(Vector3f(_gravityWell.GetPosition().x(), _gravityWell.GetPosition().y(), _eyeZ));
		_mousePosY = _screenCentreY;
		SetCursorPos(_screenCentreX,_screenCentreY);
		//ExtractFrustrum();
	}
	if (p.x>_mousePosX){//centre the mouse position and move right across the X axis
		_eyeX++;
		_centreX++;
		_gravityWell.SetPosition(Vector3f(_eyeX, _gravityWell.GetPosition().y(), _gravityWell.GetPosition().z()));
		_mousePosX = _screenCentreX;
		SetCursorPos(_screenCentreX,_screenCentreY);
		//ExtractFrustrum();
	}
	else if(p.x<_mousePosX){//centre the mouse position and move left across the X axis
		_eyeX--;
		_centreX--;
		_gravityWell.SetPosition(Vector3f(_eyeX, _gravityWell.GetPosition().y(), _gravityWell.GetPosition().z()));
		_mousePosX = _screenCentreX;
		SetCursorPos(_screenCentreX,_screenCentreY);
		//ExtractFrustrum();
	}

	//Text code (for the hud)
	UpdateText();

	if (Acquire(_mutexDelta))
		_deltaTime = deltaTime;
	Release(_mutexDelta);

	//for (unsigned int i = 0; i < _peerIDs.size(); i++)
	//{
	//	if (_server.IsPeerConnected(i))
	//	{
	//		//Acquire(_mutexPeerGravityWells);
	//		string message = "G " + ToString(_machineID) + " " + ToString(_gravityWell.GetPosition().x()) + " " + ToString(_gravityWell.GetPosition().y()) + " " + ToString(_gravityWell.GetPosition().z()) + " " + ToString(_gravityWell.GetRadius());
	//		int messageSize = message.size();
	//		string reply = _peerConnection[i].SendMessage2(ToString(messageSize));
	//		if (reply != "")
	//			cout << "Sending Gravity Well Packet Size Failed, with error: " << reply << "." << endl;
	//		reply = _peerConnection[i].SendMessage2(message);
	//		if (reply != "")
	//			cout << "Sending Gravity Well Failed, with error: " << reply << "." << endl;
	//		//Release(_mutexPeerGravityWells);
	//	}
	//}
}
void Scene::UpdateText(void){
	int fps = _timer.GetFPS();
	string gravityWellState="";
	int gravityState = _gravityWell.GetCurrentState();
	if (gravityState==0)
		gravityWellState = "None";
	else if (gravityState==1)
		gravityWellState = "Attracting";
	else if(gravityState==2)
		gravityWellState = "Repelling";

	vector<string> textString;
	vector<float> textPosition;
	vector<float> textColor;
	vector<string> textFormat;
	//Number of balls
	textString.push_back("Number of Balls: " + ToString(_ballAmount));
	textPosition.push_back(0.0f);
	textPosition.push_back((float)_windowHeight-10.0f);
	textColor.push_back(1.0f);
	textColor.push_back(1.0f);
	textColor.push_back(1.0f);
	textColor.push_back(1.0f);
	textFormat.push_back("%s \n");
	//GravityWell State
	textString.push_back("Current GravityWell State: " + gravityWellState);
	textPosition.push_back(0.0f);
	textPosition.push_back((float)_windowHeight-15.0f);
	textColor.push_back(1.0f);
	textColor.push_back(1.0f);
	textColor.push_back(1.0f);
	textColor.push_back(1.0f);
	textFormat.push_back("%s \n");
	//GravityWell Force
	textString.push_back("Current GravityWell Force: " + ToString(_gravityWell.GetForce()));
	textPosition.push_back(0.0f);
	textPosition.push_back((float)_windowHeight-20.0f);
	textColor.push_back(1.0f);
	textColor.push_back(1.0f);
	textColor.push_back(1.0f);
	textColor.push_back(1.0f);
	textFormat.push_back("%s \n");
	//FPS
	textString.push_back("FPS: " + ToString(fps));
	textPosition.push_back(0.0f);
	textPosition.push_back((float)_windowHeight-25.0f);
	textColor.push_back(1.0f);
	textColor.push_back(1.0f);
	textColor.push_back(1.0f);
	textColor.push_back(1.0f);
	textFormat.push_back("%s \n");
	//Spheres in view
	textString.push_back("Balls in View: " + ToString(_sphereID.size()));
	textPosition.push_back(0.0f);
	textPosition.push_back((float)_windowHeight-30.0f);
	textColor.push_back(1.0f);
	textColor.push_back(1.0f);
	textColor.push_back(1.0f);
	textColor.push_back(1.0f);
	textFormat.push_back("%s \n");

	_vecText.clear();
	//vector<float> tempTextPosition;
	//vector<float> tempTextColor;
	int colorI=0;
	int positionI=0;
	for (unsigned int i = 0; i < textString.size(); i++)
	{
		_text.SetPosition(textPosition[i+positionI], textPosition[i+positionI+1]);
		_text.SetColor(textColor[i+colorI], textColor[i+colorI+1],
			textColor[i+colorI+2], textColor[i+colorI+3]);
		_text.SetFormat(textFormat[i]);
		_text.SetText(textString[i]);
		_vecText.push_back(_text);
		colorI+=3;
		positionI++;
	}
}