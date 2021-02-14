#pragma once
#include "ship.h"

class ShipOriginal :
	public Ship
{
public:
	ShipOriginal(void);
	virtual ~ShipOriginal(void); // So they get cleaned up properly when out of scope
	virtual void Draw(void);
};
