#pragma once

#include <vector>
#include "MySphere.h"
#include "ParticleEmitter.h"
#include "Particle.h"
#include "Collision.h"
#include "Shape.h"
#include "Cube.h"

class Particleball : public MySphere{
public:
	Particleball();
	~Particleball();
	//Particleball(const Particleball &A);//deep copy constructor
	//Particleball& operator=(const Particleball &A);// assignment operator

	void Assign(const Vector4f *position, float radius, bool texture, std::string texLocation); 
	Particleball* Clone()const;
	Particleball* CloneToAnEmptyObject()const;
	void CollisionAndResponse(void);
	bool Create(const Vector4f *position, float radius, bool texture, std::string texLocation);
	bool Create(void);
	void Draw(void)const;
	void PositionEmitters(void);
	void SetCollisionObject(const Shape *shape);
	void Update();
	void Update(float deltaTime, float elapsedTime);

private:
	void AllocateMemory(void);
	/*void CopyNonPointerDataMembers(const Particleball &A);
	void CopyPointerDataMembers(const Particleball &A);*/
	void DeallocateMemory(void);

private:
	static const int _defaultSlices = 50;
	static const int _defaultStacks = 50;
	ParticleEmitter _emitters[6];
	std::vector<Materials> _emitterMaterials;
	std::vector<Vector4f> _emitterPosition;
	GLfloat _particleBallRadius;
	Vector4f _particleBallCentre;
	Collision _myCollision;
	Shape *_collisionObject;
};