#pragma once
#include "Vector3d.h"

class Collision
{
public:
	Collision(void);
	bool SphereSphereCollision(const Vector3d &sphere1, const Vector3d &sphere2, const int &radius1,
		const int &radius2) const;
	bool SpherePlaneCollision(const Vector3d &sphere1, const int &radius, const vector<Vector3d> &edge, 
		const vector<Vector3d> &edgeNorm, const int &whichDisc, Vector3d &normHit) const;
	int SphereTargetCollision(const Vector3d &sphere1, const std::vector<Vector3d> &targets,
		const int &radius1, const std::vector<int> &targetRadii) const;
public:
	~Collision(void);
};
