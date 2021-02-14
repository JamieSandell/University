#include <time.h>
#include "ParticleEmitter.h"
#include "Materials.h"
#include "Color.h"

using std::vector;

ParticleEmitter::ParticleEmitter(){

}

ParticleEmitter::~ParticleEmitter(){
	DeallocateMemory();
}

ParticleEmitter::ParticleEmitter(const ParticleEmitter &A){
	DeallocateMemory();
	AllocateMemory();
	CopyNonPointerDataMembers(A);
	CopyPointerDataMembers(A);
}

ParticleEmitter& ParticleEmitter::operator =(const ParticleEmitter &A){
	if (&A!=this){// the address of the object is essentially an ID to tell objects apart, don't delete itself
		CopyNonPointerDataMembers(A);
		DeallocateMemory();
		AllocateMemory();
		CopyPointerDataMembers(A);
	}
	return *this;
}

void ParticleEmitter::AllocateMemory(void){
	_particles = new Particle[_maximumNumberOfParticles];
	_aliveParticles.resize(_maximumNumberOfParticles);
	_deadParticles.resize(_maximumNumberOfParticles);
}

void ParticleEmitter::Assign(const Vector4f &position, int maxmimumNumberOfParticles, int rateOfGeneration){
	_position = position;
	_maximumNumberOfParticles = maxmimumNumberOfParticles;
	_rateOfGeneration = _rateOfGeneration;
}

void ParticleEmitter::CopyNonPointerDataMembers(const ParticleEmitter &A){
	_position = A._position;
	_maximumNumberOfParticles = A._maximumNumberOfParticles;
	_rateOfGeneration = A._rateOfGeneration;
	_pointerToEndOfDeadParticles = A._pointerToEndOfDeadParticles;
	_pointerToEndOfAliveParticles = A._pointerToEndOfAliveParticles;
}

void ParticleEmitter::CopyPointerDataMembers(const ParticleEmitter &A){
	_aliveParticles.clear();
	for (vector<Particle *>::const_iterator p = A._aliveParticles.begin(); p != A._aliveParticles.end(); ++p){
		_aliveParticles.push_back((*p)->CloneToAnEmptyObject());
	}
	_deadParticles.clear();
	for (vector<Particle *>::const_iterator p = A._deadParticles.begin(); p != A._deadParticles.end(); ++p){
		_deadParticles.push_back((*p)->CloneToAnEmptyObject());
	}
	memcpy(_particles, A._particles, _maximumNumberOfParticles*sizeof(Particle));
}

bool ParticleEmitter::Create(){
	_maximumNumberOfParticles = 10;
	Create(Vector4f(0.0f,0.0f,0.0f,1.0f), _maximumNumberOfParticles, 1);
	return true;
}

bool ParticleEmitter::Create(const Vector4f &position, int maxmimumNumberOfParticles, int rateOfGeneration){
	_position = position;
	_maximumNumberOfParticles = maxmimumNumberOfParticles;
	_rateOfGeneration = rateOfGeneration;

	AllocateMemory();

	_particleTexture=".\\Resources\\Textures\\scorch.bmp";

	//set the particle properties
	Materials mats;
	_aliveParticles.clear();//TODO use resize and insert, or get rid of resize in the allocatememory and just use push_back
	_deadParticles.clear();
	mats.create(Color(0.0f,0.0f,0.0f,1.0f), Color(1.0f,1.0f,0.0f,1.0f), Color(1.0f,1.0f,0.0f,1.0f));
	for(int i = 0; i < _maximumNumberOfParticles; i++){
		//_particles[i].Create(_position, 1.0f, rand()/(float(RAND_MAX)+1)*(2.0f-5.0f)+5.0f, 0,
		//	Vector3f(rand()/(float(RAND_MAX)+1)*(-1.0f-1.0f)+1.0f,rand()/(float(RAND_MAX)+1)*(-1.0f-1.0f)+1.0f,rand()/(float(RAND_MAX)+1)*(-1.0f-1.0f)+1.0f),
		//	"", 0,mats);//create points
		//_particles[i].Create(_position, 0.5f, rand()/(float(RAND_MAX)+1)*(2.0f-5.0f)+5.0f, 1,
		//	Vector3f(rand()/(float(RAND_MAX)+1)*(-1.0f-1.0f)+1.0f,rand()/(float(RAND_MAX)+1)*(-1.0f-1.0f)+1.0f,rand()/(float(RAND_MAX)+1)*(-1.0f-1.0f)+1.0f),
		//	"", 0,mats,_particleTexture,3);//create textured quads
		_particles[i].Create(_position, 1.0f, rand()/(float(RAND_MAX)+1)*(1.0f-2.0f)+2.0f, 1,
			Vector3f(rand()/(float(RAND_MAX)+1)*(-2.0f-2.0f)+2.0f,rand()/(float(RAND_MAX)+1)*(-2.0f-2.0f)+2.0f,rand()/(float(RAND_MAX)+1)*(-2.0f-2.0f)+2.0f),
			"", 0,mats,_particleTexture,3);//create textured quads
		//_aliveParticles.push_back(&(_particles[i].CloneToAnEmptyObject()));
		_aliveParticles.push_back(&_particles[i]);
	}
	_pointerToEndOfAliveParticles = _maximumNumberOfParticles;
	_pointerToEndOfDeadParticles = 0;
	return true;
}

