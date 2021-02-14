#pragma once

#include <cmath>
#include "GXBase.h"

class Vector3f {
private:
	GLfloat _xyz[3];

public:
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

	static inline Vector3f Abs(const Vector3f &v){
		return Vector3f(fabsf(v.x()), fabsf(v.y()), fabsf(v.z()));
	}

	static inline Vector3f Add(const Vector3f &lhs, const Vector3f &rhs){
		return Vector3f(lhs.x()+rhs.x(),lhs.y()+rhs.y(),lhs.z()+rhs.z());
	};
	inline Vector3f Add(const Vector3f &rhs) const{return Vector3f(_xyz[0] + rhs.x(), _xyz[1] + rhs.y(), _xyz[2] + rhs.z());};

	inline Vector3f CrossProduct(const  Vector3f &rhs) const{return Vector3f(_xyz[1]*rhs.z()-_xyz[2]*rhs.y(), _xyz[2]*rhs.x()-_xyz[0]*rhs.z(), _xyz[0]*rhs.y()-_xyz[1]*rhs.x());};
	static inline Vector3f CrossProduct(const  Vector3f &vec1, const Vector3f &vec2){
		return Vector3f(vec1.y()*vec2.z() - vec2.y()*vec1.z(), vec1.z()*vec2.x() - vec2.z()*vec1.x(),
			vec1.x()*vec2.y() - vec2.x()*vec1.y());
	};

	static inline Vector3f Difference(const Vector3f &lhs, const Vector3f &rhs){
		return Vector3f(lhs.x()-rhs.x(), lhs.y()-rhs.y(), lhs.z()-rhs.z());
	}

	static inline Vector3f Scale(float scalar, const Vector3f &v){
		return Vector3f(v.x()*scalar, v.y()*scalar, v.z()*scalar);
	}

	static inline Vector3f Divide(int number, const Vector3f &vec){
		return Vector3f(vec.x() / number, vec.y() / number, vec.z() / number);
	};
	Vector3f Divide(int number) const{
		return Vector3f(_xyz[0] / number, _xyz[1] / number, _xyz[2] / number);
	};
	static inline Vector3f Divide(float number, const Vector3f &vec){
		return Vector3f(vec.x() / number, vec.y() / number, vec.z() / number);
	};
	inline Vector3f Divide(float number) const{
		return Vector3f(_xyz[0] / number, _xyz[1] / number, _xyz[2] / number);
	};

	inline float DotProduct(const Vector3f &rhs)const{return _xyz[0]*rhs.x() + _xyz[1]*rhs.y() + _xyz[2]*rhs.z();};
	static inline float DotProduct(const Vector3f &lhs, const Vector3f &rhs){
		return lhs.x()*rhs.x() + lhs.y()*rhs.y() + lhs.z()*rhs.z();
	}

	static inline float Magnitude(const Vector3f &v){
		float x=v.x();float y=v.y();float z=v.z();
		return sqrtf(x*x+y*y+z*z);
	}

	inline Vector3f Multiply(const Vector3f &rhs)const{return Vector3f(_xyz[0]*rhs.x(),_xyz[1]*rhs.y(),_xyz[2]*rhs.z());};
	inline Vector3f Multiply(float rhs)const{return Vector3f(_xyz[0]*rhs,_xyz[1]*rhs,_xyz[2]*rhs);};
	static inline Vector3f Multiply(float lhs, const Vector3f &rhs){return Vector3f(rhs.x()*lhs,rhs.y()*lhs,rhs.z()*lhs);};

	static inline Vector3f Negate(const Vector3f &v){
		return Vector3f(-v.x(), -v.y(), -v.z());
	}

	inline Vector3f Scale(float scalar)const{return Vector3f(_xyz[0]*scalar, _xyz[1]*scalar, _xyz[2]*scalar);};

	static inline Vector3f Subtract(const Vector3f &leftVector, const Vector3f &rightVector){
		return Vector3f(rightVector.x()-leftVector.x(), rightVector.y()-leftVector.y(), rightVector.z()-leftVector.z());
	};

	inline Vector3f Subtract(const Vector3f &v) const{return Vector3f(_xyz[0] - v.x(), _xyz[1] - v.y(), _xyz[2] - v.z());};
	inline Vector3f Subtract(float rhs) const{return Vector3f(_xyz[0] - rhs, _xyz[1] - rhs, _xyz[2] - rhs);};

