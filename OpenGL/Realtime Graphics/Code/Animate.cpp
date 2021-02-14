#include "Animation.h"

Animation::Animation(){

}

Animation::~Animation(){

}

void Animation::Animate(Vector3f &objectPosition, const float deltaTime){
	objectPosition.AssignX(_aI.x()*sin(_bI.x()*deltaTime+_cI.x())+_dI.x());
	objectPosition.AssignY(_aI.y()*sin(_bI.y()*deltaTime+_cI.y())+_dI.y());
	objectPosition.AssignZ(_aI.z()*sin(_bI.z()*deltaTime+_cI.z())+_dI.z());
}

void Animation::Animate(Vector4f &objectPosition, float deltaTime, float timeElapsed){
	Vector4f vec;
	vec.Assign((_aI.x()*sin(_bI.x()*timeElapsed+_cI.x())+_dI.x()), (_aI.y()*sin(_bI.y()*timeElapsed+_cI.y())+_dI.y()),
		(_aI.z()*sin(_bI.z()*timeElapsed+_cI.z())+_dI.z()),1.0f);
	objectPosition=objectPosition+(vec*deltaTime);
}

void Animation::Assign(const std::vector<Vector3f> &coefficients){
	_aI = coefficients[0];
	_bI = coefficients[1];
	_cI = coefficients[2];
	_dI = coefficients[3];
}

void Animation::Assign(const Vector3f &aI, const Vector3f &bI, const Vector3f &cI, const Vector3f &dI){
	_aI = aI;
	_bI = bI;
	_cI = cI;
	_dI = dI;
}

void Animation::Assign(const Vector3f coefficients[]){
	_aI = coefficients[0];
	_bI = coefficients[1];
	_cI = coefficients[2];
	_dI = coefficients[3];
}

bool Animation::Create(){
	_aI.Assign(0.0f, 0.0f, 0.0f);
	_bI.Assign(0.0f, 0.0f, 0.0f);
	_cI.Assign(0.0f, 0.0f, 0.0f);
	_dI.Assign(0.0f, 0.0f, 0.0f);
	_directionVector.Assign(0.0f,1.0f,0.0f);
	return true;
}

bool Animation::Create(const Vector3f &aI, const Vector3f &bI, const Vector3f &cI, const Vector3f &dI){
	Assign(aI, bI, cI, dI);
	return true;
}

Vector3f Animation::GetDirectionVector(void) const{
	return _directionVector;
}

void Animation::SetDirectionVector(const Vector3f &directionVector){
	_directionVector = directionVector;
}