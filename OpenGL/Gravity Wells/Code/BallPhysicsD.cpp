#include "BallPhysics.h"

BallPhysics::BallPhysics(void)
{
}

BallPhysics::~BallPhysics(void)
{
}

void BallPhysics::UpdateVelocity(BallObject &ballObjA, const Vector3f &wellForce, const float time)
{
	ballObjA.SetOldPos(ballObjA.GetPosition());

	float dt = time;
	float ballRadius = 0.5;
	float slideCoeff = 0.5;
	float rollingCoeff = 0.1;
	float staticFrication = 0.001;
	Vector3f temp(wellForce);

	if((ballObjA.GetMovingState() == STATIONARY) && (wellForce.Length() > (staticFrication *ballObjA.GetMass() * 3.8f))) // && inGame{ 
	{
		ballObjA.SetMovingState(SLIDING);
	}

	if (ballObjA.GetMovingState() != STATIONARY)
	{
		
		if (ballObjA.GetMovingState() == ROLLING)
		{
			Vector3f sphereContactPoint(0.0f, -ballRadius, 0.0f);
			Vector3f sphereContactPointOp(0.0f, ballRadius, 0.0f);
			Vector3f primativeVelocity(sphereContactPoint.CrossProduct(ballObjA.GetAngularVel()));
			Vector3f frictionForce(( primativeVelocity.Normalise().Subtract(temp)).Scale( 3.8f*ballObjA.GetMass()*rollingCoeff));
				//Vector3f ballAcc = frictionForce.Add(temp);
				//Vector3f angularAcc((sphereContactPoint.Scale(frictionForce)).Scale((2.0f * GetMass() * ballRadius * ballRadius)*(1.0f / 5.0f)));
			Vector3f angularAcc(sphereContactPoint.CrossProduct(frictionForce).Scale(5.0f/((2.0f * ballObjA.GetMass() * ballRadius * ballRadius))));//*(1.0f / 5.0f)));
				
			ballObjA.SetAngularVel(ballObjA.GetAngularVel().Add(angularAcc.Scale(dt)));
			ballObjA.SetVelocity(ballObjA.GetAngularVel().CrossProduct(sphereContactPointOp));
				
			if((ballObjA.GetAngularVel().Length() > 0.5 )&&(ballObjA.GetVelocity().Length() > 0.05) && ( temp.Length() < (staticFrication *ballObjA.GetMass() *  3.8f)) )
			{
				ballObjA.SetVelocity(0.0f,0.0f,0.0f);
				ballObjA.SetAngularVel(0.0f,0.0f,0.0f);
				ballObjA.SetMovingState(STATIONARY);
			}
		}
		else if(ballObjA.GetMovingState() == SLIDING)
		{
			Vector3f sphereContactPoint(0.0f,-ballRadius,0.0f);
			//Vector3f primativeVelocity(GetAngularVel().Scale(sphereContactPoint).Add(GetVelocity()));
			Vector3f primativeVelocity ((ballObjA.GetAngularVel().CrossProduct(sphereContactPoint)).Add(ballObjA.GetVelocity()));
			Vector3f frictionForce( primativeVelocity.Normalise().Scale( 3.8f*ballObjA.GetMass()*-slideCoeff));
			Vector3f ballAcc = frictionForce.Add(temp);

			Vector3f acceleration(ballAcc.Scale(1.0f / ballObjA.GetMass()));
			//Vector3f angAcc((sphereContactPoint.Scale(frictionForce)).Scale( (2.0f * GetMass() * ballRadius * ballRadius)*(1.0f/5.0f) ));
			Vector3f angAcc((sphereContactPoint.CrossProduct(frictionForce)).Scale( 5.0f/((2.0f * ballObjA.GetMass() * ballRadius * ballRadius))));//*(1.0f/5.0f) ));
			
			ballObjA.SetVelocity(ballObjA.GetVelocity().Add(acceleration.Scale(dt)));
		
			ballObjA.SetAngularVel ( ballObjA.GetAngularVel().Add( angAcc.Scale(dt)));
			Vector3f newPerimeterVelocity(ballObjA.GetAngularVel().CrossProduct( sphereContactPoint).Add(ballObjA.GetVelocity()));

			float vpPar = primativeVelocity.DotProduct(primativeVelocity.Subtract( newPerimeterVelocity));
			float vpPar2 = newPerimeterVelocity.DotProduct(primativeVelocity.Subtract( newPerimeterVelocity));

			if((vpPar > 0.00f && vpPar2 < 0.00f) ||(vpPar2 > 0.00f && vpPar < 0.00f))
			{
				ballObjA.SetVelocity( ballObjA.GetAngularVel().CrossProduct(sphereContactPoint));
				//SetAngularVel(GetVelocity().CrossProduct(sphereContactPoint).Scale(5.0));
				ballObjA.SetMovingState(ROLLING);
			}
		}
	}
}

void BallPhysics::UpdatePosition(BallObject &ballObjA, const float dt)
{
	Vector3f distance = ballObjA.GetVelocity().Scale(dt);	
	ballObjA.SetPosition(ballObjA.GetPosition().Add( distance));

	ballObjA.NormaliseOrientation();     
	Quaternion spin(0.0f, ballObjA.GetAngularVel().xyz()[0], ballObjA.GetAngularVel().xyz()[1], ballObjA.GetAngularVel().xyz()[2]);
	spin = spin.Multiply(ballObjA.GetOrientation());
	spin = spin.multiply(0.5f);	
	ballObjA.SetOrientation(ballObjA.GetOrientation().Add5(spin.multiply(dt)));
}

