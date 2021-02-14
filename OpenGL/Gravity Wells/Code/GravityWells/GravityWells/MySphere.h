#pragma once

#include <vector>
#include <iostream>
#include "GXBase.h"
#include "Shape.h"
#include "Vector4f.h"

static const int _slices = 50;
static const int _stacks = 50;
static const int array_size = (_slices+1)*(_stacks-1)+2;	// +2 is for the top and bottom vertex
static const GLuint _vertexarraySize = array_size;;
static const GLuint _normalarraySize = array_size;;
static const GLuint _indexarraySize = 2+(_stacks-1)*(_slices+1)*2;;
static const GLuint _texarraySize = array_size;
static const GLuint _normalVertexIndexArraySize = array_size*2;
static const GLuint _normalVertexArraySize = array_size*2;
static float _vertexarray[_vertexarraySize][3];
static float _normalarray[_normalarraySize][3];
static GLuint _indexarray[_indexarraySize];
static float _texarray[_texarraySize][2];
static float _normalVertexArray[_normalVertexArraySize][3];
static GLuint _normalVertexIndexArray[_normalVertexIndexArraySize];

class MySphere : public Shape{
private:
	GLfloat _radius;

public:
	MySphere();//call create if you're using the default constructor
	~MySphere();
	MySphere(const MySphere &A); // deep copy constructor
	MySphere& operator=(const MySphere &A); // assignment operator

	inline void Assign(void){};
	inline virtual MySphere* Clone()const{return new MySphere(*this);};
	virtual MySphere* CloneToAnEmptyObject()const{
		MySphere *p = new MySphere;
		p->Create();
		*p = *this;
		return p;
	};
	bool Create(void);
	void Assign(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture){
		DeallocateMemory(); // remove the old memory
		Create(position, heightWidthDepth, texture);
	};//call this after a blank create
	virtual bool Create(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture);
	inline GLfloat GetRadius(void)const{return _radius;};
	void Draw(void) const;
	inline void Update(float deltaTime){};

	inline const Vector3f &GetPosition(void) const{return this->Shape::GetPosition();};
	inline void SetPosition(const Vector3f &position){this->Shape::SetPosition(position);};

	inline bool GetTextureEnabledStatus(void) const{return this->Shape::GetTextureEnabledStatus();};
	inline void SetTextureEnabledStatus(bool status){this->Shape::SetTextureEnabledStatus(status);};
	inline GLuint GetTextureID(void) const{return this->Shape::GetTextureID();};
	inline void SetTextureID(GLuint texID){this->Shape::SetTextureID(texID);};

	void AllocateMemory(void);
	void CopyNonPointerDataMembers(const MySphere &A);
	void CopyPointerDataMembers(const MySphere &A);
	void DeallocateMemory(void);
};

