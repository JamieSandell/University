#include "Cannon.h"
#include <GL/glut.h>

Cannon::Cannon(void)
{
	// Initialise private member variables to reasonable values
	_angle = 0;
	_xPos = _yPos = 0;
	_width = _height = 20;
	_colour[0] = 1.0f;
	_colour[1] = 1.0f;
	_colour[2] = 1.0f;
	_force = 10;
}

Cannon::~Cannon(void)
{
}

/// <summary>
/// Get the current firing force
/// </summary>
/// <returns>
/// The force
/// </returns>
int Cannon::GetForce() const
{
	return _force;
}

/// <summary>
/// Increase the current force
/// <param name="force">The amount in force to increase by</param>
/// </summary>
/// <returns>
/// The force
/// </returns>
void Cannon::IncreaseForce(const float &force)
{
	if (_force < 100)
	{
		_force += force;
	}
}

/// <summary>
/// Decrease the current force
/// <param name="force">The amount in force to decrease by</param>
/// </summary>
/// <returns>
/// The force
/// </returns>
void Cannon::DecreaseForce(const float &force)
{
	if (_force > 10)
	{
		_force -= force;
	}
}

// Draw the object
void Cannon::Draw(void) const
{
	glColor3fv(_colour);		// set the OpenGL colour to the colour of this object
	glLineWidth(5.0f);
	glPushMatrix();
		glTranslatef((_xPos+_width*0.5), (_yPos+_height*0.5), 0);
		glRotatef(_angle, 0, 0, 1);
		glTranslatef(-(_xPos+_width*0.5), -(_yPos+_height*0.5), 0);
		// draw the object as lines
		glBegin(GL_LINES);			
			glVertex2d(_xPos+_width,       _yPos);
			glVertex2d(_xPos+(_width*0.6), _yPos+_height);
			glVertex2d(_xPos,              _yPos);	
			glVertex2d(_xPos+(_width*0.4), _yPos+_height);	
		glEnd();
	glPopMatrix();
	glLineWidth(1.0f);
}

// Set the position of the left-bottom corner of the object
void Cannon::SetPos(const float &x, const float &y)
{
	_xPos = x;
	_yPos = y;
}

// Set the dimensions of the object
void Cannon::SetDimensions(const float &width, const float &height)
{
	_width = width;
	_height = height;
}

// Set the colour of the object
void Cannon::SetColour(const float &red, const float &green, const float &blue)
{
	_colour[0] = red;
	_colour[1] = green;
	_colour[2] = blue;
}

/// <summary>
/// Increase the angle in radians
/// </summary>
/// <returns>
/// Nothing
/// </returns>
void Cannon::IncreaseAngleRadians(void)
{
	float tempAngle = _angle;
	tempAngle += .1*(180.0/3.141); // Check we haven't gone past our limits
	if (tempAngle <= 179)
	{
		_angle += .1*(180.0/3.141);
	}
}

/// <summary>
/// Decreases the angle in radians
/// </summary>
/// <returns>
/// Nothing
///</returns>
void Cannon::DecreaseAngleRadians(void)
{
	float tempAngle = _angle;
	tempAngle -= .1*(180.0/3.141); // Check we haven't gone past our limits
	if (tempAngle > 20) // Anything less then 20 and you're hitting the cliff
	{
		_angle -= .1*(180.0/3.141);
	}
}

// Set the angle of the object in radians
void Cannon::SetAngleRadians(const float &rad)
{
	_angle = rad*(180.0/3.141);
}

// Set the angle of the object in degrees
void Cannon::SetAngleDegrees(const float &deg)
{
	_angle = deg;
}

/// <summary>
/// Gets the angle in degrees
/// </summary>
/// <returns>
/// A float - angle
/// </returns>
float Cannon::GetAngle(void) const
{
	return _angle;
}

/// <summary>
/// Gets the angle in radians
/// </summary>
/// <returns>
/// A float - angle
/// </returns>
float Cannon::GetAngleRadians(void) const
{
	return (_angle * 3.141) / 180;
}

// Get the position of the left side of the object
float Cannon::GetXPos(void) const
{
	return _xPos;
}

// Get the position of the bottom side of the object
float Cannon::GetYPos(void) const
{
	return _yPos;
}

// Get the width of the object
float Cannon::GetWidth(void) const
{
	return _width;
}

// Get the height of the object
float Cannon::GetHeight(void) const
{
	return _height;
}

// Get the colour of the object
const float* Cannon::GetColour(void) const
{
	return _colour;
}
