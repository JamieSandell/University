#include "Particle.h"

Particle::Particle(){

}

Particle::~Particle(){
	DeallocateMemory();
}

Particle::Particle(const Particle &A){
	DeallocateMemory();
	AllocateMemory();
	CopyNonPointerDataMembers(A);
	CopyPointerDataMembers(A);
}

Particle& Particle::operator =(const Particle &A){
	if (this!=&A){// the address of the object is essentially an ID to tell objects apart, don't delete itself
		CopyNonPointerDataMembers(A);
		DeallocateMemory();
		AllocateMemory();
		CopyPointerDataMembers(A);
	}
	return *this;
}

void Particle::AllocateMemory(void){
	_indexArray = new GLuint [_indexArraySize];
	_particleTextureArray = new GLfloat [_particleTextureArraySize][2];
	_scorchTextureArray = new GLfloat [_scorchTextureArraySize][2];
	_vertexArray = new GLfloat [_vertexArraySize][3];
	_scorchmarkIndexArray = new GLuint [_scorchmarkIndexArraySize];
	_scorchmarkVertexArray = new GLfloat [_scorchmarkVertexArraySize][3];
}

void Particle::Assign(const Vector4f &position, float size, float lifetime, short type, const Vector3f &velocity,
					  const std::string &scorchTexture, int scorchTextureID, const Materials &material){
  _position = position;
  _size = size;
  _lifetime = lifetime;
  _type = type;
  _velocity = velocity;
  _scorchTexture = scorchTexture;
  _scorchTextureID = scorchTextureID;
  _material = material;
}

void Particle::Assign(const Vector4f &position, float size, float lifetime, short type, const Vector3f &velocity,
					  const std::string &scorchTexture, int scorchTextureID, const Materials &material,
					  const std::string &particleTexture, int particleTextureID){
	_position = position;
	_size = size;
	_lifetime = lifetime;
	_type = type;
	_velocity = velocity;
	_scorchTexture = scorchTexture;
	_scorchTextureID = scorchTextureID;
	_material = material;
	_particleTexture = particleTexture;
	_particleTextureID = particleTextureID;
}

Particle* Particle::CloneToAnEmptyObject()const{
	Particle *p = new Particle;
	p->Create();
	*p = *this;
	return p;
}

Particle* Particle::Clone()const{
	return new Particle(*this);
}

void Particle::CopyNonPointerDataMembers(const Particle &A){
	_material = A._material;
	_defaultMaterial = A._defaultMaterial;
	_position = A._position;
	_defaultPosition = A._defaultPosition;
	_initialPosition = A._initialPosition;
	_scorchmarkPosition = A._scorchmarkPosition;
	_size = A._size;
	_defaultSize = A._size;
	_initialSize = A._initialSize;
	_scorchmarkSize = A._scorchmarkSize;
	_particleTexture = A._particleTexture;
	_scorchTexture = A._scorchTexture;
	_lifetime = A._lifetime;
	_age = A._age;
	_defaultLifetime = A._defaultLifetime;
	_scorchmarkLifetime = A._scorchmarkLifetime;
	_scorchmarkAge = A._scorchmarkAge;
	_defaultScorchmarkLifetime = A._defaultScorchmarkLifetime;
	_velocity = A._velocity;
	_defaultVelocity = A._defaultVelocity;
	_type = A._type;
	_particleTextureID = A._particleTextureID;
	_scorchTextureID = A._scorchTextureID;
	_indexArraySize = A._indexArraySize;
	_scorchTextureArraySize = A._scorchTextureArraySize;
	_particleTextureArraySize = A._particleTextureArraySize;
	_vertexArraySize = A._vertexArraySize;
	_scorchmarkIndexArraySize = A._scorchmarkIndexArraySize;
	_scorchmarkVertexArraySize = A._scorchmarkVertexArraySize;
	_alive = A._alive;
	_scorchmarkAlive = A._scorchmarkAlive;
}