void ParticleEmitter::DeallocateMemory(){
	/*for (vector<Particle *>::iterator p = _aliveParticles.begin(); p != _aliveParticles.end(); ++p){
	delete *p;
	}
	for (vector<Particle *>::iterator p = _deadParticles.begin(); p != _deadParticles.end(); ++p){
		delete *p;
	}*/
	_aliveParticles.clear();
	_deadParticles.clear();
	delete [] _particles;
}

void ParticleEmitter::Draw() const{
	glPushMatrix();
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		GLfloat matrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX,matrix);
		/*matrix[0] = 1.0f; matrix[1] = 0.0f; matrix[2] = 0.0f;
		matrix[4] = 0.0f; matrix[5] = 1.0f; matrix[6] = 0.0f;*/
		matrix[0] = matrix[5] = matrix[10] = 1.0f;
		matrix[1] = matrix[2] = matrix[4] = matrix[6] = matrix[8] = matrix[9] = 0.0f;
		glLoadMatrixf(matrix);
		glDisable(GL_CULL_FACE);
		for (vector<Particle *>::const_iterator p = _aliveParticles.begin(); p!= _aliveParticles.end(); ++p){
			(*p)->Draw();
		}
		glEnable(GL_CULL_FACE);
		glDepthMask(GL_TRUE);
	glPopMatrix();
}

vector<Particle *> ParticleEmitter::GetParticlesToModify(void){
	return _aliveParticles;
}

Vector4f ParticleEmitter::GetPosition(void)const{
	return _position;
}

void ParticleEmitter::SetPosition(const Vector4f &position){
	_position = position;
}

void ParticleEmitter::Update(float deltaTime){
	//TODO: find out if a particle is dead, if it is, move it to the dead list
	// increment the pointerToDead, decrement pointerToAlive
	// generate new particles - take the amount off the dead list, decrement the pointerToDead
	// add them to the end of the aliveParticles list, increment the pointerToAlive
	// run Particle.Update(deltaTime) on all alive particles
	vector<Particle *>::iterator pDeadInsert = _deadParticles.begin();
	pDeadInsert+=_pointerToEndOfDeadParticles;
	vector<Particle *>::iterator e = _aliveParticles.begin();
	for (vector<Particle *>::iterator p = _aliveParticles.begin(); p != _aliveParticles.end();){
		if (!(*p)->IsAlive()){//if the particle is dead
			_deadParticles.push_back(*p);
			_pointerToEndOfDeadParticles++;
			if (_pointerToEndOfDeadParticles>_maximumNumberOfParticles)//bounds checking
				_pointerToEndOfDeadParticles--;
			p = _aliveParticles.erase(p);
			_pointerToEndOfAliveParticles--;
			if (_pointerToEndOfAliveParticles<0){//bounds checking
				_pointerToEndOfAliveParticles++;
			}
			if(_pointerToEndOfAliveParticles==0)
				break;//no particles to check so leave the loop
			//p = _aliveParticles.begin(); //insert/erase cause p to become invalidated
			//e = _aliveParticles.begin();
			continue;
		}
		else
			p++;
	}
	// try and generate at the rateOfGeneration
	// however there might not be enough dead particles to bring back to life
	GLuint amountToGenerateThisFrame;
	if (_pointerToEndOfDeadParticles<_rateOfGeneration)// not enough dead particles to meet the rateOfGeneration
		amountToGenerateThisFrame = _pointerToEndOfDeadParticles;
	else//there is enough dead particles to meet the rateOfGeneration
		amountToGenerateThisFrame = _rateOfGeneration;
	/*Iterators specifying a range within the vector to be removed: [first,last). i.e.,
	the range includes all the elements between first and last, including the element
	pointed by first but not the one pointed by last.*/
	if(amountToGenerateThisFrame>0){ // only insert into aliveParticles if there is actually particles to generateThisFrame
		vector<Particle *>::iterator pFirst = _deadParticles.end()-amountToGenerateThisFrame;
		vector<Particle *>::iterator pEnd = _deadParticles.end()-1;
		vector<Particle *>::iterator pAliveInsert = _aliveParticles.begin();
		pAliveInsert+=_pointerToEndOfAliveParticles;
		for (vector<Particle *>::iterator p = _deadParticles.end()-amountToGenerateThisFrame; p!=_deadParticles.end(); ++p){
			(*p)->Initialise(_position);
		}
		_aliveParticles.insert(pAliveInsert, pFirst, pEnd+1);
		_pointerToEndOfAliveParticles+=amountToGenerateThisFrame;
		_deadParticles.erase(pFirst, pEnd+1);
		_pointerToEndOfDeadParticles-=amountToGenerateThisFrame;
	}
	//update the alive particles
	for (vector<Particle *>::iterator p = _aliveParticles.begin(); p != _aliveParticles.end(); ++p){
		(*p)->Update(deltaTime);
	}
}