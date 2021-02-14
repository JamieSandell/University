#pragma once

#include <vector>
#include "MySphere.h"
#include "Lights.h"
#include "Vector4f.h"
#include "Materials.h"

class Glowball : public MySphere{
public:
	Glowball();
	~Glowball();

	void Activate(void);//Turn the glowball lights on
	void Assign(void);
	void Assign(const Vector4f *position, float radius, bool texture, std::string texLocation); 
	Glowball* Clone()const;
	Glowball* CloneToAnEmptyObject()const;
	bool Create(const Vector4f *position, float radius, bool texture, std::string texLocation);
	bool Create(void);
	void Deactivate(void);
	void InverseNormals(void);
	void PositionLights(void);
	void Update();
	void Update(float deltaTime, float elapsedTime);

private:
	static const int _defaultSlices = 50;
	static const int _defaultStacks = 50;
	bool _glowballActivated;
	Lights _lights[6];
	std::vector<Materials> _lightMaterials;
	std::vector<Vector4f> _lightPosition;
	GLfloat _glowBallRadius;
	Vector4f _glowBallCentre;
};