#pragma  once

#include <vector>
#include "Vector3f.h"
#include "Vector4f.h"

class Animation{
public:
	Animation();//Use Create as a default constructor
	~Animation();

	bool Create(void);//Set the default animation coefficients
	bool Create(const Vector3f &aI, const Vector3f &bI, const Vector3f &cI, const Vector3f &dI);//Set the animation coefficients
	void Animate(Vector3f &objectPosition, const float deltaTime);// changes the passed in position
	void Animate(Vector4f &objectPosition, float deltaTime, float timeElapsed);//changes the passed in position
	void Assign(const Vector3f &aI, const Vector3f &bI, const Vector3f &cI, const Vector3f &dI);
	void Assign(const std::vector<Vector3f> &coefficients); // must have 4 Vector3fs in the vector
	void Assign(const Vector3f coefficients[]);//must have 4 Vector3fs in the array
	Vector3f GetDirectionVector(void)const;
	void SetDirectionVector(const Vector3f &directionVector);

private:
	Vector3f _aI, _bI, _cI, _dI, _directionVector;
};