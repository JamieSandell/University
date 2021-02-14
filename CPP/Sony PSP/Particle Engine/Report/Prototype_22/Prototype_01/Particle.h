#pragma once
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glut.h>		// Header File For The Glaux Library
#include "Texture.h"

class Particle
{
public:
	Particle(void);
	~Particle(void);

	Particle(const bool &aliveStatus, const Vector3d &colour, const float &fade, const float &life,
		const Vector3d &position, const Vector3d &speed);

	void Draw(Texture texture[3]) const;
	//void Draw(void) const;
	void Update (void);

	// Setters
	void SetAliveStatus(const bool &status);
	void SetLife(const float &life);
	void SetFade(const float &fade);
	void SetColour(const Vector3d &colour);
	void SetPosition(const Vector3d &position);
	void SetSpeed(const Vector3d &speed);
	void SetGravity(const Vector3d &gravity);

	// Getters
	bool GetAliveStatus(void) const;
	float GetLife(void) const;
	float GetFade(void) const;
	Vector3d GetColour(void) const;
	Vector3d GetPosition(void) const;
	Vector3d GetSpeed(void) const;
	Vector3d GetGravity(void) const;

private:
	bool _alive; // Is the particle alive, if it isn't don't draw it.
	float _life; // life is the brightness of the particle and is governed by fade
	float _fade; // life decreases by the value in this variable
	Vector3d _colour; // The (r,g,b) colour of the particle
	Vector3d _position; // x,y,z of the particle
	Vector3d _speed; // speed (direction) of the particle on each axes (x,y,z)
	/*
		The next three variables are important. These three variables control how fast a particle is moving
		on specific axis, and what direction to move. If xi is a negative value our particle will move left.
		Positive it will move right. If yi is negative our particle will move down. Positive it will move 
		up. Finally, if zi is negative the particle will move into the screen, and postive it will move 
		towards the viewer. 
	*/
	Vector3d _gravity; // Gravity on each of the axes.
	/*
	 Each of these variables can be thought of as gravity. If xg is a positive value, our particle will 
	 pull to the right. If it's negative our particle will be pulled to the left. So if our particle is 
	 moving left (negative) and we apply a positive gravity, the speed will eventually slow so much that 
	 our particle will start moving the opposite direction. yg pulls up or down and zg pulls towards or 
	 away from the viewer. 
	*/

};
