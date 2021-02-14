#include "GravityWell.h"

GravityWell::GravityWell(void)
{
}

GravityWell::~GravityWell(void)
{
}

GravityWell& GravityWell::operator =(const GravityWell &A){
	if (&A != this){
		Circle::operator =(A);
		this->_force = A._force;
		this->_currentState = A._currentState;
		//this->Assign(this->GetPosition(), this->)
	}
	return *this;
}

void GravityWell::Assign(void){
	this->Circle::Assign();
}

void GravityWell::Assign(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture){
	this->Circle::Assign(position, heightWidthDepth, texture);
}

bool GravityWell::Create(void){
	_force = 0.0f;
	_currentState = 0;
	return this->Circle::Create();
}

bool GravityWell::Create(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture){
	//_force = 0.0f;
	//_currentState = 0;
	return this->Circle::Create(position, heightWidthDepth, texture);
}

void GravityWell::Draw(void) const{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	this->Circle::Draw();
	glDisable(GL_BLEND);
}