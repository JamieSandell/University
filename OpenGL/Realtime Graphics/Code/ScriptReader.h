#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "Shape.h"
#include "Cube.h"
#include "MySphere.h"
#include "Tetrahedron.h"
#include "Octahedron.h"
#include "Lights.h"
#include "Color.h"
#include "Materials.h"
#include "NullObject.h"
#include "Particleball.h"
#include "Glowball.h"

////// Begin Script File Formatting //////////
// Start by specifying the type of object (e.g. Box, Sphere, Glowball etc).
// Then specify the number of objects of that type to create, e.g. (4).
// Then specify (for each object of that type to create) the properties
//	followed by the correct parameters.
////// End Script File Formatting //////////

///// Begin Example Script File //////
// Box (2)
// {
//	Box 1
//	{
//		HeightWidthDepth (2.0 2.0 2.0)
//		Texture (1)
//		Position (-1.0 0.0 -1.0)
//	}
//	Box 2
//	{
//		HeightWidthDepth (0.5 0.5 0.5)
//		Texture (0)
//		Position (0.0 0.5 -1.5)
//	}
// }
// Sphere (1)
// {
//	Sphere 1
//	{
//		HeightWidthDepth (0.3 0.3 0.3)
//		Texture (2)
//		Position (0.0, 0.7, -1.5)
//	}
// }
// Texture (2)
// {
//	Texture 1
//	{
//		Location(".\\texture1.bmp")
//	}
//	Texture 2
//	{
//		Location(".\\earth.bmp")
//	}
// }
///// End Example Script File //////

class ScriptReader{
public:
	ScriptReader();// call create or non-default constructor
	~ScriptReader();
	ScriptReader(std::string scriptFileToRead);
	ScriptReader(const ScriptReader &A); // Deep copy constructor
	ScriptReader& operator=(const ScriptReader &A); // assignment operator

	void ReadScriptFileAndParseIt(void);
	bool Create(std::string scriptFileToRead);
	template<typename T>
	void CreateShape(T &shape, std::ifstream &fin, int objectID);
	template<typename T>
	void DeallocateShapeMemoryAndAllocateShapeMemory(T &shape, int numberToCreate);
	void GetAllShapes(std::vector<Shape*> &outShapes)const;
	void GetCubes(Cube *outCubes, int &outNumberOfCubesCreated) const;
	void GetContainer(Cube *outContainers, int &outNumberOfContainersCreated) const;
	void GetLights(Lights *outLights, int &outNumberOfLightsCreated) const;
	void GetSpheres(MySphere *outSpheres, int &outNumberOfSpheresCreated) const;
	void GetTetrahedrons(Tetrahedron *outTetrahedrons, int &outNumberOfTetrahedronsCreated) const;
	std::vector<std::string>& GetCubeTextures(void);
	std::vector<std::string>& GetContainerTextures(void);
	std::vector<std::string>& GetSphereTextures(void);
	std::vector<std::string>& GetOctahedronTextures(void);
	std::vector<std::string>& GetTetrahedronTextures(void);
	std::vector<std::string>& GetTextures(void);
	void GetOctahedrons(Octahedron *outOctahedrons, int &outNumberOfOctahedronsCreated) const;
	int GetNumberOfTexturedContainers(void) const;
	int GetNumberOfTexturedCubes(void) const;
	int GetNumberOfTexturedOctahedrons(void) const;
	int GetNumberOfTexturedSpheres(void) const;
	int GetNumberOfTexturedTetrahedrons(void) const;
	int GetNumberOfTextures(void) const;
	float GetRotationSpeed(void) const;
	bool IsFogEnabled(void)const;

private:
	void AllocateMemory(void);
	void CopyNonPointerDataMembers(const ScriptReader &A);
	void CopyPointerDataMembers(const ScriptReader &A);
	void DeallocateMemory(void);
	void ResetVariables(void); //Resets variables used when parsing the script file
private:
	std::string _scriptFileToRead, _objectToCreate, _object;
	std::vector<std::string> _validObjectNames; // these could be read in from another file
	// for extra flexibility, e.g. Sphere, Box, Glowball, Texture etc
	bool _containerAlreadyCreated, _containerNeedCreating, _cubesAlreadyCreated, _cubesNeedCreating, _spheresAlreadyCreated;
	bool _spheresNeedCreating, _tetrahedronAlreadyCreated, _tetrahedronNeedCreating, _octahedronAlreadyCreated, _octahedronNeedCreating;
	bool _texturesAlreadyCreated, _texturesNeedCreating, _animationsAlreadyCreated, _animationsNeedCreating;
	bool _lightsAlreadyCreated, _lightsNeedCreating, _fogEnabled;
	char _ch;
	float _arrHWD[3]; // for platonics
	float _size; // for spheres
	float _arrPosition[4];
	float _arrAnimation[3]; // for animation coefficients
	Vector3f _hWD;
	Vector4f _position;
	int _tempCurrentLevel, _textureID, _numberOfCubesToCreate, _numberOfSpheresToCreate, _numberOfTexturesToCreate;
	int _numberOfContainersToCreate, _numberOfTetrahedronsToCreate, _numberOfOctahedronsToCreate, _currentLevel;
	int _arraySize, _objectID, _numberOfAnimationsToCreate, _animationID, _numberOfLightsToCreate;
	int _numberOfNullObjectsToCreate, _numberOfParticleBallsToCreate, _numberOfGlowballsToCreate;
	float _intensity, _cutoff, _rotationSpeed;
	std::vector<std::string> _cubeTextures, _containerTextures, _sphereTextures, _octahedronTextures;
	std::vector<std::string> _tetrahedronTextures, _textures;
	std::vector<std::vector<Vector3f> > _animation;
	Vector3f _animationVec3;
	Color _ambient, _diffuse, _emission;
	std::vector<Shape *> _allShapes;
	Cube *_cube;
	Cube *_container;
	MySphere *_sphere;
	Tetrahedron *_tetrahedron;
	NullObject* _nullObject;
	Octahedron *_octahedron;
	Particleball *_particleBall;
	Glowball *_glowball;
	Lights *_lights;
	float _shapeSize;
	int _cubeID, _containerID, _tetrahedronID, _sphereID, _octahedronID, _nullObjectID, _particleBallID;
	int _glowballID;
};