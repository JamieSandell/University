#include "Ball.h"
#include <math.h>
#include "MaterialsManager.h"

#define GRAVITY -9.8f


Ball::Ball()
{
	_mutex=CreateMutex(NULL,FALSE,"myMutex");
}

Ball::~Ball()
{
	CloseHandle(_mutex);
	_mutex = NULL;
}

void Ball::Create(int ballId, int materialId, const Vector3f &pos)
{
	_ballId = ballId;
	_materialId = materialId;
	_position = pos;
	_velocity.Assign(0.0f,0.0f,0.0f);
	_angularVelocity.Assign(0.0f,0.0f,0.0f);
	_state = NONOWNED;
	_mass = 1.0f;	
	_moveState = STATIONARY;	
	_radius = 0.4f;
	_sphereContactVector.Assign(0.0f, -_radius, 0.0f);

	_stationaryFrictionCoefficient = 0.05f;
	_slidingFrictionCoefficient = 0.2f;
	_rollingFrictionCoefficient = 0.03f;

	_rotation.identity();

	rotMat[0] = rotMat[5] = rotMat[10] = 1.0f;
	rotMat[1]=rotMat[2]=rotMat[3]=rotMat[4]=rotMat[6]=rotMat[7]=rotMat[8]=rotMat[9]=rotMat[11]=
	rotMat[12]=rotMat[13]=rotMat[14]=rotMat[15]=0;
}

void Ball::UpdatePosition(float dt)
{
	if (_moveState != STATIONARY)
	{
		_position = _position.add(_velocity.scaleBy(dt));
		//_rotation = _rotation.add(_angularVelocity.scaleBy(dt));

		//spin = 0.5 * Quaternion(0, angularVelocity.x, angularVelocity.y, angularVelocity.z) * orientation;
		//state.orientation += derivative.spin * dt;

		_rotation.normalize();

		Quaternion spin(_angularVelocity.getX(), _angularVelocity.getY(), _angularVelocity.getZ(), 0.0f);
		spin = spin.multiply(_rotation);
		spin = spin.scaleBy(0.5f);

		_rotation = _rotation.add(spin.scaleBy(dt));
	}
}
 

void Ball::UpdateVelocity(float dt, Vector3f &force)
{
	if (_moveState == STATIONARY)
	{		
		if (force.getMagnitude() > -_stationaryFrictionCoefficient*_mass*GRAVITY)
			_moveState = SLIDING;
	}
	if (_moveState == SLIDING)
	{		
		//Vector3f sphereContactVector(0.0f, 0.0f, -_radius); 
		Vector3f pVelocity = _angularVelocity.crossProduct(_sphereContactVector).add(_velocity);
		
		
		Vector3f frictionForce = pVelocity.normalize();
		frictionForce = frictionForce.scaleBy(_slidingFrictionCoefficient*_mass*GRAVITY);		

		Vector3f vAcceleration = frictionForce.add(force).scaleBy(1.0f/_mass);
		Vector3f wAcceleration = _sphereContactVector.crossProduct(frictionForce).scaleBy(5.0f/(2.0f*_mass*_radius*_radius));

		_angularVelocity = _angularVelocity.add(wAcceleration.scaleBy(dt));
		_velocity = _velocity.add(vAcceleration.scaleBy(dt));

		Vector3f newPVelocity = _angularVelocity.crossProduct(_sphereContactVector).add(_velocity);

		float vpPar = pVelocity.dotProduct(pVelocity.subtract(newPVelocity));
		float vpPar2 = newPVelocity.dotProduct(newPVelocity.subtract(pVelocity));

		if((vpPar > 0.0 && vpPar2 < 0.0) || (vpPar2 > 0.0 && vpPar < 0.0))
		{			
			//_velocity = _angularVelocity.crossProduct(_sphereContactVector.negative());
			_angularVelocity = _velocity.crossProduct(_sphereContactVector).scaleBy(5.0f);

			//Vector3f veloc2 = _angularVelocity.crossProduct(_sphereContactVector.negative());
			_moveState = ROLLING;
		}		
	}
	else if (_moveState == ROLLING)
	{		
		Vector3f pVelocity = _sphereContactVector.crossProduct(_angularVelocity);
		Vector3f frictionForce = pVelocity.normalize().scaleBy(-_rollingFrictionCoefficient*_mass*GRAVITY);
		Vector3f angularAcceleration = _sphereContactVector.crossProduct(frictionForce.subtract(force)).scaleBy(5.0f/(2.0f*_mass*_radius*_radius));

		_angularVelocity = _angularVelocity.add(angularAcceleration.scaleBy(dt));
		_velocity = _angularVelocity.crossProduct(Vector3f(0.0f, _radius, 0.0f));

		if (_angularVelocity.getMagnitude() < 0.01f && _velocity.getMagnitude() < 0.01f && force.getMagnitude() < -_stationaryFrictionCoefficient*_mass*GRAVITY)
		{
			_velocity.Assign(0.0f,0.0f,0.0f);
			_angularVelocity.Assign(0.0f,0.0f,0.0f);
			_moveState = STATIONARY;
		}
	}
	/*if (_velocity.getMagnitude() <= 0.05f && force.getMagnitude() < _maxFrictionForce)
	{
		_velocity.Assign(0.0f,0.0f,0.0f);
		_moveState = STATIONARY;
		return;
	}
	_velocity = _velocity.add(force.scaleBy(dt*_mass));
	_velocity = _velocity.add(_velocity.scaleBy(_friction*_mass*GRAVITY*dt));*/
}

