#pragma once

#include <cmath>
#include "GXBase.h"

class Vector4f {
private:
	GLfloat _xyzw[4];

public:
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

	static inline Vector4f Abs(const Vector4f &v){
		return Vector4f(fabsf(v.x()), fabsf(v.y()), fabsf(v.z()), fabsf(v.w()));
	}

	static inline Vector4f Add(const Vector4f &lhs, const Vector4f &rhs){
		return Vector4f(lhs.x()+rhs.x(),lhs.y()+rhs.y(),lhs.z()+rhs.z(),lhs.w()+rhs.w());
	};
	inline Vector4f Add(const Vector4f &rhs) const{return Vector4f(_xyzw[0] + rhs.x(), _xyzw[1] + rhs.y(), 
		_xyzw[2] + rhs.z(), _xyzw[3] + rhs.w());};

	static inline Vector4f Difference(const Vector4f &lhs, const Vector4f &rhs){
		return Vector4f(lhs.x()-rhs.x(), lhs.y()-rhs.y(), lhs.z()-rhs.z(), lhs.w()-rhs.w());
	}

	static inline Vector4f Scale(float scalar, const Vector4f &v){
		return Vector4f(v.x()*scalar, v.y()*scalar, v.z()*scalar, v.w()*scalar);
	}

	static inline Vector4f Divide(int number, const Vector4f &vec){
		return Vector4f(vec.x() / number, vec.y() / number, vec.z() / number, vec.w() / number);
	};
	Vector4f Divide(int number) const{
		return Vector4f(_xyzw[0] / number, _xyzw[1] / number, _xyzw[2] / number, _xyzw[3] / number);
	};
	static inline Vector4f Divide(float number, const Vector4f &vec){
		return Vector4f(vec.x() / number, vec.y() / number, vec.z() / number, vec.w() / number);
	};
	inline Vector4f Divide(float number) const{
		return Vector4f(_xyzw[0] / number, _xyzw[1] / number, _xyzw[2] / number, _xyzw[3] / number);
	};

	inline float DotProduct(const Vector4f &rhs)const{return _xyzw[0]*rhs.x() + _xyzw[1]*rhs.y() + 
		_xyzw[2]*rhs.z() + _xyzw[3]*rhs.w();};
	static inline float DotProduct(const Vector4f &lhs, const Vector4f &rhs){
		return lhs.x()*rhs.x() + lhs.y()*rhs.y() + lhs.z()*rhs.z() + lhs.w()*rhs.w();
	}

	static inline float Magnitude(const Vector4f &v){
		float x=v.x();float y=v.y();float z=v.z();float w=v.w();
		return sqrtf(x*x+y*y+z*z+w*w);
	}

	inline Vector4f Multiply(const Vector4f &rhs)const{return Vector4f(_xyzw[0]*rhs.x(),_xyzw[1]*rhs.y(),_xyzw[2]*rhs.z(),
		_xyzw[3]*rhs.w());};
	inline Vector4f Multiply(float rhs)const{return Vector4f(_xyzw[0]*rhs,_xyzw[1]*rhs,_xyzw[2]*rhs,_xyzw[3]*rhs);};
	static inline Vector4f Multiply(float lhs, const Vector4f &rhs){return Vector4f(rhs.x()*lhs,rhs.y()*lhs,rhs.z()*lhs,
		rhs.w()*lhs);};

	static inline Vector4f Negate(const Vector4f &v){
		return Vector4f(-v.x(), -v.y(), -v.z(), -v.w());
	}

	inline Vector4f Scale(float scalar)const{return Vector4f(_xyzw[0]*scalar, _xyzw[1]*scalar, _xyzw[2]*scalar, 
		_xyzw[3]*scalar);};

	static inline Vector4f Subtract(const Vector4f &leftVector, const Vector4f &rightVector){
		return Vector4f(rightVector.x()-leftVector.x(), rightVector.y()-leftVector.y(), rightVector.z()-leftVector.z(), 
			rightVector.w()-leftVector.w());
	};

	inline Vector4f Subtract(const Vector4f &v) const{return Vector4f(_xyzw[0] - v.x(), _xyzw[1] - v.y(), 
		_xyzw[2] - v.z(), _xyzw[3] - v.w());};
	inline Vector4f Subtract(float rhs) const{return Vector4f(_xyzw[0] - rhs, _xyzw[1] - rhs, _xyzw[2] - rhs, _xyzw[3] - rhs);};

	inline float CalculateMagnitude() const{return sqrtf((_xyzw[0]*_xyzw[0]) + (_xyzw[1]*_xyzw[1]) + 
		(_xyzw[2]*_xyzw[2]) + (_xyzw[3]*_xyzw[3]));};