void Particle::CopyPointerDataMembers(const Particle &A){
	memcpy(_indexArray, A._indexArray, _indexArraySize*sizeof(GLuint));
	memcpy(_particleTextureArray, A._particleTextureArray, _particleTextureArraySize*sizeof(GLfloat)*2);// *2 because array[2]
	memcpy(_scorchTextureArray, A._scorchTextureArray, _scorchTextureArraySize*sizeof(GLfloat)*2);// *2 because array[2]
	memcpy(_vertexArray, A._vertexArray, _vertexArraySize*sizeof(GLfloat)*3);// *3 because array[3]
	memcpy(_scorchmarkIndexArray, A._scorchmarkIndexArray, _scorchmarkIndexArraySize*sizeof(GLuint));
	memcpy(_scorchmarkVertexArray, A._scorchmarkVertexArray, _scorchmarkVertexArraySize*sizeof(GLfloat)*3);// *3 because array[3]
}

bool Particle::Create(void){
	_indexArraySize = 1;
	_scorchmarkIndexArraySize = 1;
	_particleTextureArraySize = 1;
	_scorchTextureArraySize = 1;
	_vertexArraySize = 1;
	_scorchmarkVertexArraySize = 1;
	_defaultLifetime = 1.0f;
	_defaultScorchmarkLifetime = 1.0f;
	_defaultMaterial.create();
	_defaultPosition.Assign(0.0f, 0.0f, 0.0f, 1.0f);
	_defaultSize = 0.25f;
	_defaultVelocity.Assign(0.0f, 1.0f, 0.0f);
	Create(_defaultPosition, _defaultSize, _defaultLifetime, 0, _defaultVelocity, "", 0, _defaultMaterial);
	return true;
}

bool Particle::Create(const Vector4f &position, float size, float lifetime, short type, const Vector3f &velocity,
					  const std::string &scorchTexture, int scorchTextureID, const Materials &material){
	Assign(position, size, lifetime, type, velocity, scorchTexture, scorchTextureID, material);
	_indexArraySize = 1;
	_scorchmarkIndexArraySize = 4;
	_scorchTextureArraySize = 4;
	_particleTextureArraySize = 1;
	_vertexArraySize = 1;
	_scorchmarkVertexArraySize = 4;
	AllocateMemory();

	//Initialise(position);
	_alive = false;
	_age = 0.0f;
	_position = position;
	_scorchmarkAlive = false;
	_scorchmarkAge = 0.0f;
	_scorchmarkPosition = _position;

	for (GLuint i = 0; i < _indexArraySize; i++){
		_indexArray[i] = i;
	}
	for (GLuint i = 0; i < _scorchmarkIndexArraySize; i++){
		_scorchmarkIndexArray[i] = i;
	}

	_vertexArray[0][0] = _position.x();
	_vertexArray[0][1] = _position.y();
	_vertexArray[0][2] = _position.z();

	//top left
	_scorchTextureArray[0][0] = 0.0f;//x
	_scorchTextureArray[0][1] = 1.0f;//y
	//bottom left
	_scorchTextureArray[1][0] = 0.0f;
	_scorchTextureArray[1][1] = 0.0f;
	//bottom right
	_scorchTextureArray[2][0] = 1.0f;
	_scorchTextureArray[2][1] = 0.0f;
	//top right
	_scorchTextureArray[3][0] = 1.0f;
	_scorchTextureArray[3][1] = 1.0f;

	return true;
}

