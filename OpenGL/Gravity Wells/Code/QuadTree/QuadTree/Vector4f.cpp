#include "Vector4f.h"

Vector4f::Vector4f() {
	Assign(0.0f, 0.0f, 0.0f, 0.0f);
}

Vector4f::~Vector4f(){

}

Vector4f::Vector4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	Assign(x, y, z, w);
}

Vector4f Vector4f::Add(const Vector4f &rhs) const{
	return Vector4f(_xyzw[0] + rhs.x(), _xyzw[1] + rhs.y(), _xyzw[2] + rhs.z(), _xyzw[3] + rhs.w());
}

Vector4f::Vector4f(GLfloat xyzw[]) {
	Assign(xyzw[0], xyzw[1], xyzw[2], _xyzw[3]);
}

Vector4f& Vector4f::Divide(const int &number, Vector4f &result) const{
	result.Assign(x() / number, y() / number, z() / number, w() / number);
	return result;
}

Vector4f Vector4f::Divide(int number) const{
	Vector4f result;
	result.Assign(x()/number, y()/number, z()/number, w() / number);
	return result;
}

Vector4f& Vector4f::Divide(const float &number, Vector4f &result) const{
	result.Assign(x() / number, y() / number, z() / number, w() / number);
	return result;
}

Vector4f Vector4f::Divide(float number) const{
	Vector4f result;
	result.Assign(x()/number, y()/number, z()/number, w()/number);
	return result;
}

float Vector4f::DotProduct(const Vector4f &rhs)const{
	float result = _xyzw[0]*rhs.x() + _xyzw[1]*rhs.y() + _xyzw[2]*rhs.z() + _xyzw[3]*rhs.w();
	return result;
}

Vector4f Vector4f::Normalise() const {
	float magnitude = sqrt(_xyzw[0]*_xyzw[0] + _xyzw[1]*_xyzw[1] + _xyzw[2]*_xyzw[2] + _xyzw[3]*_xyzw[3]);
	if (magnitude==0.0f)
		magnitude = 1.0f;
	Vector4f result(_xyzw[0]/magnitude, _xyzw[1]/magnitude, _xyzw[2]/magnitude, _xyzw[3]/magnitude);
	return result;
}

Vector4f Vector4f::Multiply(const Vector4f &rhs)const{
	return Vector4f(_xyzw[0]*rhs.x(), _xyzw[1]*rhs.y(), _xyzw[2]*rhs.z(), _xyzw[3]*rhs.w());
}

Vector4f Vector4f::Multiply(float rhs) const{
	return Vector4f(_xyzw[0]*rhs, _xyzw[1]*rhs, _xyzw[2]*rhs, _xyzw[3]*rhs);
}

Vector4f Vector4f::Subtract(const Vector4f &leftVector, const Vector4f &rightVector) const{
	return Vector4f(rightVector.x()-leftVector.x(), rightVector.y()-leftVector.y(), rightVector.z()-leftVector.z(),
		rightVector.w() - leftVector.w());
}

Vector4f Vector4f::Subtract(const Vector4f &v) const{
	return Vector4f(_xyzw[0] - v.x(), _xyzw[1] - v.y(), _xyzw[2] - v.z(), _xyzw[3] - v.w());
}

Vector4f Vector4f::Subtract(float rhs) const{
	return Vector4f(_xyzw[0] - rhs, _xyzw[1] - rhs, _xyzw[2] - rhs, _xyzw[3] - rhs);
}

Vector4f Vector4f::DirectionVectorBetweenTwoPoints(Vector4f source, Vector4f destination) const {
	/*Vector3f ret(destination.Subtract(source));
	ret = ret.Normalise();
	return ret;*/

	Vector4f vect;
	vect.Assign((destination.x() - source.x()), (destination.y() - source.y()), (destination.z() - source.z()),
		(destination.w() - source.w()));
	float len = (sqrt(pow(vect[0], 2) + pow(vect[1], 2) + pow(vect[2], 2) + pow(vect[3], 2)));
	if(len == 0) len = 1.0f;

	vect = vect.Normalise();
	return vect;

}

float Vector4f::VectorDistance(const Vector4f &rhs)const{
	float rhsX = rhs.x();
	float rhsY = rhs.y();
	float rhsZ = rhs.z();
	float rhsW = rhs.w();

	return sqrt((_xyzw[0] - rhsX) * (_xyzw[0] - rhsX) + (_xyzw[1] - rhsY) * (_xyzw[1] - rhsY) + 
	(_xyzw[2] - rhsZ) * (_xyzw[2] - rhsZ) + (_xyzw[3] - rhsW) * (_xyzw[3] - rhsW));
}

const GLfloat* Vector4f::xyz() const {
	return _xyzw;
}

const float& Vector4f::operator[](int i) const {
	return _xyzw[i];
}

float& Vector4f::operator[](int i) {
	return _xyzw[i];
}

Vector4f Vector4f::operator +(const Vector4f &rhs) const{
	return this->Add(rhs);
}

Vector4f Vector4f::operator +(const Vector4f &rhs){
	return this->Add(rhs);
}

Vector4f Vector4f::operator -(const Vector4f &rhs) const{
	return this->Subtract(rhs);
}

Vector4f Vector4f::operator -(const Vector4f &rhs){
	return this->Subtract(rhs);
}

Vector4f Vector4f::operator -(float rhs)const{
	return this->Subtract(rhs);
}

Vector4f &Vector4f::operator +=(const Vector4f &rhs){
	return *this=*this+rhs;
}

Vector4f &Vector4f::operator +=(float rhs){
	Vector4f vec = *this;
	vec.Assign(vec.x()+rhs,vec.y()+rhs,vec.z()+rhs,vec.w()+rhs);
	return *this=*this+vec;
}

Vector4f &Vector4f::operator *=(float rhs){
	Vector4f vec = *this;
	vec.Assign(vec.x()*rhs,vec.y()*rhs,vec.z()*rhs,vec.w()*rhs);
	return *this=*this*vec;
}

Vector4f &Vector4f::operator -=(const Vector4f &rhs){
	return *this=*this-rhs;
}

Vector4f &Vector4f::operator -=(float rhs){
	Vector4f vec = *this;
	vec.Assign(vec.x()-rhs,vec.y()-rhs,vec.z()-rhs,vec.w()-rhs);
	return *this=*this-vec;
}

Vector4f &Vector4f::operator =(const Vector4f &rhs){
	memcpy(_xyzw, rhs._xyzw, 4*sizeof(float));
	return *this;
}

Vector4f Vector4f::operator /(const int &rhs) const{
	return this->Divide(rhs);
}

Vector4f Vector4f::operator /(const float &rhs) const{
	return this->Divide(rhs);
}

Vector4f Vector4f::operator*(const Vector4f &rhs)const{
	return this->Multiply(rhs);
}

Vector4f Vector4f::operator*(const float &rhs)const{
	return this->Multiply(rhs);
}

Vector4f operator *(const float lhs, const Vector4f &rhs){
	return Vector4f(lhs*rhs.x(), lhs*rhs.y(), lhs*rhs.z(), lhs*rhs.w());
}

Vector4f operator +(float lhs, const Vector4f &rhs){
	return Vector4f(lhs+rhs.x(), lhs+rhs.y(), lhs+rhs.z(), lhs+rhs.w());
}

Vector4f operator +(const Vector4f &lhs, float rhs){
	return Vector4f(lhs.x()+rhs, lhs.y()+rhs, lhs.z()+rhs, lhs.w()+rhs);
}

Vector4f Normalise(const Vector4f &vec){
	return vec.Normalise();
}