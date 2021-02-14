#include <fstream>
#include "ScriptReader.h"
#include "Vector3f.h"
#include "Vector4f.h"

// TODO: Load object materials (ambient, diffuse, emission) from script file

using namespace std;

ScriptReader::ScriptReader() {
}

ScriptReader::~ScriptReader() {
	DeallocateMemory();
}

ScriptReader::ScriptReader(std::string scriptFileToRead) {
	_scriptFileToRead = scriptFileToRead;
}

ScriptReader::ScriptReader(const ScriptReader &A){
	CopyNonPointerDataMembers(A);
	CopyPointerDataMembers(A);
}
ScriptReader& ScriptReader::operator =(const ScriptReader &A){
	if (this != &A){
		CopyNonPointerDataMembers(A);
		DeallocateMemory();
		AllocateMemory();
		CopyPointerDataMembers(A);
	}
	return *this;
}
void ScriptReader::AllocateMemory(void){
	_container = new Cube[1];
	_container[0].Create();
	_cube = new Cube[1];
	_cube[0].Create();
	_sphere = new MySphere[1];
	_sphere[0].Create();
	_octahedron = new Octahedron[1];
	_octahedron[0].Create();
	_tetrahedron = new Tetrahedron[1];
	_tetrahedron[0].Create();
	_lights = new Lights[1]();
	_particleBall = new Particleball[1];
	_particleBall[0].Create();
	_glowball = new Glowball[1];
	_glowball[0].Create();
	//_lights[0].create();
}

