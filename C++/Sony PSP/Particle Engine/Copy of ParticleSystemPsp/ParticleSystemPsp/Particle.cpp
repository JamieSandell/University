#include "Vector3d.h"
#include "Particle.h"

Particle::Particle(void)
{
	// Add appropriate initial values here
	_alive = true;
	_colour = Vector3d(1.0f, 0.0f, 1.0f);
	_fade = float(rand()%100)/1000.0f+0.003f;	// Later allow the user to specify random range, +0.003
	// ensures the fade value is never 0, if it was 0 the particle would never die.
	_life = 1.0f; // 1.0 = full life
	_position = Vector3d(0,0,0);
	_speed = Vector3d(30.0, 30.0, 30.0); // (X,Y,Z axis)The next three variables are important. These three variables
	// control how fast a particle is moving on specific axis, and what direction to move. If xi is a 
	// negative value our particle will move left. Positive it will move right. If yi is negative our 
	// particle will move down. Positive it will move up. Finally, if zi is negative the particle will move
	// into the screen, and positive it will move towards the viewer.
	_gravity = Vector3d(-100.0, 1.0, -0.5); //  (X,Y,Z axis) If xg is a positive value, our particle will pull to the 
	// right. If it's negative our particle will be pulled to the left. So if our particle is moving left 
	// (negative) and we apply a positive gravity, the speed will eventually slow so much that our particle
	// will start moving the opposite direction. yg pulls up or down and zg pulls towards or away from the 
	// viewer. 
}

Particle::~Particle(void)
{
}

Particle::Particle(const bool &aliveStatus, const Vector3d &colour, const float &fade, const float &life,
				   const Vector3d &position, const Vector3d &speed)
{
	_alive = aliveStatus;
	_colour = colour;
	_fade = fade;
	_life = life;
	_position = position;
	_speed = speed;
}

void Particle::Draw(Texture texture[3]) const
//void Particle::Draw(void) const
{
	glBindTexture(GL_TEXTURE_2D, texture[1].texID);


	// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
	glColor4f(_colour.X(), _colour.Y(), _colour.Z(), _life);


	GLfloat circleColour[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	GLfloat circleDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, circleColour);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, circleDiffuse);
		//glColor4f(_colour.X(), _colour.Y(), _colour.Z(), _life);
		glColor4f(1.0, 0.3, 0.0, _life);
		//glNormal3f( 0.0f, 1.0f, 0.0f);					// Normal Pointing Up
		glTexCoord2f(1.0,1.0f); glVertex3f(_position.X()+5.0f,_position.Y()+1.8f,_position.Z()); // Top Right
		glTexCoord2f(0.0,1.0f); glVertex3f(_position.X()-1.8f,_position.Y()+1.8f,_position.Z()); // Top Left
		glTexCoord2f(1.0,0.0f); glVertex3f(_position.X()+5.0f,_position.Y()-1.8f,_position.Z()); // Bottom Right
		glTexCoord2f(0.0,0.0f); glVertex3f(_position.X()-1.8f,_position.Y()-1.8f,_position.Z()); // Bottom Left


}

