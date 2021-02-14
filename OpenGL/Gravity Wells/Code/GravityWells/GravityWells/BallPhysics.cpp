#include "BallPhysics.h"
#define EPSILON 1.0e-5
#define PI  (float)3.1415926
#define STATIONARY 0
#define SLIDING 1
#define ROLLING 2
#define SLIDINGCOEFF 0.2f
#define ROLLCOEFF 0.03f

using namespace Physics;

BallPhysics::BallPhysics(void)
{
}

BallPhysics::~BallPhysics(void)
{
}
bool BallPhysics::BallBallCollision(BallPhysics &rhs, float deltaTime){
	Vector3f rhsPosition = rhs.GetPosition();
	Vector3f rhsVelocity = rhs.GetVelocity();
	float rhsRadius = rhs.GetRadius();
	Vector3f moveVector = _velocity - rhsVelocity; //get the relative velocity

	/////////Begin Escape Clauses
	// If the length of the move vector is less than the distance between the centres
	// of the spheres there is no way they can collide
	float distanceVector = rhsPosition.VectorDistance(_oldPosition); //Get the distance
	// between the two vectors before they was moved
	float sumOfRadii = _radius+rhsRadius;
	distanceVector-=sumOfRadii;
	if (moveVector.CalculateMagnitude() <  distanceVector)
		return false;
	//Normalise the moveVector
	Vector3f n = moveVector.Normalise();

	//Find C, the vector from the centre of the moving vector (sphere1)
	// to the centre of the second sphere (sphere2)
	Vector3f c = rhsPosition - _position;

	// D = N.C=||C||*cos(angle between N and C)
	float d = n.DotProduct(c);

	//Make sure that the first sphere is actually moving towards the second sphere
	// if it isn't then they won't collide
	if (d <= 0.0f)
		return false;

	//Make sure that they can actually hit eachother
	// if the closest that Sphere1 can get to Sphere2 is more than the sum of their collective
	// radii then they cannot hit
	float lengthOfC = c.CalculateMagnitude();
	float f = (lengthOfC*lengthOfC)-(d*d);
	float sumOfRadiiSquared = sumOfRadii*sumOfRadii;
	if (f >= sumOfRadiiSquared)
		return false;

	//f and sumOfRadiiSquared are two sides of a right triangle
	// can use these to find the missing side, if t is less than 0 return false and avoid square rooting
	// a negative number
	float t = sumOfRadiiSquared - f;
	if (t < 0.0f)
		return false;

	// The distance that Sphere1 has to travel along the moveVector is d - sqrt(t)
	// If the length of the moveVector is less than the distance to travel then a collision is not possible
	float distance  = d - sqrt(t);
	float lengthOfMoveVector = moveVector.CalculateMagnitude();
	if (lengthOfMoveVector < distance)
		return false;
	/////////End Escape Clauses
	//If at this point the two spheres will collide
	rhsPosition = rhs.GetPosition();
	float distance2 = (rhsPosition.x()-_position.x())*(rhsPosition.x()-_position.x()) +
		(rhsPosition.z()-_position.z())*(rhsPosition.z()-_position.z());
	// Sqrt too expensive so avoid it
	Vector3f delta = (_position - rhs.GetPosition());
	float r = _radius + rhsRadius;
	float dist2 = delta.DotProduct(delta);

	if(r*r>distance2){
		//Separation Vector
		rhsPosition = rhs.GetPosition();
		Vector3f d(rhsPosition - _position);
		//Distance between circle centres, squared
		float distanceSquared = d.DotProduct(d);
		//Combined radii squared
		float radius = rhsRadius + _radius;
		float radiusSquared = radius*radius;
		// distance between circle centres
		float dist = sqrtf(distanceSquared);
		// normal of collision
		Vector3f ncoll = (d / dist);
		// penetration distance
		float dcoll = (radius - dist);
		float rhsMass = rhs.GetMass();
		// inverse masses (0 means, infinite mass, object is static).
		float ima = (_mass > 0.0f)? 1.0f / _mass : 0.0f;
		float imb = (rhsMass > 0.0f)? 1.0f / rhsMass : 0.0f;
		// separation vector
		Vector3f separationVector = ncoll * (dcoll / (ima + imb));
		// separate the circles
		_position -= separationVector * ima;
		rhs.SetPosition(rhsPosition+separationVector* imb);
		// combines velocity
		Vector3f vcoll = (rhsVelocity - _velocity);
		// impact speed 
		float vn = vcoll.DotProduct(ncoll);
		// objects are moving away. Don't reflect velocity
		if(vn > 0.0f) 
			return true; // we did collide
		// collision impulse
		float j = -((1.0f + _elasticity) * vn) / (ima + imb);
		// collision impulse vector
		Vector3f impulse = j * ncoll;
		// change momentum of the circles
		_velocity=_velocity - impulse * ima;
		rhs.SetVelocity(rhsVelocity+impulse * imb);

		Vector3f velocityOpposite = _velocity*-1;
		velocityOpposite=velocityOpposite*_gravity;
		if (fabsf(_distance.CalculateMagnitude()) < EPSILON ){
			_distance = velocityOpposite; //outside the gravity well
		}
		velocityOpposite = rhsVelocity*-1;
		velocityOpposite=velocityOpposite*_gravity;
		if (fabsf(rhs.GetForce().CalculateMagnitude()) < EPSILON ){
			rhs.SetForce(velocityOpposite); //outside the gravity well
		}

		_currentMovementState = SLIDING;
		rhs.SetCurrentMovementState(SLIDING);
		_angularVelocity.Assign(0.0f,0.0f,0.0f);
		rhs.SetAngularVelocity(_angularVelocity);
		return true;
	}
	return false;
}

