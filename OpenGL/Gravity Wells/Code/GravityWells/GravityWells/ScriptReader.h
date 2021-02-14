#pragma once
#include <string>
#include <vector>
#include "BallPhysics.h"
#include "Circle.h"
#include "Color.h"
#include "GravityWell.h"
#include "MyCylinder.h"
#include "MySphere.h"
#include "Server.h"
#include "TextureManager.h"

class ScriptReader
{
public:
	ScriptReader(void);
	~ScriptReader(void);
	ScriptReader(std::string fileToRead);

	inline void Create(std::string fileToRead){_fileToRead=fileToRead;_textureManager=_textureManager.GetSingleton();};
	void Destroy(void);
	inline std::vector<MySphere *> *GetBalls(void)const{return _ballVec;};
	inline std::vector<BallPhysics *> *GetBallPhysics(void)const{return _ballPhysicsVec;};
	inline float GetFloorFriction(void){return _floorFriction;};
	inline int GetMachineID(void)const{return _machineID;};
	inline std::vector<GravityWell *> *GetPeerGravityWells(void)const{return _gravityWellVec;};
	inline std::vector<int> GetPeerIDs(void)const{return _peerID;};
	inline std::vector<std::string> GetPeerIPs(void)const{return _acceptableIPs;};
	inline int GetPortNumber(void)const{return _portNumber;};
	inline const MyCylinder &GetWall(void)const{return _wall;};
	inline float GetWallElasticity(void)const{return _wallElasticity;};
	inline const GravityWell &GetGravityWell(void)const{return _gravityWell;};
	inline const Circle &GetPlanarSurface(void)const{return _planarSurface;};
	void ReadScriptFileAndParseIt();
	void ResetVariables(void);

private:
	ScriptReader& operator=(const ScriptReader& rhs){};
	ScriptReader(const ScriptReader &rhs){};

private:
	std::vector<std::string> _acceptableIPs;
	MySphere* _ball;
	float _ballElasticity;
	float _ballSize;
	std::vector<MySphere *> *_ballVec;
	char _ch;
	Color _color;
	std::string _fileToRead;
	int _currentLevel;
	float _floorFriction;
	float _gravityForce;
	GravityWell _gravityWell;
	GravityWell* _gravityWells;
	std::vector<GravityWell *> *_gravityWellVec;
	float _lightMass, _mediumMass, _heavyMass;
	int _machineID;
	std::string _machineIP;
	int _numberOfObjectsToCreate, _numberOfTexturesToCreate;
	int _numberOfLightBalls, _numberOfMediumBalls, _numberOfHeavyBalls;
	std::string _object;
	Circle _planarSurface;
	float _planarSurfaceFriction;
	int _portNumber;
	float _position[3];
	BallPhysics* _ballPhysics;
	std::vector<BallPhysics *> *_ballPhysicsVec;
	std::vector<int> _peerID;
	int _realismLevel;
	bool _texturesNeedCreating;
	std::vector<GLuint> _textureID;
	TextureManager _textureManager;
	std::string _texturePath, _textureWrap;
	MyCylinder _wall;
	float _wallElasticity;
};