Vector3f Ball::CheckProximity(Ball &ball)
{
	float positionDifference = (_position.subtract(ball.GetPosition())).getMagnitude();
	if(positionDifference < _radius*2.0f + 0.05f)
	{
		Vector3f distanceNormal = _position.subtract(ball.GetPosition()).normalize();
		return distanceNormal.scaleBy(50.0f*((_radius*2+0.05f)-positionDifference));
	}	
	return Vector3f(0.0f, 0.0f, 0.0f);	
}

float Ball::CheckCollision(Ball &ball)
{
	float collisionTime = 1000.0f;
	Vector3f velocityDifference = _velocity.subtract(ball.GetVelocity());
	Vector3f positionDifference = _position.subtract(ball.GetPosition());

	if (positionDifference.getMagnitude() > 1.6f)
		return collisionTime;

	float a = velocityDifference.dotProduct(velocityDifference);
	float b = 2*(positionDifference.dotProduct(velocityDifference));
	float c = positionDifference.dotProduct(positionDifference) - (4 * 0.4f * 0.4f);
	float s = b*b-4*a*c;	

	if (b*b > c)
	{
		s = (s > 0.0f ? sqrt(s) : 0.0f);
		float t1 = (-b+s) / (2*a);
		float t2 = (-b-s) / (2*a);
		collisionTime = (t1 < t2 ? t1 : t2);		
		if (collisionTime <= 0.0f)
			collisionTime = 1000.0f;
	}	
	return collisionTime;
}

void Ball::DoCollision(Ball &ball)
{
	Vector3f collisionNormal = _position.subtract(ball.GetPosition()).normalize();

	Vector3f an = collisionNormal.negative().scaleBy(_velocity.dotProduct(collisionNormal.negative()));
	Vector3f at = _velocity.subtract(an);

	Vector3f bn = collisionNormal.scaleBy(ball.GetVelocity().dotProduct(collisionNormal));
	Vector3f bt = ball.GetVelocity().subtract(bn);

	_velocity = at.add(bn);
	Vector3f Veloc2 = bt.add(an);
	ball.SetVelocity(bt.add(an));

	


	//float a1 = _velocity.dotProduct(collisionNormal);
	//float a2 = ball.GetVelocity().dotProduct(collisionNormal);
	//double p = 2 * ((a1 - a2) / 2.0f); // calculate impulse

	//_velocity = _velocity.subtract(collisionNormal.scaleBy(p));
	//ball.SetVelocity(ball.GetVelocity().add((collisionNormal.scaleBy(p))));
	_moveState = SLIDING;
	ball.SetMoveState(SLIDING);
	_angularVelocity.Assign(0.0f,0.0f,0.0f);
	ball.SetWVelocity(Vector3f(0.0f,0.0f,0.0f));	
}
