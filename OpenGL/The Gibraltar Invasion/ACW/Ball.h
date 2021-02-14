#pragma once
#include "NewtonianObject.h"
#include "Cannon.h"
#include "Timer.h"

class Ball : NewtonianObject
{
public:
	Ball(void);
	~Ball(void);

	void Draw(const float &_angle, const int &_height, const int &_width) const;
	void SetPos(const float &x, const float &y);
	void SetRadius(const float &radius);
	void SetColour(const float &red, const float &green, const float &blue);
	void SetVelocity(const float &xVelocity, const float &yVelocity);
	void ChangeFirstCreationFlag();
	void SetAliveStatus(const bool &status);

	virtual void UpdatePos(const float &dt, const Cannon &cannon, const int &screenBoundaryX, const int &screenBoundaryY);

	void GetVelocity(float &xVelocity, float &yVelocity) const;
	float GetXPos(void) const;
	float GetYPos(void) const;
	float GetRadius(void) const;
	const float* GetColour(void) const;

	bool GetAliveStatus(void) const;

private:
	float _xPos, _yPos, _initialXPos, _initialYPos, _yPosSpeed, _radius;
	float _colour[3];
	float _initialXVelocity, _initialYVelocity, _xVelocity, _yVelocity, _gravityVelocity;
	bool  _firstCreation, _ballStillAlive;
	Timer _ballTimer;
};
