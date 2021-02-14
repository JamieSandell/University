#include "Table.h"

Table::Table(void)
{
	/////////// Friction
	_surfaceFriction = 0.1;
	_sideFriction = 0.1;
	_discToSideElasticity = 1.0;
	/////////// Friction

	/////////// Test
	_angle = 0.0;
	/////////// Test

	/////////// Playing Surface
	_playingSurfaceLength = 2500; // 2500mm
	_playingSurfaceWidth = 1200;
	_playingSurfaceHeight = 0;
	_playingSurfaceTopLeft.SetVector(0, _playingSurfaceLength, _playingSurfaceHeight);
	_playingSurfaceTopRight.SetVector(_playingSurfaceWidth, _playingSurfaceLength, _playingSurfaceHeight);
	_playingSurfaceBottomRight.SetVector(_playingSurfaceWidth, 0, _playingSurfaceHeight);
	_playingSurfaceBottomLeft.SetVector(0, 0 , _playingSurfaceHeight);
	/////////// Playing Surface

	/////// Circles
	// Outermost circle
	_outerMostCircle.SetVector(600, _playingSurfaceLength-600, _playingSurfaceHeight); // centre of the circle
	_outerMostCircleRadius = 400; // 800mm diameter
	// Inner circle
	_innerCircle = _outerMostCircle; // Share the same centre point
	_innerCircleRadius = 250;
	// Innermost circle
	_innerMostCircle = _outerMostCircle;
	_innerMostCircleRadius = 100;
	/////// Circles

	/////////// Starting Line
	_startingLine.SetVector(0, 150, _playingSurfaceHeight); // 15cm
	/////////// Starting Line

	//////////// Left Edge
	_tableLeftEdgeLength = 2550;
	_tableLeftEdgeWidth= 50;
	_tableLeftEdgeHeight = 50;
	// Top
	_tableLeftEdgeTopTopLeft.SetVector(-_tableLeftEdgeWidth, _tableLeftEdgeLength, _tableLeftEdgeHeight);
	_tableLeftEdgeTopTopRight.SetVector(0, _tableLeftEdgeLength, _tableLeftEdgeHeight);
	_tableLeftEdgeTopBottomRight.SetVector(0, 0, _tableLeftEdgeHeight);
	_tableLeftEdgeTopBottomLeft.SetVector(-_tableLeftEdgeWidth, 0, _tableLeftEdgeHeight);

	// Bottom
	_tableLeftEdgeBottomTopLeft.SetVector(-_tableLeftEdgeWidth, _tableLeftEdgeLength, _playingSurfaceHeight);
	_tableLeftEdgeBottomTopRight.SetVector(0, _tableLeftEdgeLength, _playingSurfaceHeight);
	_tableLeftEdgeBottomBottomRight.SetVector(0, 0, _playingSurfaceHeight);
	_tableLeftEdgeBottomBottomLeft.SetVector(-_tableLeftEdgeWidth, 0, _playingSurfaceHeight);

	// Left
	_tableLeftEdgeLeftTopLeft.SetVector(-_tableLeftEdgeWidth, _tableLeftEdgeLength, _tableLeftEdgeHeight);
	_tableLeftEdgeLeftTopRight.SetVector(-_tableLeftEdgeWidth, 0, _tableLeftEdgeHeight);
	_tableLeftEdgeLeftBottomRight.SetVector(-_tableLeftEdgeWidth, 0, 0);
	_tableLeftEdgeLeftBottomLeft.SetVector(-_tableLeftEdgeWidth, _tableLeftEdgeLength, 0);

	// Right
	_tableLeftEdgeRightTopLeft.SetVector(0, _tableLeftEdgeLength, _tableLeftEdgeHeight);
	_tableLeftEdgeRightTopRight.SetVector(0, 0, _tableLeftEdgeHeight);
	_tableLeftEdgeRightBottomRight.SetVector(0, 0, _playingSurfaceHeight);
	_tableLeftEdgeRightBottomLeft.SetVector(0, _tableLeftEdgeLength, _playingSurfaceHeight);

	// Front
	_tableLeftEdgeFrontTopLeft.SetVector(-_tableLeftEdgeWidth, 0, _tableLeftEdgeHeight);
	_tableLeftEdgeFrontTopRight.SetVector(0, 0, _tableLeftEdgeHeight);
	_tableLeftEdgeFrontBottomRight.SetVector(0, 0, _playingSurfaceHeight);
	_tableLeftEdgeFrontBottomLeft.SetVector(-_tableLeftEdgeWidth, 0, _playingSurfaceHeight);

	// Back
	_tableLeftEdgeBackTopLeft.SetVector(-_tableLeftEdgeWidth, _tableLeftEdgeLength, _tableLeftEdgeHeight);
	_tableLeftEdgeBackTopRight.SetVector(0, _tableLeftEdgeLength, _tableLeftEdgeHeight);
	_tableLeftEdgeBackBottomRight.SetVector(0, _tableLeftEdgeLength, _playingSurfaceHeight);
	_tableLeftEdgeBackBottomLeft.SetVector(-_tableLeftEdgeWidth, _tableLeftEdgeLength,
		_playingSurfaceHeight);

	// For collision code
	_tableLeftEdgeRightSide.SetVector(0,0,0);
	_tableLeftEdgeRightSideNorm.SetVector(1,0,0);
	_sides.push_back(_tableLeftEdgeRightSide);
	_sidesNorm.push_back(_tableLeftEdgeRightSideNorm);
	///////// Left Edge

	//////// Right Edge
	_tableRightEdgeLength = 2550;
	_tableRightEdgeWidth= 50;
	_tableRightEdgeHeight = 50;
	// Top
	_tableRightEdgeTopTopLeft.SetVector(_playingSurfaceWidth, _playingSurfaceLength+50,
		_tableRightEdgeHeight);
	_tableRightEdgeTopTopRight.SetVector(_playingSurfaceWidth+_tableRightEdgeWidth, _playingSurfaceLength+50,
		_tableRightEdgeHeight);
	_tableRightEdgeTopBottomRight.SetVector(_playingSurfaceWidth+_tableRightEdgeWidth, 0,
		_tableRightEdgeHeight);
	_tableRightEdgeTopBottomLeft.SetVector(_playingSurfaceWidth, 0, _tableRightEdgeHeight);

	// Bottom
	_tableRightEdgeBottomTopLeft.SetVector(_playingSurfaceWidth, _playingSurfaceLength,
		_playingSurfaceHeight);
	_tableRightEdgeBottomTopRight.SetVector(_playingSurfaceWidth+_tableRightEdgeWidth,
		_playingSurfaceLength, _playingSurfaceHeight);
	_tableRightEdgeBottomBottomRight.SetVector(_playingSurfaceWidth+_tableRightEdgeWidth, 0,
		_playingSurfaceHeight);
	_tableRightEdgeBottomBottomLeft.SetVector(_playingSurfaceWidth, 0, _playingSurfaceHeight);

	// Front
	_tableRightEdgeFrontTopLeft.SetVector(_playingSurfaceWidth, 0, _tableRightEdgeHeight);
	_tableRightEdgeFrontTopRight.SetVector(_playingSurfaceWidth+_tableRightEdgeWidth, 0,
		_tableRightEdgeHeight);
	_tableRightEdgeFrontBottomRight.SetVector(_playingSurfaceWidth+_tableRightEdgeWidth, 0,
		_playingSurfaceHeight);
	_tableRightEdgeFrontBottomLeft.SetVector(_playingSurfaceWidth, 0, _playingSurfaceHeight);

	// Back
	_tableRightEdgeBackTopLeft.SetVector(_playingSurfaceWidth, _playingSurfaceLength,
		_tableRightEdgeHeight);
	_tableRightEdgeBackTopRight.SetVector(_playingSurfaceWidth+_tableRightEdgeWidth,
		_playingSurfaceLength, _tableRightEdgeHeight);
	_tableRightEdgeBackBottomRight.SetVector(_playingSurfaceWidth+_tableRightEdgeWidth,
		_playingSurfaceLength, _playingSurfaceHeight);
	_tableRightEdgeBackBottomLeft.SetVector(_playingSurfaceWidth, _playingSurfaceLength,
		_playingSurfaceHeight);

	// Left
	_tableRightEdgeLeftTopLeft.SetVector(_playingSurfaceWidth, _playingSurfaceLength,
		_tableRightEdgeHeight);
	_tableRightEdgeLeftTopRight.SetVector(_playingSurfaceWidth, 0, _tableRightEdgeHeight);
	_tableRightEdgeLeftBottomRight.SetVector(_playingSurfaceWidth, 0, _playingSurfaceHeight);
	_tableRightEdgeLeftBottomLeft.SetVector(_playingSurfaceWidth, _playingSurfaceLength,
		_playingSurfaceHeight);

	// Right
	_tableRightEdgeRightTopLeft.SetVector(_playingSurfaceWidth+_tableRightEdgeWidth,
		_playingSurfaceLength, _tableRightEdgeHeight);
	_tableRightEdgeRightTopRight.SetVector(_playingSurfaceWidth+_tableRightEdgeWidth,
		0, _tableRightEdgeHeight);
	_tableRightEdgeRightBottomRight.SetVector(_playingSurfaceWidth+_tableRightEdgeWidth,
		0, _playingSurfaceHeight);
	_tableRightEdgeRightBottomLeft.SetVector(_playingSurfaceWidth+_tableRightEdgeWidth,
		_playingSurfaceLength, _playingSurfaceHeight);

	// For collision code
	_tableRightEdgeLeftSide.SetVector(_playingSurfaceWidth,0,0);
	_tableRightEdgeLeftSideNorm.SetVector(1,0,0);
	_sides.push_back(_tableRightEdgeLeftSide);
	_sidesNorm.push_back(_tableRightEdgeLeftSideNorm);
	/////// Right Edge

	/////// Top Edge
	_tableTopEdgeLength = 2550;
	_tableTopEdgeWidth= 50;
	_tableTopEdgeHeight = 50;
	// Top
	_tableTopEdgeTopTopLeft.SetVector(0, _playingSurfaceLength+_tableTopEdgeWidth,
		_tableTopEdgeHeight);
	_tableTopEdgeTopTopRight.SetVector(_playingSurfaceWidth, _playingSurfaceLength+_tableTopEdgeWidth,
		_tableTopEdgeHeight);
	_tableTopEdgeTopBottomRight.SetVector(_playingSurfaceWidth, _playingSurfaceLength,
		_tableTopEdgeHeight);
	_tableTopEdgeTopBottomLeft.SetVector(0, _playingSurfaceLength, _tableTopEdgeHeight);

	// Bottom
	_tableTopEdgeBottomTopLeft.SetVector(0, _playingSurfaceLength+_tableTopEdgeWidth,
		_playingSurfaceHeight);
	_tableTopEdgeBottomTopRight.SetVector(_playingSurfaceWidth, _playingSurfaceLength+_tableTopEdgeWidth,
		_playingSurfaceHeight);
	_tableTopEdgeBottomBottomRight.SetVector(_playingSurfaceWidth, _playingSurfaceLength,
		_playingSurfaceHeight);
	_tableTopEdgeBottomBottomLeft.SetVector(0, _playingSurfaceLength, _playingSurfaceHeight);

	// Left
	_tableTopEdgeLeftTopLeft.SetVector(0, _playingSurfaceLength, _tableTopEdgeHeight);
	_tableTopEdgeLeftTopRight.SetVector(_playingSurfaceWidth, _playingSurfaceLength, _tableTopEdgeHeight);
	_tableTopEdgeLeftBottomRight.SetVector(_playingSurfaceWidth, _playingSurfaceLength,
		_playingSurfaceHeight);
	_tableTopEdgeLeftBottomLeft.SetVector(0, _playingSurfaceLength, _playingSurfaceHeight);

	// Right
	_tableTopEdgeRightTopLeft.SetVector(0, _playingSurfaceLength+_tableTopEdgeWidth,
		_tableTopEdgeHeight);
	_tableTopEdgeRightTopRight.SetVector(_playingSurfaceWidth, _playingSurfaceLength+_tableTopEdgeHeight,
		_tableTopEdgeHeight);
	_tableTopEdgeRightBottomRight.SetVector(_playingSurfaceWidth,
		_playingSurfaceLength+_tableTopEdgeHeight, _playingSurfaceHeight);
	_tableTopEdgeRightBottomLeft.SetVector(0, _playingSurfaceLength+_tableTopEdgeWidth,
		_playingSurfaceHeight);

	// For collision code
	_tableTopEdgeLeftSide.SetVector(0,_playingSurfaceLength,0);
	_tableTopEdgeLeftSideNorm.SetVector(0,1,0);
	_sides.push_back(_tableTopEdgeLeftSide);
	_sidesNorm.push_back(_tableTopEdgeLeftSideNorm);
	/////// Top Edge

}

