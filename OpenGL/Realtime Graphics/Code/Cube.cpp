#include <cmath>
#include <iostream>
#include "Cube.h"

using namespace std;

Cube::Cube(void)
{
}

Cube::~Cube()
{
	DeallocateMemory();
}

Cube::Cube(const Cube &A) {
	DeallocateMemory();
	AllocateMemory();
	CopyNonPointerDataMembers(A);
	CopyPointerDataMembers(A);
}

Cube& Cube::operator=(const Cube &A){
	if (this != &A){ // the address of the object is essentially an ID to tell objects apart, don't delete itself
		CopyNonPointerDataMembers(A);
		DeallocateMemory();
		AllocateMemory();// make sure the pointer members have enough space allocated for the memcpy
		CopyPointerDataMembers(A);
	}
	return *this;
}

void Cube::AllocateMemory(void){
	_vertexArray = new GLfloat [_vertexArraySize][3];
	_normalArray = new GLfloat [_normalArraySize][3];
	_texArray = new GLfloat [_texArraySize][2];
	_indexArray  = new GLuint [_indexArraySize];
	_normalVertexArray = new GLfloat [_normalVertexArraySize][3];
	_normalVertexIndexArray = new GLuint [_normalVertexIndexArraySize];
}

void Cube::Animate(float deltaTime, float timeElapsed){
	Vector4f pos = GetPosition();
	Vector4f oldPos = GetPosition();
	GetAnimation().Animate(pos, deltaTime, timeElapsed);
	Vector4f directionVector = oldPos.DirectionVectorBetweenTwoPoints(oldPos, pos);
	Vector3f dirVector;
	dirVector.Assign(directionVector.x(), directionVector.y(), directionVector.z());
	SetDirectionVector(dirVector);
	SetPosition(pos);
}
void Cube::Assign(const Vector4f *xyzw, float size, bool texEnabled, std::string texLocation){
	DeallocateMemory(); // remove the old memory
	Create(xyzw, size, texEnabled, texLocation);
}

void Cube::DeallocateMemory(void){
	delete [] _vertexArray;
	delete [] _normalArray;
	delete [] _texArray;
	delete [] _indexArray;
	delete [] _normalVertexArray;
	delete [] _normalVertexIndexArray;
}

void Cube::DrawNormals(void)const{
	glDisable(GL_LIGHTING);
	glColor3f(1.0f,1.0f,1.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _normalVertexArray);
	glDrawElements(GL_LINES, _normalVertexIndexArraySize, GL_UNSIGNED_INT, _normalVertexIndexArray);//_normalVertexIndexArraySize
	glDisableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_LIGHTING);
}

Cube* Cube::CloneToAnEmptyObject()const{
	Cube *p = new Cube;
	p->Create();
	*p = *this;
	return p;
}

Cube* Cube::Clone()const{
	return new Cube(*this);
}

void Cube::CopyNonPointerDataMembers(const Cube &A){
	// Copy non-pointer data members
	_splitSize = A._splitSize;
	_indexArraySize = A._indexArraySize;
	_normalArraySize = A._normalArraySize;
	_vertexArraySize = A._vertexArraySize;
	_texArraySize = A._texArraySize;
	_defaultCubePosition = A._defaultCubePosition;
	_defaultCubeSize = A._defaultCubeSize;
	_oldPosition = A._oldPosition;
	_textureID = A._textureID;
	_normalVertexIndexArraySize = A._normalVertexIndexArraySize;
	_normalVertexArraySize = A._normalVertexArraySize;
	copy(A._defaultAnimation.begin(), A._defaultAnimation.end(), _defaultAnimation.begin());
	CopyBaseMembers(A);
}

