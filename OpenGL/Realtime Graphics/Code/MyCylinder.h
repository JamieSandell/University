#pragma once

#include <vector>
#include "GXBase.h"
#include "Shape.h"
#include "Vector4f.h"
#include "Vector3f.h"

class MyCylinder : public Shape {
private:
	// TODO: Gang of Three
	float (*_vertexarrayTop)[3];	// contains the vertices
	float (*_vertexarrayBody)[3];	// contains the vertices
	float (*_vertexarrayBottom)[3];	// contains the vertices
	float (*_normalarrayTop)[3];	// contains the normals to each top and bottom vertex
	float (*_normalarrayBody)[3];	// contains the normals to each top and bottom vertex
	float (*_normalarrayBottom)[3];	// contains the normals to each top and bottom vertex
	GLfloat (*_normalVertexArrayBottom)[3]; //used for DrawNormals()
	GLfloat (*_normalVertexArrayTop)[3]; //used for DrawNormals()
	GLfloat (*_normalVertexArrayBody)[3]; //used for DrawNormals()
	GLuint *_indexarrayTop;			// index array that defines the polygons
	GLuint *_indexarrayBody;			// index array that defines the polygons
	GLuint *_indexarrayBottom;			// index array that defines the polygons
	GLuint *_normalVertexIndexArrayTop;//used for DrawNormals()
	GLuint *_normalVertexIndexArrayBody;//used for DrawNormals()
	GLuint *_normalVertexIndexArrayBottom;//used for DrawNormals()
	float (*_texarrayTop)[2];	// texture coordinates for each vertex
	float (*_texarrayBody)[2];		// texture coordinates for each vertex
	float (*_texarrayBottom)[2];	// texture coordinates for each vertex
	GLuint _vertexarrayBodySize, _vertexarrayBottomSize, _vertexarrayTopSize;
	GLuint _indexarrayBodySize, _indexarrayBottomSize, _indexarrayTopSize;
	GLuint _normalarrayBodySize, _normalarrayBottomSize, _normalarrayTopSize;
	GLuint _texarrayBodySize, _texarrayBottomSize, _texarrayTopSize;
	GLuint _normalVertexArrayBodySize, _normalVertexArrayBottomSize, _normalVertexArrayTopSize;//used for DrawNormals()
	GLuint _normalVertexIndexArrayBodySize, _normalVertexIndexArrayBottomSize, _normalVertexIndexArrayTopSize;//used for DrawNormals()
	Vector4f _defaultSpherePosition;
	float xAngle,yAngle;
	static const float _topRadius;
	static const int _slices = 10;
	static const int _stacks = 5;

public:
	MyCylinder(); //call create if you're using the default constructor
	virtual ~MyCylinder();
	MyCylinder(const MyCylinder &A); // deep copy constructor
	MyCylinder& operator=(const MyCylinder &A); // assignment operator

	void Animate(float deltaTime, float timeElapsed);
	void Assign();
	MyCylinder* Clone()const;
	MyCylinder* CloneToAnEmptyObject()const;
	bool Create();//Calls GeneratePhysicalNormals
	void Assign(const Vector4f *position, float bottomRadius, bool texture, std::string texLocation);// call this after create
	bool Create(const Vector4f *position, float bottomRadius, bool texture, std::string texLocation);
	void Draw() const;
	void DrawNormals(void)const;
	void GeneratePhysicalNormals(void);
	void Update();
	void Update(const Vector4f &objectToPointAt);
	void Update(float deltaTime, float timeElapsed);
	void SetAnimationCoefficients(const std::vector<Vector3f> &animation);
	void SetPosition(const Vector4f &position);
	const Vector4f &GetPosition(void);

private:
	void AllocateMemory(void);
	void CopyNonPointerDataMembers(const MyCylinder &A);
	void CopyPointerDataMembers(const MyCylinder &A);
	void DeallocateMemory(void);
};