Table::~Table(void)
{
}

// Draw the table
void Table::DrawTable(Texture texture[3]) const
{

		DrawSurface(texture);
		DrawLeftEdge(texture);
		DrawRightEdge(texture);
		DrawTopEdge(texture);
		DrawStartingLine();
		DrawTarget(texture);
		SetupLights();

}

// Draw the table's surface
void Table::DrawSurface(Texture texture[3]) const
{
	glBegin(GL_QUADS);
		GLfloat surfaceColour[] = { 0.0f, 1.0f, 0.0f, 1.0f };
		GLfloat surfaceSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Shiny smooth table
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, surfaceColour);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, surfaceSpecular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);
		glColor3d(0, 1, 0);
		glNormal3f( 0.0f, 1.0f, 0.0f);					// Normal Pointing Up
		glVertex3d(_playingSurfaceTopLeft.X(), _playingSurfaceTopLeft.Y(), _playingSurfaceTopLeft.Z());
		glVertex3d(_playingSurfaceTopRight.X(), _playingSurfaceTopRight.Y(), _playingSurfaceTopRight.Z());
		glVertex3d(_playingSurfaceBottomRight.X(), _playingSurfaceBottomRight.Y(),
			_playingSurfaceBottomRight.Z());
		glVertex3d(_playingSurfaceBottomLeft.X(), _playingSurfaceBottomLeft.Y(),
			_playingSurfaceBottomLeft.Z());
	glEnd();
}

