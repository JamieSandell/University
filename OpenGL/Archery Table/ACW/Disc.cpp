#include "Disc.h"

Disc::Disc()
{
	_radius = 20; // 20mm radius
	_height = 10;
	_weight = 0.02; // 0.02kg
	_justFired = false;
	_movedToStart = false;
	xPos = 0;
	yPos = 0;
	_distanceMovedX = 0;
	_distanceMovedY = 0;
	_vFX = 0.0;
	_vFY = 0.0;

	quadric=gluNewQuadric();			// Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(quadric, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
	gluQuadricTexture(quadric, GL_TRUE);		// Create Texture Coords ( NEW )
}

Disc::~Disc(void)
{
}

// Draw the disc
void Disc::DrawDisc(Texture texture[3]) const
{
	// translate the disc to it's co-ords
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[1].texID);
		glTranslated(_centre.X(), _centre.Y(), _centre.Z());
		GLfloat discColour[] = { _centre.X(), _centre.Y(), _centre.Z(), 1.0f };
		GLfloat discSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Shiny smooth table
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, discColour);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, discSpecular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);
		glColor3f(_colour.X(), _colour.Y(), _colour.Z());
		glNormal3f( 0.0f, 1.0f, 0.0f);					// Normal Pointing Up
		gluCylinder(quadric, _radius, _radius, _height ,32, 32);
		gluDisk(quadric, 0, _radius, 32, 32);
	glPopMatrix();
}

// Set the disc colour
void Disc::SetColour(const double colour[])
{
	_colour.SetVector(colour[0], colour[1], colour[2]);
}

// Set the position of the disc
void Disc::SetPosition(const int position[])
{
	_centre.SetVector(position[0], position[1], position[2]);
	_originalPosition.SetVector(position[0], position[1], position[2]);
}

// Get the radius of the disc
int Disc::GetRadius() const
{
	return _radius;
}

// Get disc position
Vector3d Disc::GetDiscPosition() const
{
	return _centre;
}

// Move the disc to a new position
void Disc::MoveDisc(const int &xPos, const int &yPos)
{
	_centre.SetVector(xPos, yPos, 0);
}

