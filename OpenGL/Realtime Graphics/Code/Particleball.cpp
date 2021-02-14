#include "Particleball.h"

using std::vector;

Particleball::Particleball(){
}

Particleball::~Particleball(){
	DeallocateMemory();
}

void Particleball::AllocateMemory(void){
	_collisionObject = new Cube[1];
	_collisionObject->Create();
}

void Particleball::Assign(const Vector4f *position, float radius, bool texture, std::string texLocation){
	_particleBallRadius = radius;
	_particleBallCentre.Assign(position->x(),position->y(),position->z(),1.0f);
	SetTextureEnabledStatus(texture);
	SetTexture(texLocation);
}

Particleball* Particleball::Clone() const{
	return new Particleball(*this);
}

Particleball* Particleball::CloneToAnEmptyObject()const{
	Particleball *p = new Particleball;
	p->Create();
	*p = *this;
	return p;
}

void Particleball::CollisionAndResponse(void){
	vector<Particle *> particles;
	for (int i  = 0; i < 6; i++){
		particles = _emitters[i].GetParticlesToModify();
		bool collisionResult;
		int planeHit;
		Vector4f scorchmarkPosition;
		for(vector<Particle *>::iterator p = particles.begin(); p != particles.end(); ++p){
			collisionResult = _myCollision.ParticleCubeCollision((*p)->GetPosition(), (*p)->GetSize(), _collisionObject, planeHit);
			if (collisionResult){
				(*p)->SetAliveStatus(false);
				scorchmarkPosition.Assign((*p)->GetPosition().x(),(*p)->GetPosition().y(),
					(*p)->GetPosition().z(),1.0f);
			}
		}
	}
}

//void Particleball::CopyNonPointerDataMembers(const Particleball &A){
//	// Copy non-pointer data members
//	_emitterMaterials = A._emitterMaterials;
//	_emitterPosition = A._emitterPosition;
//	_particleBallRadius = A._particleBallRadius;
//	_particleBallCentre = A._particleBallCentre;
//	_myCollision = A._myCollision;
//	MySphere::CopyNonPointerDataMembers(A);
//}
//
//void Particleball::CopyPointerDataMembers(const Particleball &A) {
//	*_collisionObject = *_collisionObject;
//	memcpy(_emitters, A._emitters, sizeof(Particleball)*6); //6 emitters
//	MySphere::CopyPointerDataMembers(A);
//}

bool Particleball::Create(){
	Create(&(Vector4f(0.0f,0.0f,0.0f,1.0f)), 0.5f, false, "");
	return true;
}

bool Particleball::Create(const Vector4f *position, float radius, bool texture, std::string texLocation){
	Assign(position, radius, texture, texLocation);
	MySphere::Create(position, radius, texture, texLocation);
	AllocateMemory();
	Vector4f emitterPosition(_particleBallCentre.x()-radius, _particleBallCentre.y()-radius*0.5f,//left
		_particleBallCentre.z()+radius*2.0f,1.0f); //left
	_emitters[0].Create(emitterPosition, 50, 10);
	emitterPosition.Assign(_particleBallCentre.x()-radius/5.2f, _particleBallCentre.y()-radius*0.5f,//right
		_particleBallCentre.z()+radius*2.0f,1.0f);
	_emitters[1].Create(emitterPosition, 50, 10);
	emitterPosition.Assign(_particleBallCentre.x()-radius*0.5f, _particleBallCentre.y(),//top
		_particleBallCentre.z()+radius*2.0f,1.0f);
	_emitters[2].Create(emitterPosition, 50, 10);
	emitterPosition.Assign(_particleBallCentre.x()-radius*0.5f, _particleBallCentre.y()-radius,//bottom
		_particleBallCentre.z()+radius*2.0f,1.0f);
	_emitters[3].Create(emitterPosition, 50, 10);
	emitterPosition.Assign(_particleBallCentre.x()-radius*0.5f, _particleBallCentre.y()-radius*0.5f,//front
		_particleBallCentre.z()+radius*2.5f,1.0f);
	_emitters[4].Create(emitterPosition, 50, 10);
	emitterPosition.Assign(_particleBallCentre.x()-radius*0.5f, _particleBallCentre.y()-radius*0.5f,//back
		_particleBallCentre.z()+radius*2.5f,1.0f);
	_emitters[5].Create(emitterPosition, 50, 10);
	return true;
}

void Particleball::DeallocateMemory(void){
	delete [] _collisionObject;
}

void Particleball::Draw(void)const{
	MySphere::Draw();
	for (int i = 0; i < 6; i++){
		glPushMatrix();
			//glTranslatef(-GetPosition().x(), -GetPosition().y(), -GetPosition().z());
			glPushMatrix();
				//glTranslatef(_emitters[i].GetPosition().x(),_emitters[i].GetPosition().y(),
					//_emitters[i].GetPosition().z());
				_emitters[i].Draw();
			glPopMatrix();
		glPopMatrix();
	}
}

void Particleball::PositionEmitters(void){
}

void Particleball::SetCollisionObject(const Shape *shape){
	*_collisionObject = *shape;
}

void Particleball::Update(void){

}

void Particleball::Update(float deltaTime, float elapsedTime){
	//PositionEmitters();
	for (int i = 0; i < 6; i++){
		_emitters[i].Update(deltaTime);
	}
	CollisionAndResponse();
}