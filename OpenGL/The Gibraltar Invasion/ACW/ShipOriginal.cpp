#include <cstdlib>
#include <GL/glut.h>
#include "ShipOriginal.h"

ShipOriginal::ShipOriginal(void)
{
}

ShipOriginal::~ShipOriginal(void)
{
}

void ShipOriginal::Draw(void)
{
	glColor3fv(0);		// set the OpenGL colour to the colour of this object
	//glBegin(GL_LINE_LOOP);	// draw the object as an outline
	glLineWidth(5.0f);
	// draw the object as lines
	glBegin(GL_LINE_STRIP);			
	glVertex2d(             GetXPos(), GetYPos()+(GetHeight()*0.5));	
	glVertex2d(GetXPos()+(GetWidth()*0.3),               GetYPos());	
	glVertex2d(GetXPos()+(GetWidth()*0.7),               GetYPos());	
	glVertex2d(      GetXPos()+GetWidth(), GetYPos()+(GetHeight()*0.5));	
	glEnd();
	glBegin(GL_LINE_STRIP);			
	glVertex2d(GetXPos()+(GetWidth()*0.45),               GetYPos());	
	glVertex2d(GetXPos()+(GetWidth()*0.45),               GetYPos()+GetHeight());	
	glVertex2d(GetXPos()+(GetWidth()*0.75), GetYPos()+(GetHeight()*0.7));	
	glVertex2d(GetXPos()+(GetWidth()*0.45), GetYPos()+(GetHeight()*0.4));	
	glEnd();
	glLineWidth(1.0f);
}
