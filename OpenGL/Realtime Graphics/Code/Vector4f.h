#pragma once

#include "GXBase.h"

class Vector4f {
private:
	GLfloat _xyzw[4];

public:
	// TODO: add efficient operators
	Vector4f Add(const Vector4f &rhs) const;
	void Assign(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void AssignX(GLfloat x);
	void AssignY(GLfloat y);
	void AssignZ(GLfloat z);
	void AssignW(GLfloat w);

	Vector4f();

	Vector4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	Vector4f(GLfloat xyzw[]);

	const GLfloat* xyzw() const;

	GLfloat x() const;

	GLfloat y() const;

	GLfloat z() const;

	GLfloat w() const;

	Vector4f Subtract(const Vector4f &v) const;
	Vector4f Subtract(const Vector4f &leftVector, const Vector4f &rightVector) const;

	float CalculateMagnitude() const;

	Vector4f Normalise() const;

	Vector4f DirectionVectorBetweenTwoPoints(Vector4f source, Vector4f destination) const;
	Vector4f Divide(float number) const;

	float DotProduct(const Vector4f &rhs)const;

	Vector4f Multiply(const Vector4f &rhs)const;
	Vector4f Multiply(float lhs, const Vector4f &rhs);

	const float& operator[](int i) const;

	float& operator[](int i);
	Vector4f operator+=(const Vector4f &rhs) const;
	Vector4f operator-(const Vector4f &rhs) const;
	Vector4f operator/(const float &rhs) const;
	Vector4f operator*(const Vector4f &rhs) const;
	Vector4f operator*(float rhs) const;
};
Vector4f operator +(const Vector4f &lhs, const Vector4f &rhs);