bool Particle::Create(const Vector4f &position, float size, float lifetime, short type, const Vector3f &velocity,
					  const std::string &scorchTexture, int scorchTextureID, const Materials &material,
					  const std::string &particleTexture, int particleTextureID){
	Assign(position, size, lifetime, type, velocity, scorchTexture, scorchTextureID, material, particleTexture, particleTextureID);
	_indexArraySize = 4;
	_scorchmarkIndexArraySize = 4;
	_scorchTextureArraySize = 4;
	_particleTextureArraySize = 4;
	_vertexArraySize = 4;
	_scorchmarkVertexArraySize = 4;
	//Initialise(position);
	_alive = false;
	_age = 0.0f;
	_position = position;
	_scorchmarkAlive = false;
	_scorchmarkAge = 0.0f;
	_scorchmarkPosition = _position;
	AllocateMemory();
	float x = position.x();
	float y = position.y();
	float z = position.z();
	float halfSize = size/2;

	for (GLuint i = 0; i < _indexArraySize; i++){
		_indexArray[i] = i;
	}
	for (GLuint i = 0; i < _scorchmarkIndexArraySize; i++){
		_scorchmarkIndexArray[i] = i;
	}

	//top left corner
	_vertexArray[0][0] = x-halfSize;//x
	_vertexArray[0][1] = y+halfSize;//y
	_vertexArray[0][2] = z;
	_particleTextureArray[0][0] = 0.0f;
	_particleTextureArray[0][1] = 1.0f;
	_scorchTextureArray[0][0] = 0.0f;
	_scorchTextureArray[0][1] = 1.0f;
	//bottom left corner
	_vertexArray[1][0] = x-halfSize;//x
	_vertexArray[1][1] = y-halfSize;//y
	_vertexArray[1][2] = z;
	_particleTextureArray[1][0] = 0.0f;
	_particleTextureArray[1][1] = 0.0f;
	_scorchTextureArray[1][0] = 0.0f;
	_scorchTextureArray[1][1] = 0.0f;
	//bottom right corner
	_vertexArray[2][0] = x+halfSize;//x
	_vertexArray[2][1] = y-halfSize;//y
	_vertexArray[2][2] = z;
	_particleTextureArray[2][0] = 1.0f;
	_particleTextureArray[2][1] = 0.0f;
	_scorchTextureArray[2][0] = 1.0f;
	_scorchTextureArray[2][1] = 0.0f;
	//top right corner
	_vertexArray[3][0] = x+halfSize;//x
	_vertexArray[3][1] = y+halfSize;//y
	_vertexArray[3][2] = z;
	_particleTextureArray[3][0] = 1.0f;
	_particleTextureArray[3][1] = 1.0f;
	_scorchTextureArray[3][0] = 1.0f;
	_scorchTextureArray[3][1] = 1.0f;

	memcpy(_scorchmarkVertexArray, _vertexArray, _scorchmarkVertexArraySize*sizeof(GLfloat)*3);

	return true;
}

void Particle::CreateScorchMark(void){
	_scorchmarkAge = 0.0f;
	_scorchmarkLifetime = 5.0f;
	_scorchmarkPosition = _position;
	_scorchmarkAlive = true;
}

void Particle::DeallocateMemory(void){
	delete [] _indexArray;
	delete [] _scorchmarkIndexArray;
	delete [] _particleTextureArray;
	delete [] _scorchTextureArray;
	delete [] _vertexArray;
	delete [] _scorchmarkVertexArray;
}

