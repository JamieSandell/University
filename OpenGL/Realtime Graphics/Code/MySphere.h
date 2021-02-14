#pragma once

#include <vector>
#include <iostream>
#include "GXBase.h"
#include "Shape.h"
#include "Vector4f.h"

class MySphere : public Shape{
private:
	float (*_vertexarray)[3];	// contains the vertices
	float (*_normalarray)[3];	// contains the normals to each vertex
	GLfloat (*_normalVertexArray)[3]; //used for DrawNormals()
	GLuint *_indexarray;		// index array that defines the polygons
	GLuint *_normalVertexIndexArray;
	float (*_texarray)[2];		// texture coordinates for each vertex
	GLuint _vertexarraySize, _normalarraySize, _indexarraySize, _texarraySize, _textureID, _normalVertexArraySize;
	GLuint _normalVertexIndexArraySize;
	Vector4f _defaultSpherePosition;
	GLfloat _radius;
	static const int _slices = 10;
	static const int _stacks = 10;

public:
	MySphere();//call create if you're using the default constructor
	virtual ~MySphere(); // virtual because will be inherited from glowball and particle ball
	MySphere(const MySphere &A); // deep copy constructor
	MySphere& operator=(const MySphere &A); // assignment operator

	void Assign(void);
	virtual MySphere* Clone()const;
	virtual MySphere* CloneToAnEmptyObject()const;
	bool Create(void);
	void Assign(const Vector4f *position, float radius, bool texture, std::string texLocation);//call this after a blank create
	virtual bool Create(const Vector4f *position, float radius, bool texture, std::string texLocation);
	void GeneratePhysicalNormals(void);
	GLfloat GetRadius(void)const;
	GLuint GetTextureID(void)const;
	void Draw(void) const;
	void DrawNormals(void)const;
	void InverseNormals(void);//Calls GeneratePhysicalNormals
	void Update(float deltaTime, float timeElapsed);
	void Update();

	void SetAnimationCoefficients(const std::vector<Vector3f> &animation);
	const Vector4f &GetPosition(void) const;
	void SetPosition(const Vector4f &position);

	void SetTexture(std::string image);
	bool GetTextureEnabledStatus(void) const;
	void SetTextureEnabledStatus(bool status);
	void SetTextureID(GLuint texID);

	void AllocateMemory(void);
	void CopyNonPointerDataMembers(const MySphere &A);
	void CopyPointerDataMembers(const MySphere &A);
	void DeallocateMemory(void);
};

