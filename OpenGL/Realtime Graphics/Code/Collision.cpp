#include "Collision.h"

Collision::Collision(){

}

Collision::~Collision(){

}

bool Collision::ParticleCubeCollision(const Vector4f &particleCentre, float particleSize, const Shape *cube, int &planeHit)const{
	particleSize = particleSize;
	Vector4f cubeCentre = cube->GetPosition();
	float cubeSize = cube->GetHeightWidthDepth().x()/3.0f;

	if(particleCentre.x()<=cubeCentre.x()-cubeSize){
		planeHit = 0;
		return true;
	}
	if(particleCentre.x()>=cubeCentre.x()+cubeSize){
		planeHit = 1;
		return true;
	}
	if(particleCentre.y()<=cubeCentre.y()-cubeSize){
		planeHit = 2;
		return true;
	}
	if(particleCentre.y()>=cubeCentre.y()+cubeSize){
		planeHit = 3;
		return true;
	}
	if(particleCentre.z()<=cubeCentre.z()-cubeSize){
		planeHit = 4;
		return true;
	}
	if(particleCentre.z()>=cubeCentre.z()+cubeSize){
		planeHit = 5;
		return true;
	}
	return false;
}

bool Collision::QuadPlaneCollision(const Vector4f &quadCentre, float quadSize, const Vector4f &planePosition,
								   const Vector3f &planeNormal, float &outDistance)const{
    Vector3f vec3QuadPosition;
	Vector3f vec3PlanePosition;
	vec3PlanePosition.Assign(planePosition.x(), planePosition.y(), planePosition.z());
	vec3QuadPosition.Assign(quadCentre.x(), quadCentre.y(), quadCentre.z());
	float distance = planeNormal.DotProduct(vec3PlanePosition);
	distance = vec3QuadPosition.DotProduct(planeNormal)-distance;
	outDistance = distance;
	if (fabs(distance)<quadSize){//outside is touching
		return true;
	}
	else if(fabs(distance)<=quadSize){// Moved too fast and it's now intersecting at 2 points
		return true;
	}
	return false;
}

bool Collision::QuadPlanesOfACubeCollision(const Vector4f &quadCentre, float quadSize, const Shape* cube, float &outDistance)const{
	Vector4f cubeCentre = cube->GetPosition();
	float cubeSize = cube->GetHeightWidthDepth().y()/2;
	Vector4f cubePlane = cubeCentre;
	Vector3f planeNormal;

	//top plane
	cubePlane.Assign(cubeCentre.x(), cubeCentre.y()+cubeSize, cubeCentre.z(),1.0f);
	planeNormal.Assign(0.0f, -1.0f, 0.0f); //pointing down
	bool result = QuadPlaneCollision(quadCentre, quadSize, cubePlane, planeNormal, outDistance);
	if (result)
		return true;
	//bottom plane
	cubePlane = cubeCentre;
	cubePlane.Assign(cubeCentre.x(), cubeCentre.y()-cubeSize, cubeCentre.z(),1.0f);
	planeNormal.Assign(0.0f, 1.0f, 0.0f); //pointing up
	result = QuadPlaneCollision(quadCentre, quadSize, cubePlane, planeNormal, outDistance);
	if (result)
		return true;
	//left plane
	cubePlane = cubeCentre;
	cubePlane.Assign(cubeCentre.x()-cubeSize, cubeCentre.y(), cubeCentre.z(),1.0f);
		planeNormal.Assign(1.0f, 0.0f, 0.0f); //pointing right
	result = QuadPlaneCollision(quadCentre, quadSize, cubePlane, planeNormal, outDistance);
	if (result)
		return true;
	//right plane
	cubePlane = cubeCentre;
	cubePlane.Assign(cubeCentre.x()+cubeSize, cubeCentre.y(), cubeCentre.z(),1.0f);
		planeNormal.Assign(-1.0f, 0.0f, 0.0f); //pointing left
	result = QuadPlaneCollision(quadCentre, quadSize, cubePlane, planeNormal, outDistance);
	if (result)
		return true;
	//front plane
	cubePlane = cubeCentre;
	cubePlane.Assign(cubeCentre.x(), cubeCentre.y(), cubeCentre.z()+cubeSize,1.0f);
		planeNormal.Assign(0.0f, 0.0f, -1.0f); //pointing in
	result = QuadPlaneCollision(quadCentre, quadSize, cubePlane, planeNormal, outDistance);
	if (result)
		return true;
	//back plane
	cubePlane = cubeCentre;
	cubePlane.Assign(cubeCentre.x(), cubeCentre.y(), cubeCentre.z()-cubeSize,1.0f);
		planeNormal.Assign(0.0f, 0.0f, 1.0f); //pointing out
	result = QuadPlaneCollision(quadCentre, quadSize, cubePlane, planeNormal, outDistance);
	if (result)
		return true;
	return false;
}