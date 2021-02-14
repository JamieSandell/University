#include "Ball.h"
#include "Timer.h"
#include <GL/glut.h>
#include <math.h>

Ball::Ball(void) : NewtonianObject()
{
	// Initialise private member variables to reasonable values
	_xPos = 0;
	_yPos = 0;
	_initialXPos = 0;
	_initialYPos = 0;
	_yPosSpeed = 0;
	_radius = 1;
	_colour[0] = 1.0f;
	_colour[1] = 1.0f;
	_colour[2] = 1.0f;
	_firstCreation = _ballStillAlive = false;
	_initialXVelocity = 0;
	_initialYVelocity = 0;
	_xVelocity = 0;
	_yVelocity = 0;
	_gravityVelocity = 0;
}

Ball::~Ball(void)
{
}

/// <summary>
/// Sets the status of the ball's life
/// <param name="status">True/False Alive/Not alive</param>
/// </summary>
/// <returns>
/// Nothing
/// </returns>
void Ball::SetAliveStatus(const bool &status)
{
	_ballStillAlive = status;
	_xPos = 0;
	_yPos = 0;
}
void Ball::GetVelocity(float &xVelocity, float &yVelocity) const
{
	xVelocity = _xVelocity;
	yVelocity = _yVelocity;
}

void Ball::SetVelocity(const float &xVelocity, const float &yVelocity)
{
	_xVelocity = xVelocity;
	_yVelocity = yVelocity;
}

/// <summary>
/// Gets the status of the ball's life
/// </summary>
/// <returns>
/// The status of the ball's live
/// </returns>
bool Ball::GetAliveStatus(void) const
{
	return _ballStillAlive;
}

/// <summary>
/// Changes the _firstCreation flag
/// </summary>
/// <returns>
/// Nothing
/// </returns>
void Ball::ChangeFirstCreationFlag()
{
	if (!_ballStillAlive) // Old ball has gone so set flags to create a new one
	{
		_firstCreation = true;
		_ballStillAlive = true;
	}
}

/// <summary>
/// Updates the position of the cannonball
/// <param name="dt">Delta Time</param>
/// <param name="cannon">A cannon object</param>
/// <param name="screenBoundaryX">The right hand side of the screen</param>
/// <param name="screenBoundaryY">The bottom of the screen</param>
/// </summary>
/// <returns>
/// Nothing
/// <returns>
void Ball::UpdatePos(const float &dt, const Cannon &cannon, const int &screenBoundaryX,
					 const int &screenBoundaryY)
{	
	if (_ballStillAlive) // Something to update
	{
		if (_firstCreation) // Only just been fired so set it's initial position
		{
			float cannonAngle = cannon.GetAngleRadians(); // For the firing angle

			// Reset these when firing a new cannon so we don't contain any old data
			// Essentially creating a new ball without new/delete - more efficient
			_yPosSpeed = 0;
			_ballTimer.ResetTimer();
			_yPos = 0;
			_xPos = 0;
			_xVelocity = 0;
			_yVelocity = 0;
			_gravityVelocity = 0;
			//

			_initialXVelocity = (cannon.GetForce());
			_initialYVelocity = (cannon.GetForce());
			_initialXPos = (cannon.GetXPos());
			_initialYPos = (cannon.GetYPos());
			_firstCreation = false; // So we don't keep resetting the position
			_xVelocity = _initialXVelocity * (sinf(cannonAngle));
			_yVelocity = _initialYVelocity * (cosf(cannonAngle));
			SetVelocity(_xVelocity, _yVelocity);
		}
		else // Already been fired
		{
			double gravity = GetGravity();

			// GetCreationTime gets the time since the ball was fired/created
			// this ensures independent processor animation
			_gravityVelocity = gravity * _ballTimer.GetCreationTime();
			_xPos = _initialXPos + _xVelocity * _ballTimer.GetCreationTime();
			_yPos = _initialYPos - _yVelocity  * _ballTimer.GetCreationTime() - 0.5 * _gravityVelocity * _ballTimer.GetCreationTime() * _ballTimer.GetCreationTime();

			// Has the ball left the screen?
			if ((_xPos > screenBoundaryX) || (_yPos < screenBoundaryY))
			{
				_ballStillAlive = false; // Kill the ball

			}
		}
	}
}

// Draw the object
void Ball::Draw(const float &_angle, const int &_height, const int &_width) const
{
	if (_ballStillAlive) // Something to draw
	{
		glColor3fv(_colour);		// set the OpenGL colour to the colour of this object
		glPushMatrix();
			glTranslatef((_xPos+_width*0.5), (_yPos+_height*0.5), 0);
			glRotatef(_angle, 0, 0, 1);
			glTranslatef(-(_xPos+_width*0.5), -(_yPos+_height*0.5), 0);
			glBegin(GL_POLYGON);	// draw the object as an outline
				for(float angle = 0; angle < 2*3.141; angle += 0.1)
				{
					glVertex2d(_xPos+_radius*sin(angle), _yPos+_radius*cos(angle));
				}
			glEnd();
		glPopMatrix();
	}

}

// Set the position of the centre of the object
void Ball::SetPos(const float &x, const float &y)
{
	_xPos = x;
	_yPos = y;
}

// Set the radius of the object
void Ball::SetRadius(const float &radius)
{
	_radius = radius;
}

// Set the colour of the object
void Ball::SetColour(const float &red, const float &green, const float &blue)
{
	_colour[0] = red;
	_colour[1] = green;
	_colour[2] = blue;
}

// Get the position of the left side of the object's centre
float Ball::GetXPos(void) const
{
	return _xPos;
}

// Get the position of the bottom side of the object's centre
float Ball::GetYPos(void) const
{
	return _yPos;
}

// Get the radius of the object
float Ball::GetRadius(void) const
{
	return _radius;
}

// Get the colour of the object
const float* Ball::GetColour(void) const
{
	return _colour;
}