void BallPhysics::BallWallCollision(const Vector3f &wallPosition, float wallRadius, float deltaTime, float wallElasticity){
	//float a((GetPosition().Subtract(_oldPosition)).DotProduct(GetPosition().Subtract(_oldPosition)));
	//float b(2*((GetPosition().Subtract(_oldPosition)).DotProduct(_oldPosition.Subtract(Vector3f(0.0f,0.0f,0.0f)))));
	//float c((_oldPosition.Subtract(Vector3f(0.0f,0.0f,0.0f))).DotProduct(_oldPosition.Subtract(Vector3f(0.0f,0.0f,0.0f)))- ((100.0f-ballRadius)* (100.0f-ballRadius)));
	if (_position.CalculateMagnitude() >= wallRadius - _radius) //Only do the check if the ball is near the wall
	{
		//Make sure the ball has some velocity
		if (fabsf(_velocity.CalculateMagnitude())>0.01f)
		{
			float a = _position.Subtract(_oldPosition).DotProduct(_position.Subtract(_oldPosition));
			float b = 2 * ((_position.Subtract(_oldPosition)).DotProduct(_oldPosition.Subtract(wallPosition)));
			float c = (_oldPosition.Subtract(wallPosition)).DotProduct(_oldPosition.Subtract(wallPosition))
				- ((wallRadius-_radius)*(wallRadius-_radius));
			float s = (b*b-4.0f*a*c);
			s = (s>0.0f ? sqrtf(s) : 0.0f);

			float u1 = (-b+s)/(2.0f*a);
			float u2 = (-b-s)/(2.0f*a);

			float collisionT = 0.0f;
			if (u2>0.0f)
				collisionT = (u2 < u1 ? u2:u1);
			else if(u1>0.0f)
				collisionT = (u1 < u2 ? u1:u2);

			if ((0.0f <= collisionT) && (collisionT <= 1.0f))
			{
				// Return the position to the point of contact
				// Update the oldvelocity to the velocity at the contact point
				_position = _oldPosition.Add(_position.Subtract(_oldPosition).Scale(collisionT));
				_oldVelocity = _oldVelocity.Add(_velocity.Subtract(_oldVelocity).Scale(collisionT));
				Vector3f wallNormal = _position.Normalise().Scale(-1.0f);

				_velocity = _oldVelocity - (1.0f+wallElasticity)*(_oldVelocity.DotProduct(wallNormal))*wallNormal;
				float timeLeft = deltaTime-collisionT;
				Vector3f distance = _velocity.Scale(timeLeft);
				_oldPosition = _position;
				_position = _position.Add(distance);
				_position.AssignY(_oldPosition.y());

				_currentMovementState = SLIDING;
				_angularVelocity.Assign(0.0f,0.0f,0.0f);
			}
		}
	}
}

BallPhysics* BallPhysics::CloneToAnEmptyObject()const{
	BallPhysics *p = new BallPhysics;
	p->Create(Vector3f (1.0f,1.0f,1.0f), 1.0f);
	*p = *this;
	return p;
}
void BallPhysics::Create(const Vector3f &position, float radius){
	_position = _oldPosition = position;
	_radius = radius;
	_gravity = 6.7f;
	_mass = 2.0f;
	_velocity.AssignX(0.0f);
	_velocity.AssignY(0.0f);
	_velocity.AssignZ(0.0f);
	_oldVelocity = _velocity;
	_moving = false;
	_elasticity = 0.95f; //coefficient of restitution
	_slideCoeff = 0.2f;
	_rollingCoeff = 0.03f;
	_staticFriction = 0.05f;

	_currentMovementState = STATIONARY;
	_orientation.Identity();
	_pbm = ParticlesMimic;
}

