#include "Vector4f.h"
#include <cmath>

Vector4f Vector4f::Add(const Vector4f &rhs) const{
	return Vector4f(_xyzw[0] + rhs.x(), _xyzw[1] + rhs.y(), _xyzw[2] + rhs.z(), 1.0f);
}

void Vector4f::Assign(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	_xyzw[0] = x;
	_xyzw[1] = y;
	_xyzw[2] = z;
	_xyzw[3] = w;
}

void Vector4f::AssignX(GLfloat x){
	_xyzw[0] = x;
}

void Vector4f::AssignY(GLfloat y){
	_xyzw[1] = y;
}

void Vector4f::AssignZ(GLfloat z){
	_xyzw[2] = z;
}

void Vector4f::AssignW(GLfloat w){
	_xyzw[3] = w;
}

Vector4f::Vector4f() {
	Assign(0.0, 0.0, 0.0, 1.0);
}

Vector4f::Vector4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	Assign(x, y, z, w);
}

Vector4f::Vector4f(GLfloat xyzw[]) {
	Assign(xyzw[0], xyzw[1], xyzw[2], xyzw[3]);
}

const GLfloat* Vector4f::xyzw() const {
	return _xyzw;
}

GLfloat Vector4f::x() const {
	return _xyzw[0];
}

GLfloat Vector4f::y() const {
	return _xyzw[1];
}

GLfloat Vector4f::z() const {
	return _xyzw[2];
}

GLfloat Vector4f::w() const{
	return _xyzw[3];
}

float Vector4f::CalculateMagnitude() const {
	return sqrt((_xyzw[0]*_xyzw[0]) + (_xyzw[1]*_xyzw[1]) + (_xyzw[2]*_xyzw[2]));
}

Vector4f Vector4f::Divide(float number) const{
	Vector4f result;
	result.Assign(x()/number, y()/number, z()/number, 1.0f);
	return result;
}

float Vector4f::DotProduct(const Vector4f &rhs)const{
	float result = this->x()*rhs.x() + this->y()*rhs.y() + this->z()*rhs.z();
	return result;
}

Vector4f Vector4f::Normalise() const {
	float magnitude = sqrt(_xyzw[0]*_xyzw[0] + _xyzw[1]*_xyzw[1] + _xyzw[2]*_xyzw[2]);
	if (magnitude==0.0f)
		magnitude = 1.0f;
	Vector4f result(_xyzw[0]/magnitude, _xyzw[1]/magnitude, _xyzw[2]/magnitude, _xyzw[3]);
	return result;
}

Vector4f Vector4f::Multiply(const Vector4f &rhs)const{
	return Vector4f(this->x()*rhs.x(), this->y()*rhs.y(), this->z()*rhs.z(),1.0f);
}

Vector4f Vector4f::Subtract(const Vector4f &v) const{
	return Vector4f(_xyzw[0] - v.x(), _xyzw[1] - v.y(), _xyzw[2] - v.z(), 1.0f);
}

Vector4f Vector4f::Subtract(const Vector4f &leftVector, const Vector4f &rightVector) const{
	return Vector4f(rightVector.x()-leftVector.x(), rightVector.y()-leftVector.y(), rightVector.z()-leftVector.z(),1.0f);
}

Vector4f Vector4f::DirectionVectorBetweenTwoPoints(Vector4f source, Vector4f destination) const {
	Vector4f ret(destination.Subtract(source));
	ret = ret.Normalise();
	return ret;
}

const float& Vector4f::operator[](int i) const {
	return _xyzw[i];
}

float& Vector4f::operator[](int i) {
	return _xyzw[i];
}

Vector4f Vector4f::operator -(const Vector4f &rhs) const{
	return this->Subtract(rhs);
}

Vector4f Vector4f::operator /(const float &rhs) const{
	return this->Divide(rhs);
}


Vector4f operator +(const Vector4f &lhs, const Vector4f &rhs){
	return Vector4f(lhs)+=(rhs);
}

Vector4f Vector4f::operator +=(const Vector4f &rhs) const{
	return this->Add(rhs);
}

Vector4f Vector4f::operator*(const Vector4f &rhs)const{
	return this->Multiply(rhs);
}

Vector4f Vector4f::operator *(float rhs)const{
	return Vector4f(rhs*this->x(),rhs*this->y(),rhs*this->z(),1.0f);
}