// Draw the left edge of the table
void Table::DrawLeftEdge(Texture texture[3]) const
{
	glBindTexture(GL_TEXTURE_2D, texture[0].texID);
	glBegin(GL_QUADS);
		GLfloat edgeColour[] = { 0.9f, 0.3f, 0.3f, 1.0f };
		GLfloat edgeSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, edgeColour);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, edgeSpecular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);
		glColor3d(0.9, 0.3, 0.3);
		// Top
		glNormal3f( 0.0f, 1.0f, 0.0f);					// Normal Pointing Up
		glTexCoord2f(0.0f, 1.0f); glVertex3d(_tableLeftEdgeTopTopLeft.X(), _tableLeftEdgeTopTopLeft.Y(),
			_tableLeftEdgeTopTopLeft.Z());
		glTexCoord2f(1.0f, 1.0f); glVertex3d(_tableLeftEdgeTopTopRight.X(), _tableLeftEdgeTopTopRight.Y(),
			_tableLeftEdgeTopTopRight.Z());
		glTexCoord2f(1.0f, 0.0f); glVertex3d(_tableLeftEdgeTopBottomRight.X(), _tableLeftEdgeTopBottomRight.Y(),
			_tableLeftEdgeTopBottomRight.Z());
		glTexCoord2f(0.0f, 0.0f); glVertex3d(_tableLeftEdgeTopBottomLeft.X(), _tableLeftEdgeTopBottomLeft.Y(),
			_tableLeftEdgeTopBottomLeft.Z());
	glEnd();
	glBegin(GL_QUADS);
		//glColor3d(0.5, 0.5, 0.5);
		// Bottom
		glNormal3f( 0.0f,-1.0f, 0.0f);					// Normal Pointing Down
		glTexCoord2f(0.0f, 1.0f); glVertex3d(_tableLeftEdgeBottomTopLeft.X(), _tableLeftEdgeBottomTopLeft.Y(),
			_tableLeftEdgeBottomTopLeft.Z());
		glTexCoord2f(1.0f, 1.0f); glVertex3d(_tableLeftEdgeBottomTopRight.X(), _tableLeftEdgeBottomTopRight.Y(),
			_tableLeftEdgeBottomTopRight.Z());
		glTexCoord2f(1.0f, 0.0f); glVertex3d(_tableLeftEdgeBottomBottomRight.X(),
			_tableLeftEdgeBottomBottomRight.Y(), _tableLeftEdgeBottomBottomRight.Z());
		glTexCoord2f(0.0f, 0.0f); glVertex3d(_tableLeftEdgeBottomBottomLeft.X(),
			_tableLeftEdgeBottomBottomLeft.Y(), _tableLeftEdgeBottomBottomLeft.Z());
	glEnd();
	glBegin(GL_QUADS);
		//glColor3d(0.5, 0.5, 0.5);
		// Front
		glNormal3f( 0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
		glTexCoord2f(0.0f, 1.0f); glVertex3d(_tableLeftEdgeFrontTopLeft.X(), _tableLeftEdgeFrontTopLeft.Y(),
			_tableLeftEdgeFrontTopLeft.Z());
		glTexCoord2f(1.0f, 1.0f); glVertex3d(_tableLeftEdgeFrontTopRight.X(), _tableLeftEdgeFrontTopRight.Y(),
			_tableLeftEdgeFrontTopRight.Z());
		glTexCoord2f(1.0f, 0.0f); glVertex3d(_tableLeftEdgeFrontBottomRight.X(), _tableLeftEdgeFrontBottomRight.Y(),
			_tableLeftEdgeFrontBottomRight.Z());
		glTexCoord2f(0.0f, 0.0f); glVertex3d(_tableLeftEdgeFrontBottomLeft.X(), _tableLeftEdgeFrontBottomLeft.Y(),
			_tableLeftEdgeFrontBottomLeft.Z());
	glEnd();
	glBegin(GL_QUADS);
		//glColor3d(0.5, 0.5, 0.5);
		// Back
		glNormal3f( 0.0f, 0.0f,-1.0f);					// Normal Pointing Away From Viewer
		glTexCoord2f(0.0f, 1.0f); glVertex3d(_tableLeftEdgeBackTopLeft.X(), _tableLeftEdgeBackTopLeft.Y(),
			_tableLeftEdgeBackTopLeft.Z());
		glTexCoord2f(1.0f, 1.0f); glVertex3d(_tableLeftEdgeBackTopRight.X(), _tableLeftEdgeBackTopRight.Y(),
			_tableLeftEdgeBackTopRight.Z());
		glTexCoord2f(1.0f, 0.0f); glVertex3d(_tableLeftEdgeBackBottomRight.X(), _tableLeftEdgeBackBottomRight.Y(),
			_tableLeftEdgeBackBottomRight.Z());
		glTexCoord2f(0.0f, 0.0f); glVertex3d(_tableLeftEdgeBackBottomLeft.X(), _tableLeftEdgeBackBottomLeft.Y(),
			_tableLeftEdgeBackBottomLeft.Z());
	glEnd();
	glBegin(GL_QUADS);
		//glColor3d(0.5, 0.5, 0.5);
		// Left
		glNormal3f(-1.0f, 0.0f, 0.0f);					// Normal Pointing Left
		glTexCoord2f(0.0f, 1.0f); glVertex3d(_tableLeftEdgeLeftTopLeft.X(), _tableLeftEdgeLeftTopLeft.Y(),
			_tableLeftEdgeLeftTopLeft.Z());
		glTexCoord2f(1.0f, 1.0f); glVertex3d(_tableLeftEdgeLeftTopRight.X(), _tableLeftEdgeLeftTopRight.Y(),
			_tableLeftEdgeLeftTopRight.Z());
		glTexCoord2f(1.0f, 0.0f);glVertex3d(_tableLeftEdgeLeftBottomRight.X(), _tableLeftEdgeLeftBottomRight.Y(),
			_tableLeftEdgeLeftBottomRight.Z());
		glTexCoord2f(0.0f, 0.0f); glVertex3d(_tableLeftEdgeLeftBottomLeft.X(), _tableLeftEdgeLeftBottomLeft.Y(),
			_tableLeftEdgeLeftBottomLeft.Z());
	glEnd();
	glBegin(GL_QUADS);
		//glColor3d(0.5, 0.5, 0.5);
		// Right
		glNormal3f( 1.0f, 0.0f, 0.0f);					// Normal Pointing Right
		glTexCoord2f(0.0f, 1.0f); glVertex3d(_tableLeftEdgeRightTopLeft.X(), _tableLeftEdgeRightTopLeft.Y(),
			_tableLeftEdgeRightTopLeft.Z());
		glTexCoord2f(1.0f, 1.0f); glVertex3d(_tableLeftEdgeRightTopRight.X(), _tableLeftEdgeRightTopRight.Y(),
			_tableLeftEdgeRightTopRight.Z());
		glTexCoord2f(1.0f, 0.0f);glVertex3d(_tableLeftEdgeRightBottomRight.X(), _tableLeftEdgeRightBottomRight.Y(),
			_tableLeftEdgeRightBottomRight.Z());
		glTexCoord2f(0.0f, 0.0f);glVertex3d(_tableLeftEdgeRightBottomLeft.X(), _tableLeftEdgeRightBottomLeft.Y(),
			_tableLeftEdgeRightBottomLeft.Z());
	glEnd();
}

