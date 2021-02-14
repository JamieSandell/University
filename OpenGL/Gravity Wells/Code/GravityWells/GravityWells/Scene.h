#pragma once
#include <sstream>
#include <vector>
#include "Client.h"
#include "Server.h"
#include "GXBase.h"
#include "BallPhysics.h"
#include "Circle.h"
#include "GravityWell.h"
#include "MySphere.h"
#include "MyCylinder.h"
#include "Quaternion.h"
#include "ScriptReader.h"
#include "Text.h"
#include "TextureManager.h"
#include "Timer.h"

using std::vector;

class Scene
{
public:
	Scene(void);
	~Scene(void);

	inline bool Acquire(HANDLE handle) const {
		return (WaitForSingleObject(handle,500L) == WAIT_OBJECT_0);
	}
	void OnCreate(int viewportHeight, int viewportWidth);
	void Draw(void)const;
	void ExtractFrustrum(void);
	inline const std::vector<Text>& GetText(void)const{return _vecText;};
	void Update(float deltaTime);
	inline void SetHWND(HWND handle){_hwnd = handle;};
	bool SphereInFrustum( const MySphere &ball)const;
	void OnKeyboard(int key, bool down);
	void OnMouseButton(int mouse, bool down);//left = 0, middle = 1, right = 2
	inline void Release(HANDLE handle) const {
		ReleaseMutex(handle);
	}
	inline void Resume(HANDLE hThread){ResumeThread(hThread);};
	int Run(void);
	int CheckClientForConnection(void);
	HANDLE Start(void);
	HANDLE StartCheckForClientsLoop(void);
	static unsigned __stdcall threadFunc(void *param) {
		if (param)
			return ((Scene*)param)->Run();
		return 1;  // Return error
	}
	static unsigned __stdcall threadFuncCheckForConnection(void *param) {
		if (param)
			return ((Scene*)param)->CheckClientForConnection();
		return 1;  // Return error
	}
	template <class T>
	inline std::string ToString (const T& t)
	{
		std::stringstream ss;
		ss << t;
		return ss.str();
	}
	void UpdateText(void);
	inline void WaitForTermination(HANDLE hThread) {
		// wait for it to stop
		WaitForSingleObject(hThread, INFINITE);
		// close thread handle
		CloseHandle(hThread);
		hThread=0;
	}

private:
	std::vector<MySphere *> *_allBalls;
	std::vector<BallPhysics *> *_allBallPhysics;
	float _frustum[6][4];
	int _mousePosX, _mousePosY, _windowHeight, _windowWidth;
	HWND _hwnd;
	float _eyeZ, _centreZ, _eyeX, _centreX, _eyeY, _centreY;
	POINT _mouse;
	int _screenCentreX, _screenCentreY;
	Circle _circle;
	float _deltaTime;
	MySphere *_sphere;
	BallPhysics *_ballPhysics;
	MyCylinder _myCylinder;
	GravityWell _gravityWell;
	float _floorFriction;
	HANDLE _mutexDelta;
	HANDLE _hThread, _hCheckConnectionThread;
	HANDLE _mutexBalls;
	HANDLE _mutexPeerGravityWells;
	int _test;
	int _ballAmount;
	bool _leftMouseButtonDown, _rightMouseButtonDown;
	int _machineID;
	std::vector<GravityWell *> *_peerGravityWells;
	std::vector<Client> _peerConnection;
	std::vector<int> _peerIDs;
	std::vector<string> _peerIPs;
	int _port;
	Quaternion _quaternion;
	TextureManager _textureManager;
	std::vector<Text> _vecText;
	Text _text;
	float _surfaceFriction;
	Timer _timer;
	Server _server;
	vector<int> _sphereID; //ids of the spheres in the frustum
	ScriptReader _scriptReader;
	bool _terminate;
	float _wallElasticity;
};
