#pragma once

#include <vector>
#include "Vector3f.h"
#include "Vector4f.h"
#include "Shape.h"

class Octahedron : public Shape{
public:
	Octahedron(void);
	virtual ~Octahedron(void);
	Octahedron(const Octahedron &A); //deep copy constructor
	Octahedron& operator=(const Octahedron &A); // assignment operator
	void Animate(float deltaTime, float timeElapsed);
	void Assign(void);
	void Assign(const Vector4f *xyzw, float size, bool textureEnabled, std::string texLocation); //call this after create
	Octahedron* Clone()const;
	Octahedron* CloneToAnEmptyObject()const;
	bool Create(void);
	bool Create(const Vector4f *xyzw, float size, bool textureEnabled, std::string texLocation);
	void Draw(void) const;
	void DrawNormals(void)const;
	void GeneratePhysicalNormals(void);
	Vector3f GetHeightWidthDepth(void) const;
	const Vector4f &GetPosition(void) const;
	bool GetTextureEnabledStatus(void) const;
	GLuint GetTextureID(void)const;
	void SetAnimationCoefficients(const std::vector<Vector3f> &animation);
	void SetHeightWidthDepth(const Vector3f *hWD);
	void SetTexture(std::string image);
	void SetTextureEnabledStatus(bool status);
	void SetTextureID(GLuint texID);
	virtual void Update();
	void Update(float deltaTime, float timeElapsed);

private:
	void AllocateMemory(void);
	void CopyNonPointerDataMembers(const Octahedron &A);
	void CopyPointerDataMembers(const Octahedron &A);
	void DeallocateMemory(void);

private:
	GLfloat (*_vertexArray)[3];
	GLfloat (*_normalArray)[3];
	GLfloat (*_normalVertexArray)[3]; //used for DrawNormals()
	GLfloat (*_texArray)[2];
	GLuint *_indexArray;
	GLuint *_normalVertexIndexArray;
	GLuint _vertexArraySize, _normalArraySize, _indexArraySize, _texArraySize, _textureID, _normalVertexArraySize;
	GLuint _normalVertexIndexArraySize;
	Vector4f _defaultOctahedronPosition;
	Vector3f _defaultOctahedronHeightWidthDepth;
};