// Draw the right edge of the table
void Table::DrawRightEdge(Texture texture[3]) const
{
	glBegin(GL_QUADS);
		GLfloat edgeColour[] = { 0.9f, 0.3f, 0.3f, 1.0f };
		GLfloat edgeSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, edgeColour);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, edgeSpecular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);
		glColor3d(0.9, 0.3, 0.3);
		// Top
		glNormal3f( 0.0f, 1.0f, 0.0f);					// Normal Pointing Up
		glVertex3d(_tableRightEdgeTopTopLeft.X(), _tableLeftEdgeTopTopLeft.Y(),
			_tableRightEdgeTopTopLeft.Z());
		glTexCoord2f(1.0f, 1.0f); glVertex3d(_tableRightEdgeTopTopRight.X(), _tableRightEdgeTopTopRight.Y(),
			_tableRightEdgeTopTopRight.Z());
		glTexCoord2f(1.0f, 0.0f);glVertex3d(_tableRightEdgeTopBottomRight.X(), _tableRightEdgeTopBottomRight.Y(),
			_tableRightEdgeTopBottomRight.Z());
		glTexCoord2f(0.0f, 0.0f);glVertex3d(_tableRightEdgeTopBottomLeft.X(), _tableRightEdgeTopBottomLeft.Y(),
			_tableRightEdgeTopBottomLeft.Z());
	glEnd();

	glBegin(GL_QUADS);
		// Bottom
		glNormal3f( 0.0f,-1.0f, 0.0f);					// Normal Pointing Down
		glTexCoord2f(0.0f, 1.0f); glVertex3d(_tableRightEdgeBottomTopLeft.X(), _tableRightEdgeBottomTopLeft.Y(),
			_tableRightEdgeBottomTopLeft.Z());
		glTexCoord2f(1.0f, 1.0f); glVertex3d(_tableRightEdgeBottomTopRight.X(), _tableRightEdgeBottomTopRight.Y(),
			_tableRightEdgeBottomTopRight.Z());
		glTexCoord2f(1.0f, 0.0f);glVertex3d(_tableRightEdgeBottomBottomRight.X(), _tableRightEdgeBottomBottomRight.Y(),
			_tableRightEdgeBottomBottomRight.Z());
		glTexCoord2f(0.0f, 0.0f);glVertex3d(_tableRightEdgeBottomBottomLeft.X(), _tableRightEdgeBottomBottomLeft.Y(),
			_tableRightEdgeBottomBottomLeft.Z());
	glEnd();

	glBegin(GL_QUADS);
		// Front
		glNormal3f( 0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
		glTexCoord2f(0.0f, 1.0f); glVertex3d(_tableRightEdgeFrontTopLeft.X(), _tableRightEdgeFrontTopLeft.Y(),
			_tableRightEdgeFrontTopLeft.Z());
		glTexCoord2f(1.0f, 1.0f);glVertex3d(_tableRightEdgeFrontTopRight.X(), _tableRightEdgeFrontTopRight.Y(),
			_tableRightEdgeFrontTopRight.Z());
		glTexCoord2f(1.0f, 0.0f);glVertex3d(_tableRightEdgeFrontBottomRight.X(), _tableRightEdgeFrontBottomRight.Y(),
			_tableRightEdgeFrontBottomRight.Z());
		glTexCoord2f(0.0f, 0.0f);glVertex3d(_tableRightEdgeFrontBottomLeft.X(), _tableRightEdgeFrontBottomLeft.Y(),
			_tableRightEdgeFrontBottomLeft.Z());
	glEnd();

	glBegin(GL_QUADS);
		// Back
		glNormal3f( 0.0f, 0.0f,-1.0f);					// Normal Pointing Away From Viewer
		glTexCoord2f(0.0f, 1.0f);glVertex3d(_tableRightEdgeBackTopLeft.X(), _tableRightEdgeBackTopLeft.Y(),
			_tableRightEdgeBackTopLeft.Z());
		glTexCoord2f(1.0f, 1.0f);glVertex3d(_tableRightEdgeBackTopRight.X(), _tableRightEdgeBackTopRight.Y(),
			_tableRightEdgeBackTopRight.Z());
		glTexCoord2f(1.0f, 0.0f);glVertex3d(_tableRightEdgeBackBottomRight.X(), _tableRightEdgeBackBottomRight.Y(),
			_tableRightEdgeBackBottomRight.Z());
		glTexCoord2f(0.0f, 0.0f);glVertex3d(_tableRightEdgeBackBottomLeft.X(), _tableRightEdgeBackBottomLeft.Y(),
			_tableRightEdgeBackBottomLeft.Z());
	glEnd();

	glBegin(GL_QUADS);
		// Left
		glNormal3f(-1.0f, 0.0f, 0.0f);					// Normal Pointing Left
		glTexCoord2f(0.0f, 1.0f);glVertex3d(_tableRightEdgeLeftTopLeft.X(), _tableRightEdgeLeftTopLeft.Y(),
			_tableRightEdgeLeftTopLeft.Z());
		glTexCoord2f(1.0f, 1.0f);glVertex3d(_tableRightEdgeLeftTopRight.X(), _tableRightEdgeLeftTopRight.Y(),
			_tableRightEdgeLeftTopRight.Z());
		glTexCoord2f(1.0f, 0.0f);glVertex3d(_tableRightEdgeLeftBottomRight.X(), _tableRightEdgeLeftBottomRight.Y(),
			_tableRightEdgeLeftBottomRight.Z());
		glTexCoord2f(0.0f, 0.0f);glVertex3d(_tableRightEdgeLeftBottomLeft.X(), _tableRightEdgeLeftBottomLeft.Y(),
			_tableRightEdgeLeftBottomLeft.Z());
	glEnd();

	glBegin(GL_QUADS);
		// Right
		glNormal3f( 1.0f, 0.0f, 0.0f);					// Normal Pointing Right
		glTexCoord2f(0.0f, 1.0f);glVertex3d(_tableRightEdgeRightTopLeft.X(), _tableRightEdgeRightTopLeft.Y(),
			_tableRightEdgeRightTopLeft.Z());
		glTexCoord2f(1.0f, 1.0f);glVertex3d(_tableRightEdgeRightTopRight.X(), _tableRightEdgeRightTopRight.Y(),
			_tableRightEdgeRightTopRight.Z());
		glTexCoord2f(1.0f, 0.0f);glVertex3d(_tableRightEdgeRightBottomRight.X(), _tableRightEdgeRightBottomRight.Y(),
			_tableRightEdgeRightBottomRight.Z());
		glTexCoord2f(0.0f, 0.0f);glVertex3d(_tableRightEdgeRightBottomLeft.X(), _tableRightEdgeRightBottomLeft.Y(),
			_tableRightEdgeRightBottomLeft.Z());
	glEnd();
}
// Draw the top edge of the table
void Table::DrawTopEdge(Texture texture[3]) const
{
	glBegin(GL_QUADS);
		GLfloat edgeColour[] = { 0.9f, 0.3f, 0.3f, 1.0f };
		GLfloat edgeSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, edgeColour);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, edgeSpecular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);
		glColor3d(0.9, 0.3, 0.3);
		// Top
		glNormal3f( 0.0f, 1.0f, 0.0f);					// Normal Pointing Up
		glTexCoord2f(0.0f, 1.0f);glVertex3d(_tableTopEdgeTopTopLeft.X(), _tableTopEdgeTopTopLeft.Y(), _tableTopEdgeTopTopLeft.Z());
		glTexCoord2f(1.0f, 1.0f);glVertex3d(_tableTopEdgeTopTopRight.X(), _tableTopEdgeTopTopRight.Y(),
			_tableTopEdgeTopTopRight.Z());
		glTexCoord2f(1.0f, 0.0f);glVertex3d(_tableTopEdgeTopBottomRight.X(), _tableTopEdgeTopBottomRight.Y(),
			_tableTopEdgeTopBottomRight.Z());
		glTexCoord2f(0.0f, 0.0f);glVertex3d(_tableTopEdgeTopBottomLeft.X(), _tableTopEdgeTopBottomLeft.Y(),
			_tableTopEdgeTopBottomLeft.Z());
	glEnd();

	glBegin(GL_QUADS);
		// Bottom
		glNormal3f( 0.0f,-1.0f, 0.0f);					// Normal Pointing Down
		glTexCoord2f(0.0f, 1.0f);glVertex3d(_tableTopEdgeBottomTopLeft.X(), _tableTopEdgeBottomTopLeft.Y(),
			_tableTopEdgeBottomTopLeft.Z());
		glTexCoord2f(1.0f, 1.0f);glVertex3d(_tableTopEdgeBottomTopRight.X(), _tableTopEdgeBottomTopRight.Y(),
			_tableTopEdgeBottomTopRight.Z());
		glTexCoord2f(1.0f, 0.0f);glVertex3d(_tableTopEdgeBottomBottomRight.X(), _tableTopEdgeBottomBottomRight.Y(),
			_tableTopEdgeBottomBottomRight.Z());
		glTexCoord2f(0.0f, 0.0f);glVertex3d(_tableTopEdgeBottomBottomLeft.X(), _tableTopEdgeBottomBottomLeft.Y(),
			_tableTopEdgeBottomBottomLeft.Z());
	glEnd();

	glBegin(GL_QUADS);
		// Front
		glNormal3f( 0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
		glTexCoord2f(0.0f, 1.0f);glVertex3d(_tableTopEdgeFrontTopLeft.X(), _tableTopEdgeFrontTopLeft.Y(),
			_tableTopEdgeFrontTopLeft.Z());
		glTexCoord2f(1.0f, 1.0f);glVertex3d(_tableTopEdgeFrontTopRight.X(), _tableTopEdgeFrontTopRight.Y(),
			_tableTopEdgeFrontTopRight.Z());
		glTexCoord2f(1.0f, 0.0f);glVertex3d(_tableTopEdgeFrontBottomRight.X(), _tableTopEdgeFrontBottomRight.Y(),
			_tableTopEdgeFrontBottomRight.Z());
		glTexCoord2f(0.0f, 0.0f);glVertex3d(_tableTopEdgeFrontBottomLeft.X(), _tableTopEdgeFrontBottomLeft.Y(),
			_tableTopEdgeFrontBottomLeft.Z());
	glEnd();

	glBegin(GL_QUADS);
		// Back
		glNormal3f( 0.0f, 0.0f,-1.0f);					// Normal Pointing Away From Viewer
		glTexCoord2f(0.0f, 1.0f);glVertex3d(_tableTopEdgeBackTopLeft.X(), _tableTopEdgeBackTopLeft.Y(),
			_tableTopEdgeBackTopLeft.Z());
		glTexCoord2f(1.0f, 1.0f);glVertex3d(_tableTopEdgeBackTopRight.X(), _tableTopEdgeBackTopRight.Y(),
			_tableTopEdgeBackTopRight.Z());
		glTexCoord2f(1.0f, 0.0f);glVertex3d(_tableTopEdgeBackBottomRight.X(), _tableTopEdgeBackBottomRight.Y(),
			_tableTopEdgeBackBottomRight.Z());
		glTexCoord2f(0.0f, 0.0f);glVertex3d(_tableTopEdgeBackBottomLeft.X(), _tableTopEdgeBackBottomLeft.Y(),
			_tableTopEdgeBackBottomLeft.Z());
	glEnd();

	glBegin(GL_QUADS);
		// Left
		glNormal3f(-1.0f, 0.0f, 0.0f);					// Normal Pointing Left
		glTexCoord2f(0.0f, 1.0f);glVertex3d(_tableTopEdgeLeftTopLeft.X(), _tableTopEdgeLeftTopLeft.Y(),
			_tableTopEdgeLeftTopLeft.Z());
		glTexCoord2f(1.0f, 1.0f);glVertex3d(_tableTopEdgeLeftTopRight.X(), _tableTopEdgeLeftTopRight.Y(),
			_tableTopEdgeLeftTopRight.Z());
		glTexCoord2f(1.0f, 0.0f);glVertex3d(_tableTopEdgeLeftBottomRight.X(), _tableTopEdgeLeftBottomRight.Y(),
			_tableTopEdgeLeftBottomRight.Z());
		glTexCoord2f(0.0f, 0.0f);glVertex3d(_tableTopEdgeLeftBottomLeft.X(), _tableTopEdgeLeftBottomLeft.Y(),
			_tableTopEdgeLeftBottomLeft.Z());
	glEnd();

	glBegin(GL_QUADS);
		// Right
		glNormal3f( 1.0f, 0.0f, 0.0f);					// Normal Pointing Right
		glTexCoord2f(0.0f, 1.0f);glVertex3d(_tableTopEdgeRightTopLeft.X(), _tableTopEdgeRightTopLeft.Y(),
			_tableTopEdgeRightTopLeft.Z());
		glTexCoord2f(1.0f, 1.0f);glVertex3d(_tableTopEdgeRightTopRight.X(), _tableTopEdgeRightTopRight.Y(),
			_tableTopEdgeRightTopRight.Z());
		glTexCoord2f(1.0f, 0.0f);glVertex3d(_tableTopEdgeRightBottomRight.X(), _tableTopEdgeRightBottomRight.Y(),
			_tableTopEdgeRightBottomRight.Z());
		glTexCoord2f(0.0f, 0.0f);glVertex3d(_tableTopEdgeRightBottomLeft.X(), _tableTopEdgeRightBottomLeft.Y(),
			_tableTopEdgeRightBottomLeft.Z());
	glEnd();
}

