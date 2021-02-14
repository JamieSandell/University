#pragma once

#include <vector>
#include "Vector4f.h"
#include "Particle.h"

class ParticleEmitter{
public:
	ParticleEmitter();
	~ParticleEmitter();

	ParticleEmitter(const ParticleEmitter &A);//deep copy operator
	ParticleEmitter& operator=(const ParticleEmitter &A);//assignment operator

	void AllocateMemory();
	void Assign(const Vector4f &Position, int maxmimumNumberOfParticles, int rateOfGeneration);
	void CopyNonPointerDataMembers(const ParticleEmitter &A);
	void CopyPointerDataMembers(const ParticleEmitter &A);
	bool Create();
	bool Create(const Vector4f &Position, int maxmimumNumberOfParticles, int rateOfGeneration);
	void DeallocateMemory();
	void Draw(void)const;
	Vector4f GetPosition(void)const;
	std::vector<Particle *> GetParticlesToModify(void); //Returns alive particles. For collision code, can directly flag a collided particle as such
	void SetPosition(const Vector4f &position);
	void Update(float deltaTime);
private:
	Vector4f _position;
	int _maximumNumberOfParticles;
	int _rateOfGeneration;
	int _pointerToEndOfAliveParticles;
	int _pointerToEndOfDeadParticles;
	Particle *_particles;
	std::vector<Particle *> _aliveParticles;
	std::vector<Particle *> _deadParticles;
	std::string _particleTexture;
	GLuint _particleTextureID;
};