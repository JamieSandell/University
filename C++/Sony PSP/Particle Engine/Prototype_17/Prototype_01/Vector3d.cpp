#include "Vector3d.h"

Vector3d::Vector3d(void)
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3d::~Vector3d(void)
{
}

Vector3d::Vector3d(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3d Vector3d::add(const Vector3d& v) const
{
	return Vector3d(x+v.X(), y+v.Y(), z+v.Z());
}

Vector3d Vector3d::subtract(const Vector3d &v) const
{
	return Vector3d(x - v.X(), y - v.Y(), z - v.Z());
}

double Vector3d::dotProduct(const Vector3d &v) const
{
	return v.X()*x + v.Y()*y + v.Z() * z;
}

double Vector3d::CalculateMagnitude() const
{
	return sqrt(x*x + y*y + z*z);
}

Vector3d Vector3d::Normalise() const
{
	return Vector3d(x/CalculateMagnitude(), y/CalculateMagnitude(), z/CalculateMagnitude());
}

Vector3d Vector3d::crossProduct(const Vector3d &v) const
{
	return Vector3d(v.Y()*z-v.Z()*y, v.Z()*x-v.X()*z, v.X()*y-v.Y()*x);
}

Vector3d Vector3d::ScalarMultiplication(const double &ScalarFactor) const
{
	return Vector3d(x*ScalarFactor, y*ScalarFactor, z*ScalarFactor);
}

double Vector3d::X() const
{
    return x;
}

double Vector3d::Y() const
{
    return y;
}

double Vector3d::Z() const
{
    return z;
}

void Vector3d::SetVector(const double &newX, const double &newY, const double &newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}

void Vector3d::SetVectorX(const double &newX)
{
	x = newX;
}

void Vector3d::SetVectorY(const double &newY)
{
	y = newY;
}

void Vector3d::SetVectorZ(const double &newZ)
{
	z = newZ;
}

Vector3d Vector3d::operator *(const double &input) const
{
	return ScalarMultiplication(input);
}

Vector3d Vector3d::operator *(const Vector3d &input) const
{
	Vector3d result(this->X() * input.X(), this->Y() * input.Y(), this->Z() * input.Z());
	return result;
}

Vector3d Vector3d::operator -(const Vector3d &input) const
{
	Vector3d result(this->x-input.x, this->y-input.y, this->z-input.z);
	return result;
}

Vector3d Vector3d::operator +(const Vector3d &input) const
{
	Vector3d result(this->x+input.x, this->y+input.y, 0);
	return result;
}

void Vector3d::operator =(const Vector3d &input)
{
	this->SetVector(input.x, input.y, input.z);
}