// Draw the throwing line/starting line across the table
void Table::DrawStartingLine() const
{
	glLineWidth(1.0);
	glBegin(GL_LINES);
	GLfloat lineColour[] = { 0.0f, 0.3f, 0.0f, 1.0f };
	GLfloat lineDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, lineColour);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lineDiffuse);
		glColor3d(0, 0.3, 0);
		glNormal3f( 0.0f, 1.0f, 0.0f);					// Normal Pointing Up
		glVertex3d(_startingLine.X(), _startingLine.Y(), _startingLine.Z());
		glVertex3d(_startingLine.X()+_playingSurfaceWidth, _startingLine.Y(), _startingLine.Z());
	glEnd();
}
// Draw the cirles/targets
void Table::DrawTarget(Texture texture[3]) const
{
	Vector3d colour;
	colour.SetVector(1, 0.3, 0.5);
	DrawCircle(_outerMostCircle, _outerMostCircleRadius, colour, texture);
	colour.SetVector(1, 1, 1);
	DrawCircle(_innerCircle, _innerCircleRadius, colour, texture);
	colour.SetVector(1, 0.3, 0);
	DrawCircle(_innerMostCircle, _innerMostCircleRadius, colour, texture);
}

// Draw a circle
void Table::DrawCircle(const Vector3d &circle, const int &radius, const Vector3d &colour, Texture texture[3]) const
{
	glBindTexture(GL_TEXTURE_2D, texture[2].texID);
	glBegin(GL_TRIANGLE_FAN);
		GLfloat circleColour[] = { colour.X(), colour.Y(), colour.Z(), 1.0f };
		GLfloat circleDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, circleColour);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, circleDiffuse);
		glColor3d(colour.X(), colour.Y(), colour.Z());
		glNormal3f( 0.0f, 1.0f, 0.0f);					// Normal Pointing Up
		glTexCoord2f(0.0f, 1.0f);glVertex3d(circle.X(), circle.Y(), circle.Z());
		for (int angle = 0; angle< 360; angle+=1)
		{
			glTexCoord2f(0.0f, 1.0f);
			glVertex3d(circle.X() + sinf(angle) * radius,
				circle.Y() + cosf(angle) * radius, circle.Z());
		}
	glEnd();
}
// Set up the lights
void Table::SetupLights() const
{
	GLfloat LightAmbient[]= { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f }; 	
	GLfloat LightSpecular[]= { 1.0f, 1.0f, 1.0f, 1.0f }; 	

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	float spotlight1Position[] = {600, 0, 2000, 1};
	float spotlight2Position[] = {600, 1275, 2000, 1};
	float spotlight3Position[] = {600, 2555, 2000, 1};
	float spotlight1Direction[] = {0, 0, -1};
	float spotlight2Direction[] = {0, 0, -1};
	float spotlight3Direction[] = {0, 0, -1};

	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR,LightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, spotlight1Position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotlight1Direction);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 30.0f);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF,45.0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR,LightSpecular);
	glLightfv(GL_LIGHT1, GL_POSITION, spotlight2Position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlight2Direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 30.0f);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF,45.0); 

	glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR,LightSpecular);
	glLightfv(GL_LIGHT2, GL_POSITION, spotlight3Position);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotlight3Direction);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 30.0f); 
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF,45.0); 


	float global_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glEnable(GL_NORMALIZE);
}
// For collision code
Vector3d Table::GetLeftEdgeRightSide() const
{
	return _tableLeftEdgeRightSide;
}
// For collision code
Vector3d Table::GetLeftEdgeRightSideNorm() const
{
	return _tableLeftEdgeRightSideNorm;
}
// For collision code
Vector3d Table::GetRightEdgeLeftSide() const
{
	return _tableRightEdgeLeftSide;
}
// For collision code
Vector3d Table::GetRightEdgeLeftSideNorm() const
{
	return _tableRightEdgeLeftSideNorm;
}
// For collision code
Vector3d Table::GetTopEdgeLeftSide() const
{
	return _tableTopEdgeLeftSide;
}
// For collision code
Vector3d Table::GetTopEdgeLeftSideNorm() const
{
	return _tableTopEdgeLeftSideNorm;
}
// For collision code
vector<Vector3d> Table::GetSides() const
{
	return _sides;
}