	inline Vector4f Normalise() const{
		float magnitude = sqrt(_xyzw[0]*_xyzw[0] + _xyzw[1]*_xyzw[1] + _xyzw[2]*_xyzw[2] + _xyzw[3]*_xyzw[3]);
		if (magnitude==0.0f)
			magnitude = 1.0f;
		return Vector4f(_xyzw[0]/magnitude, _xyzw[1]/magnitude, _xyzw[2]/magnitude, _xyzw[3]/magnitude);
	};
	static inline Vector4f DirectionVectorBetweenTwoPoints(Vector4f source, Vector4f destination){
		Vector4f vect (destination.x() - source.x(), destination.y() - source.y(), destination.z() - source.z(), 
			destination.w() - source.w());
		float len = (sqrtf(powf(vect[0], 2) + powf(vect[1], 2) + powf(vect [2], 2) + powf(vect[3], 2)));
		if(len == 0.0f) len = 1.0f;
		return vect.Normalise();
	};

	static inline Vector4f Unit(const Vector4f &v){
		float result = Magnitude(v);
		if (result==0.0f)
			result = 1.0f;
		return Vector4f(Scale(1/result,v));
	}

	inline float VectorDistance(const Vector4f &rhs)const{
		float rhsX = rhs.x();
		float rhsY = rhs.y();
		float rhsZ = rhs.z();
		float rhsW = rhs.w();

		return sqrtf((_xyzw[0]- rhsX)*(_xyzw[0] - rhsX) + (_xyzw[1] - rhsY)*(_xyzw[1] - rhsY) + 
			(_xyzw[2] - rhsZ)*(_xyzw[2] - rhsZ) + (_xyzw[3] - rhsZ)*(_xyzw[3] - rhsZ));
	};

	inline const GLfloat* xyzw() const{return _xyzw;};
	inline GLfloat x() const{return _xyzw[0];};
	inline GLfloat y() const{return _xyzw[1];};
	inline GLfloat z() const{return _xyzw[2];};
	inline GLfloat w() const{return _xyzw[3];};

	inline const float& operator[](int i) const{return _xyzw[i];};

	inline float& operator[](int i){return _xyzw[i];};

	inline Vector4f operator+(const Vector4f &rhs) const{return this->Add(rhs);};
	inline Vector4f operator+(const Vector4f &rhs){return this->Add(rhs);};

	inline Vector4f operator-(const Vector4f &rhs) const{return this->Subtract(rhs);};
	inline Vector4f operator-(const Vector4f &rhs){return this->Subtract(rhs);};
	inline Vector4f operator-(float rhs) const{return this->Subtract(rhs);};

	inline Vector4f &operator=(const Vector4f &rhs){memcpy(_xyzw, rhs._xyzw, 4*sizeof(float));return *this;};

	inline Vector4f &operator+=(const Vector4f &rhs){return *this=*this+rhs;};
	inline Vector4f &operator+=(float rhs){
		Vector4f vec = *this;
		vec.Assign(vec.x()+rhs,vec.y()+rhs,vec.z()+rhs,vec.w()+rhs);
		return *this=*this+vec;
	};

	inline Vector4f &operator*=(float rhs){
		Vector4f vec = *this;
		vec.Assign(vec.x()*rhs,vec.y()*rhs,vec.z()*rhs,vec.w()*rhs);
		return *this=*this*vec;
	};

	inline Vector4f &operator-=(const Vector4f &rhs){return *this=*this-rhs;};
	inline Vector4f &operator-=(float rhs){
		Vector4f vec = *this;
		vec.Assign(vec.x()-rhs,vec.y()-rhs,vec.z()-rhs,vec.w()-rhs);
		return *this=*this-vec;
	};

	inline Vector4f operator/(int rhs) const{return this->Divide(rhs);};
	inline Vector4f operator/(float rhs) const{return this->Divide(rhs);};

	inline Vector4f operator*(const Vector4f &rhs) const{return this->Multiply(rhs);};
	inline Vector4f operator*(float rhs) const{return this->Multiply(rhs);};
};
inline Vector4f operator *(const float lhs, const Vector4f &rhs){return Vector4f(lhs*rhs.x(), lhs*rhs.y(), lhs*rhs.z(), 
								lhs*rhs.w());};

inline Vector4f operator +(float lhs, const Vector4f &rhs){return Vector4f(lhs+rhs.x(), lhs+rhs.y(), lhs+rhs.z(), 
								lhs+rhs.w());};
inline Vector4f operator +(const Vector4f &lhs, float rhs){return Vector4f(lhs.x()+rhs, lhs.y()+rhs, lhs.z()+rhs, 
								lhs.w()+rhs);};

inline Vector4f Normalise(const Vector4f &vec){return vec.Normalise();};