void Cube::CopyPointerDataMembers(const Cube &A) {
	// C++ guarantee that elements of multidimensional arrays occupy contiguous memory addresses
	// this is quicker then the for-loop method
	// Copy pointer data members
	memcpy(_vertexArray, A._vertexArray, _vertexArraySize*sizeof(float)*3); // destination, source, size
	memcpy(_normalArray, A._normalArray, _normalArraySize*sizeof(float)*3); // *3 because array[][3]
	memcpy(_texArray, A._texArray, _texArraySize*sizeof(float)*2); // *2 because array[][2]
	memcpy(_indexArray, A._indexArray, _indexArraySize*sizeof(GLuint));
	memcpy(_normalVertexArray, A._normalVertexArray, _normalVertexArraySize*sizeof(float)*3); // *3 because array[][3]
	memcpy(_normalVertexIndexArray, A._normalVertexIndexArray, _normalVertexIndexArraySize*sizeof(GLuint)); // *3 because array[][3]
}

const Vector4f &Cube::GetPosition(void) const {
	return this->Shape::GetPosition();
}

Vector3f Cube::GetHeightWidthDepth(void) const {
	return this->Shape::GetHeightWidthDepth();
}

void Cube::InverseNormals(){
	this->Shape::InverseNormals(_normalArray, _normalArraySize);
	GeneratePhysicalNormals();
}

Vector4f Cube::GetOldPosition(void)const{
	return _oldPosition;
}
GLuint Cube::GetTextureID(void) const{
	return _textureID;
}
bool Cube::GetTextureEnabledStatus(void) const{
	return this->Shape::GetTextureEnabledStatus();
}
bool Cube::Create(void)
{
	_vertexArraySize = 1;
	_indexArraySize = 1;
	_normalArraySize = 1;
	_texArraySize = 1;
	_splitSize = 1;
	_normalVertexIndexArraySize = 1;
	_normalVertexArraySize = 1;
	Create(&_defaultCubePosition, _defaultCubeSize, false, "");
	return true;
}