void BallPhysics::GravityWellBallCollision(const Vector3f &position, float radius, int status, float externalForce){
	float pos1X = _position.x();
	float pos1Z = _position.z();
	float pos2X = position.x();
	float pos2Z = position.z();
	_distance.Assign(_position.Subtract(position));

	float distance = (pos2X-pos1X)*(pos2X-pos1X) + (pos2Z-pos1Z)*(pos2Z-pos1Z);
	// Sqrt too expensive so avoid it
	if ( (_radius + radius)*(_radius + radius) >= distance)
	{
		_moving = true; //Collision occurred
		if (fabs(_velocity.CalculateMagnitude()) < EPSILON )
			_currentMovementState = SLIDING;
		float distance2 = _distance.CalculateMagnitude();
		if (distance2 < 5.0f)
			distance2 = 5.0f;
		_distance = _distance.Normalise();
		_distance = _distance * ((_gravity*externalForce)/(distance2*distance2));
	}
	else{
		_distance.Assign(0.0f,0.0f,0.0f); //outside the gravity well so set the gravity well force
		//acting on the ball to zero
	}
}


void BallPhysics::Update(float deltaTime, float floorFriction){
	if (_pbm==Particles){
		Vector3f acceleration = _distance/_mass; //a=f/m
		_oldVelocity = _velocity;
		_velocity=_velocity+(acceleration*deltaTime);
		_velocity.AssignY(0.0f);
		//apply friction
		ApplyFriction(_velocity, floorFriction, deltaTime);
		Vector3f distance = _velocity*deltaTime;
		float y = _position.y();
		_oldPosition = _position;
		_position=_position+distance;
		_position.AssignY(y);

		//Quaternion code
		_orientation.Add(_spin.Multiply(deltaTime));
		_orientation.Normalize();
		_spin =Quaternion(0, _angularVelocity.x(), _angularVelocity.y(),
			_angularVelocity.z()).Multiply(_orientation).Multiply(0.5f);
		//_orientation.Add(_spin);
		float angle;
		Vector3f axis;		
		_orientation.AngleAxis(angle, axis);
		_orientationAngle = _orientation.GetAngle();
		_orientationVector = _orientation.GetVector();

		if (fabs(distance.CalculateMagnitude())<0.01f)//Check against a small number near zero, as getting
			// to zero can take a long time
			_currentMovementState = STATIONARY;
		}
	else if(_pbm==ParticlesMimic)
	{
		if (_currentMovementState!=STATIONARY){ //We are now rolling
			//Update position
			_oldPosition = _position;
			ApplyFriction(_velocity, floorFriction, deltaTime);
			_position = _position+(_velocity*deltaTime);
			_position.AssignY(_oldPosition.y());

			//_angularPosition = _angularPosition + (_angularVelocity * deltaTime);

			//Quaternion code
			//_orientation.Add(_spin.multiply(deltaTime));
			_orientation.Normalize();
			_spin =Quaternion(0.0f, _angularVelocity.x(), _angularVelocity.y(),
				_angularVelocity.z()).Multiply(_orientation).Multiply(0.5f);
			_orientation.Add(_spin.Multiply(deltaTime));
			float angle;
			Vector3f axis;		
			_orientation.AngleAxis(angle, axis);
			_orientationAngle = _orientation.GetAngle();
			_orientationVector = _orientation.GetVector();

			_sphereContactPoint.Assign(0.0f, -_radius, 0.0f);
			Vector3f oppositeSideContactPoint(0.0f, _radius, 0.0f);

			_perimiterVelocity = Vector3f::CrossProduct(_sphereContactPoint, _angularVelocity);
			_frictionForce = Vector3f::Scale(_rollingCoeff*_mass, Vector3f::Unit(_perimiterVelocity));//Add negative sign?

			_angularAcceleration = Vector3f::Scale(5.0f/(2.0f*_mass*_radius*_radius),
				Vector3f::CrossProduct(_sphereContactPoint,(_frictionForce.Subtract(_distance))));
			_angularVelocity = Vector3f::Add(_angularVelocity,Vector3f::Scale(deltaTime,_angularAcceleration));
			_velocity = Vector3f::CrossProduct(_angularVelocity,oppositeSideContactPoint);

			if((_angularVelocity.CalculateMagnitude() < 0.5f )&&(_velocity.CalculateMagnitude() < 0.05f) && ( _distance.CalculateMagnitude() < (_staticFriction *_mass)))
			{
				_velocity.Assign(0.0f,0.0f,0.0f);
				_angularVelocity.Assign(0.0f,0.0f,0.0f);
				//_currentMovementState = STATIONARY;
			}
		}
	}
	else if(_pbm==Rigid){
		if (_currentMovementState!=STATIONARY)
		{
			//Update position
			_oldPosition = _position;
			ApplyFriction(_velocity, floorFriction, deltaTime);
			_position = _position+(_velocity*deltaTime);
			_position.AssignY(_oldPosition.y());

			//_angularPosition = _angularPosition + (_angularVelocity * deltaTime);

			//Quaternion code
			//_orientation.Add(_spin.multiply(deltaTime));
			_orientation.Normalize();
			_spin =Quaternion(0.0f, _angularVelocity.x(), _angularVelocity.y(),
				_angularVelocity.z()).Multiply(_orientation).Multiply(0.5f);
			_orientation.Add(_spin.Multiply(deltaTime));
			float angle;
			Vector3f axis;		
			_orientation.AngleAxis(angle, axis);
			_orientationAngle = _orientation.GetAngle();
			_orientationVector = _orientation.GetVector();

			if (_currentMovementState == SLIDING)
			{
				//Physics
				_sphereContactPoint.Assign(0.0f, -_radius, 0.0f);
				Vector3f oppositeSideContactPoint(0.0f, _radius, 0.0f);
				//Perimeter velocity of the ball at contact point with the floor
				_perimiterVelocity = Vector3f::Add(_velocity, Vector3f::CrossProduct(_sphereContactPoint,_angularVelocity));

				_frictionForce = Vector3f::Scale(-_slideCoeff*_mass,Vector3f::Unit(_perimiterVelocity)); //Remove negative?
				Vector3f ballAcc = _frictionForce;
				ballAcc = ballAcc.Add(_distance);
				_accelerationVec = Vector3f::Scale(1.0f/_mass,ballAcc);
				_angularAcceleration = Vector3f::Scale(5.0f/(2.0f*_mass*_radius*_radius), 
					Vector3f::CrossProduct(_sphereContactPoint,_frictionForce));

				_velocity = Vector3f::Add(_velocity, Vector3f::Scale(deltaTime,_accelerationVec));
				_angularVelocity = Vector3f::Add(_angularVelocity, Vector3f::Scale(deltaTime, _angularAcceleration));

				Vector3f newPerimiterVelocity = Vector3f::Add(_velocity, 
					Vector3f::CrossProduct(_angularVelocity,_sphereContactPoint));
				float vpPar = Vector3f::DotProduct(_perimiterVelocity, 
					Vector3f::Difference(_perimiterVelocity, newPerimiterVelocity));
				float vpPar2 = Vector3f::DotProduct(newPerimiterVelocity, 
					Vector3f::Difference(_perimiterVelocity, newPerimiterVelocity));

				if ((vpPar > 0.0f && vpPar2 < 0.0f) || (vpPar2 > 0.0f && vpPar < 0.0f)) 
				{
					_velocity = Vector3f::CrossProduct(_angularVelocity, oppositeSideContactPoint);
					_currentMovementState = ROLLING;
				}
			}
			else if(_currentMovementState==ROLLING){ //We are now rolling
				_sphereContactPoint.Assign(0.0f, -_radius, 0.0f);
				Vector3f oppositeSideContactPoint(0.0f, _radius, 0.0f);

				_perimiterVelocity = Vector3f::CrossProduct(_sphereContactPoint, _angularVelocity);
				_frictionForce = Vector3f::Scale(_rollingCoeff*_mass, Vector3f::Unit(_perimiterVelocity));//Add negative sign?

				_angularAcceleration = Vector3f::Scale(5.0f/(2.0f*_mass*_radius*_radius),
					Vector3f::CrossProduct(_sphereContactPoint,(_frictionForce.Subtract(_distance))));
				_angularVelocity = Vector3f::Add(_angularVelocity,Vector3f::Scale(deltaTime,_angularAcceleration));
				_velocity = Vector3f::CrossProduct(_angularVelocity,oppositeSideContactPoint);

				if((_angularVelocity.CalculateMagnitude() < 0.5f )&&(_velocity.CalculateMagnitude() < 0.05f) && ( _distance.CalculateMagnitude() < (_staticFriction *_mass)))
				{
					_velocity.Assign(0.0f,0.0f,0.0f);
					_angularVelocity.Assign(0.0f,0.0f,0.0f);
					//_currentMovementState = STATIONARY;
				}
			}
		}
	}
}