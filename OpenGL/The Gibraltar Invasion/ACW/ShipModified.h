#pragma once
#include <GL/glut.h>
#include "ship.h"

class ShipModified :
	public Ship
{
public:
	ShipModified(void);
	virtual ~ShipModified(void); // So they get cleaned up properly when out of scope

	virtual void Draw(void) const;
};