bool Cube::Create(const Vector4f *xyzw, float size, bool texEnabled, string texLocation) {
//(* index array of vertex array for glDrawElements()
//   Notice the indices are listed straight from beginning to end as exactly
//   same order of vertex array without hopping, because of different normals at
//   a shared vertex. For this case, glDrawArrays() and glDrawElements() have no
//   difference. *)

	_splitSize = 1; // equals 1 by default, can call set method later, used for tessellation if non-phong shading used
	float height = size / 2.0f; // divide hWD by 2 so when drawing, we are drawing from the centre of the object
	float width = height;
	float depth = height;
	int arraySize;

	if (_splitSize==1) {
		arraySize = 24;
	}
	else {
		arraySize = 24; // this needs changing
	}
	_vertexArraySize = arraySize;
	_normalArraySize = arraySize;
	_indexArraySize = arraySize;
	_texArraySize = arraySize;
	_normalVertexIndexArraySize = arraySize*2;
	_normalVertexArraySize = _normalVertexIndexArraySize;
	AllocateMemory();

	for (int i = 0; i < arraySize; i++){
		_indexArray[i] = i;
	}

	int numberOfFaces = 6;
	//Vector3f *faceNormals = new Vector3f[numberOfFaces];

	// front side top right corner v0
	_normalArray[0][0] = 0.0f;
	_normalArray[0][1] = 0.0f;
	_normalArray[0][2] = 1.0f;
	_texArray[0][0] = 1.0f;
	_texArray[0][1] = 1.0f;
	_vertexArray[0][0] = +width; // x
	_vertexArray[0][1] = +height; // y
	_vertexArray[0][2] = +depth; // z
	// front side top left corner v1
	_normalArray[1][0] = 0.0f;
	_normalArray[1][1] = 0.0f;
	_normalArray[1][2] = 1.0f;
	_texArray[1][0] = 0.0f;
	_texArray[1][1] = 1.0f;
	_vertexArray[1][0] = -width;
	_vertexArray[1][1] = +height;
	_vertexArray[1][2] = +depth;
	// front side bottom left corner v2
	_normalArray[2][0] = 0.0f;
	_normalArray[2][1] = 0.0f;
	_normalArray[2][2] = 1.0f;
	_texArray[2][0] = 0.0f;
	_texArray[2][1] = 0.0f;
	_vertexArray[2][0] = -width;
	_vertexArray[2][1] = -height;
	_vertexArray[2][2] = +depth;
	// front side bottom right corner v3
	_normalArray[3][0] = 0.0f;
	_normalArray[3][1] = 0.0f;
	_normalArray[3][2] = 1.0f;
	_texArray[3][0] = 1.0f;
	_texArray[3][1] = 0.0f;
	_vertexArray[3][0] = +width;
	_vertexArray[3][1] = -height;
	_vertexArray[3][2] = +depth;
	Vector3f v0, v1, v2;
	Vector3f normal;
	//// Calculate face normals
	//v0.Assign(_vertexArray[0][0], _vertexArray[0][1], _vertexArray[0][2]);
	//v1.Assign(_vertexArray[1][0], _vertexArray[1][1], _vertexArray[1][2]);
	//v2.Assign(_vertexArray[2][0], _vertexArray[2][1], _vertexArray[2][2]);
	//faceNormals[0] = normal.CalculateFaceNormals(v0, v1, v2); // test code, should return 0,0,-1


	_normalArray[4][0] = 1.0f;
	_normalArray[4][1] = 0.0f;
	_normalArray[4][2] = 0.0f;
	_normalArray[5][0] = 1.0f;
	_normalArray[5][1] = 0.0f;
	_normalArray[5][2] = 0.0f;
	_normalArray[6][0] = 1.0f;
	_normalArray[6][1] = 0.0f;
	_normalArray[6][2] = 0.0f;
	_normalArray[7][0] = 1.0f;
	_normalArray[7][1] = 0.0f;
	_normalArray[7][2] = 0.0f;
	// right side top left corner v0
	_texArray[4][0] = 0.0f;
	_texArray[4][1] = 1.0f;
	_vertexArray[4][0] = +width; // x
	_vertexArray[4][1] = +height; // y
	_vertexArray[4][2] = +depth; // z
	// right side bottom left corner v3
	_texArray[5][0] = 0.0f;
	_texArray[5][1] = 0.0f;
	_vertexArray[5][0] = +width;
	_vertexArray[5][1] = -height;
	_vertexArray[5][2] = +depth;
	// right side bottom right corner v4
	_texArray[6][0] = 1.0f;
	_texArray[6][1] = 0.0f;
	_vertexArray[6][0] = +width;
	_vertexArray[6][1] = -height;
	_vertexArray[6][2] = -depth;
	// right side top right corner v5
	_texArray[7][0] = 1.0f;
	_texArray[7][1] = 1.0f;
	_vertexArray[7][0] = +width;
	_vertexArray[7][1] = +height;
	_vertexArray[7][2] = -depth;

	_normalArray[8][0] = 0.0f;
	_normalArray[8][1] = 1.0f;
	_normalArray[8][2] = 0.0f;
	_normalArray[9][0] = 0.0f;
	_normalArray[9][1] = 1.0f;
	_normalArray[9][2] = 0.0f;
	_normalArray[10][0] = 0.0f;
	_normalArray[10][1] = 1.0f;
	_normalArray[10][2] = 0.0f;
	_normalArray[11][0] = 0.0f;
	_normalArray[11][1] = 1.0f;
	_normalArray[11][2] = 0.0f;
	// top side bottom right corner v0
	_texArray[8][0] = 1.0f;
	_texArray[8][1] = 0.0f;
	_vertexArray[8][0] = +width; // x
	_vertexArray[8][1] = +height; // y
	_vertexArray[8][2] = +depth; // z
	// top side top right corner v5
	_texArray[9][0] = 1.0f;
	_texArray[9][1] = 1.0f;
	_vertexArray[9][0] = +width;
	_vertexArray[9][1] = +height;
	_vertexArray[9][2] = -depth;
	// top side top left corner v6
	_texArray[10][0] = 0.0f;
	_texArray[10][1] = 1.0f;
	_vertexArray[10][0] = -width;
	_vertexArray[10][1] = +height;
	_vertexArray[10][2] = -depth;
	// top side bottom left corner v1
	_texArray[11][0] = 0.0f;
	_texArray[11][1] = 0.0f;
	_vertexArray[11][0] = -width;
	_vertexArray[11][1] = +height;
	_vertexArray[11][2] = +depth;

	_normalArray[12][0] = -1.0f;
	_normalArray[12][1] = 0.0f;
	_normalArray[12][2] = 0.0f;
	_normalArray[13][0] = -1.0f;
	_normalArray[13][1] = 0.0f;
	_normalArray[13][2] = 0.0f;
	_normalArray[14][0] = -1.0f;
	_normalArray[14][1] = 0.0f;
	_normalArray[14][2] = 0.0f;
	_normalArray[15][0] = -1.0f;
	_normalArray[15][1] = 0.0f;
	_normalArray[15][2] = 0.0f;
	// left side top right corner v1
	_texArray[12][0] = 1.0f;
	_texArray[12][1] = 1.0f;
	_vertexArray[12][0] = -width; // x
	_vertexArray[12][1] = +height; // y
	_vertexArray[12][2] = +depth; // z
	// left side top left corner v6
	_texArray[13][0] = 0.0f;
	_texArray[13][1] = 1.0f;
	_vertexArray[13][0] = -width;
	_vertexArray[13][1] = +height;
	_vertexArray[13][2] = -depth;
	// left side bottom left corner v7
	_texArray[14][0] = 0.0f;
	_texArray[14][1] = 0.0f;
	_vertexArray[14][0] = -width;
	_vertexArray[14][1] = -height;
	_vertexArray[14][2] = -depth;
	// left side bottom right corner v2
	_texArray[15][0] = 1.0f;
	_texArray[15][1] = 0.0f;
	_vertexArray[15][0] = -width;
	_vertexArray[15][1] = -height;
	_vertexArray[15][2] = +depth;

	_normalArray[16][0] = 0.0f;
	_normalArray[16][1] = -1.0f;
	_normalArray[16][2] = 0.0f;
	_normalArray[16][0] = 0.0f;
	_normalArray[16][1] = -1.0f;
	_normalArray[16][2] = 0.0f;
	_normalArray[17][0] = 0.0f;
	_normalArray[17][1] = -1.0f;
	_normalArray[17][2] = 0.0f;
	_normalArray[18][0] = 0.0f;
	_normalArray[18][1] = -1.0f;
	_normalArray[18][2] = 0.0f;
	_normalArray[19][0] = 0.0f;
	_normalArray[19][1] = -1.0f;
	_normalArray[19][2] = 0.0f;
	// bottom side top left corner v7
	_texArray[16][0] = 0.0f;
	_texArray[16][1] = 1.0f;
	_vertexArray[16][0] = -width;
	_vertexArray[16][1] = -height;
	_vertexArray[16][2] = -depth;
	// bottom side top right corner v4
	_texArray[17][0] = 1.0f;
	_texArray[17][1] = 1.0f;
	_vertexArray[17][0] = +width;
	_vertexArray[17][1] = -height;
	_vertexArray[17][2] = -depth;
	// bottom side bottom right corner v3
	_texArray[18][0] = 1.0f;
	_texArray[18][1] = 0.0f;
	_vertexArray[18][0] = +width;
	_vertexArray[18][1] = -height;
	_vertexArray[18][2] = +depth;
	// bottom side bottom left corner v2
	_texArray[19][0] = 0.0f;
	_texArray[19][1] = 0.0f;
	_vertexArray[19][0] = -width;
	_vertexArray[19][1] = -height;
	_vertexArray[19][2] = +depth;

	_normalArray[20][0] = 0.0f;
	_normalArray[20][1] = 0.0f;
	_normalArray[20][2] = -1.0f;
	_normalArray[21][0] = 0.0f;
	_normalArray[21][1] = 0.0f;
	_normalArray[21][2] = -1.0f;
	_normalArray[22][0] = 0.0f;
	_normalArray[22][1] = 0.0f;
	_normalArray[22][2] = -1.0f;
	_normalArray[23][0] = 0.0f;
	_normalArray[23][1] = 0.0f;
	_normalArray[23][2] = -1.0f;
	// back side bottom right corner v4
	_texArray[20][0] = 1.0f;
	_texArray[20][1] = 0.0f;
	_vertexArray[20][0] = +width;
	_vertexArray[20][1] = -height;
	_vertexArray[20][2] = -depth;
	// back side bottom left corner v7
	_texArray[21][0] = 0.0f;
	_texArray[21][1] = 0.0f;
	_vertexArray[21][0] = -width;
	_vertexArray[21][1] = -height;
	_vertexArray[21][2] = -depth;
	// back side top left corner v6
	_texArray[22][0] = 0.0f;
	_texArray[22][1] = 1.0f;
	_vertexArray[22][0] = -width;
	_vertexArray[22][1] = +height;
	_vertexArray[22][2] = -depth;
	// back side top right corner v5
	_texArray[23][0] = 1.0f;
	_texArray[23][1] = 1.0f;
	_vertexArray[23][0] = +width;
	_vertexArray[23][1] = +height;
	_vertexArray[23][2] = -depth;

	/*int numberOfFaceConnectionsPerFace = 3;
	int numberOfVerticesPerFace = 4;
	CalculateVertexNormals(numberOfFaces, _normalArray, _vertexArray, _vertexArraySize, numberOfFaceConnectionsPerFace,
		numberOfVerticesPerFace);*/
	GeneratePhysicalNormals();

	this->SetHeightWidthDepth(&(Vector3f(size,size,size)));
	this->SetTextureEnabledStatus(texEnabled);
	this->SetTexture(texLocation);
	this->SetPosition(*xyzw);
	this->Shape::SetInitialPosition(*xyzw);

	return true; // add checking code to make sure everything was created fine (memory allocation etc)
}

