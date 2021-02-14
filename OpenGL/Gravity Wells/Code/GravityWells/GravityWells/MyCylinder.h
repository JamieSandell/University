#pragma once

#include <vector>
#include "GXBase.h"
#include "Shape.h"
#include "Vector4f.h"
#include "Vector3f.h"

class MyCylinder : public Shape {
private:

public:
	MyCylinder(); //call create if you're using the default constructor
	virtual ~MyCylinder();
	MyCylinder(const MyCylinder &A); // deep copy constructor
	MyCylinder& operator=(const MyCylinder &A); // assignment operator

	inline void Assign(){};
	inline MyCylinder* Clone()const{return new MyCylinder(*this);};
	inline MyCylinder* CloneToAnEmptyObject()const{
		MyCylinder *p = new MyCylinder;
		p->Create();
		*p = *this;
		return p;
	};
	bool Create();//Calls GeneratePhysicalNormals
	inline void Assign(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture){
		DeallocateMemory(); // remove the old memory
		Create(position, heightWidthDepth, texture);
	};// call this after create
	bool Create(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture);
	void Draw() const;
	inline void Update(){};
	inline void Update(float deltaTime){};
	inline void SetPosition(const Vector3f &position){this->Shape::SetPosition(position);};
	inline const Vector3f &GetPosition(void) const{return this->Shape::GetPosition();};

private:
	inline void AllocateMemory(void){
		_vertexarray = new float[_vertexarraySize][3];
		_texarray = new float[_texarraySize][2];
		_indexarray = new GLuint[_indexarraySize];}
	;
	inline void CopyNonPointerDataMembers(const MyCylinder &A){
		// Copy non-pointer data members
		_indexarraySize = A._indexarraySize;
		_texarraySize = A._texarraySize;
		_vertexarraySize = A._vertexarraySize;
		CopyBaseMembers(A);
	};
	inline void CopyPointerDataMembers(const MyCylinder &A){
		// C++ guarantee that elements of multidimensional arrays occupy contiguous memory addresses
		// this is quicker then the for-loop method
		// Copy pointer data members
		memcpy(_vertexarray, A._vertexarray, _vertexarraySize*sizeof(float)*3); //*3 because array[][3]
		memcpy(_texarray, A._texarray, _texarraySize*sizeof(float)*2);
		memcpy(_indexarray, A._indexarray, _indexarraySize*sizeof(float));
	};
	inline void DeallocateMemory(void){	delete [] _vertexarray;delete [] _indexarray;delete [] _texarray;};

	float (*_vertexarray)[3]; // contains the vertices
	GLuint *_indexarray; // index array that defines the polygons
	float (*_texarray)[2]; // texture coordinates for each vertex
	const static int _stacks = 2;
	const static int _slices = 35;
	int _vertexarraySize, _indexarraySize, _texarraySize;
};