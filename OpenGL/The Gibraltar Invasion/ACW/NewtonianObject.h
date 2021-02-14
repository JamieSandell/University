#pragma once

class NewtonianObject
{
public:
	NewtonianObject(void);
	~NewtonianObject(void);

	virtual void UpdatePos(const float &dt);
	double GetGravity() const;

private:
	double _gravity;
};
