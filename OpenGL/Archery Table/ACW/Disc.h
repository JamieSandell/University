#pragma once
#include "Vector3d.h"
#include "Texture.h"
#include <windows.h>		// Header File For Windows
#include <stdio.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glut.h>		// Header File For The Glaux Library

/*
5. Each player has 6 disks. Player 1 has red disks and Player 2 has blue disks. Initially the disks are
placed at the bottom of the table and towards opposite sides of the table (see figure 1). Each playing 
disk is 50 mm in diameter, 10 mm in height, and weights 0.02 kg. The disks always move along the
surface of the table and so they never leave the table top surface.
*/

class Disc
{
public:
	Disc();
	~Disc(void);

	void DrawDisc(Texture texture[3]) const;
	void SetPosition(const int position[]);
	void SetColour(const double colour[]);
	void MoveDisc(const int &xPos, const int &yPos);
	void Update(const float &dt, const double &angle, const int &force, const double &surfaceFriction,
		const double &sideFriction);
	void FireDisc();
	void SetVelocityVector(Vector3d vector);
	void SetCollisionNormal (Vector3d vector);
	void SetFiredStatus (const bool &status);
	void ResetDiscPosition();
	void SetDiscHeight(const double &input);
	void MoveDiscLeft();
	void MoveDiscRight();
	void SetMovedToStartStatus(const bool &input);

	Vector3d GetDiscPosition() const;
	Vector3d GetVelocityVector() const;
	Vector3d GetCollisionNormal() const;

	int GetRadius() const;

	bool GetFiredStatus() const;
	bool GetMovedToStartStatus() const;

	double GetMass() const;
	double GetYVelocity() const;

private:
	Vector3d _centre; // Centre of the disc
	Vector3d _colour;
	double _radius;
	double _height;
	double _weight;
	double _vFX; // Velocity Friction Reduction on the Xpos.
	double _vFY;
	int _distanceMovedX;
	int _distanceMovedY;
	int xPos;
	int yPos;
	bool _fired;
	bool _justFired;
	bool _movedToStart;
	Vector3d _velocity;
	Vector3d _collisionNormal;
	Vector3d _originalPosition;
	GLUquadric* quadric; // Storage For a Quadric Object
};
