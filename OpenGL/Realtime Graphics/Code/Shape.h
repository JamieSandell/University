#pragma once

#include <vector>
#include <string>
#include "Vector3f.h"
#include "Vector4f.h"
#include "Animation.h"
#include "Materials.h"

class Shape
{
public:
	Shape(void);
	virtual ~Shape();//virtual destructor

	virtual void Animate(float deltaTime, float timeElapsed);//virtual function, overload or use default
	void ApplyMaterial(void)const;
	virtual void Assign(const Vector4f *position, float size, bool texture, std::string texLocation) = 0;//pure virtual must provide your own
	virtual Shape* CloneToAnEmptyObject()const = 0;//pure virtual must provide your own Calls create
	virtual Shape* Clone()const = 0;//pure virtual must provide your own Calls copy constructor
	virtual bool Create(void) = 0;//pure virtual must provide your own
	virtual bool Create(const Vector4f *position, float size, bool texture, std::string texLocation) = 0;//pure virtual must provide your own
	virtual void Update(float deltaTime, float timeElapsed) = 0;//pure virtual must provide your own
	virtual void Draw() const = 0;//pure virtual must provide your own
	virtual void DrawNormals(void) const;
	void CalculateFaceConnectivity(int faceConnectivityArray[], int sizeOfFaceConnectivityArray,
		const Vector3f (*vertexArray)[3], int sizeOfVertexArray, int numberOfFaces, const int faceTable[]) const;//faceTable links each vertex of the shape with one of the shapes faces
	void CalculateVertexNormals(int numberOfFaces, GLfloat(*normalArray)[3], GLfloat(*vertexArray)[3], int sizeOfArrays,
		int numberOfFaceConnectionsPerFace, int numberOfVerticesPerFace) const;//Calls Vector3f.CalculateFaceNormals
	void CopyBaseMembers(const Shape &source);
	void InverseNormals(GLfloat (*normalArray)[3], GLuint normalArraySize);
	virtual void InverseNormals(); //nop method

public: // accessors
	Animation GetAnimation(void) const;
	void SetAnimation(const Animation &animation);

	void SetAnimationCoefficients(const std::vector<Vector3f> &animation);

	virtual void SetCollisionObject(const Shape *shape);//nop method

	Vector3f GetHeightWidthDepth(void) const;
	void SetHeightWidthDepth(const Vector3f *hWD);

	virtual const Vector4f &GetPosition(void) const;
	void SetPosition(const Vector4f &position);

	void SetTextureEnabledStatus(bool status);
	bool GetTextureEnabledStatus() const;

	void SetTexture(std::string image); // e.g. image = "images/"myTexture.bmp""
	std::string GetTexture(void) const;

	virtual GLuint GetTextureID(void) const; // for binding textures
	virtual	void SetTextureID(GLuint textureID);

	Vector3f GetDirectionVector(void)const;
	void SetDirectionVector(const Vector3f &directionVector);

	void SetInitialPosition(const Vector4f &initialPosition);

	void SetMaterial(const Materials &material);
private:
	Vector3f _heightWidthDepth, _directionVector;
	Vector4f _position, _initialPosition;
	bool _textureEnabled;
	std::string _image;
	Animation _animation;
	Materials _material;
};