void Particle::Draw(void) const{
	glPushMatrix();
		glDisable(GL_LIGHTING);
		_material.apply();
		if (_alive){
			glPushMatrix();
				//glRotatef(-90.0f,1.0f,0.0f,0.0f);
				glTranslatef(_position.x(), _position.y(), _position.z());
				//glRotatef(-90.0f,1.0f,0.0f,0.0f);
				glColor4f(1.0f, 1.0f, 0.0f, _lifetime-_age);//will fade out as the particle ages
				if (_type!=1){//draw the point particle
					glDisable(GL_TEXTURE_2D);
					glPointSize(_size);
					glEnableClientState(GL_VERTEX_ARRAY);
					glVertexPointer(3, GL_FLOAT, 0, _vertexArray);
					glDrawElements(GL_POINTS, _indexArraySize, GL_UNSIGNED_INT, _indexArray);
					glDisableClientState(GL_VERTEX_ARRAY);
					glEnable(GL_TEXTURE_2D);
				}
				else{//draw the textured quad
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, _particleTextureID);
					glEnableClientState(GL_VERTEX_ARRAY);
					glEnableClientState(GL_TEXTURE_COORD_ARRAY);

					glVertexPointer(3, GL_FLOAT, 0, _vertexArray);
					glTexCoordPointer(2, GL_FLOAT, 0, _particleTextureArray);

					glDrawElements(GL_QUADS, _indexArraySize, GL_UNSIGNED_INT, _indexArray);

					glDisableClientState(GL_VERTEX_ARRAY);
					glDisableClientState(GL_TEXTURE_COORD_ARRAY);
					glDisable(GL_TEXTURE_2D);
					}
			glPopMatrix();
		}
		if (_scorchmarkAlive){
			//glPushMatrix();
			//	glTranslatef(_scorchmarkPosition.x(), _scorchmarkPosition.y(), _scorchmarkPosition.z());
			//	//glRotatef(90.0f,1.0f,0.0f,0.0f);
			//	glColor4f(1.0f, 1.0f, 1.0f, _scorchmarkLifetime-_scorchmarkAge);//will fade out as the particle ages
			//	glEnable(GL_TEXTURE_2D);
			//	glBindTexture(GL_TEXTURE_2D, _scorchTextureID);
			//	glEnableClientState(GL_VERTEX_ARRAY);
			//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			//	glVertexPointer(3, GL_FLOAT, 0, _scorchmarkVertexArray);
			//	glTexCoordPointer(2, GL_FLOAT, 0, _scorchTextureArray);

			//	glDrawElements(GL_QUADS, _scorchmarkIndexArraySize, GL_UNSIGNED_INT, _scorchmarkIndexArray);

			//	glDisableClientState(GL_VERTEX_ARRAY);
			//	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			//	glDisable(GL_TEXTURE_2D);
			//glPopMatrix();
		}
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

Vector4f Particle::GetPosition(void) const{
	return _position;
}

float Particle::GetSize(void)const{
	return _size;
}

bool Particle::IsAlive(void)const{
	return _alive;
}

void Particle::Initialise(const Vector4f &position){
	_alive = true;
	_age = 0.0f;
	_position = position;
}

bool Particle::IsScorchmarkAlive(void)const{
	return _scorchmarkAlive;
}

void Particle::SetAliveStatus(bool status){
	_alive = status;
}

void Particle::SetLifetime(float lifetime){
	_lifetime = lifetime;
}

void Particle::SetMaterial(const Materials &material){
	_material = material;
}

void Particle::SetParticleTexture(const std::string &particleTexture){
	_particleTexture = particleTexture;
}

void Particle::SetParticleTextureID(int particleTextureID){
	_particleTextureID = particleTextureID;
}

void Particle::SetPosition(const Vector4f &position){
	_position = position;
}

void Particle::SetScorchPosition(const Vector4f &position){
	_scorchmarkPosition = position;
}

void Particle::SetScorchTexture(const std::string &scorchTexture){
	_scorchTexture = scorchTexture;
}

void Particle::SetScorchTextureID(int scorchTextureID){
	_scorchTextureID = scorchTextureID;
}

void Particle::SetSize(float size){
	_size = size;
}

void Particle::SetType(short type){
	_type = type;
}

void Particle::SetVelocity(const Vector3f &velocity){
	_velocity = velocity;
}

void Particle::Update(float deltaTime){
	if (_alive){
		_age+=deltaTime;
		if (_age>_lifetime)//exceeded it's lifetime
			_alive = false;
		Vector4f velocity(_velocity.x(), _velocity.y(), _velocity.z(), 1.0f);
		_position = _position + (velocity*deltaTime);
	}
	if (_scorchmarkAlive){
		_scorchmarkAge+=deltaTime;
		if (_scorchmarkAge>_scorchmarkLifetime)
			_scorchmarkAlive = false;
	}
}