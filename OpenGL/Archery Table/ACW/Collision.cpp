#include <cmath>
#include "Collision.h"

Collision::Collision(void)
{
}

Collision::~Collision(void)
{
}

bool Collision::SphereSphereCollision(const Vector3d &sphere1, const Vector3d &sphere2, const int &radius1,
									  const int &radius2) const
{
	// No need for Z checking since the spheres cannot leave the table

	// Sqrt too expensive
	if (((radius1 + radius2)*(radius1 + radius2)) >=
		((sphere2.X()-sphere1.X())*(sphere2.X()-sphere1.X())) + 
		((sphere2.Y()-sphere1.Y())*(sphere2.Y()-sphere1.Y())))
	{
		return true; // Collision
	}

	return false; // No collision
}

bool Collision::SpherePlaneCollision(const Vector3d &sphere1, const int &radius, const vector<Vector3d> &edge, 
									 const vector<Vector3d> &edgeNorm, const int &whichDisc,
									 Vector3d &normHit) const
{
	double distance;

	for (int i = 0; i < edge.size(); i++)
	{
		distance = edge[i].dotProduct(edgeNorm[i]); // Check for collision against each edge
		distance = sphere1.dotProduct(edgeNorm[i]) - distance;
		if (abs(distance) < radius) // Outside is touching
		{
			normHit.SetVector(edgeNorm[i].X(), edgeNorm[i].Y(), edgeNorm[i].Z());
			return true; // Collision
		}

		if (abs(distance) <= 0) // Moved too fast and it's now intersecting at 2 points
		{
			return true; // Collision
		}
	}
	return false; // No collision
}
int Collision::SphereTargetCollision(const Vector3d &sphere1, const std::vector<Vector3d> &targets,
									 const int &radius1, const std::vector<int> &targetRadii) const
{
	// No need for Z checking since the spheres cannot leave the table

	int result;
	result = -1; // no collision
	for (int i = 0; i < targets.size(); i++)
	{
		// Sqrt too expensive
		if (((radius1 + targetRadii[i])*(radius1 + targetRadii[i])) >=
			((targets[i].X()-sphere1.X())*(targets[i].X()-sphere1.X())) + 
			((targets[i].Y()-sphere1.Y())*(targets[i].Y()-sphere1.Y())))
		{
			result =  i; // Collision
		}
	}

	return result; // No collision
}