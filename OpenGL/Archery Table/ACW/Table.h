#pragma once
#include <cmath>
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glut.h>		// Header File For The Glaux Library
#include <vector>
#include "Vector3d.h"
#include "Matrix33d.h"
#include "Texture.h"

using namespace std;

/*
2. The archery table has an overall size of 2550 mm long and 1300 mm wide (see figure 1). The table has a
	pale-green playing surface of 2500 mm long and 1200 mm wide (see figure 1). There are 3 sides to the
	table and these sides are brown in colour and are 50 mm wide and 50 mm high. There is a dark-green
	throwing line that runs across the bottom of the table that is 150 mm from the bottom of the table
	(see figure 1).
3. There is a target painted onto the table surface which consists of 3 circles. The centre of all 3
	circles is a point at 600 mm away from the top and both sides of the table (see figure 1). The outer
	circle is coloured pink and is 800 mm in diameter. The middle circle is coloured white and is 500 mm
	in diameter. The inner circle is coloured orange and is 200 mm in diameter.
*/

class Table
{
public:
	Table(void);
	~Table(void);

	void DrawTable(Texture texture[3]) const;
	void DrawSurface(Texture texture[3]) const;
	void DrawLeftEdge(Texture texture[3]) const;
	void DrawRightEdge(Texture texture[3]) const;
	void DrawTopEdge(Texture texture[3]) const;
	void DrawStartingLine() const;
	void DrawTarget(Texture texture[3]) const;
	void DrawCircle(const Vector3d &circle, const int &radius, const Vector3d &colour, Texture texture[3]) const;
	void SetupLights() const;
	void DrawThrowingLine(const int &length, const Vector3d &discPosition) const;
	void IncreaseAngle();
	void DecreaseAngle();
	void IncreaseSurfaceFriction();
	void DecreaseSurfaceFriction();
	void IncreaseSideFriction();
	void DecreaseSideFriction();
	void IncreaseDiscToSideElasticity();
	void DecreaseDiscToSideElasticity();
	void renderBitmapString(float x, float y, void *font,const char *string) const;
	void PrintFrictionInfo() const;

	double GetThrowingAngle() const;
	double GetSurfaceFriction() const;
	double GetSideFriction() const;
	double GetDiscToSideElasticity() const;

	Vector3d GetTableCentre() const; // For use as a camera
	Vector3d GetLeftEdgeRightSide() const; // For collision code
	Vector3d GetLeftEdgeRightSideNorm() const; // For collision code
	Vector3d GetRightEdgeLeftSide() const; // For collision code
	Vector3d GetRightEdgeLeftSideNorm() const; // For collision code
	Vector3d GetTopEdgeLeftSide() const; // For collision code
	Vector3d GetTopEdgeLeftSideNorm() const; // For collision code

	vector<Vector3d> GetSides() const; // For collision code
	vector<Vector3d> GetSidesNorm() const; // For collision code
	vector<Vector3d> GetTargetsCentres() const;

	vector<int> GetTargetRadii() const;

private:

	/////// Friction
	double _surfaceFriction;
	double _sideFriction;
	double _discToSideElasticity;
	/////// Friction

	/////// Throwing Line
	double _angle;
	/////// Throwing Line

	/////// Circles
	// Outermost circle
	Vector3d _outerMostCircle;
	double _outerMostCircleRadius;
	// Inner circle
	Vector3d _innerCircle;
	double _innerCircleRadius;
	// Innermost circle
	Vector3d _innerMostCircle;
	double _innerMostCircleRadius;
	/////// Circles

	/////// Starting Line
	Vector3d _startingLine;
	/////// Starting Line

	/////// Playing Surface
	int _playingSurfaceLength, _playingSurfaceWidth, _playingSurfaceHeight;
	Vector3d _playingSurfaceTopLeft;
	Vector3d _playingSurfaceTopRight;
	Vector3d _playingSurfaceBottomRight;
	Vector3d _playingSurfaceBottomLeft;
	//////// Playing Surface

