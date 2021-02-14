#pragma once
#include "circle.h"

class GravityWell :
	public Circle
{
public:
	GravityWell(void);
	~GravityWell(void);
	GravityWell& operator=(const GravityWell &A); // assignment operator

	void Assign(void);
	bool Create(void);
	void Assign(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture);//call this after a create
	bool Create(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture);
	void Draw(void) const;
	inline void SetCurrentState(int state){
		if ((state >= 0) && (state<=2))
			_currentState=state;
	};// 0 = not attracting or repelling, 1 = attracting, 2 = repelling
	inline int GetCurrentState(void)const{return _currentState;};
	inline void SetForce(float force){_force=force;};
	inline float GetForce(void)const{return _force;};

private:
	float _force;
	int _currentState; // 0 = not attracting or repelling, 1 = attracting, 2 = repelling
};