// For collision code
vector<Vector3d> Table::GetSidesNorm() const
{
	return _sidesNorm;
}

// Draw the throwing line
void Table::DrawThrowingLine(const int &length, const Vector3d &discPosition) const
{
	glLineWidth(3.0);
	glPushMatrix();
		glTranslated(discPosition.X(), 150, 0);
		glRotated(_angle,0,0,1);
		glBegin(GL_LINES);
			GLfloat lineColour[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			GLfloat lineDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, lineColour);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lineDiffuse);
			glColor3d(1, 1, 1);
			glNormal3f( 0.0f, 1.0f, 0.0f);					// Normal Pointing Up
			glVertex3d(0, 0, 0);
			glVertex3d(0, (length)*5, 0);
		glEnd();
	glPopMatrix();
}

// Increase the angle of the throwing line
void Table::IncreaseAngle()
{
	_angle -= 15.0;
	if (_angle == -90) // No point shooting at -90/90
	{
		_angle += 15.0;
	}
}

// Decrease the angle of the throwing line
void Table::DecreaseAngle()
{
	_angle += 15.0;
	if (_angle == 90) // No point shooting at -90/90
	{
		_angle -= 15.0;
	}
}
// Get the current throwing angle
double Table::GetThrowingAngle() const
{
	return _angle;
}

