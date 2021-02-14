#pragma once

#include "Shape.h"

class NullObject : public Shape{
public:
	NullObject();
	~NullObject();

	void Animate(float deltaTime, float timeElapsed);
	void Assign(const Vector4f *position, float size, bool texture, std::string texLocation);
	NullObject* CloneToAnEmptyObject()const;
	NullObject* Clone()const;
	bool Create(void);
	bool Create(const Vector4f *position, float size, bool texture, std::string texLocation);
	void Update(float deltaTime, float timeElapsed);
	void Draw() const;

};