void ScriptReader::ReadScriptFileAndParseIt(void) {
	ifstream fin(_scriptFileToRead.c_str());
	if (!fin) {
		// TODO: didn't load the file, add error handling
	}
	ResetVariables();
	while (fin >> _object) { // while there is stuff to read in
		if (_object == "{"){
			_currentLevel++;
			continue;
		}
		if (_object == "}") {
			_currentLevel--;
			continue;
		}
		if (_currentLevel>0) {
				if (_object == "CONTAINER"){
					CreateShape(_container, fin, _containerID);
					_containerID++;
					continue;
				}
				if (_object == "CUBE"){
					CreateShape(_cube, fin, _cubeID);
					_cubeID++;
					continue;
				}
				if (_object == "GLOWBALL"){
					CreateShape(_glowball, fin, _glowballID);
					_glowballID++;
					continue;
				}
				if (_object == "NULLOBJECT"){
					CreateShape(_nullObject, fin, _nullObjectID);
					_nullObjectID++;
					continue;
				}
				if (_object == "OCTAHEDRON"){
					CreateShape(_octahedron, fin, _octahedronID);
					_octahedronID++;
					continue;
				}
				if (_object == "SPHERE"){
					CreateShape(_sphere, fin, _sphereID);
					_sphereID++;
					continue;
				}
				if (_object == "TETRAHEDRON"){
					CreateShape(_tetrahedron, fin, _tetrahedronID);
					_tetrahedronID++;
					continue;
				}
				if (_object == "PARTICLEBALL"){
					CreateShape(_particleBall, fin, _particleBallID);
					_particleBallID++;
					continue;
				}
				if (_lightsNeedCreating) {
					if (_object == "LIGHT"){
						fin >> _objectID; // so we know the id of the object to set properties to
						if (_objectID >= _numberOfLightsToCreate) //TODO: put this into a method, objID, numberToCreate, bool
							_lightsNeedCreating = false;
						_objectToCreate = "LIGHT"; // so we know what object to set properties to
						_tempCurrentLevel = _currentLevel;
						while (_object!="}") {
							fin >> _object;
							if (_object == "}") {
								_currentLevel--;
								_lights[_objectID-1].create(_objectID-1, _ambient, _diffuse);
								_lights[_objectID-1].setSpot(_cutoff, _intensity);

							}
							if (_object == "{") {
								_currentLevel++;
							}
							if (_object == "AMBIENT") {
								fin >> _ch; // get rid of the '(' to get to the parameters
								fin >> _arrPosition[0];
								fin >> _arrPosition[1];
								fin >> _arrPosition[2];
								fin >> _arrPosition[3];
								_ambient.Assign(_arrPosition[0],_arrPosition[1],_arrPosition[2],_arrPosition[3]);
							}
							if (_object == "DIFFUSE") {
								fin >> _ch; // get rid of the '(' to get to the parameters
								fin >> _arrPosition[0];
								fin >> _arrPosition[1];
								fin >> _arrPosition[2];
								fin >> _arrPosition[3];
								_diffuse.Assign(_arrPosition[0],_arrPosition[1],_arrPosition[2],_arrPosition[3]);
							}
							if (_object == "INTENSITY"){
								fin >> _ch; // get rid of the '(' to get to the parameters
								fin >> _intensity;
							}
							if (_object == "CUTOFF"){
								fin >> _ch; // get rid of the '(' to get to the parameters
								fin >> _cutoff;
							}
						}
						continue;
					}
				}
				if (_texturesNeedCreating) {
					if (_object == "TEXTURE"){
						fin >> _objectID; // so we know the id of the object to set properties to
						if (_objectID >= _numberOfTexturesToCreate)
							_texturesNeedCreating = false;
						_objectToCreate = "TEXTURE"; // so we know what object to set properties to
						_tempCurrentLevel = _currentLevel;
						while (_object!="}") {
							fin >> _object;
							if (_object == "}") {
								_currentLevel--;
							}
							if (_object == "{") {
								_currentLevel++;
							}
							if (_object == "LOCATION") {
								fin >> _ch; // get rid of the '(' to get to the parameters
								fin >> _object; // get location of the texture (string)
								_object = _object.substr(0, _object.length()-1); // remove the end ')'
								_textures.push_back(_object); // store the texture location that has just been read in
							}
						}
						continue;
					}
				}
				if (_animationsNeedCreating) {
					if (_object == "ANIMATION"){
						fin >> _objectID; // so we know the id of the object to set properties to
						if (_objectID >= _numberOfAnimationsToCreate)
							_animationsNeedCreating = false;
						_objectToCreate = "ANIMATION"; // so we know what object to set properties to
						_tempCurrentLevel = _currentLevel;
						while (_object!="}") {
							fin >> _object;
							if (_object == "}") {
								_currentLevel--;
							}
							if (_object == "{") {
								_currentLevel++;
							}
							if (_object == "A") {
								fin >> _ch; // get rid of the '(' to get to the parameters
								fin >> _arrAnimation[0]; // get animation coefficients (floats)
								fin >> _arrAnimation[1];
								fin >> _arrAnimation[2];
								_animation.resize(_animation.size()+1);
								_animation[_objectID-1].push_back(Vector3f(_arrAnimation));// store the animation that has just been read in
							}
							if (_object == "B") {
								fin >> _ch; // get rid of the '(' to get to the parameters
								fin >> _arrAnimation[0]; // get animation coefficients (floats)
								fin >> _arrAnimation[1];
								fin >> _arrAnimation[2];
								//_animationVec3.Assign(_arrAnimation);
								_animation[_objectID-1].push_back(Vector3f(_arrAnimation));// store the animation that has just been read in
							}
							if (_object == "C") {
								fin >> _ch; // get rid of the '(' to get to the parameters
								fin >> _arrAnimation[0]; // get animation coefficients (floats)
								fin >> _arrAnimation[1];
								fin >> _arrAnimation[2];
								_animation[_objectID-1].push_back(Vector3f(_arrAnimation));// store the animation that has just been read in
							}
							if (_object == "D") {
								fin >> _ch; // get rid of the '(' to get to the parameters
								fin >> _arrAnimation[0]; // get animation coefficients (floats)
								fin >> _arrAnimation[1];
								fin >> _arrAnimation[2];
								_animation[_objectID-1].push_back(Vector3f(_arrAnimation));// store the animation that has just been read in
							}
						}
						continue;
					}
				}
			continue;
		}
		if (0 == _currentLevel) { // if we're at this level (outside a '{') we need to find an object to create
			if (_object == "TEXTURE") { // if it's a texture then set the logic to create the texture
				if (!(_texturesAlreadyCreated)) { // only set this creation logic if textures haven't already been created
					_texturesAlreadyCreated = true; // so we don't overwrite the array
					// the script file formatting dictates objects are grouped
					// together when creating them anyways
					fin >> _ch; // get rid of the '(' to get to the parameters
					fin >> _arraySize; // read in the number of objects to create
					_textures.clear(); // delete the old textures
					_sphereTextures.clear();
					_cubeTextures.clear();
					_containerTextures.clear();
					_octahedronTextures.clear();
					_tetrahedronTextures.clear();
					_numberOfTexturesToCreate = _arraySize; // so we know how many textures to add to the texture vector
					_texturesNeedCreating = true;
					continue; // found valid object, no need to keep looking
				}
			}
			if (_object == "ANIMATION") { // if it's an animation then set the logic to create the animation
				if (!(_animationsAlreadyCreated)){ // only set this creation logic if animations haven't been created
					_animationsAlreadyCreated = true;// so we don't overwrite the data
					fin >> _ch; // get rid of the '(' to get to the parameters
					fin >> _arraySize; // read in the number of animations to create
					_animation.clear(); // delete the old animations
					_numberOfAnimationsToCreate = _arraySize; // so we know how many animations to add to the animation vector
					_animationsNeedCreating = true;
					continue; // found valid object, no need to keep looking
				}
			}
			if (_object == "LIGHT") { // if it's a light then set the logic to create the light
				if (!(_lightsAlreadyCreated)){ // only set this creation logic if lights haven't been created
					_lightsAlreadyCreated = true;// so we don't overwrite the data
					fin >> _ch; // get rid of the '(' to get to the parameters
					fin >> _arraySize; // read in the number of lights to create
					delete [] _lights; // delete the old memory
					_lights = new Lights[_arraySize]; // allocate the new memory
					_numberOfLightsToCreate = _arraySize; // so we know how many lights need creating
					_lightsNeedCreating = true;
					continue; // found valid object, no need to keep looking
				}
			}
			if (_object == "ROTATIONSPEED"){
				fin >> _ch;
				fin >> _rotationSpeed;
				continue;
			}
			if (_object == "FOGENABLED"){
				fin >> _ch;
				string fogString;
				fin >> fogString;
				if (fogString=="TRUE)")
					_fogEnabled = true;
				else
					_fogEnabled = false;
				continue;
			}
			if (_object == "CONTAINER"){
				fin >> _ch;
				fin >> _numberOfContainersToCreate;
				delete [] _container;
				_container = new Cube [_numberOfContainersToCreate];
				continue;
			}
			if (_object == "CUBE"){
				fin >> _ch;
				fin >> _numberOfCubesToCreate;
				delete [] _cube;
				_cube = new Cube [_numberOfCubesToCreate];
				continue;
			}
			if (_object == "GLOWBALL"){
				fin >> _ch;
				fin >> _numberOfGlowballsToCreate;
				delete [] _glowball;
				_glowball = new Glowball [_numberOfGlowballsToCreate];
				continue;
			}
			if (_object == "NULLOBJECT"){
				fin >> _ch;
				fin >> _numberOfNullObjectsToCreate;
				delete [] _nullObject;
				_nullObject = new NullObject [_numberOfNullObjectsToCreate];
				continue;
			}
			if (_object == "OCTAHEDRON"){
				fin >> _ch;
				fin >> _numberOfOctahedronsToCreate;
				delete [] _octahedron;
				_octahedron = new Octahedron [_numberOfOctahedronsToCreate];
				continue;
			}
			if (_object == "TETRAHEDRON"){
				fin >> _ch;
				fin >> _numberOfTetrahedronsToCreate;
				delete [] _tetrahedron;
				_tetrahedron = new Tetrahedron [_numberOfTetrahedronsToCreate];
				continue;
			}
			if (_object == "SPHERE"){
				fin >> _ch;
				fin >> _numberOfSpheresToCreate;
				delete [] _sphere;
				_sphere = new MySphere [_numberOfSpheresToCreate];
				continue;
			}
			if (_object == "PARTICLEBALL"){
				fin >> _ch;
				fin >> _numberOfParticleBallsToCreate;
				delete [] _particleBall;
				_particleBall = new Particleball [_numberOfParticleBallsToCreate];
				continue;
			}
		}
	}
}
void ScriptReader::CopyNonPointerDataMembers(const ScriptReader &A){
	_containerAlreadyCreated = A._containerAlreadyCreated;
	_containerNeedCreating = A._containerNeedCreating;
	_cubesAlreadyCreated = A._cubesAlreadyCreated;
	_cubesNeedCreating = A._cubesNeedCreating;
	_spheresAlreadyCreated = A._spheresAlreadyCreated;
	_spheresNeedCreating = A._spheresNeedCreating;
	_tetrahedronAlreadyCreated = A._tetrahedronAlreadyCreated;
	_tetrahedronNeedCreating = A._tetrahedronNeedCreating;
	_octahedronAlreadyCreated = A._octahedronAlreadyCreated;
	_octahedronNeedCreating = A._octahedronNeedCreating;
	_numberOfCubesToCreate = A._numberOfCubesToCreate;
	_numberOfSpheresToCreate = A._numberOfSpheresToCreate;
	_numberOfContainersToCreate = A._numberOfContainersToCreate;
	_numberOfTetrahedronsToCreate = A._numberOfTetrahedronsToCreate;
	_numberOfOctahedronsToCreate = A._numberOfOctahedronsToCreate;
	_texturesAlreadyCreated = A._texturesAlreadyCreated;
	_texturesNeedCreating = A._texturesNeedCreating;
	_animationsNeedCreating = A._animationsNeedCreating;
	_animationsAlreadyCreated = A._animationsAlreadyCreated;
	_currentLevel = A._currentLevel;
	_tempCurrentLevel = A._tempCurrentLevel;
	_textureID = A._textureID;
	_arraySize = A._arraySize;
	_scriptFileToRead = A._scriptFileToRead;
	_scriptFileToRead.clear();
	_object = A._object;
	_objectToCreate = A._objectToCreate;
	_hWD = A._hWD;
	_position = A._position;
	_ch = A._ch;
	_size = A._size;
	_animationID = A._animationID;
	_rotationSpeed = A._rotationSpeed;
	_lightsAlreadyCreated = A._lightsAlreadyCreated;
	_lightsNeedCreating = A._lightsNeedCreating;
	_numberOfLightsToCreate = A._numberOfLightsToCreate;
    _ambient = A._ambient;
	_diffuse = A._diffuse;
	_intensity = A._intensity;
	_cutoff = A._cutoff;
	_containerID = A._containerID;
	_cubeID = A._cubeID;
	_sphereID = A._sphereID;
	_octahedronID = A._octahedronID;
	_tetrahedronID = A._tetrahedronID;
	_nullObjectID = A._nullObjectID;
	_numberOfNullObjectsToCreate = A._numberOfNullObjectsToCreate;
	_particleBallID = A._particleBallID;
	_numberOfParticleBallsToCreate = A._numberOfParticleBallsToCreate;
	_glowballID = A._glowballID;
	_numberOfGlowballsToCreate = A._numberOfGlowballsToCreate;
	_fogEnabled = A._fogEnabled;
	std::copy(A._validObjectNames.begin(), A._validObjectNames.end(), _validObjectNames.begin());
	std::copy(A._animation.begin(), A._animation.end(), _animation.begin());
	std::copy(A._cubeTextures.begin(), A._cubeTextures.end(), _cubeTextures.begin());
	std::copy(A._containerTextures.begin(), A._containerTextures.end(), _containerTextures.begin());
	std::copy(A._sphereTextures.begin(), A._sphereTextures.end(), _sphereTextures.begin());
	std::copy(A._octahedronTextures.begin(), A._octahedronTextures.end(), _octahedronTextures.begin());
	std::copy(A._tetrahedronTextures.begin(), A._tetrahedronTextures.end(), _tetrahedronTextures.begin());
}
void ScriptReader::CopyPointerDataMembers(const ScriptReader &A){
	memcpy(_container, A._container, _numberOfContainersToCreate*sizeof(Cube));
	memcpy(_cube, A._cube, _numberOfCubesToCreate*sizeof(Cube));
	memcpy(_octahedron, A._octahedron, _numberOfOctahedronsToCreate*sizeof(Octahedron));
	memcpy(_tetrahedron, A._tetrahedron, _numberOfTetrahedronsToCreate*sizeof(Tetrahedron));
	memcpy(_particleBall, A._particleBall, _numberOfParticleBallsToCreate*sizeof(Particleball));
	memcpy(_glowball, A._glowball, _numberOfGlowballsToCreate*sizeof(Glowball));
	memcpy(_nullObject, A._nullObject, _numberOfNullObjectsToCreate*sizeof(NullObject));
	memcpy(_arrHWD, A._arrHWD, sizeof(float)*3);//*3 because of array[3]
	memcpy(_arrPosition, A._arrPosition, sizeof(float)*4);
	memcpy(_arrAnimation, A._arrAnimation, sizeof(float)*3);
	memcpy(_lights, A._lights, _numberOfLightsToCreate*sizeof(Lights));
}
bool ScriptReader::Create(string scriptFileToRead) {
	_scriptFileToRead = scriptFileToRead;
	//_validObjectNames.push_back("CUBE"); // TODO: Add in if there is time
	ResetVariables();
	AllocateMemory();
	return true;
}
template<typename T>
void ScriptReader::CreateShape(T &shape, std::ifstream &fin, int objectID){
	Color ambient;
	Color diffuse;
	Color emission;
	fin >> _objectID; // so we know the id of the object to set properties to
	_tempCurrentLevel = _currentLevel;
	while (_object!="}") {
		fin >> _object;
		if (_object == "}") {
			_currentLevel--;
			if (_textureID>0){
				shape[objectID].Create(&_position, _shapeSize, true, _textures[_textureID-1]);
				shape[objectID].SetTextureID(_textureID);
			}
			else
				shape[objectID].Create(&_position, _shapeSize, false, "");
			if (_animationID>0){//don't use the default one
				shape[objectID].SetAnimationCoefficients(_animation[_animationID-1]);
			}
			Materials material;
			material.create(ambient, diffuse, emission);
			shape[objectID].SetMaterial(material);
			if(_allShapes.size()>0) //make sure first container has been set
					shape[objectID].SetCollisionObject(_allShapes[0]);
			_allShapes.push_back(&shape[objectID]);
			continue;
		}
		if (_object == "{") {
			_currentLevel++;
			continue;
		}
		if (_object == "SIZE") {
			fin >> _ch; // get rid of the '(' to get to the parameters
			fin >> _shapeSize;
			continue;
		}
		if (_object == "POSITION") {
			fin >> _ch; // get rid of the '(' to get to the parameters
			fin >> _arrPosition[0];
			fin >> _arrPosition[1];
			fin >> _arrPosition[2];
			fin >> _arrPosition[3];
			_position.Assign(_arrPosition[0], _arrPosition[1], _arrPosition[2], _arrPosition[3]);
			continue;
		}
		if (_object == "TEXTURE") {
			fin >> _ch; // get rid of the '(' to get to the parameters
			fin >> _textureID; // store the texture id
			//if (_textureID > 0) { // if >0 then set the texture, else no texture is to be used
			//	// find the texture in the _texture vector from the _textureID read in
			//	//  and put it in the _objectnameTextures vector
			//	_textures.push_back(_textures[_textureID-1]);
			//}
			continue;
		}
		if (_object == "ANIMATION") {
			fin >> _ch; // get rid of the '(' to get to the parameters
			fin >> _animationID; // store the texture id
			if (_animationID > 0) { // if >0 then set the animation, else default animation
				// find the animation in the _animation vector from the _animationID read in
				// and then assign it to the shape
				shape[objectID].SetAnimationCoefficients(_animation[_animationID-1]);
			}
			continue;
		}
		if (_object == "AMBIENT"){
			fin >> _ch; // get rid of the '(' to get to the parameters
			fin >> _arrPosition[0];
			fin >> _arrPosition[1];
			fin >> _arrPosition[2];
			fin >> _arrPosition[3];
			ambient.Assign(_arrPosition[0], _arrPosition[1], _arrPosition[2], _arrPosition[3]);
			continue;
		}
		if (_object == "DIFFUSE"){
			fin >> _ch; // get rid of the '(' to get to the parameters
			fin >> _arrPosition[0];
			fin >> _arrPosition[1];
			fin >> _arrPosition[2];
			fin >> _arrPosition[3];
			diffuse.Assign(_arrPosition[0], _arrPosition[1], _arrPosition[2], _arrPosition[3]);
			continue;
		}
		if (_object == "EMISSION"){
			fin >> _ch; // get rid of the '(' to get to the parameters
			fin >> _arrPosition[0];
			fin >> _arrPosition[1];
			fin >> _arrPosition[2];
			fin >> _arrPosition[3];
			emission.Assign(_arrPosition[0], _arrPosition[1], _arrPosition[2], _arrPosition[3]);
			continue;
		}
	}
}
void ScriptReader::DeallocateMemory(void){
	//_allShapes.clear();
	/*for (vector<Shape *>::iterator p = _allShapes.begin(); p != _allShapes.end(); ++p){
		delete *p;
	}*/
	/*delete [] _container; // TODO sort this, causes error
	delete [] _nullObject;
	delete [] _cube;
	delete [] _sphere;
	delete [] _tetrahedron;
	delete [] _octahedron;
	delete [] _lights;*/
}
void ScriptReader::GetAllShapes(vector<Shape *> &outShapes)const{
	for (vector<Shape *>::const_iterator p = _allShapes.begin(); p != _allShapes.end(); ++p){
		outShapes.push_back((*p)->CloneToAnEmptyObject());
	}
}
void ScriptReader::GetLights(Lights *outLights, int &outNumberOfLightsCreated)const{
	memcpy(outLights, _lights, sizeof(Lights)*_numberOfLightsToCreate);
	outNumberOfLightsCreated = _numberOfLightsToCreate;
}
float ScriptReader::GetRotationSpeed(void)const{
	return _rotationSpeed;
}
vector<string>& ScriptReader::GetContainerTextures(void){
	return _containerTextures;
}
vector<string>& ScriptReader::GetCubeTextures(void){
	return _cubeTextures;
}
vector<string>& ScriptReader::GetOctahedronTextures(void){
	return _octahedronTextures;
}
vector<string>& ScriptReader::GetSphereTextures(void){
	return _sphereTextures;
}
vector<string>& ScriptReader::GetTetrahedronTextures(void){
	return _tetrahedronTextures;
}
vector<string>& ScriptReader::GetTextures(void){
	return _textures;
}
int ScriptReader::GetNumberOfTexturedContainers(void) const{
	return _containerTextures.size();
}
int ScriptReader::GetNumberOfTexturedCubes(void) const{
	return _cubeTextures.size();
}
int ScriptReader::GetNumberOfTexturedOctahedrons(void) const{
	return _octahedronTextures.size();
}
int ScriptReader::GetNumberOfTexturedSpheres(void) const{
	return _sphereTextures.size();
}
int ScriptReader::GetNumberOfTexturedTetrahedrons(void) const{
	return _tetrahedronTextures.size();
}
int ScriptReader::GetNumberOfTextures(void) const{
	return _numberOfTexturesToCreate;
}
bool ScriptReader::IsFogEnabled(void)const{
	return _fogEnabled;
}
void ScriptReader::ResetVariables(void){
	_containerAlreadyCreated = false;
	_containerNeedCreating = false;
	_cubesAlreadyCreated = false;
	_cubesNeedCreating = false;
	_spheresAlreadyCreated = false;
	_spheresNeedCreating = false;
	_tetrahedronAlreadyCreated = false;
	_tetrahedronNeedCreating = false;
	_octahedronAlreadyCreated = false;
	_octahedronNeedCreating = false;
	_texturesAlreadyCreated = false;
	_texturesAlreadyCreated = false;
	_numberOfCubesToCreate = 0;
	_numberOfSpheresToCreate = 0;
	_numberOfContainersToCreate = 0;
	_numberOfTetrahedronsToCreate = 0;
	_numberOfOctahedronsToCreate = 0;
	_currentLevel = 0;
	_textureID = 0;
	_arraySize = 0;
	_objectID = 0;
	_size = 0;
	_cubeTextures.clear();
	_containerTextures.clear();
	_sphereTextures.clear();
	_octahedronTextures.clear();
	_tetrahedronTextures.clear();
	_textures.clear();
	_containerID = 0;
	_cubeID = 0;
	_sphereID = 0;
	_tetrahedronID = 0;
	_octahedronID = 0;
	_nullObjectID = 0;
	_particleBallID = 0;
	_glowballID = 0;
	_fogEnabled = false;
}