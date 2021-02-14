#pragma once

#include <vector>
#include "Vector4f.h"
#include "Vector3f.h"
#include "Shape.h"

class Cube : public Shape
{
public:
	Cube(void);//call create if you're using the default constructor
	virtual ~Cube();
	Cube(const Cube &A); // deep copy constructor
	Cube& operator=(const Cube &A); // assignment operator
	void Animate(float deltaTime, float timeElapsed);
	void Assign(const Vector4f *xyzw, float size, bool texEnabled, std::string texLocation); 
	Cube* Clone()const;
	Cube* CloneToAnEmptyObject()const;
	bool Create(void);
	bool Create(const Vector4f *xyzw, float size, bool texEnabled, std::string texLocation);
	void Draw(void) const;
	void DrawNormals(void)const;
	void GeneratePhysicalNormals(void);
	Vector3f GetDirectionVector(void) const;
	const Vector4f& GetPosition(void) const;
	Vector3f GetHeightWidthDepth(void) const;
	Vector4f GetOldPosition(void)const;
	bool GetTextureEnabledStatus(void) const;
	GLuint GetTextureID(void)const;
	void InverseNormals();//Calls GeneratePhysicalNormals
	void SetAnimationCoefficients(const std::vector<Vector3f> &animation);
	void SetDirectionVector(const Vector3f &directionVector);
	void SetHeightWidthDepth(const Vector3f *hWD);
	void SetSplitSize(int splitSize);
	void SetTexture(std::string image);
	void SetTextureEnabledStatus(bool status);
	void SetTextureID(GLuint texID);
	void Update(float deltaTime, float timeElapsed);

private:
	void DeallocateMemory(void);
	void AllocateMemory(void);
	void CopyNonPointerDataMembers(const Cube &A);
	void CopyPointerDataMembers(const Cube &A);

private:
	Vector4f _oldPosition;
	GLfloat (*_vertexArray)[3];
	GLfloat (*_normalArray)[3];
	GLfloat (*_texArray)[2];
	GLfloat (*_normalVertexArray)[3]; //used for DrawNormals()
	GLuint *_indexArray;
	GLuint *_normalVertexIndexArray;
	GLuint _splitSize, _vertexArraySize, _normalArraySize, _indexArraySize, _texArraySize, _textureID, _normalVertexArraySize;
	GLuint _normalVertexIndexArraySize;
	Vector4f _defaultCubePosition;
	float _defaultCubeSize;
	std::vector<Vector3f> _defaultAnimation;
};
