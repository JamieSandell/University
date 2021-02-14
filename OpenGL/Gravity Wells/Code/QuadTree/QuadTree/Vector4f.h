#pragma once

#include <cmath>
#include "GXBase.h"

class Vector4f {
	//friend Vector3f operator+(const Vector3f &lhs, const Vector3f &rhs);
private:
	GLfloat _xyzw[4];

public:
	// TODO: Add efficient operators
	inline void Assign(GLfloat x, GLfloat y, GLfloat z, GLfloat w){_xyzw[0]=x;_xyzw[1]=y;_xyzw[2]=z;_xyzw[3]=w;};
	inline void Assign(GLfloat xyzw[]){memcpy(_xyzw,xyzw,4*sizeof(float));};
	inline void Assign(const Vector4f &xyzw){_xyzw[0]=xyzw.x();_xyzw[1]=xyzw.y();_xyzw[2]=xyzw.z();_xyzw[3]=xyzw.w();};
	inline void AssignX(GLfloat x){_xyzw[0]=x;};
	inline void AssignY(GLfloat y){_xyzw[1]=y;};
	inline void AssignZ(GLfloat z){_xyzw[2]=z;};
	inline void AssignW(GLfloat w){_xyzw[3]=w;};

	Vector4f();
	~Vector4f();

	Vector4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	Vector4f(GLfloat xyzw[]);

	Vector4f Add(const Vector4f &rhs) const;

	Vector4f CrossProduct(const Vector4f &vec1, const Vector4f &vec2) const;

	Vector4f& Divide(const int &number, Vector4f &result) const;
	Vector4f Divide(int number) const;
	Vector4f& Divide(const float &number, Vector4f &result) const;
	Vector4f Divide(float number) const;

	float DotProduct(const Vector4f &rhs)const;

	Vector4f Multiply(const Vector4f &rhs)const;
	Vector4f Multiply(float rhs)const;
	Vector4f Multiply(const float lhs, const Vector4f &rhs);

	Vector4f Subtract(const Vector4f &leftVector, const Vector4f &rightVector) const;

	Vector4f Subtract(const Vector4f &v) const;
	Vector4f Subtract(float rhs) const;

	inline float CalculateMagnitude() const{return sqrt((_xyzw[0]*_xyzw[0]) + (_xyzw[1]*_xyzw[1]) + 
		(_xyzw[2]*_xyzw[2]) + (_xyzw[3]*_xyzw[3]));};

	Vector4f Normalise() const;

	Vector4f DirectionVectorBetweenTwoPoints(Vector4f source, Vector4f destination) const;

	float VectorDistance(const Vector4f &rhs)const;

	const GLfloat* xyz() const;

	inline GLfloat x() const{return _xyzw[0];};

	inline GLfloat y() const{return _xyzw[1];};

	inline GLfloat z() const{return _xyzw[2];};

	inline GLfloat w() const{return _xyzw[3];};

	const float& operator[](int i) const;

	float& operator[](int i);

	Vector4f operator+(const Vector4f &rhs) const;
	Vector4f operator+(const Vector4f &rhs);
	Vector4f operator-(const Vector4f &rhs) const;
	Vector4f operator-(const Vector4f &rhs);
	Vector4f operator-(float rhs) const;
	Vector4f &operator=(const Vector4f &rhs);

	Vector4f &operator+=(const Vector4f &rhs);
	Vector4f &operator+=(float rhs);
	Vector4f &operator*=(float rhs);
	Vector4f &operator-=(const Vector4f &rhs);
	Vector4f &operator-=(float rhs);

	Vector4f operator/(const int &rhs) const;
	Vector4f operator/(const float &rhs) const;
	Vector4f operator*(const Vector4f &rhs) const;
	Vector4f operator*(const float &rhs) const;
};
Vector4f operator *(const float lhs, const Vector4f &rhs);
Vector4f operator +(float lhs, const Vector4f &rhs);
Vector4f operator +(const Vector4f &lhs, float rhs);
Vector4f Normalise(const Vector4f &vec);