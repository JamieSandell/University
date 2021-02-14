#pragma once
#include "shape.h"

class Circle : public Shape
{
public:
	Circle(void);
	virtual ~Circle(void);
	Circle(const Circle &A); // deep copy constructor
	Circle& operator=(const Circle &A); // assignment operator

	virtual void Assign(void);
	virtual Circle* Clone()const{return new Circle(*this);};
	virtual Circle* CloneToAnEmptyObject()const;
	virtual bool Create(void){
		_vertexarraySize = _indexarraySize = _texarraySize = 1;
		Create(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f,1.0f,1.0f), false);
		return true;
	};
	virtual void Assign(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture);//call this after a blank create
	virtual bool Create(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture);
	inline GLfloat GetRadius(void)const{return this->Shape::GetHeightWidthDepth().y();};
	inline void SetRadius(float radius){this->Shape::SetWidth(radius);};
	virtual void Draw(void) const;
	inline void Update(float deltaTime){};

	inline const Vector3f &GetPosition(void) const{return this->Shape::GetPosition();};
	inline void SetPosition(const Vector3f &position){this->Shape::SetPosition(position);};

	inline bool GetTextureEnabledStatus(void) const{return this->Shape::GetTextureEnabledStatus();};
	inline void SetTextureEnabledStatus(bool status){this->Shape::SetTextureEnabledStatus(status);};
	inline GLuint GetTextureID(void) const{return this->Shape::GetTextureID();};
	inline void SetTextureID(GLuint texID){this->Shape::SetTextureID(texID);};

	void AllocateMemory(void);
	void CopyNonPointerDataMembers(const Circle &A);
	void CopyPointerDataMembers(const Circle &A);
	void DeallocateMemory(void){delete [] _vertexarray;delete [] _indexarray;delete [] _texarray;};

private:
	float (*_vertexarray)[3];	// contains the vertices
	GLuint *_indexarray;		// index array that defines the polygons
	float (*_texarray)[2];		// texture coordinates for each vertex
	const static int _stacks = 50;
	const static int _slices = 50;
	int _vertexarraySize, _indexarraySize, _texarraySize;
};
