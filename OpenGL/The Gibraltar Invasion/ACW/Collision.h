#pragma once
#include "Ball.h"
#include "Ship.h"

class Collision
{
public:
	Collision(void);
	bool WasThereACollision(const Ball &inBall, const Ship &inShip) const;
public:
	~Collision(void);
};
