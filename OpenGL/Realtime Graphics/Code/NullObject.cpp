#include "NullObject.h"

NullObject::NullObject(){

}

NullObject::~NullObject(){

}

void NullObject::Animate(float deltaTime, float timeElapsed){
	Vector4f pos = GetPosition();
	GetAnimation().Animate(pos, deltaTime, timeElapsed);
	SetPosition(pos);
}

void NullObject::Assign(const Vector4f *position, float size, bool texture, std::string texLocation){
	SetPosition(*position);
	SetHeightWidthDepth(&(Vector3f(size,size,size)));
	SetTextureEnabledStatus(texture);
	SetTexture(texLocation);
}

NullObject* NullObject::Clone()const{
	return new NullObject(*this);
}

NullObject* NullObject::CloneToAnEmptyObject()const{
	NullObject *p = new NullObject;
	p->Create();
	*p = *this;
	return p;
}

bool NullObject::Create(){
	SetPosition(Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
	SetHeightWidthDepth(&(Vector3f(0.0f, 0.0f, 0.0f)));
	SetTextureEnabledStatus(false);
	SetTexture("");
	return true;
}

bool NullObject::Create(const Vector4f *position, float size, bool texture, std::string texLocation){
	Assign(position, size, texture, texLocation);
	return true;
}

void NullObject::Update(float deltaTime, float timeElapsed){
}

void NullObject::Draw() const{

}