#pragma once

#include <cmath>
#include "GXBase.h"

class Vector3f {
	//friend Vector3f operator+(const Vector3f &lhs, const Vector3f &rhs);
private:
	GLfloat _xyz[3];

public:
	// TODO: Add efficient operators
	inline void Assign(GLfloat x, GLfloat y, GLfloat z){_xyz[0]=x;_xyz[1]=y;_xyz[2]=z;};
	inline void Assign(GLfloat xyz[]){memcpy(_xyz,xyz,3*sizeof(float));};
	inline void Assign(const Vector3f &xyz){_xyz[0]=xyz.x();_xyz[1]=xyz.y();_xyz[2]=xyz.z();};
	inline void AssignX(GLfloat x){_xyz[0]=x;};
	inline void AssignY(GLfloat y){_xyz[1]=y;};
	inline void AssignZ(GLfloat z){_xyz[2]=z;};

	Vector3f();
	~Vector3f();

	Vector3f(GLfloat x, GLfloat y, GLfloat z);

	Vector3f(GLfloat xyz[]);

	Vector3f Add(const Vector3f &rhs) const;

	Vector3f CalculateFaceNormals(const Vector3f &vec1, const Vector3f &vec2, const Vector3f &vec3) const;

	Vector3f CrossProduct(const  Vector3f &vec1, const Vector3f &vec2) const;

	Vector3f& Divide(const int &number, Vector3f &result) const;
	Vector3f Divide(int number) const;
	Vector3f& Divide(const float &number, Vector3f &result) const;
	Vector3f Divide(float number) const;

	float DotProduct(const Vector3f &rhs)const;

	Vector3f Multiply(const Vector3f &rhs)const;
	Vector3f Multiply(float rhs)const;
	Vector3f Multiply(const float lhs, const Vector3f &rhs);

	Vector3f Subtract(const Vector3f &leftVector, const Vector3f &rightVector) const;

	Vector3f Subtract(const Vector3f &v) const;
	Vector3f Subtract(float rhs) const;

	inline float CalculateMagnitude() const{return sqrt((_xyz[0]*_xyz[0]) + (_xyz[1]*_xyz[1]) + (_xyz[2]*_xyz[2]));};

	Vector3f Normalise() const;

	Vector3f DirectionVectorBetweenTwoPoints(Vector3f source, Vector3f destination) const;

	float VectorDistance(const Vector3f &rhs)const;

	const GLfloat* xyz() const;

	inline GLfloat x() const{return _xyz[0];};

	inline GLfloat y() const{return _xyz[1];};

	inline GLfloat z() const{return _xyz[2];};

	const float& operator[](int i) const;

	float& operator[](int i);

	Vector3f operator+(const Vector3f &rhs) const;
	Vector3f operator+(const Vector3f &rhs);
	Vector3f operator-(const Vector3f &rhs) const;
	Vector3f operator-(const Vector3f &rhs);
	Vector3f operator-(float rhs) const;
	Vector3f &operator=(const Vector3f &rhs);

	Vector3f &operator+=(const Vector3f &rhs);
	Vector3f &operator+=(float rhs);
	Vector3f &operator*=(float rhs);
	Vector3f &operator-=(const Vector3f &rhs);
	Vector3f &operator-=(float rhs);

	Vector3f operator/(const int &rhs) const;
	Vector3f operator/(const float &rhs) const;
	Vector3f operator*(const Vector3f &rhs) const;
	Vector3f operator*(const float &rhs) const;
};
Vector3f operator *(const float lhs, const Vector3f &rhs);
Vector3f operator +(float lhs, const Vector3f &rhs);
Vector3f operator +(const Vector3f &lhs, float rhs);
Vector3f Normalise(const Vector3f &vec);