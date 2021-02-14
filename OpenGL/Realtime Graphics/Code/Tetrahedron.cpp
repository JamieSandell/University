#include "Tetrahedron.h"

using std::vector;

Tetrahedron::Tetrahedron(void){
}

Tetrahedron::~Tetrahedron(void){
	DeallocateMemory();
}

Tetrahedron::Tetrahedron(const Tetrahedron &A){
	CopyNonPointerDataMembers(A);
	CopyPointerDataMembers(A);
}

Tetrahedron& Tetrahedron::operator =(const Tetrahedron &A){
	if (&A != this){
		CopyNonPointerDataMembers(A);
		DeallocateMemory();
		AllocateMemory();// make sure the pointer members have enough space allocated for the memcpy
		CopyPointerDataMembers(A);
	}
	return *this;
}
void Tetrahedron::Assign(const Vector4f *xyzw, float size, bool texEnabled, std::string texLocation){
	DeallocateMemory();
	Create(xyzw, size, texEnabled, texLocation);
}

void Tetrahedron::AllocateMemory(void) {
	_vertexArray = new GLfloat [_vertexArraySize][3];
	_normalArray = new GLfloat [_normalArraySize][3];
	_texArray = new GLfloat [_texArraySize][2];
	_indexArray = new GLuint [_indexArraySize];
	_normalVertexArray = new GLfloat [_normalVertexArraySize][3];
	_normalVertexIndexArray = new GLuint [_normalVertexIndexArraySize];
}

Tetrahedron* Tetrahedron::CloneToAnEmptyObject()const{
	Tetrahedron *p = new Tetrahedron;
	p->Create();
	*p = *this;
	return p;
}

Tetrahedron* Tetrahedron::Clone()const{
	return new Tetrahedron(*this);
}

void Tetrahedron::CopyNonPointerDataMembers(const Tetrahedron &A){
	_indexArraySize = A._indexArraySize;
	_normalArraySize = A._normalArraySize;
	_vertexArraySize = A._vertexArraySize;
	_texArraySize = A._texArraySize;
	_textureID = A._textureID;
	_normalVertexIndexArraySize = A._normalVertexIndexArraySize;
	_normalVertexArraySize = A._normalVertexArraySize;
	CopyBaseMembers(A);
}