void Particle::Update(void)
{
	// Incorporate the Timer (dt) class

	// Now we can move the particle. The math below may look strange, but once again, it's pretty simple. 
	// First we take the current particle x position. Then we add the x movement value to the particle 
	// divided by slowdown times 1000. So if our particle was in the center of the screen on the x axis 
	// (0), our movement variable (xi) for the x axis was +10 (moving us to the right) and slowdown was 
	// equal to 1, we would be moving to the right by 10/(1*1000), or 0.01f. If we increase the slowdown to
	// 2 we'll only be moving at 0.005f. Hopefully that helps you understand how slowdown works. That's 
	// also why multiplying the start values by 10.0f made the pixels move alot faster, creating an 
	// explosion. We use the same formula for the y and z axis to move the particle around on the screen.

	//Smaller the slowdown variable is the faster the particles move
	_position.SetVectorX(_position.X()+_speed.X()/(1.0*1000)); // Change 1 to slowdown variable, Move On The X Axis By X Speed
	_position.SetVectorY(_position.Y()+_speed.Y()/(1.0*1000)); // Change 1 to slowdown variable, Move On The Y Axis By Y Speed
	_position.SetVectorZ(_position.Z()+_speed.Z()/(1.0*1000)); // Change 1 to slowdown variable, Move On The Z Axis By Z Speed

	/*
		After we've calculated where to move the particle to next, we have to apply gravity or resistance. 
		In the first line below, we do this by adding our resistance (xg) to the speed we are moving at 
		(xi). Lets say our moving speed was 10 and our resistance was 1. Each time our particle was drawn 
		resistance would act on it. So the second time it was drawn, resistance would act, and our moving 
		speed would drop from 10 to 9. This causes the particle to slow down a bit. The third time the 
		particle is drawn, resistance would act again, and our moving speed would drop to 8. If the 
		particle burns for more than 10 redraws, it will eventually end up moving the opposite direction 
		because the moving speed would become a negative value. The resistance is applied to the y and z 
		moving speed the same way it's applied to the x moving speed. 
	*/

	//particle[loop].xi+=particle[loop].xg;			// Take Pull On X Axis Into Account
	//particle[loop].yi+=particle[loop].yg;			// Take Pull On Y Axis Into Account
	//particle[loop].zi+=particle[loop].zg;			// Take Pull On Z Axis Into Account

	_speed.SetVectorX(_speed.X()+_gravity.X());
	_speed.SetVectorY(_speed.Y()+_gravity.Y());
	_speed.SetVectorZ(_speed.Z()+_gravity.Z());

	_life-=_fade; // decrease the life of the particle (fade out)
	//_life=1.0f;

	 //Still alive?
	if (_life<0.0f)
	{
		int xspeed = 0; // testing purposes
		int yspeed = 0; // testing purposes
		int low = 0; // needs to be outside if statement
		int high = 10;

		// dead, so bring it back to life
		_life = 1.0f;
		_fade = float(rand()%100)/10000.0f+0.003f; // Allow user to select fade value
		// if user wants a random fade value allow the min/max range to be set.

		// reset position of the particle, this should be the initial place of the particle
		// (rand() % (high - low + 1) + low)
		_position.SetVector(rand () % (high - low + 1) + low, 0.0f, 0.0f);

		// reset speed and direction, user should select whether random and min/max range
		_speed.SetVector(xspeed+float(rand () % (60) - 32.0f),
			yspeed+float(rand () % (60) - 30.0f),float((rand()%60)-30.0f)); // need to add in speed variable

		// Assign a new colour - later allow if the user wants the colour to change
		_colour.SetVector(rand()/(float(RAND_MAX)+1), rand()/(float(RAND_MAX)+1), rand()/(float(RAND_MAX)+1));
	}

}

bool Particle::GetAliveStatus() const
{
	return _alive;
}

Vector3d Particle::GetColour() const
{
	return _colour;
}

float Particle::GetFade() const
{
	return _fade;
}

float Particle::GetLife() const
{
	return _life;
}

Vector3d Particle::GetPosition() const
{
	return _position;
}

Vector3d Particle::GetSpeed() const
{
	return _speed;
}

Vector3d Particle::GetGravity() const
{
	return _gravity;
}

void Particle::SetAliveStatus(const bool &status)
{
	_alive = status;
}

void Particle::SetColour(const Vector3d &colour)
{
	_colour = colour;
}

void Particle::SetFade(const float &fade)
{
	_fade = fade;
}

void Particle::SetLife(const float &life)
{
	_life = life;
}

void Particle::SetPosition(const Vector3d &position)
{
	_position = position;
}

void Particle::SetSpeed(const Vector3d &speed)
{
	_speed = speed;
}

void Particle::SetGravity(const Vector3d &gravity)
{
	_gravity = gravity;
}