#pragma once

#include <vector>
#include "GXBase.h"
#include "Vector4f.h"
#include "Vector3f.h"
#include "Cube.h"
#include "MySphere.h"
#include "Materials.h"
#include "MyCylinder.h"
#include "Lights.h"
#include "ScriptReader.h"
#include "Octahedron.h"
#include "Glowball.h"
#include "Shader.h"
#include "Shape.h"
#include "ParticleEmitter.h"
#include "Collision.h"
using namespace gxbase;

class MyWindow :public GLWindowEx {
private:
	float angle_inc, angle, current_time, _cameraAngle, _cameraPosition, _cameraRotation, _startTime, _timeElapsed;
	MyCylinder *_lights;
	Materials _material3, _materialTransparency, _materialSphere, _materialLights, _materialInnerContainer;
	bool _leftDown, _rightDown, _wireframe, _flatShading, _gouraudShading, _rotateBoxAutomatically, _drawNormals, _animate;
	//Lights _lightSource0, _lightSource1, _lightSource2, _lightSource3, _lightSource4, _lightSource5, _lightSource6, _lightSource7;
	Lights *_lightSource;
	ScriptReader _myScriptReader;
	Image *_images;
	GLuint *_textures;
	int _numberOfLightsCreated;
	Shader _myShader;
	int _direction; // direction of the box, 1 is right, -1 is left
	std::vector<Shape *> _allShapes;
	int _maxSelectionModeValue;
	ParticleEmitter _particleEmitter;
	Collision _myCollision;
	GLfloat _fogColor[4];
	bool _fogEnabled;

	enum _displayMode{
		WIREFRAME,
		NONTEXTUREDFLATSHADING,
		SMOOTHSHADING,
		SMOOTHSHADEDTEXTURED
	};
	enum _shadows{
		NOSHADOWS,
		WALLSHADOWS
	};
	int _selectedMode;
	int _shadowsToShow;

public:
	~MyWindow();
	MyWindow(float cam);
	void CreateShadow(const Lights &lightSource, float shadowMatrix, float lightPosition)const;
	void DrawScene(float deltaTime);
	void OnCreate();
	void OnDisplay();//calls Update
	void OnIdle();
	void PositionLights(void);
	void OnResize(int w, int h);
	void OnKeyboard(int key, bool down);
	void OnMouseButton(MouseButton button, bool down);
	void OnMouseMove(int x, int y);
	void LoadImages(int numberOfTextures, Image *images, const std::vector<std::string> &textures) const;
	void Build2DMipMaps(int numberOfTextures, Image *images, const GLuint *textureID) const;
	void Update(float deltaTime);
};

