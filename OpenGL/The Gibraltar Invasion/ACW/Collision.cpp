#include <cmath>
#include "Collision.h"

Collision::Collision(void)
{
}

Collision::~Collision(void)
{
}

bool Collision::WasThereACollision(const Ball &inBall, const Ship &inShip) const
{
	float xPoint = inBall.GetXPos() - (inShip.GetXPos()+inShip.GetXPos()) / 2;
	float yPoint = inBall.GetYPos() - inShip.GetYPos();
	float distance = sqrtf(xPoint*xPoint + yPoint*yPoint); // sqrt is expensive
	float combinedRadius = (inShip.GetWidth() / 2) + inBall.GetRadius();

	if (distance <= combinedRadius)
	{
		return true;
	}

	return false;
}
