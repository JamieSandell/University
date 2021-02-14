#pragma once

#include <vector>
#include "Vector3f.h"
#include "Vector4f.h"
#include "Shape.h"

class Tetrahedron : public Shape {
public:
	Tetrahedron(void);
	virtual ~Tetrahedron(void);
	Tetrahedron(const Tetrahedron &A); // Deep copy constructor
	Tetrahedron& operator=(const Tetrahedron &A); // assignment operator
	void Assign(const Vector4f *position, float size, bool textureEnabled, std::string texLocation);
	Tetrahedron* Clone()const;
	Tetrahedron* CloneToAnEmptyObject()const;
	bool Create(void);
	virtual bool Create(const Vector4f *position, float size, bool textureEnabled, std::string texLocation);
	virtual void Draw(void) const;
	void DrawNormals(void)const;
	void GeneratePhysicalNormals(void);
	const Vector4f &GetPosition(void) const;
	Vector3f GetHeightWidthDepth(void) const;
	bool GetTextureEnabledStatus(void) const;
	GLuint GetTextureID(void)const;
	void SetAnimationCoefficients(const std::vector<Vector3f> &animation);
	void SetHeightWidthDepth(const Vector3f *hWD);
	void SetTexture(std::string image);
	void SetTextureEnabledStatus(bool status);
	void SetTextureID(GLuint textureID);
	void Update(float deltaTime, float timeElapsed);
private:
	void DeallocateMemory(void);
	void AllocateMemory(void);
	void CopyNonPointerDataMembers(const Tetrahedron &A);
	void CopyPointerDataMembers(const Tetrahedron &A);

private:
	GLfloat (*_vertexArray)[3];
	GLfloat (*_normalArray)[3];
	GLfloat (*_texArray)[2];
	GLfloat (*_normalVertexArray)[3]; //used for DrawNormals()
	GLuint *_indexArray;
	GLuint *_normalVertexIndexArray;
	GLuint _vertexArraySize, _normalArraySize, _indexArraySize, _texArraySize, _textureID, _normalVertexArraySize;
	GLuint _normalVertexIndexArraySize;
	Vector4f _defaultTetrahedronPosition;
	Vector3f _defaultTetrahedronHeightWidthDepth;
	const static float _defaultTetrahedronSize;
};