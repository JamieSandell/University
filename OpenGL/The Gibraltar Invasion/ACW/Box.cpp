#include "Box.h"
#include <GL/glut.h>

Box::Box(void)
{
	// Initialise private member variables to reasonable values
	_xPos = _yPos = 0;
	_width = _height = 20;
	_colour[0] = 1.0f;
	_colour[1] = 1.0f;
	_colour[2] = 1.0f;
}

Box::~Box(void)
{
}

// Draw the object
void Box::Draw(void) const
{
	glColor3fv(_colour);		// set the OpenGL colour to the colour of this object
	//glBegin(GL_LINE_LOOP);	// draw the object as an outline
	glBegin(GL_QUADS);			// draw the object as a solid
		glVertex2d(       _xPos,         _yPos);	// bottom-left coord
		glVertex2d(_xPos+_width,         _yPos);	// bottom-right coord
		glVertex2d(_xPos+_width, _yPos+_height);	// top-right coord
		glVertex2d(       _xPos, _yPos+_height);	// top-left coord
	glEnd();
}

// Set the position of the left-bottom corner of the object
void Box::SetPos(const float &x, const float &y)
{
	_xPos = x;
	_yPos = y;
}

// Set the dimensions of the object
void Box::SetDimensions(const float &width, const float &height)
{
	_width = width;
	_height = height;
}

// Set the colour of the object
void Box::SetColour(const float &red, const float &green, const float &blue)
{
	_colour[0] = red;
	_colour[1] = green;
	_colour[2] = blue;
}

// Get the position of the left side of the object
float Box::GetXPos(void) const
{
	return _xPos;
}

// Get the position of the bottom side of the object
float Box::GetYPos(void) const
{
	return _yPos;
}

// Get the width of the object
float Box::GetWidth(void) const
{
	return _width;
}

// Get the height of the object
float Box::GetHeight(void) const
{
	return _height;
}

// Get the colour of the object
const float* Box::GetColour(void) const
{
	return _colour;
}