void Tetrahedron::CopyPointerDataMembers(const Tetrahedron &A){
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

bool Tetrahedron::Create(void){
	_indexArraySize = 1;
	_normalArraySize = 1;
	_vertexArraySize = 1;
	_texArraySize = 1;
	_normalVertexIndexArraySize = 1;
	_normalVertexArraySize = 1;
	const float _defaultTetrahedronSize(1.0f);
	Create(&_defaultTetrahedronPosition, _defaultTetrahedronSize, false, "");
	return true;
}

bool Tetrahedron::Create(const Vector4f *xyzw, float size, bool texEnabled, std::string texLocation){
	float height = size / 2.0f; // divide hWD by 2 so when drawing, we are drawing from the centre of the object
	float width = height;
	float depth = height;

	_vertexArraySize = 12;
	_normalArraySize = 12;
	_indexArraySize = 12;
	_texArraySize = 12;
	_normalVertexIndexArraySize = _normalArraySize*2;
	_normalVertexArraySize = _normalVertexIndexArraySize;
	AllocateMemory();

	for (GLuint i = 0; i < _indexArraySize; i++){
		_indexArray[i] = i;
	}

	// face 0
	//front triangle, top middle vertex
	_texArray[0][0] = 0.5f;//u
	_texArray[0][1] = 1.0f;//v
	_vertexArray[0][0] = 0; //x
	_vertexArray[0][1] = +height; //y
	_vertexArray[0][2] = 0; //z
	// front triangle, bottom left vertex
	_texArray[1][0] = 0.0f;//u
	_texArray[1][1] = 0.0f;//v
	_vertexArray[1][0] = -width; //x
	_vertexArray[1][1] = -height; //y
	_vertexArray[1][2] = +depth; //z
	//front triangle, bottom right vertex
	_texArray[2][0] = 1.0f;//u
	_texArray[2][1] = 0.0f;//v
	_vertexArray[2][0] = +width; //x
	_vertexArray[2][1] = -height; //y
	_vertexArray[2][2] = +depth; //z
	//Vector3f v0, v1, v2;
	//Vector3f normal;
	//// Calculate face normals
	//v0.Assign(_vertexArray[0][0], _vertexArray[0][1], _vertexArray[0][2]);
	//v1.Assign(_vertexArray[1][0], _vertexArray[1][1], _vertexArray[1][2]);
	//v2.Assign(_vertexArray[2][0], _vertexArray[2][1], _vertexArray[2][2]);
	//faceNormals[0] = normal.CalculateFaceNormals(v0, v1, v2);

	// face 1
	// right triangle, top middle vertex
	_texArray[3][0] = 0.5f;//u
	_texArray[3][1] = 1.0f;//v
	_vertexArray[3][0] = 0; //x
	_vertexArray[3][1] = +height; //y
	_vertexArray[3][2] = 0; //z
	// right triangle, bottom left vertex
	_texArray[4][0] = 0.0f;//u
	_texArray[4][1] = 0.0f;//v
	_vertexArray[4][0] = +width; //x
	_vertexArray[4][1] = -height; //y
	_vertexArray[4][2] = +depth; //z
	// right triangle, bottom right vertex
	_texArray[5][0] = 1.0f;
	_texArray[5][1] = 0.0f;
	_vertexArray[5][0] = 0; //x
	_vertexArray[5][1] = -height; //y
	_vertexArray[5][2] = -depth; //z
	// Calculate face normals
	/*v0.Assign(_vertexArray[3][0], _vertexArray[3][1], _vertexArray[3][2]);
	v1.Assign(_vertexArray[4][0], _vertexArray[4][1], _vertexArray[4][2]);
	v2.Assign(_vertexArray[5][0], _vertexArray[5][1], _vertexArray[5][2]);
	faceNormals[1] = normal.CalculateFaceNormals(v0, v1, v2);*/

	//face 2
	// left triangle, top middle vertex
	_texArray[6][0] = 0.5f;//u
	_texArray[6][1] = 1.0f;//v
	_vertexArray[6][0] = 0; //x
	_vertexArray[6][1] = +height; //y
	_vertexArray[6][2] = 0;//z
	// left triangle, bottom left vertex
	_texArray[7][0] = 0.0f;//u
	_texArray[7][1] = 0.0f;//v
	_vertexArray[7][0] = 0; //x
	_vertexArray[7][1] = -height; //y
	_vertexArray[7][2] = -depth; //z
	// left triangle, bottom right vertex
	_texArray[8][0] = 1.0f;//u
	_texArray[8][1] = 0.0f;//v
	_vertexArray[8][0] = -width; //x
	_vertexArray[8][1] = -height; //y
	_vertexArray[8][2] = +depth; //z
	// Calculate face normals
	/*v0.Assign(_vertexArray[6][0], _vertexArray[6][1], _vertexArray[6][2]);
	v1.Assign(_vertexArray[7][0], _vertexArray[7][1], _vertexArray[7][2]);
	v2.Assign(_vertexArray[8][0], _vertexArray[8][1], _vertexArray[8][2]);
	faceNormals[2] = normal.CalculateFaceNormals(v0, v1, v2);*/

	//face 3
	// bottom triangle, top middle vertex
	_texArray[9][0] = 0.5f;//u
	_texArray[9][1] = 0.0f;//v
	_vertexArray[9][0] = 0; //x
	_vertexArray[9][1] = -height; //y
	_vertexArray[9][2] = -depth; //z
	// bottom triangle, bottom right vertex
	_texArray[10][0] = 0.0f;//u
	_texArray[10][1] = 1.0f;//v
	_vertexArray[10][0] = +width; //x
	_vertexArray[10][1] = -height; //y
	_vertexArray[10][2] = +depth; //z
	// bottom triangle, bottom left vertex
	_texArray[11][0] = 1.0f;//u
	_texArray[11][1] = 1.0f;//v
	_vertexArray[11][0] = -width; //x
	_vertexArray[11][1] = -height; //y
	_vertexArray[11][2] = +depth; //z

	int faceConnectivity = 3; // number of faces each vertex is shared with
	int numberOfFaceConnectionsPerFace = 3;
	int numberOfVerticesPerFace = 3;
	int numberOfFaces = 4;
	Vector3f *faceNormals = new Vector3f[numberOfFaces];
	int faceTableSize = numberOfFaceConnectionsPerFace*numberOfFaces*numberOfVerticesPerFace;
	int *faceTable = new int[faceTableSize];



	CalculateVertexNormals(numberOfFaces, _normalArray, _vertexArray, _vertexArraySize, numberOfFaceConnectionsPerFace,
		numberOfVerticesPerFace);
	GeneratePhysicalNormals();

	this->SetHeightWidthDepth(&(Vector3f(size,size,size)));
	this->SetPosition(*xyzw);
	this->SetTexture(texLocation);
	this->SetTextureEnabledStatus(texEnabled);

	delete [] faceNormals;
	delete [] faceTable;

	return true;
}

void Tetrahedron::DeallocateMemory(void) {
	delete [] _indexArray;
	delete [] _normalArray;
	delete [] _vertexArray;
	delete [] _texArray;
	delete [] _normalVertexArray;
	delete [] _normalVertexIndexArray;
}

void Tetrahedron::Draw() const {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, _vertexArray);
	glTexCoordPointer(2, GL_FLOAT, 0, _texArray);
	glNormalPointer(GL_FLOAT, 0, _normalArray);
	glDrawElements(GL_TRIANGLES, _indexArraySize, GL_UNSIGNED_INT, _indexArray);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Tetrahedron::DrawNormals(void)const{
	glDisable(GL_LIGHTING);
	glColor3f(1.0f,1.0f,1.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _normalVertexArray);
	glDrawElements(GL_LINES, _normalVertexIndexArraySize, GL_UNSIGNED_INT, _normalVertexIndexArray);//_normalVertexIndexArraySize
	glDisableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_LIGHTING);
}
void Tetrahedron::GeneratePhysicalNormals(void){
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
Vector3f Tetrahedron::GetHeightWidthDepth(void) const{
	return this->Shape::GetHeightWidthDepth();
}

const Vector4f &Tetrahedron::GetPosition(void) const{
	return this->Shape::GetPosition();
}

bool Tetrahedron::GetTextureEnabledStatus(void) const{
	return this->Shape::GetTextureEnabledStatus();
}
GLuint Tetrahedron::GetTextureID(void)const{
	return _textureID;
}
void Tetrahedron::SetAnimationCoefficients(const vector<Vector3f> &animation){
	this->Shape::SetAnimationCoefficients(animation);
}
void Tetrahedron::SetHeightWidthDepth(const Vector3f *hWD){
	this->Shape::SetHeightWidthDepth(hWD);
}
void Tetrahedron::SetTexture(std::string image){
	this->Shape::SetTexture(image);
}
void Tetrahedron::SetTextureEnabledStatus(bool status){
	this->Shape::SetTextureEnabledStatus(status);
}
void Tetrahedron::SetTextureID(GLuint textureID){
	_textureID = textureID;
}
void Tetrahedron::Update(float deltaTime, float timeElapsed){
}