#include "Vector3f.h"

void Vector3f::Assign(GLfloat x, GLfloat y, GLfloat z) {
	_xyz[0] = x;
	_xyz[1] = y;
	_xyz[2] = z;
}

void Vector3f::Assign(const Vector3f &xyz) {
	_xyz[0] = xyz.x();
	_xyz[1] = xyz.y();
	_xyz[2] = xyz.z();
}

void Vector3f::AssignX(GLfloat x){
	_xyz[0] = x;
}

void Vector3f::AssignY(GLfloat y){
	_xyz[1] = y;
}

void Vector3f::AssignZ(GLfloat z){
	_xyz[2] = z;
}

Vector3f::Vector3f() {
	Assign(0.0, 0.0, 0.0);
}

Vector3f::~Vector3f(){

}

Vector3f::Vector3f(GLfloat x, GLfloat y, GLfloat z) {
	Assign(x, y, z);
}

Vector3f Vector3f::Add(const Vector3f &rhs) const{
	return Vector3f(_xyz[0] + rhs.x(), _xyz[1] + rhs.y(), _xyz[2] + rhs.z());
}

void Vector3f::Assign(GLfloat xyz[]){
	_xyz[0] = xyz[0];
	_xyz[1] = xyz[1];
	_xyz[2] = xyz[2];
}

Vector3f::Vector3f(GLfloat xyz[]) {
	Assign(xyz[0], xyz[1], xyz[2]);
}

Vector3f Vector3f::CalculateFaceNormals(const Vector3f &vec1, const Vector3f &vec2, const Vector3f &vec3) const{
	Vector3f normal, edge1, edge2;

	edge2 = edge2.Subtract(vec1, vec2);
	edge1 = edge1.Subtract(vec2, vec3);

	normal = normal.CrossProduct(edge1, edge2);
	normal = normal.Normalise();

	return normal;
}

Vector3f Vector3f::CrossProduct(const Vector3f &vec1, const Vector3f &vec2) const{
	Vector3f result;
	result.Assign(vec1.y()*vec2.z() - vec2.y()-vec1.z(), vec1.z()*vec2.x() - vec2.z()*vec1.x(),
		vec1.x()*vec2.y() - vec2.x()*vec1.y());
	return result;
}

float Vector3f::CalculateMagnitude() const {
	return sqrt((_xyz[0]*_xyz[0]) + (_xyz[1]*_xyz[1]) + (_xyz[2]*_xyz[2]));
}

Vector3f& Vector3f::Divide(const int &number, Vector3f &result) const{
	result.Assign(x() / number, y() / number, z() / number);
	return result;
}

Vector3f Vector3f::Divide(int number) const{
	Vector3f result;
	result.Assign(x()/number, y()/number, z()/number);
	return result;
}

Vector3f& Vector3f::Divide(const float &number, Vector3f &result) const{
	result.Assign(x() / number, y() / number, z() / number);
	return result;
}

Vector3f Vector3f::Divide(float number) const{
	Vector3f result;
	result.Assign(x()/number, y()/number, z()/number);
	return result;
}

float Vector3f::DotProduct(const Vector3f &rhs)const{
	float result = this->x()*rhs.x() + this->y()*rhs.y() + this->z()*rhs.z();
	return result;
}

Vector3f Vector3f::Normalise() const {
	float magnitude = sqrt(_xyz[0]*_xyz[0] + _xyz[1]*_xyz[1] + _xyz[2]*_xyz[2]);
	if (magnitude==0.0f)
		magnitude = 1.0f;
	Vector3f result(_xyz[0]/magnitude, _xyz[1]/magnitude, _xyz[2]/magnitude);
	return result;
}

Vector3f Vector3f::Multiply(const Vector3f &rhs)const{
	return Vector3f(this->x()*rhs.x(), this->y()*rhs.y(), this->z()*rhs.z());
}

Vector3f Vector3f::Multiply(float rhs) const{
	return Vector3f(this->x()*rhs, this->y()*rhs, this->z()*rhs);
}

Vector3f Vector3f::Subtract(const Vector3f &leftVector, const Vector3f &rightVector) const{
	return Vector3f(rightVector.x()-leftVector.x(), rightVector.y()-leftVector.y(), rightVector.z()-leftVector.z());
}

Vector3f Vector3f::Subtract(const Vector3f &v) const{
	return Vector3f(_xyz[0] - v.x(), _xyz[1] - v.y(), _xyz[2] - v.z());
}

Vector3f Vector3f::DirectionVectorBetweenTwoPoints(Vector3f source, Vector3f destination) const {
	/*Vector3f ret(destination.Subtract(source));
	ret = ret.Normalise();
	return ret;*/

	Vector3f vect;
	vect.Assign((destination.x() - source.x()), (destination.y() - source.y()), (destination.z() - source.z()));
	float len = (sqrt(pow(vect[0], 2) + pow(vect[1], 2) + pow(vect [2], 2)));
	if(len == 0) len = 1.0f;

	vect = vect.Normalise();
	return vect;

}

const GLfloat* Vector3f::xyz() const {
	return _xyz;
}

GLfloat Vector3f::x() const {
	return _xyz[0];
}

GLfloat Vector3f::y() const {
	return _xyz[1];
}

GLfloat Vector3f::z() const {
	return _xyz[2];
}

const float& Vector3f::operator[](int i) const {
	return _xyz[i];
}

float& Vector3f::operator[](int i) {
	return _xyz[i];
}

Vector3f Vector3f::operator +(const Vector3f &rhs) const{
	return this->Add(rhs);
}

Vector3f Vector3f::operator +=(const Vector3f &rhs) const{
	return this->Add(rhs);
}

Vector3f Vector3f::operator /(const int &rhs) const{
	return this->Divide(rhs);
}

Vector3f Vector3f::operator /(const float &rhs) const{
	return this->Divide(rhs);
}

Vector3f Vector3f::operator*(const Vector3f &rhs)const{
	return this->Multiply(rhs);
}

Vector3f Vector3f::operator*(const float &rhs)const{
	return this->Multiply(rhs);
}

Vector3f operator *(const float lhs, const Vector3f &rhs){
	return Vector3f(lhs*rhs.x(), lhs*rhs.y(), lhs*rhs.z());
}

Vector3f operator +(float lhs, const Vector3f &rhs){
	return Vector3f(lhs+rhs.x(), lhs+rhs.y(), lhs+rhs.z());
}

Vector3f operator +(const Vector3f &lhs, float rhs){
	return Vector3f(lhs.x()+rhs, lhs.y()+rhs, lhs.z()+rhs);
}