// Get the disc's fired status
bool Disc::GetFiredStatus() const
{
	return _fired;
}
// Update the disc's position
void Disc::Update(const float &dt, const double &angle, const int &force, const double &surfaceFriction,
				  const double &sideFriction)
{
	// If the disc has only just been fired then set it's initial path
	if(_justFired)
	{
		double firingAngle = (angle * 3.141) / 180;
		double newForce = force; // *5
		_velocity.SetVector(newForce*(sin(firingAngle*-1)), newForce*(cos(firingAngle*-1)), 0);
		_justFired = false; // So we don't enter here again and reset values
	}
	if (_velocity.Y() != 0) // still moving
	{
		double oldXPos = _centre.X(); // For distance traveled calculations
		double oldYPos = _centre.Y();
		xPos = _centre.X() + (_velocity.X()); // Replace 1 with dt
		yPos = _centre.Y() + (_velocity.Y());
		_distanceMovedY = (yPos - oldYPos);
		_distanceMovedX = (xPos - oldXPos);

		double friction = surfaceFriction * _weight * 9.81; //		F = kN
		_vFY = friction * _distanceMovedY;
		_vFX = friction * _distanceMovedX;

		if (oldYPos > yPos) // disc is coming back down
		{
			_distanceMovedY = abs(yPos - oldYPos);
			_velocity.SetVectorY(_velocity.Y()-_vFY);
		}
		else // moving up
		{
			_distanceMovedY = yPos - oldYPos;
			_velocity.SetVectorY(_velocity.Y()-_vFY);
		}
		if (oldXPos != xPos) // has moved left or right
		{
			if (oldXPos > xPos) // disc is moving to the left
			{
				_distanceMovedX = (xPos - oldXPos);
				_velocity.SetVectorX(_velocity.X()-_vFX);
			}
			else // Moving to the right
			{
				_distanceMovedX = abs(xPos - oldXPos); // abs because it's traveling in a negative
				//direction
				_velocity.SetVectorX(_velocity.X()-_vFX);
			}
		}

		// dt is calculated earlier
		_centre.SetVector(_centre.X() + (_velocity.X()), _centre.Y() + (_velocity.Y()) ,0);

		// Only use noticeable movement amounts, otherwise more cpu intensive.
		// TODO://
		// Optimize these values
		if (((_distanceMovedY < 0.01) && (_velocity.Y() > 0)) || ((_distanceMovedY < -0.01) && (_velocity.Y() > 0)))
		{
			_velocity.SetVectorY(0.0);
			//_fired = false;
			if(((_distanceMovedX < 0.01) && (_velocity.X() > 0)) || ((_distanceMovedX < 0.01) && (_velocity.X() > 0)))
			{
				// both velocities are 0 so _fired should be set to false
				_velocity.SetVectorX(0.0);
			}
		}
		if (oldXPos != xPos) // Obviously hasn't moved on the x-axis so don't check the distanceMoved
		{
			if (((_distanceMovedX < 0.01) && (_velocity.X() > 0)) || ((_distanceMovedX < 0.01) && (_velocity.X() > 0)))
			{
				_velocity.SetVectorX(0.0); // If x is moving and becomes 0 then so should the y
				_velocity.SetVectorY(0.0);
				//_fired = false;
			}
		}
		if (_centre.Y() < 149) // Beneath the starting line
		{
			ResetDiscPosition();
			_velocity.SetVectorX(0.0);
			_velocity.SetVectorY(0.0);
			//_fired = false;
		}
	}
}
// Fire the disc
void Disc::FireDisc()
{
	if (!_fired) // If the disc hasn't been fired then fire it
	{
		_fired = true;
		_justFired = true;
	}
}
// Get the velocity vector
Vector3d Disc::GetVelocityVector() const
{
	return _velocity;
}
// Set the velocity vector
void Disc::SetVelocityVector(Vector3d vector)
{
	_velocity.SetVector(vector.X(), vector.Y(), vector.Z());
}
// Get the collision normal
Vector3d Disc::GetCollisionNormal() const
{
	return _collisionNormal;
}
// Set the collision normal of the disc
void Disc::SetCollisionNormal(Vector3d vector)
{
	_collisionNormal.SetVector(vector.X(), vector.Y(), vector.Z());
	_collisionNormal = _collisionNormal.Normalise();
}
// Get the mass of the disc
double Disc::GetMass() const
{
	return _weight;
}
// Set the fired status of the disc
void Disc::SetFiredStatus(const bool &status)
{
	_fired = status;
}
// Get the Y velocity of the disc
double Disc::GetYVelocity() const
{
	return _velocity.Y();
}
// Reset the disc's position to its original value
void Disc::ResetDiscPosition()
{
	_centre.SetVector(_originalPosition.X(), _originalPosition.Y(), 0);
}
// Set the disc's height
void Disc::SetDiscHeight(const double &input)
{
	_height = input;
}
// Move the disc left
void Disc::MoveDiscLeft()
{
	Vector3d currentPosition = _centre;
	_centre.SetVectorX(_centre.X()-10);
	if (_centre.X() <= 20)
	{
		_centre.SetVectorX(currentPosition.X());
	}
}
// Move the disc right
void Disc::MoveDiscRight()
{
	Vector3d currentPosition = _centre;
	_centre.SetVectorX(_centre.X() + 10);
	if (_centre.X() >= 1180)
	{
		_centre.SetVectorX(currentPosition.X());
	}
}
// Get the moved to start status - if it's already been moved there then it can be moved left/right
bool Disc::GetMovedToStartStatus() const
{
	return _movedToStart;
}
// Set the moved to start status
void Disc::SetMovedToStartStatus(const bool &input)
{
	_movedToStart = input;
}