Vector3f Cube::GetDirectionVector(void)const{
	return this->Shape::GetDirectionVector();
}

void Cube::GeneratePhysicalNormals(void){
	int counter = 0; // used to point to the correct _normalVertexArray index when initialising the loop
	// can't just use 'i' because that will end up overwriting values
	for (GLuint i = 0; i < _vertexArraySize; i++){
		_normalVertexArray[i+counter][0] = _vertexArray[i][0]; // x - start of the line
		_normalVertexArray[i+counter][1] = _vertexArray[i][1]; // y - start of the line
		_normalVertexArray[i+counter][2] = _vertexArray[i][2]; // z - start of the line

		_normalVertexArray[i+counter+1][0] = _vertexArray[i][0]+_normalArray[i][0]; // x - end of the line
		_normalVertexArray[i+counter+1][1] = _vertexArray[i][1]+_normalArray[i][1]; // x - end of the line
		_normalVertexArray[i+counter+1][2] = _vertexArray[i][2]+_normalArray[i][2]; // x - end of the line

		counter++;
	}
	for (GLuint i = 0; i < _normalVertexIndexArraySize; i++){ // populate the index array for the normalvertex
		_normalVertexIndexArray[i] = i;
	}	
}
void Cube::Draw(void) const {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, _vertexArray);
	glNormalPointer(GL_FLOAT, 0, _normalArray);
	glTexCoordPointer(2, GL_FLOAT, 0, _texArray);

	glDrawElements(GL_QUADS, _indexArraySize, GL_UNSIGNED_INT, _indexArray);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


void Cube::SetAnimationCoefficients(const vector<Vector3f> &animation){
	this->Shape::SetAnimationCoefficients(animation);
}

void Cube::SetDirectionVector(const Vector3f &directionVector){
	this->Shape::SetDirectionVector(directionVector);
}

void Cube::SetHeightWidthDepth(const Vector3f *hWD) {
	this->Shape::SetHeightWidthDepth(hWD);
}
void Cube::SetTexture(string image){
	this->Shape::SetTexture(image);
}
void Cube::SetTextureID(GLuint texID){
	_textureID = texID;
}
void Cube::SetTextureEnabledStatus(bool status){
	this->Shape::SetTextureEnabledStatus(status);
}
void Cube::SetSplitSize(int splitSize){
	_splitSize = splitSize;
}

void Cube::Update(float deltaTime, float timeElapsed){

}