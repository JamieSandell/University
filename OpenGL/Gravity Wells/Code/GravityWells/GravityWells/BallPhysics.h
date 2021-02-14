#pragma once

#include "Circle.h"
#include "Quaternion.h"
#include "Vector3f.h"

namespace Physics{
	enum PBM{
		Particles,
		ParticlesMimic,
		Rigid,
		NUMBER_OF_VALUES,
		FIRST_VALUE = Particles
	};
}

class BallPhysics
{
public:
	BallPhysics(void);
	~BallPhysics(void);

	inline void ApplyFriction(Vector3f &velocity, float friction, float deltaTime){
		Vector3f frictionalImpulse = _velocity*-1;
		frictionalImpulse=frictionalImpulse*friction*deltaTime;
		_velocity=_velocity+frictionalImpulse;
	};
	void Create(const Vector3f &position, float _radius);
	bool BallBallCollision(BallPhysics &rhs, float deltaTime);
	void BallWallCollision(const Vector3f &wallPosition, float wallRadius, float deltaTime, float wallElasticity);
	BallPhysics* CloneToAnEmptyObject(void)const;
	inline float GetOrientationAngle(void)const{return _orientationAngle;};
	inline const Vector3f &GetOrientationVector(void)const{return _orientationVector;};
	inline void SetAngularVelocity(const Vector3f &v){_angularVelocity=v;};
	inline float GetElasticity(void)const{return _elasticity;};
	inline void SetElasticity(float elasticity){_elasticity=elasticity;};
	inline float GetMass(void)const{return _mass;};
	inline void SetMass(float mass){_mass=mass;};
	inline const Vector3f &GetForce(void)const{return _distance;};
	inline void SetForce(const Vector3f &force){_distance=force;};
	inline const Vector3f &GetOldPosition(void)const{return _oldPosition;};
	inline float GetRadius(void)const{return _radius;};
	inline int GetRealismLevel(void)const{return _pbm;};
	inline void SetRealismLevel(int level){
		if(level>=Physics::FIRST_VALUE&&level<=Physics::NUMBER_OF_VALUES)
			_pbm=(Physics::PBM(level));
	};//0-Particle,1-ParticleMimic,2-RigidBodies
	inline const Vector3f &GetVelocity(void)const{return _velocity;};
	inline const Vector3f &GetOldVelocity(void)const{return _oldVelocity;};
	void GravityWellBallCollision(const Vector3f &position, float radius, int status, float externalForce);//status, 0=repel, 1=attract
	inline const Vector3f& GetPosition(void)const{return _position;};
	inline void SetPosition(const Vector3f &position){_position=position;};
	inline void SetVelocity(const Vector3f &velocity){_velocity=velocity;};
	inline bool GetMoving(void)const{return _moving;};
	inline void SetMoving(bool status){_moving=status;};
	inline int GetCurrentMovementState(void)const{return _currentMovementState;};
	inline void SetCurrentMovementState(int state){_currentMovementState=state;};
	void Update(float deltaTime, float floorFriction);

private:
	Vector3f _position, _oldPosition;
	float _radius;
	float _gravity;
	Vector3f _velocity, _oldVelocity;
	float _mass;
	float _elasticity;
	float _acceleration;
	Vector3f _force;
	bool _moving;
	Vector3f _distance;
	int _currentMovementState;
	Physics::PBM _pbm;
	float _slideCoeff;
	float _rollingCoeff;
	float _staticFriction;

	Vector3f _accelerationVec;
	Vector3f _angularAcceleration;
	Vector3f _angularPosition;
	Vector3f _angularVelocity;
	Vector3f _frictionForce;
	Quaternion _orientation;
	float _orientationAngle;
	Vector3f _orientationVector;
	Vector3f _perimiterVelocity;
	Vector3f _sphereContactPoint;
	Quaternion _spin;
};
