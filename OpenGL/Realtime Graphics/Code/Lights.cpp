#include "Lights.h"

Lights::Lights() {
	_lightNumber = -1;
}

void Lights::create(GLuint lightNum, const Color &ambient, const Color &diffuse, const Vector4f &position) {
	// the light being defined
	_lightNumber = lightNum;	

	setAmbient(ambient);
	setDiffuse(diffuse);
	setPosition(position);
}

Color Lights::GetDiffuse(void)const{
	return _diffuse;
}

void Lights::setAmbient(const Color &ambient) {
	_ambient = ambient;
	glLightfv(GL_LIGHT0+_lightNumber, GL_AMBIENT, _ambient.rgba());
}		

void Lights::setDiffuse(const Color &diffuse) {
	_diffuse = diffuse;
	glLightfv(GL_LIGHT0+_lightNumber, GL_DIFFUSE, _diffuse.rgba());
}		

void Lights::setPosition(const Vector4f &position) {
	_position = position;
	glLightfv(GL_LIGHT0+_lightNumber, GL_POSITION, _position.xyzw());
}

void Lights::apply() const {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0 + _lightNumber);
}

void Lights::setDirection(const Vector3f &direction) {
	_direction = direction;
	glLightfv(GL_LIGHT0+_lightNumber, GL_SPOT_DIRECTION, _direction.xyz());
}

void Lights::setSpot(const GLfloat &cutoff, const GLfloat &exponent) {
	_cutoff = cutoff;
	_exponent = exponent;
	glLightf(GL_LIGHT0+_lightNumber,GL_SPOT_CUTOFF, cutoff);
	glLightf(GL_LIGHT0+_lightNumber,GL_SPOT_EXPONENT, exponent);
}

const float& Lights::operator [](int i) const {
	return _position[i];
}

float& Lights::operator [](int i) {
	return _position[i];
}

Vector4f Lights::GetPosition() const {
	return _position;
}