	inline float CalculateMagnitude() const{return sqrt((_xyz[0]*_xyz[0]) + (_xyz[1]*_xyz[1]) + (_xyz[2]*_xyz[2]));};

	inline Vector3f Normalise() const{
		float magnitude = sqrt(_xyz[0]*_xyz[0] + _xyz[1]*_xyz[1] + _xyz[2]*_xyz[2]);
		if (magnitude==0.0f)
			magnitude = 1.0f;
		return Vector3f(_xyz[0]/magnitude, _xyz[1]/magnitude, _xyz[2]/magnitude);
	};
	static inline Vector3f DirectionVectorBetweenTwoPoints(Vector3f source, Vector3f destination){
		Vector3f vect (destination.x() - source.x(), destination.y() - source.y(), destination.z() - source.z());
		float len = (sqrtf(powf(vect[0], 2) + powf(vect[1], 2) + powf(vect [2], 2)));
		if(len == 0.0f) len = 1.0f;
		return vect.Normalise();
	};

	static inline Vector3f Unit(const Vector3f &v){
		float result = Magnitude(v);
		if (result==0.0f)
			result = 1.0f;
		return Vector3f(Scale(1/result,v));
	}

	inline float VectorDistance(const Vector3f &rhs)const{
		float rhsX = rhs.x();
		float rhsY = rhs.y();
		float rhsZ = rhs.z();

		return sqrt((_xyz[0]- rhsX)*(_xyz[0] - rhsX) + (_xyz[1] - rhsY)*(_xyz[1] - rhsY) + 
			(_xyz[2] - rhsZ)*(_xyz[2] - rhsZ));
	};

	inline const GLfloat* xyz() const{return _xyz;};
	inline GLfloat x() const{return _xyz[0];};
	inline GLfloat y() const{return _xyz[1];};
	inline GLfloat z() const{return _xyz[2];};

	inline const float& operator[](int i) const{return _xyz[i];};

	inline float& operator[](int i){return _xyz[i];};

	inline Vector3f operator+(const Vector3f &rhs) const{return this->Add(rhs);};
	inline Vector3f operator+(const Vector3f &rhs){return this->Add(rhs);};

	inline Vector3f operator-(const Vector3f &rhs) const{return this->Subtract(rhs);};
	inline Vector3f operator-(const Vector3f &rhs){return this->Subtract(rhs);};
	inline Vector3f operator-(float rhs) const{return this->Subtract(rhs);};

	inline Vector3f &operator=(const Vector3f &rhs){memcpy(_xyz, rhs._xyz, 3*sizeof(float));return *this;};

	inline Vector3f &operator+=(const Vector3f &rhs){return *this=*this+rhs;};
	inline Vector3f &operator+=(float rhs){
		Vector3f vec = *this;
		vec.Assign(vec.x()+rhs,vec.y()+rhs,vec.z()+rhs);
		return *this=*this+vec;
	};

	inline Vector3f &operator*=(float rhs){
		Vector3f vec = *this;
		vec.Assign(vec.x()*rhs,vec.y()*rhs,vec.z()*rhs);
		return *this=*this*vec;
	};

	inline Vector3f &operator-=(const Vector3f &rhs){return *this=*this-rhs;};
	inline Vector3f &operator-=(float rhs){
		Vector3f vec = *this;
		vec.Assign(vec.x()-rhs,vec.y()-rhs,vec.z()-rhs);
		return *this=*this-vec;
	};

	inline Vector3f operator/(int rhs) const{return this->Divide(rhs);};
	inline Vector3f operator/(float rhs) const{return this->Divide(rhs);};

	inline Vector3f operator*(const Vector3f &rhs) const{return this->Multiply(rhs);};
	inline Vector3f operator*(float rhs) const{return this->Multiply(rhs);};
};
inline Vector3f operator *(const float lhs, const Vector3f &rhs){return Vector3f(lhs*rhs.x(), lhs*rhs.y(), lhs*rhs.z());};

inline Vector3f operator +(float lhs, const Vector3f &rhs){return Vector3f(lhs+rhs.x(), lhs+rhs.y(), lhs+rhs.z());};
inline Vector3f operator +(const Vector3f &lhs, float rhs){return Vector3f(lhs.x()+rhs, lhs.y()+rhs, lhs.z()+rhs);};

inline Vector3f Normalise(const Vector3f &vec){return vec.Normalise();};