	//////// Top Edge
	int _tableTopEdgeLength, _tableTopEdgeWidth, _tableTopEdgeHeight;
	Vector3d _tableTopEdgeFrontTopLeft;
	Vector3d _tableTopEdgeFrontTopRight;
	Vector3d _tableTopEdgeFrontBottomRight;
	Vector3d _tableTopEdgeFrontBottomLeft;
	Vector3d _tableTopEdgeBackTopLeft;
	Vector3d _tableTopEdgeBackTopRight;
	Vector3d _tableTopEdgeBackBottomRight;
	Vector3d _tableTopEdgeBackBottomLeft;
	Vector3d _tableTopEdgeLeftTopLeft;
	Vector3d _tableTopEdgeLeftTopRight;
	Vector3d _tableTopEdgeLeftBottomRight;
	Vector3d _tableTopEdgeLeftBottomLeft;
	Vector3d _tableTopEdgeRightTopLeft;
	Vector3d _tableTopEdgeRightTopRight;
	Vector3d _tableTopEdgeRightBottomRight;
	Vector3d _tableTopEdgeRightBottomLeft;
	Vector3d _tableTopEdgeTopTopLeft;
	Vector3d _tableTopEdgeTopTopRight;
	Vector3d _tableTopEdgeTopBottomRight;
	Vector3d _tableTopEdgeTopBottomLeft;
	Vector3d _tableTopEdgeBottomTopLeft;
	Vector3d _tableTopEdgeBottomTopRight;
	Vector3d _tableTopEdgeBottomBottomRight;
	Vector3d _tableTopEdgeBottomBottomLeft;
	Vector3d _tableTopEdgeLeftSide; // For collision code
	Vector3d _tableTopEdgeLeftSideNorm; // For collision code
	//////// Top Edge

	//////// Left Edge
	int _tableLeftEdgeLength, _tableLeftEdgeWidth, _tableLeftEdgeHeight;
	Vector3d _tableLeftEdgeFrontTopLeft;
	Vector3d _tableLeftEdgeFrontTopRight;
	Vector3d _tableLeftEdgeFrontBottomRight;
	Vector3d _tableLeftEdgeFrontBottomLeft;
	Vector3d _tableLeftEdgeBackTopLeft;
	Vector3d _tableLeftEdgeBackTopRight;
	Vector3d _tableLeftEdgeBackBottomRight;
	Vector3d _tableLeftEdgeBackBottomLeft;
	Vector3d _tableLeftEdgeTopTopLeft;
	Vector3d _tableLeftEdgeTopTopRight;
	Vector3d _tableLeftEdgeTopBottomRight;
	Vector3d _tableLeftEdgeTopBottomLeft;
	Vector3d _tableLeftEdgeBottomTopLeft;
	Vector3d _tableLeftEdgeBottomTopRight;
	Vector3d _tableLeftEdgeBottomBottomRight;
	Vector3d _tableLeftEdgeBottomBottomLeft;
	Vector3d _tableLeftEdgeLeftTopLeft;
	Vector3d _tableLeftEdgeLeftTopRight;
	Vector3d _tableLeftEdgeLeftBottomRight;
	Vector3d _tableLeftEdgeLeftBottomLeft;
	Vector3d _tableLeftEdgeRightTopLeft;
	Vector3d _tableLeftEdgeRightTopRight;
	Vector3d _tableLeftEdgeRightBottomRight;
	Vector3d _tableLeftEdgeRightBottomLeft;
	Vector3d _tableLeftEdgeRightSide; // For collision code
	Vector3d _tableLeftEdgeRightSideNorm; // For collision code
	//////// Left Edge

	//////// Right Edge
	int _tableRightEdgeLength, _tableRightEdgeWidth, _tableRightEdgeHeight;
	Vector3d _tableRightEdgeFrontTopLeft;
	Vector3d _tableRightEdgeFrontTopRight;
	Vector3d _tableRightEdgeFrontBottomRight;
	Vector3d _tableRightEdgeFrontBottomLeft;
	Vector3d _tableRightEdgeBackTopLeft;
	Vector3d _tableRightEdgeBackTopRight;
	Vector3d _tableRightEdgeBackBottomRight;
	Vector3d _tableRightEdgeBackBottomLeft;
	Vector3d _tableRightEdgeLeftTopLeft;
	Vector3d _tableRightEdgeLeftTopRight;
	Vector3d _tableRightEdgeLeftBottomRight;
	Vector3d _tableRightEdgeLeftBottomLeft;
	Vector3d _tableRightEdgeRightTopLeft;
	Vector3d _tableRightEdgeRightTopRight;
	Vector3d _tableRightEdgeRightBottomRight;
	Vector3d _tableRightEdgeRightBottomLeft;
	Vector3d _tableRightEdgeTopTopLeft;
	Vector3d _tableRightEdgeTopTopRight;
	Vector3d _tableRightEdgeTopBottomRight;
	Vector3d _tableRightEdgeTopBottomLeft;
	Vector3d _tableRightEdgeBottomTopLeft;
	Vector3d _tableRightEdgeBottomTopRight;
	Vector3d _tableRightEdgeBottomBottomRight;
	Vector3d _tableRightEdgeBottomBottomLeft;
	Vector3d _tableRightEdgeLeftSide; // For collision code
	Vector3d _tableRightEdgeLeftSideNorm; // For collision code
	//////// Right Edge

	// For collision code
	vector<Vector3d> _sides;
	vector<Vector3d> _sidesNorm;
	// For collision code
};
