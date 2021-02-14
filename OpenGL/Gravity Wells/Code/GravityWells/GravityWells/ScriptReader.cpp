#include "Server.h"
#include <fstream>
#include "ScriptReader.h"

using std::string;
using std::ifstream;
using std::vector;

ScriptReader::ScriptReader(void)
{
}

ScriptReader::~ScriptReader(void)
{
	//for (vector<MySphere *>::iterator p = _ballVec.begin(); p != _ballVec.end(); ++p){
	//	delete *p;
	//}
	//for (vector<BallPhysics *>::iterator p = _ballPhysicsVec.begin(); p != _ballPhysicsVec.end(); ++p){
	//	delete *p;
	//}
	//delete [] _ballPhysics;
	//delete [] _ball;
}

ScriptReader::ScriptReader(string fileToRead): _fileToRead(fileToRead){

}

void ScriptReader::Destroy(void){
	//for (vector<MySphere *>::iterator p = (*_ballVec).begin(); p != (*_ballVec).end(); ++p){
	//	delete *p;
	//}
	//for (vector<BallPhysics *>::iterator p = _ballPhysicsVec->begin(); p != _ballPhysicsVec->end(); ++p){
	//	delete *p;
	//}
	delete [] _ballPhysics;
	delete [] _ball;
	delete [] _gravityWells;
}
void ScriptReader::ReadScriptFileAndParseIt(void){
	ifstream fin(_fileToRead.c_str());
	if (!fin) {
		// TODO: didn't load the file, add error handling
	}
	ResetVariables();
	while (fin >> _object){ //stuff to read in
		if (_object == "{"){
			_currentLevel++; //we've gone up a level
			continue; //go back and read the next character
		}
		if (_object == "}"){
			_currentLevel--; //we've gone down a level
			continue; //go back and read the next character
		}
		if (_currentLevel==0){ //find the object to create
			if (_object == "TEXTURE"){
				//_texturesNeedCreating = true; //set the flag so texture get created
				fin >> _ch; //get rid of the parentheses
				int itemsCreated = 0;
				fin >> _numberOfObjectsToCreate;
				while (itemsCreated<_numberOfObjectsToCreate){
					fin >> _object;
					if (_object == "{"){
						_currentLevel++; //we've gone up a level
						continue; //go back and read the next character
					}
					if (_object == "}"){
						_currentLevel--; //we've gone down a level
						continue; //go back and read the next character
					}
					if (_currentLevel == 2){ //at the stage where we can read the properties to set
						if (_object == "FILEPATH"){
							fin >> _ch; //get rid of the parentheses
							fin >> _texturePath; //Read the file path
							_texturePath.erase(_texturePath.end()-1); //Remove the last parentheses
						}
						if (_object == "WRAP"){
							fin >> _ch; //get rid of the parentheses
							fin >> _textureWrap; //Read the file path
							_textureWrap.erase(_textureWrap.end()-1); //Remove the last parentheses
							GLuint result = _textureManager.LoadTexture(_texturePath,_textureWrap);
							_textureID.push_back(result);
							itemsCreated++;
						}
					}
				}
			}
			if (_object == "PLANARSURFACE"){
				_numberOfObjectsToCreate = 1;
				int itemsCreated = 0;
				vector<float> colorVec;
				float color;
				colorVec.reserve(4);
				while (itemsCreated < _numberOfObjectsToCreate)
				{
					fin >> _object;
					if (_object == "{"){
						_currentLevel++; //we've gone up a level
						continue; //go back and read the next character
					}
					if (_object == "}"){
						_currentLevel--; //we've gone down a level
						continue; //go back and read the next character
					}
					if (_currentLevel == 2)
					{
						if (_object == "COLOUR")
						{
							fin >> _ch; //Remove the opening parentheses
							colorVec.clear();
							while (colorVec.size() < 4){
								fin >> color;
								colorVec.push_back(color);
							}
							_color.Assign(colorVec[0], colorVec[1], colorVec[2], colorVec[3]);
							_planarSurface.SetColor(_color);
							continue;
						}
						if (_object == "POSITION")
						{
							fin >> _ch; //Remove the opening parentheses
							Vector3f position;
							float temp[4];
							for (int i = 0; i < 3; i++){
								fin >> temp[i];
							}
							position.AssignX(temp[0]);
							position.AssignY(temp[1]);
							position.AssignZ(temp[2]);
							_planarSurface.SetPosition(position);
						}
						if (_object == "SIZE")
						{
							fin >> _ch; //Remove the opening parentheses
							fin >> _ballSize;
							Vector3f Size(_ballSize, _ballSize, _ballSize);
							_planarSurface.SetHeightWidthDepth(Size);
							_planarSurface.Assign(_planarSurface.GetPosition(), _planarSurface.GetHeightWidthDepth(),
								_planarSurface.GetTextureEnabledStatus());
						}
						if (_object == "FRICTION")
						{
							fin >> _ch; //Remove the opening parentheses
							fin >> _planarSurfaceFriction;
						}
						if (_object == "TEXTURE")
						{
							fin >> _ch; //Remove the opening parentheses
							int texID;
							fin >> texID;
							_planarSurface.SetTextureID(_textureID[texID-1]);
							_planarSurface.SetTextureEnabledStatus(true);
							itemsCreated++;
						}
					}
				}
			}
			if (_object == "WALL"){
				_numberOfObjectsToCreate = 1;
				int itemsCreated = 0;
				vector<float> colorVec;
				float color;
				colorVec.reserve(4);
				while (itemsCreated < _numberOfObjectsToCreate)
				{
					fin >> _object;
					if (_object == "{"){
						_currentLevel++; //we've gone up a level
						continue; //go back and read the next character
					}
					if (_object == "}"){
						_currentLevel--; //we've gone down a level
						continue; //go back and read the next character
					}
					if (_object == "COLOUR")
					{
						fin >> _ch; //Remove the opening parentheses
						colorVec.clear();
						while (colorVec.size() < 4){
							fin >> color;
							colorVec.push_back(color);
						}
						_color.Assign(colorVec[0], colorVec[1], colorVec[2], colorVec[3]);
						_wall.SetColor(_color);
						continue;
					}
					if (_object == "HEIGHTWIDTHDEPTH")
					{
						fin >> _ch; //Remove the opening parentheses
						for (int i = 0; i < 3; i++){
							fin >> _position[i];
						}
						Vector3f position(_position);
						_wall.SetHeightWidthDepth(position);
						_wall.Assign(_wall.GetPosition(), _wall.GetHeightWidthDepth(), _wall.GetTextureEnabledStatus());
						continue;
					}
					if (_object == "TEXTURE")
					{
						fin >> _ch; //Remove the opening parentheses
						int texID;
						fin >> texID;
						_wall.SetTextureID(texID);
						_wall.SetTextureEnabledStatus(true);
						itemsCreated++;
						continue;
					}
				}
			}
			if (_object == "GRAVITYWELL")
			{
				fin >> _ch; //Get rid of the opening parentheses
				vector<float> colorVec;
				float color;
				colorVec.reserve(4);
				int itemsCreated = 0;
				fin >> _numberOfObjectsToCreate;
				_gravityWells = new GravityWell [_numberOfObjectsToCreate];
				for (int i = 0; i < _numberOfObjectsToCreate; i++)
				{
					_gravityWells[i].Create();
					(*_gravityWellVec).push_back(&_gravityWells[i]);
				}
				while (itemsCreated < _numberOfObjectsToCreate){
					fin >> _object;
					if (_object == "{"){
						_currentLevel++; //we've gone up a level
						continue; //go back and read the next character
					}
					if (_object == "}"){
						_currentLevel--; //we've gone down a level
						continue; //go back and read the next character
					}
					if (_object == "COLOUR"){
						fin >> _ch; //Remove the opening parentheses
						colorVec.clear();
						while (colorVec.size() < 4){
							fin >> color;
							colorVec.push_back(color);
						}
						_color.Assign(colorVec[0], colorVec[1], colorVec[2], colorVec[3]);
						(*_gravityWellVec)[itemsCreated]->SetColor(_color);
						continue;
					}
					if (_object == "POSITION")
					{
						fin >> _ch; //Remove the opening parentheses
						Vector3f position;
						float temp[4];
						for (int i = 0; i < 3; i++){
							fin >> temp[i];
						}
						position.AssignX(temp[0]);
						position.AssignY(temp[1]);
						position.AssignZ(temp[2]);
						(*_gravityWellVec)[itemsCreated]->SetPosition(position);
						continue;
					}
					if (_object == "SIZE")
					{
						fin >> _ch; //Remove the opening parentheses
						float sz;
						fin >> sz;
						(*_gravityWellVec)[itemsCreated]->SetHeightWidthDepth(Vector3f(sz,sz,sz));
						(*_gravityWellVec)[itemsCreated]->Assign((*_gravityWellVec)[itemsCreated]->GetPosition(),
							(*_gravityWellVec)[itemsCreated]->GetHeightWidthDepth(), (*_gravityWellVec)[itemsCreated]->GetTextureEnabledStatus());
						itemsCreated++;
						continue;
					}
				}
				//Created the gravity wells, now determine which gravity well belongs to this machine
				// put that into the single _gravityWell variable, and remove it from the _gravityWells list
				_gravityWell = (*(*_gravityWellVec)[_machineID-1]);
				vector<GravityWell*>::const_iterator it = _gravityWellVec->begin();// + _machineID-1;
				_gravityWellVec->erase(it);

			}
			if (_object == "PEER"){
				fin >> _ch; //Get rid of the opening parentheses
				int itemsCreated = 0;
				vector<float> colorVec;
				float color;
				colorVec.reserve(4);
				fin >> _numberOfObjectsToCreate;
				while (itemsCreated < _numberOfObjectsToCreate){
					fin >> _object;
					if (_object == "{"){
						_currentLevel++; //we've gone up a level
						continue; //go back and read the next character
					}
					if (_object == "}"){
						_currentLevel--; //we've gone down a level
						continue; //go back and read the next character
					}
					if (_object == "PEER")
					{
						int p;
						fin >> p;
						_peerID.push_back(p);
					}
					if (_object == "LIGHTCOLOUR"){
						fin >> _ch; //Remove the opening parentheses
						colorVec.clear();
						while (colorVec.size() < 4){
							fin >> color;
							colorVec.push_back(color);
						}
						_color.Assign(colorVec[0], colorVec[1], colorVec[2], colorVec[3]);
						for (int i = 0; i < _numberOfLightBalls; i++){
							(*_ballVec)[i]->SetColor(_color);
						}
						continue;
					}
					if (_object == "MEDIUMCOLOUR"){
						fin >> _ch; //Remove the opening parentheses
						colorVec.clear();
						while (colorVec.size() < 4){
							fin >> color;
							colorVec.push_back(color);
						}
						_color.Assign(colorVec[0], colorVec[1], colorVec[2], colorVec[3]);
						for (int i = _numberOfLightBalls; i < _numberOfLightBalls+_numberOfMediumBalls; i++){
							(*_ballVec)[i]->SetColor(_color);
						}
						continue;
					}
					if (_object == "HEAVYCOLOUR"){
						fin >> _ch; //Remove the opening parentheses
						colorVec.clear();
						while (colorVec.size() < 4){
							fin >> color;
							colorVec.push_back(color);
						}
						_color.Assign(colorVec[0], colorVec[1], colorVec[2], colorVec[3]);
						for (int i = _numberOfLightBalls+_numberOfMediumBalls; i < _numberOfLightBalls+_numberOfMediumBalls+_numberOfHeavyBalls; i++){
							(*_ballVec)[i]->SetColor(_color);
						}
						continue;
					}
					if (_object == "IP")
					{
						fin >> _ch; //Remove the opening parentheses
						fin >> _object;
						_object.resize(_object.size()-1); //Get rid of end parentheses
						_acceptableIPs.push_back(_object);
						continue;
					}
					if (_object == "TEXTURE"){
						int texID;
						fin >> _ch; //Remove the opening parentheses
						fin >> texID;
						for (vector<MySphere *>::const_iterator i = _ballVec->begin(); i != _ballVec->end(); ++i){
							(*i)->SetTextureID(_textureID[texID-1]);
						}
						itemsCreated++;
					}
				}
				// If here all peer info has been extracted, can now work out this machine's peer ID based upon
				//	this machine's ip compared against the _acceptableIPs vector.
				//	Then erase this ip from the _acceptableIPs vector because the _acceptableIPs vector will act as a vector of ips
				//		of the other peers to communicate with.
				for (unsigned int i = 0; i < _acceptableIPs.size(); i++)
				{
					if (Server::IsLocalIP(_acceptableIPs[i]))
					{
						_machineID = i+1;
						_machineIP = _acceptableIPs[i];
						vector<string>::const_iterator it = _acceptableIPs.begin() + i;
						_acceptableIPs.erase(it);
						break; //No need to be in the loop
					}
				}
				// remove this machine's id from the list of peer ids
				for (unsigned int i = 0; i < _peerID.size(); i++)
				{
					if (_peerID[i]==_machineID)
					{
						vector<int>::const_iterator it = _peerID.begin() + i;
						_peerID.erase(it);
						break; //No need to be in the loop
					}
				}
			}
			if (_object == "MAXIMUMNUMBEROFBALLS"){
				fin >> _ch; //Get rid of the opening parentheses.
				int objectsToCreate;
				fin >> objectsToCreate;
				_ball = new MySphere[objectsToCreate];
				_ballPhysics = new BallPhysics[objectsToCreate];
				Vector3f position(0.0f,0.0f,0.0f);
				Vector3f heightWidthDepth(_ballSize, _ballSize, _ballSize);
				//Create the light balls and add them to the ball, and physics vectors
				(*_ballVec).reserve(sizeof(_ball)*objectsToCreate);
				(*_ballPhysicsVec).reserve(sizeof(_ballPhysics)*objectsToCreate);
				for (int i = 0; i < _numberOfLightBalls; i++){
					_ball[i].Create(position, heightWidthDepth, true);
					_ballPhysics[i].Create(position, _ballSize);
					_ballPhysics[i].SetMass(_lightMass);
					_ballPhysics[i].SetRealismLevel(_realismLevel);
					_ballPhysics[i].SetElasticity(_ballElasticity);
					(*_ballVec).push_back(&_ball[i]);
					(*_ballPhysicsVec).push_back(&_ballPhysics[i]);
				}
				//Create the medium balls and add them to the ball, and physics vectors
				for (int i = _numberOfLightBalls; i < _numberOfLightBalls+_numberOfMediumBalls; i++){
					_ball[i].Create(position, heightWidthDepth, true);
					_ballPhysics[i].Create(position, _ballSize);
					_ballPhysics[i].SetMass(_mediumMass);
					_ballPhysics[i].SetRealismLevel(_realismLevel);
					_ballPhysics[i].SetElasticity(_ballElasticity);
					(*_ballVec).push_back(&_ball[i]);
					(*_ballPhysicsVec).push_back(&_ballPhysics[i]);
				}
				//Create the heavy balls and add them to the ball, and physics vectors
				for (int i = _numberOfLightBalls+_numberOfMediumBalls; i < _numberOfLightBalls+_numberOfMediumBalls+_numberOfHeavyBalls; i++){
					_ball[i].Create(position, heightWidthDepth, true);
					_ballPhysics[i].Create(position, _ballSize);
					_ballPhysics[i].SetMass(_heavyMass);
					_ballPhysics[i].SetRealismLevel(_realismLevel);
					_ballPhysics[i].SetElasticity(_ballElasticity);
					(*_ballVec).push_back(&_ball[i]);
					(*_ballPhysicsVec).push_back(&_ballPhysics[i]);
				}
			}
			if (_object == "PBM"){
				fin >> _ch; //Get rid of the opening parentheses.
				fin >> _realismLevel;
			}
			if (_object == "MASSLIGHT"){
				fin >> _ch; //Get rid of the opening parentheses.
				fin >> _lightMass;
			}
			if (_object == "MASSMEDIUM"){
				fin >> _ch; //Get rid of the opening parentheses.
				fin >> _mediumMass;
			}
			if (_object == "MASSHEAVY"){
				fin >> _ch; //Get rid of the opening parentheses.
				fin >> _heavyMass;
			}
			if (_object == "FLOORFRICTION"){
				fin >> _ch; //Get rid of the opening parentheses.
				fin >> _floorFriction;
			}
			if (_object == "BALLELASTICITY"){
				fin >> _ch; //Get rid of the opening parentheses.
				fin >> _ballElasticity;
			}
			if (_object == "BALLSIZE"){
				fin >> _ch; //Get rid of the opening parentheses.
				fin >> _ballSize;
			}
			if (_object == "LIGHTBALLS"){
				fin >> _ch; //Get rid of the opening parentheses.
				fin >> _numberOfLightBalls;
			}
			if (_object == "MEDIUMBALLS"){
				fin >> _ch; //Get rid of the opening parentheses.
				fin >> _numberOfMediumBalls;
			}
			if (_object == "HEAVYBALLS"){
				fin >> _ch; //Get rid of the opening parentheses.
				fin >> _numberOfHeavyBalls;
			}
			if (_object == "PORT"){
				fin >> _ch; //Get rid of the opening parentheses.
				fin >> _portNumber;
			}
			if (_object == "WALLELASTICITY"){
				fin >> _ch; //Get rid of the opening parentheses.
				fin >> _wallElasticity;
			}
		}
	}
}

void ScriptReader::ResetVariables(void){
	_currentLevel = 0;
	_object = "";
	_numberOfObjectsToCreate = 0;
	_numberOfTexturesToCreate = 0;
	_texturesNeedCreating = false;
	_texturePath = "";
	_textureWrap = "";

	_planarSurface.Create();
	_wall.Create();
	_gravityWell.Create();
	_ballVec = new vector<MySphere *>; //make sure it points to the type of vector it should
	_ballPhysicsVec = new vector<BallPhysics *>;
	_gravityWellVec = new vector<GravityWell *>;
}