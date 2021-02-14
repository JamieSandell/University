#pragma once

#include <cmath>
#include "GXBase.h"

class Vector3f {
	//friend Vector3f operator+(const Vector3f &lhs, const Vector3f &rhs);
private:
	GLfloat _xyz[3];

public:
	// TODO: Add efficient operators
	void Assign(GLfloat x, GLfloat y, GLfloat z);
	void Assign(GLfloat xyz[]);
	void AssignX(GLfloat x);
	void AssignY(GLfloat y);
	void AssignZ(GLfloat z);

	Vector3f();
	~Vector3f();

	Vector3f(GLfloat x, GLfloat y, GLfloat z);

	Vector3f(GLfloat xyz[]);

	Vector3f Add(const Vector3f &rhs) const;

	Vector3f CalculateFaceNormals(const Vector3f &vec1, const Vector3f &vec2, const Vector3f &vec3) const;

	Vector3f CrossProduct(const  Vector3f &vec1, const Vector3f &vec2) const;

	Vector3f& Divide(const int &number, Vector3f &result) const;
	Vector3f Divide(int number) const;

	float DotProduct(const Vector3f &rhs)const;

	Vector3f Multiply(const Vector3f &rhs)const;
	Vector3f Multiply(float rhs)const;
	Vector3f Multiply(const float lhs, const Vector3f &rhs);

	Vector3f Subtract(const Vector3f &leftVector, const Vector3f &rightVector) const;

	Vector3f Subtract(const Vector3f &v) const;

	float CalculateMagnitude() const;

	Vector3f Normalise() const;

	Vector3f DirectionVectorBetweenTwoPoints(Vector3f source, Vector3f destination) const;

	const GLfloat* xyz() const;

	GLfloat x() const;

	GLfloat y() const;

	GLfloat z() const;

	const float& operator[](int i) const;

	float& operator[](int i);

	Vector3f operator+(const Vector3f &rhs) const;

	Vector3f operator+=(const Vector3f &rhs) const;

	Vector3f operator/(const int &rhs) const;
	Vector3f operator*(const Vector3f &rhs) const;
	Vector3f operator*(const float &rhs) const;
};
Vector3f operator *(const float lhs, const Vector3f &rhs);