#pragma once
#include "Vector3f.h"

class Quaternion
{
public:
	Quaternion(void);
	Quaternion(const float n, const float e1, const float e2, const float e3);
	Quaternion(float angle,const Vector3f &axis);
	~Quaternion(void);

	inline Vector3f GetVector(void) const{return _v;};
	inline float GetScalar(void) const {return _n;};
	inline float GetAngle(void) const {return (float) (2.0f * acosf(_n)) ;};

	void AngleAxis(float &angle, Vector3f &axis);
	inline void Zero(void){ _n = 0.0f; _v.Assign(0.0f,0.0f,0.0f); };
	inline void Identity(void){ _n = 1.0f; _v.Assign(0.0f,0.0f,0.0f); };
	Quaternion Multiply(const Quaternion &q);

	inline void Add(const Quaternion &q)
	{	
		//	return Quaternion((_n + q.GetScalar()), (_v.Add(q.GetVector())));
		_n += q.GetScalar();
		_v = _v.Add(q.GetVector());	
	};

	inline Quaternion AddQuat(const Quaternion &q)
	{	
		return Quaternion(_n + q.GetScalar(), _v.xyz()[0] + q.GetVector().xyz()[0], _v.xyz()[1] + q.GetVector().xyz()[1], _v.xyz()[2] + q.GetVector().xyz()[2]);
	};

	inline void Subtract(const Quaternion &q)
	{	
		_n -= q.GetScalar();
		_v = _v.Subtract(q.GetVector());	
	};

	inline Quaternion Multiply(float s)
	{	
		//_n *= s;
		//_v = _v.Scale(s);
		return Quaternion((_n *= s), _v.xyz()[0] * s,  _v.xyz()[1] * s, _v.xyz()[2] * s );//_v.Scale(s));
	};

	inline void Scale(float s){_n*=s; _v=_v*s;};

	inline void Divide(float s)
	{	
		assert(s!=0);
		const float inv = 1.0f / s;
		_n *= inv;
		_v = _v.Scale(inv);
	};

	inline float Length(void) const
	{ 
		return sqrtf((_n * _n) + (_v.xyz()[0] * _v.xyz()[0] ) + (_v.xyz()[1] * _v.xyz()[1] ) + (_v.xyz()[2] * _v.xyz()[2] ));
	};

	inline float Norm(void) const
	{ 
		return ((_n * _n) + (_v.xyz()[0] * _v.xyz()[0] ) + (_v.xyz()[1] * _v.xyz()[1] ) + (_v.xyz()[2] * _v.xyz()[2] ));
	};

	void Normalize(void);	

private:
	float _n; /// Scalar part
	Vector3f _v; ///Vector
};

