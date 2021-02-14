#include "Glowball.h"
#include "Vector4f.h"

using std::vector;
using std::copy;

Glowball::Glowball(){

}

Glowball::~Glowball(){

}

void Glowball::Activate(void){
	_glowballActivated = true;
	for(int i = 0; i < 6; i++){
		_lights[i].create(i, Color::black(), Color(1.0f,0.0f,0.0f,1.0f), Vector4f(0.0,0.0,0.0,1.0));//position of the light will be set later
	}
	_lights[0].setDiffuse(Color(0.0f,1.0f,0.0f,1.0f));
	_lights[0].setDiffuse(Color(1.0f,0.0f,0.0f,1.0f));
	_lights[2].setDiffuse(Color(0.0f,0.0f,1.0f,1.0f));
	_lights[3].setDiffuse(Color(1.0f,1.0f,0.0f,1.0f));
	_lights[4].setDiffuse(Color(1.0f,0.0f,1.0f,1.0f));
	_lights[5].setDiffuse(Color(1.0f,1.0f,1.0f,1.0f));

	_lights[0].setSpot(45.0f, 5.0f);
	_lights[1].setSpot(45.0f, 5.0f);
	_lights[2].setSpot(45.0f, 5.0f);
	_lights[3].setSpot(45.0f, 5.0f);
	_lights[4].setSpot(45.0f, 5.0f);
	_lights[5].setSpot(45.0f, 5.0f);

	glDisable(GL_LIGHT6); //disable the two lights not used
	glDisable(GL_LIGHT7);

	InverseNormals();
}

void Glowball::Assign(void){
	Vector4f position;
	MySphere::Create(&position, 1.0f, false, "");
	_glowBallCentre = MySphere::GetPosition()/2;
	_glowBallRadius = MySphere::GetRadius();
	_lightPosition.resize(6);
}

void Glowball::Assign(const Vector4f *position, float radius, bool texture, std::string texLocation){
	MySphere::Create(position, radius, texture, texLocation);
	_glowBallCentre.Assign(position->x(), position->y(), position->z(), position->w());
	_glowBallRadius = radius;
	_lightPosition.resize(6);
}

Glowball* Glowball::Clone() const{
	return new Glowball(*this);
}

Glowball* Glowball::CloneToAnEmptyObject()const{
	Glowball *p = new Glowball;
	p->Create();
	*p = *this;
	return p;
}

bool Glowball::Create(void){
	Assign();
	Activate();
	return true;
}

bool Glowball::Create(const Vector4f *position, float radius, bool texture, std::string texLocation){
	Assign(position, radius, texture, texLocation);
	Activate();
	return true;
}

void Glowball::InverseNormals(){
	this->MySphere::InverseNormals();
}

void Glowball::PositionLights(void){
	Vector3f lightDir;
	for (int i = 0; i < 6; i++){
		_lightPosition[i].Assign(GetPosition().x(),GetPosition().y(),GetPosition().z(),1.0f);
	}
	lightDir.Assign(0.0f, 1.0f, 0.0f);
	_lights[0].setPosition(_lightPosition[0]); // top light
	_lights[0].setDirection(lightDir);
	lightDir.Assign(0.0f, -1.0f, 0.0f);
	_lights[1].setPosition(_lightPosition[1]); // bottom light
	_lights[1].setDirection(lightDir);
	lightDir.Assign(-1.0f, 0.0f, 0.0f);
	_lights[2].setPosition(_lightPosition[2]); // left light
	_lights[2].setDirection(lightDir);
	lightDir.Assign(1.0f, 0.0f, 0.0f);
	_lights[3].setPosition(_lightPosition[3]); // right light
	_lights[3].setDirection(lightDir);
	lightDir.Assign(0.0f, 0.0f, 1.0f);
	_lights[4].setPosition(_lightPosition[4]); // front light
	_lights[4].setDirection(lightDir);
	lightDir.Assign(0.0f, 0.0f, -1.0f);
	_lights[5].setPosition(_lightPosition[5]); // back light
	_lights[5].setDirection(lightDir);
}

void Glowball::Update(){

}
void Glowball::Update(float deltaTime, float elapsedTime){
	MySphere::Update(deltaTime, elapsedTime);
	PositionLights();
}