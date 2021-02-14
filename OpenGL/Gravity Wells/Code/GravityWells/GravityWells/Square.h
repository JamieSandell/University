#pragma once
#include "Shape.h"

class Square : public Shape
{
public:
	Square(void);
	~Square(void);
	Square(const Square &A); // deep copy constructor
	Square& operator=(const Square &A); // assignment operator

	void Assign(void);
	Square* Clone()const;
	Square* CloneToAnEmptyObject()const;
	bool Create(void);
	void Assign(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture);//call this after a blank create
	bool Create(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture);
	GLfloat GetSize(void)const;
	void Draw(void) const;
	void Update(float deltaTime);

	const Vector3f &GetPosition(void) const;
	void SetPosition(const Vector3f &position);

	bool GetTextureEnabledStatus(void) const;
	void SetTextureEnabledStatus(bool status);
	GLuint GetTextureID(void) const;
	void SetTextureID(GLuint texID);

	void AllocateMemory(void);
	void CopyNonPointerDataMembers(const Square &A);
	void CopyPointerDataMembers(const Square &A);
	void DeallocateMemory(void);

private:
	float (*_vertexarray)[3];	// contains the vertices
	GLuint *_indexarray;		// index array that defines the polygons
	float (*_texarray)[2];		// texture coordinates for each vertex
	GLuint _vertexarraySize, _indexarraySize, _texarraySize;
};