// Get the current disc to side elasticity
double Table::GetDiscToSideElasticity() const
{
	return _discToSideElasticity;
}

// Get the current surface friction
double Table::GetSurfaceFriction() const
{
	return _surfaceFriction;
}

// Get the current side friction
double Table::GetSideFriction() const
{
	return _sideFriction;
}

// Increase the current disc to side elasticity
void Table::IncreaseDiscToSideElasticity()
{
	_discToSideElasticity += 0.1;
	if (_discToSideElasticity > 1.0) // Over the limit
	{
		DecreaseDiscToSideElasticity();
	}
}

// Decrease the current disc to side elasticity
void Table::DecreaseDiscToSideElasticity()
{
	_discToSideElasticity -= 0.1;
	if (_discToSideElasticity < 0.1) // Out of bounds
	{
		IncreaseDiscToSideElasticity();
	}
}

// Increase the current surface friction
void Table::IncreaseSurfaceFriction()
{
	_surfaceFriction += 0.1;
	if (_surfaceFriction > 0.5)
	{
		_surfaceFriction = 0.5;
	}
}

// Decrease the current surface friction
void Table::DecreaseSurfaceFriction()
{
	_surfaceFriction -= 0.1;
	if (_surfaceFriction < 0.1) // Make sure there is always some friction
	{
		IncreaseSurfaceFriction();
	}
}

