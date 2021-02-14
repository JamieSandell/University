#include "NewtonianObject.h"

NewtonianObject::NewtonianObject(void) : _gravity(9.81)
{
}

NewtonianObject::~NewtonianObject(void)
{
}

void NewtonianObject::UpdatePos(const float &dt)
{
}

/// <summary>
/// Gets the _gravity value
/// </summary>
/// <returns>
/// A double which holds the _gravity value
/// </returns>
double NewtonianObject::GetGravity() const
{
	return _gravity;
}
