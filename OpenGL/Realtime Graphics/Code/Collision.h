#pragma once

#include "MySphere.h"
#include "Cube.h"
#include "Vector4f.h"

class Collision{
public:
	Collision();
	~Collision();

	bool QuadPlanesOfACubeCollision(const Vector4f &quadCentre, float quadSize, const Shape* cube, float &outDistance)const;//tests whether a quad has collided with any of the 6 planes of a cube. Calls QuadPlaneCollision()
	bool QuadPlaneCollision(const Vector4f &quadCentre, float quadSize, const Vector4f &planePosition, const Vector3f &planeNormal,
		float &outDistance)const;
	bool ParticleCubeCollision(const Vector4f &particleCentre, float particleSize, const Shape *cube, int &planeHit)const;

private:
};