// Increase the current side friction
void Table::IncreaseSideFriction()
{
	_sideFriction += 0.1;
}

// Decrease the current side friction
void Table::DecreaseSideFriction()
{
	_sideFriction -= 0.1;
	if (_sideFriction < 0.1) // Make sure there is always some friction
	{
		IncreaseSideFriction();
	}
}
// Get the targets centres - 0 been the largest 2 the smallest
vector<Vector3d> Table::GetTargetsCentres() const
{
	vector<Vector3d> result;
	result.push_back(_outerMostCircle);
	result.push_back(_innerCircle);
	result.push_back(_innerMostCircle);
	return result;
}
// Get the targets radii - 0 been the largest, 2 the smallest
vector<int> Table::GetTargetRadii() const
{
	vector<int> result;
	result.push_back(_outerMostCircleRadius);
	result.push_back(_innerCircleRadius);
	result.push_back(_innerMostCircleRadius);
	return result;
}
void Table::renderBitmapString(float x, float y, void *font,const char *string) const
{

	const char *c = string;
	glRasterPos2f(x, y);
	for (; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}  /* end renderBitmapString() */
// Print the relevant friction info
void Table::PrintFrictionInfo() const
{
	char frictionString[500];
	glColor3d(1,1,1);
	sprintf_s(frictionString, "Table Surface Friction: %0.2f",
		_surfaceFriction);
	renderBitmapString(-1500,1500, GLUT_BITMAP_HELVETICA_12, frictionString);
	sprintf_s(frictionString, "Table Side Friction: %0.2f",
		_sideFriction);
	renderBitmapString(-1500,1400, GLUT_BITMAP_HELVETICA_12, frictionString);
	sprintf_s(frictionString, "Table Disc Elasticity: %0.2f",
		_discToSideElasticity);
	renderBitmapString(-1500,1300, GLUT_BITMAP_HELVETICA_12, frictionString);
	sprintf_s(frictionString, "Press 't' to toggle obstructions on/off.");
	glColor3d(1,0,1);
	renderBitmapString(-1500,1200, GLUT_BITMAP_HELVETICA_12, frictionString);
}