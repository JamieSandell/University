#include "Ship.h"
#include <cstdlib>
#include <GL/glut.h>

Ship::Ship(void)
{
	// Initialise private member variables to reasonable values
	_xPos = _yPos = 0;
	_width = _height = 20;
	_colour[0] = 1.0f;
	_colour[1] = 1.0f;
	_colour[2] = 1.0f;
	_direction = 0;
	_xVelocity = 0;
	_yVelocity = 0;
	_shipIsSinking = false;
	_shipIsAlive = true;
}

Ship::~Ship(void)
{
}
/// <summary>
/// Gets the sinking status of the ship
/// </summary>
/// <returns>
/// A bool containing the status of the ship's sinking state
/// </returns>
bool Ship::GetSinkingStatus() const
{
	return _shipIsSinking;
}
/// <summary>
/// Gets the alive status of the ship
/// </summary>
/// <returns>
/// A bool containing the status of the ship's life
/// </returns>
bool Ship::GetAliveStatus() const
{
	return _shipIsAlive;
}

/// <summary>
/// Sets the sinking status of the ship
/// <param name="status">true/false = sinking/not sinking</param>
/// </summary>
/// <returns>
/// Nothing
/// </returns>
void Ship::SetSinking(const bool &status)
{
	_shipIsSinking = status;
}
/// <summary>
/// Sets the alive status of the ship
/// <param name="status">true/false = alive/not alive</param>
/// </summary>
/// <returns>
/// Nothing
/// </returns>
void Ship::SetAlive(const bool &status)
{
	_shipIsAlive = status;
}

/// <summary>
/// Sinks the ship
/// </summary>
/// <returns>
/// Nothing
/// </returns>
void Ship::SinkShip(const float &dt)
{
	if (_yPos + _height > 0) // Hasn't finished sinking
	{
		_yPos  -= 60 * dt;
	}
	else
	{
		_shipIsSinking = false; // Finished sinking
		_shipIsAlive = false; // No longer alive now that it has sank
		// No reset it's xpos/ypos for the next time it's drawn/alive
		_xPos = 400;
		_yPos = 75;
	}
}

/// <summary>
/// Sets the x,y velocity of the ship
/// <param name="xVelocity">x velocity of the ship</param>
/// <param name="yVelocity">y velocity of the ship</param>
/// </summary>
/// <returns>
/// Nothing
/// </returns>
void Ship::SetVelocity(float const &xVelocity, float const &yVelocity)
{
	_xVelocity = xVelocity;
	_yVelocity = yVelocity;
}

/// <summary>
/// Gets the x,y velocities of the ship
/// <param name="xVelocity">x velocity of the ship to return</param>
/// <param name="yVelocity">y velocity of the ship to return</param>
/// </summary>
/// <returns>
/// Nothing
/// </returns>
void Ship::GetVelocity(float &xVelocity, float &yVelocity) const
{
	xVelocity = _xVelocity;
	yVelocity = _yVelocity;
}

/// <summary>
/// Updates the ships postion
/// <param name="dt">Delta Time</param>
/// <param name="leftX">The left X position the ship must not pass</param>
/// <param name="rightX">The right X position the ship must not pass</param>
/// </summary>
/// <returns>
/// Nothing
/// </returns>
void Ship::Update(const float &dt, const int &leftX, const int &rightX)
{
	if (_shipIsAlive)
	{
		// velocity for the ship will be random within a set range
		int velocity = rand() % (20 - 5) + 5 + 1; // between 5 and 20
		SetVelocity(velocity, 0);

		if (_shipIsSinking)
		{
			SinkShip(dt);
		}
		else
		{
			while (true) // Loop forever until we have a set direction without breaking x limits
			{
				if (_direction == 0) // 0 for left, 1 for right
				{
					_xPos -= velocity*dt;
					// but did we exceed our limit?
					if (_xPos <= leftX)
					{
						_direction = 1; // Now we go right
					}
					else // didn't break any limits so we can exit the loop
					{
						break;
					}
				}
				else
				{
					_xPos += velocity*dt;
					// but did we exceed our limit?
					if (_xPos + _width >= rightX)
					{
						_direction = 0;
					}
					else // didn't break any limits so we can exit the loop
					{
						break;
					}
				}
			}
		}
	}
}

// Draw the object
void Ship::Draw(void) const
{
	if (_shipIsAlive)
	{
		glColor3fv(_colour);		// set the OpenGL colour to the colour of this object
		//glBegin(GL_LINE_LOOP);	// draw the object as an outline
		glLineWidth(5.0f);
		// draw the object as lines
		glBegin(GL_LINE_STRIP);			
			glVertex2d(             _xPos, _yPos+(_height*0.5));	
			glVertex2d(_xPos+(_width*0.3),               _yPos);	
			glVertex2d(_xPos+(_width*0.7),               _yPos);	
			glVertex2d(      _xPos+_width, _yPos+(_height*0.5));	
		glEnd();
		glBegin(GL_LINE_STRIP);			
			glVertex2d(_xPos+(_width*0.45),               _yPos);	
			glVertex2d(_xPos+(_width*0.45),               _yPos+_height);	
			glVertex2d(_xPos+(_width*0.75), _yPos+(_height*0.7));	
			glVertex2d(_xPos+(_width*0.45), _yPos+(_height*0.4));	
		glEnd();
		glLineWidth(1.0f);
	}
}

// Set the position of the left-bottom corner of the object
void Ship::SetPos(const float &x, const float &y)
{
	_xPos = x;
	_yPos = y;
}

// Set the dimensions of the object
void Ship::SetDimensions(const float &width, const float &height)
{
	_width = width;
	_height = height;
}

// Set the colour of the object
void Ship::SetColour(const float &red, const float &green, const float &blue)
{
	_colour[0] = red;
	_colour[1] = green;
	_colour[2] = blue;
}

// Get the position of the left side of the object
float Ship::GetXPos(void) const
{
	return _xPos;
}

// Get the position of the bottom side of the object
float Ship::GetYPos(void) const
{
	return _yPos;
}

// Get the width of the object
float Ship::GetWidth(void) const
{
	return _width;
}

// Get the height of the object
float Ship::GetHeight(void) const
{
	return _height;
}

// Get the colour of the object
const float* Ship::GetColour(void) const
{
	return _colour;
}
