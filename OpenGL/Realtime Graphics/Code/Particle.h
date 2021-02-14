#pragma once

#include "Vector3f.h"
#include "Vector4f.h"
#include "Materials.h"
#include "Color.h"

class Particle{
public:
	Particle();
	~Particle();

	Particle(const Particle &A);//deep copy constructor
	Particle& operator=(const Particle &A);// assignment operator

	void Assign(const Vector4f &position, float size, float lifetime, short type, const Vector3f &velocity,
		const std::string &scorchTexture, int scorchTextureID, const Materials &material);//point particle
	void Assign(const Vector4f &position, float size, float lifetime, short type, const Vector3f &velocity,
		const std::string &scorchTexture, int scorchTextureID, const Materials &material,
		const std::string &particleTexture, int particleTextureID);//texturedQuad particle
	Particle* Clone(void)const;
	Particle* CloneToAnEmptyObject(void)const;
	bool Create();//create a default particle(point)
	bool Create(const Vector4f &position, float size, float lifetime, short type, const Vector3f &velocity,
		const std::string &scorchTexture, int scorchTextureID, const Materials &material);//point particle
	bool Create(const Vector4f &position, float size, float lifetime, short type, const Vector3f &velocity,
		const std::string &scorchTexture, int scorchTextureID, const Materials &material,
		const std::string &particleTexture, int particleTextureID);//texturedQuad particle
	void CreateScorchMark(void);
	void Draw(void)const;
	Vector4f GetPosition(void)const;
	float GetSize(void)const;
	void Initialise(const Vector4f &position);
	bool IsAlive(void)const;
	bool IsScorchmarkAlive(void)const;
	void Update(float deltaTime);

	void AllocateMemory(void);
	void CopyNonPointerDataMembers(const Particle &A);
	void CopyPointerDataMembers(const Particle &A);
	void DeallocateMemory(void);
	void SetAliveStatus(bool status);
	void SetLifetime(float lifetime);
	void SetMaterial(const Materials &material);
	void SetParticleTexture(const std::string &particleTexture);
	void SetParticleTextureID(int particleTexture);
	void SetPosition(const Vector4f &position);
	void SetScorchPosition(const Vector4f &position);
	void SetScorchTexture(const std::string &scorchTexture);
	void SetScorchTextureID(int scorchTextureID);
	void SetSize(float size);
	void SetType(short type);
	void SetVelocity(const Vector3f &velocity);

private:
	Materials _material, _defaultMaterial;
	Vector4f _position, _defaultPosition, _initialPosition, _scorchmarkPosition;
	float _size, _defaultSize, _initialSize, _scorchmarkSize;
	std::string _particleTexture, _scorchTexture;
	float _lifetime, _age, _defaultLifetime, _scorchmarkLifetime, _scorchmarkAge, _defaultScorchmarkLifetime;
	Vector3f _velocity, _defaultVelocity;
	short _type; // 1 = Textured Quad, 0 or any value that isn't 1 = point
	int _particleTextureID, _scorchTextureID;
	GLfloat (*_vertexArray)[3];
	GLfloat (*_scorchmarkVertexArray)[3];
	GLfloat (*_scorchTextureArray)[2];
	GLfloat (*_particleTextureArray)[2];
	GLuint *_indexArray;
	GLuint *_scorchmarkIndexArray;
	GLuint _indexArraySize, _scorchTextureArraySize, _particleTextureArraySize, _vertexArraySize, _scorchmarkIndexArraySize;
	GLuint _scorchmarkVertexArraySize;
	bool _alive, _scorchmarkAlive;
};