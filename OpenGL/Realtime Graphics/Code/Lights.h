#pragma once

#include "GXBase.h"
#include "Vector4f.h"
#include "Vector3f.h"
#include "Color.h"

class Lights {
private:
	// Light number
	GLuint _lightNumber;				

	// Ambient, diffuse and position
	Color _ambient;
	Color _diffuse;
	Vector4f _position;
	Vector3f _direction;
	GLfloat _cutoff, _exponent;

public:
	Lights();

	void create(GLuint lightNum, const Color &ambient=Color::black(), const Color &diffuse=Color::white(), const Vector4f &position=Vector4f(0.0f,0.0f,0.0f,1.0f));

	Color GetDiffuse(void)const;

	void setAmbient(const Color &ambient);

	void setDiffuse(const Color &diffuse);

	void setPosition(const Vector4f &position);

	void apply() const;

	void setDirection(const Vector3f &direction);

	void setSpot(const GLfloat &cutoff, const GLfloat &exponent);

	const float& operator[](int i) const;

	float& operator[](int i);

	Vector4f GetPosition() const;
};
