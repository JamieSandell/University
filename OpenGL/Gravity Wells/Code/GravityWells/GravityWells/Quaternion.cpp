#include "Quaternion.h"

Quaternion::Quaternion(void)
{
	_n = 1.0f;
	_v.Assign(0.0f,0.0f,0.0f);
}

Quaternion::Quaternion(const float n, const float e1, const float e2, const float e3)
{
	_n = n;
	_v.Assign(e1,e2,e3);
}

/// construct quaternion from angle-axis

Quaternion::Quaternion(float angle, const Vector3f &axis)
{
	const float a = angle * 0.5f;
	const float s = (float) sin(a);
	const float c = (float) cos(a);
	_n = c;
	_v.Assign(axis.xyz()[0] * s,  axis.xyz()[1] * s,  axis.xyz()[2] * s);	
}

Quaternion::~Quaternion(void)
{
}

void Quaternion::AngleAxis(float &angle, Vector3f &axis) 
{
	const float squareLength = (( _v.xyz()[0] * _v.xyz()[0] ) + ( _v.xyz()[1] * _v.xyz()[1] ) + ( _v.xyz()[2] * _v.xyz()[2] ));
	if(squareLength > 0.0001)
	{
		angle = 2.0f * acosf(_n);
		const float inverseLength = 1.0f / powf(squareLength, 0.5f);

		axis.Assign(_v.xyz()[0] * inverseLength,
			_v.xyz()[1] * inverseLength,
			_v.xyz()[2] * inverseLength);
	}
	else
	{
		angle = 0.0f;
		axis.Assign(1.0f,0.0f,0.0f); //x=1.0f
	}
}
//
void Quaternion::Normalize(void)
{
	const float length = this->Length();

	if (length == 0)
	{
		_n = 1.0;
		_v.Assign(0.0f,0.0f,0.0f);
	}
	else
	{
		float inv = 1.0f / length;
		_n *= inv;
		_v = _v.Scale(inv);
	}
}


Quaternion Quaternion::Multiply(const Quaternion &q)
{
	const float rw = _n* q.GetScalar()          - _v.xyz()[0]*q.GetVector().xyz()[0]  - _v.xyz()[1]*q.GetVector().xyz()[1]   - _v.xyz()[2]*q.GetVector().xyz()[2];
	const float rx = _n* q.GetVector().xyz()[0] + _v.xyz()[0]*q.GetScalar()           + _v.xyz()[1]*q.GetVector().xyz()[2]   - _v.xyz()[2]*q.GetVector().xyz()[1];
	const float ry = _n* q.GetVector().xyz()[1] - _v.xyz()[0]*q.GetVector().xyz()[2]  + _v.xyz()[1]*q.GetScalar()            + _v.xyz()[2]*q.GetVector().xyz()[0];
	const float rz = _n* q.GetVector().xyz()[2] + _v.xyz()[0]*q.GetVector().xyz()[1]  - _v.xyz()[1]*q.GetVector().xyz()[0]   + _v.xyz()[2]*q.GetScalar();
	return Quaternion(rw,rx,ry, rz);			
}

