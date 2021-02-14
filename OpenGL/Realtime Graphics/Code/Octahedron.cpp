#include "Octahedron.h"

using std::vector;

Octahedron::Octahedron(void){

}

Octahedron::~Octahedron(void){
	DeallocateMemory();
}

Octahedron::Octahedron(const Octahedron &A){
	CopyNonPointerDataMembers(A);
	CopyPointerDataMembers(A);
}

Octahedron& Octahedron::operator =(const Octahedron &A){
	if (&A != this){
		CopyNonPointerDataMembers(A);
		DeallocateMemory();
		AllocateMemory(); // make sure the pointer members have enough space allocated for the memcpy
		CopyPointerDataMembers(A);
	}
	return *this;
}

void Octahedron::AllocateMemory(void){
	_vertexArray = new GLfloat [_vertexArraySize][3];
	_normalArray = new GLfloat [_normalArraySize][3];
	_texArray = new GLfloat [_texArraySize][2];
	_indexArray  = new GLuint [_indexArraySize];
	_normalVertexArray = new GLfloat [_normalVertexArraySize][3];
	_normalVertexIndexArray = new GLuint [_normalVertexIndexArraySize];
}

void Octahedron::Animate(float deltaTime, float timeElapsed){
	Vector4f pos = GetPosition();
	GetAnimation().Animate(pos, deltaTime, timeElapsed);
	SetPosition(pos);
}

void Octahedron::Assign(void){

}

void Octahedron::Assign(const Vector4f *xyzw, float size, bool textureEnabled, std::string texLocation){
	DeallocateMemory(); //remove the old memory
	Create(xyzw, size, textureEnabled, texLocation);
}

Octahedron* Octahedron::CloneToAnEmptyObject()const{
	Octahedron *p = new Octahedron;
	p->Create();
	*p = *this;
	return p;
}
Octahedron* Octahedron::Clone()const{
	return new Octahedron(*this);
}

void Octahedron::CopyNonPointerDataMembers(const Octahedron &A){
	// Copy non-pointer data members
	_indexArraySize = A._indexArraySize;
	_normalArraySize = A._normalArraySize;
	_vertexArraySize = A._vertexArraySize;
	_texArraySize = A._texArraySize;
	_textureID = A._textureID;
	_normalVertexIndexArraySize = A._normalVertexIndexArraySize;
	_normalVertexArraySize = A._normalVertexArraySize;
	CopyBaseMembers(A);
}

void Octahedron::CopyPointerDataMembers(const Octahedron &A){
	// C++ guarantee that elements of multidimensional arrays occupy contiguous memory addresses
	// this is quicker then the for-loop method
	// Copy pointer data members
	memcpy(_vertexArray, A._vertexArray, _vertexArraySize*sizeof(float)*3); // destination, source, size
	memcpy(_normalArray, A._normalArray, _normalArraySize*sizeof(float)*3); // *3 because array[][3]
	memcpy(_texArray, A._texArray, _texArraySize*sizeof(float)*2); // *2 because array[][2]
	memcpy(_indexArray, A._indexArray, _indexArraySize*sizeof(float));
	memcpy(_normalVertexArray, A._normalVertexArray, _normalVertexArraySize*sizeof(float)*3); // *3 because array[][3]
	memcpy(_normalVertexIndexArray, A._normalVertexIndexArray, _normalVertexIndexArraySize*sizeof(GLuint)); // *3 because array[][3]
}

bool Octahedron::Create(void){
	_vertexArraySize = 1;
	_indexArraySize = 1;
	_normalArraySize = 1;
	_texArraySize = 1;
	_normalVertexIndexArraySize = 1;
	_normalVertexArraySize = 1;
	//Create(&_defaultOctahedronPosition, &_defaultOctahedronHeightWidthDepth, false, "");
	AllocateMemory();
	return true;
}

bool Octahedron::Create(const Vector4f *xyzw, float size, bool textureEnabled, std::string texLocation){
	float height = size / 2.0f; // divide hWD by 2 so when drawing, we are drawing from the centre of the object
	float width = height;
	float depth = height;

	_vertexArraySize = 24;
	_normalArraySize = 24;
	_indexArraySize = 24;
	_texArraySize = 24;
	_normalVertexIndexArraySize = _normalArraySize*2;
	_normalVertexArraySize = _normalVertexIndexArraySize;

	AllocateMemory();

	for (GLuint i = 0; i < _indexArraySize; i++){
		_indexArray[i] = i;
	}
	////// Begin Top Triangles ///////////
	// top middle vertex of top front triangle
	//face 0
	_texArray[0][0] = 0.5f;//u
	_texArray[0][1] = 1.0f;//v
	_vertexArray[0][0] = 0;//x
	_vertexArray[0][1] = +height;//y
	_vertexArray[0][2] = 0;//z
	// bottom left vertex of top front triangle
	_texArray[1][0] = 0.0f;//u
	_texArray[1][1] = 0.0f;//v
	_vertexArray[1][0] = -width;//x
	_vertexArray[1][1] = 0;//y
	_vertexArray[1][2] = +depth;//z
	// bottom right vertex of top front triangle
	_texArray[2][0] = 1.0f;//u
	_texArray[2][1] = 0.0f;//v
	_vertexArray[2][0] = +width;//x
	_vertexArray[2][1] = 0;//y
	_vertexArray[2][2] = +depth;//z

	//face 1
	// top middle vertex of top right triangle
	_texArray[3][0] = 0.5;//u
	_texArray[3][1] = 1.0f;//v
	_vertexArray[3][0] = 0;//x
	_vertexArray[3][1] = +height;//y
	_vertexArray[3][2] = 0;//z
	// bottom left vertex of top right triangle
	_texArray[4][0] = 0.0f;//u
	_texArray[4][1] = 0.0f;//v
	_vertexArray[4][0] = +width;//x
	_vertexArray[4][1] = 0;//y
	_vertexArray[4][2] = +depth;//z
	// bottom right vertex of top right triangle
	_texArray[5][0] = 0.0f;//u
	_texArray[5][1] = 1.0f;//v
	_vertexArray[5][0] = +width;//x
	_vertexArray[5][1] = 0;//y
	_vertexArray[5][2] = -depth;//z

	//face 2
	// top middle vertex of top back triangle
	_texArray[6][0] = 0.5f;//u
	_texArray[6][1] = 1.0f;//v
	_vertexArray[6][0] = 0;//x
	_vertexArray[6][1] = +height;//y
	_vertexArray[6][2] = 0;//z
	// bottom left vertex of top back triangle
	_texArray[7][0] = 0.0f; //u
	_texArray[7][1] = 0.0f;//v
	_vertexArray[7][0] = +width;//x
	_vertexArray[7][1] = 0;//y
	_vertexArray[7][2] = -depth;//z
	// bottom right vertex of top back triangle
	_texArray[8][0] = 0.0f;//u
	_texArray[8][1] = 1.0f;//v
	_vertexArray[8][0] = -width;//x
	_vertexArray[8][1] = 0;//y
	_vertexArray[8][2] = -depth;

	//face 3
	// top middle vertex of top left triangle
	_texArray[9][0] = 0.5f;//u
	_texArray[9][1] = 1.0f;//v
	_vertexArray[9][0] = 0;//x
	_vertexArray[9][1] = +height;//y
	_vertexArray[9][2] = 0;//z
	// bottom left vertex of top left triangle
	_texArray[10][0] = 0.0f;//u
	_texArray[10][1] = 0.0f;//v
	_vertexArray[10][0] = -width;//x
	_vertexArray[10][1] = 0;//y
	_vertexArray[10][2] = -depth;//z
	// bottom right vertex of top left triangle
	_texArray[11][0] = 0.0f;//u
	_texArray[11][1] = 1.0f;//v
	_vertexArray[11][0] = -width;//x
	_vertexArray[11][1] = 0;//y
	_vertexArray[11][2] = +depth;//z
	////// End Top Triangles ///////////

	////// Begin Bottom Triangles ///////////
	//face 4
	// top middle vertex of bottom front triangle
	_texArray[12][0] = 0.5f;//u
	_texArray[12][1] = 1.0f;//v
	_vertexArray[12][0] = 0;//x
	_vertexArray[12][1] = -height;//y
	_vertexArray[12][2] = 0;//z
	// bottom left vertex of bottom front triangle
	_texArray[13][0] = 0.0f;//u
	_texArray[13][1] = 0.0f;//v
	_vertexArray[13][0] = +width;//x
	_vertexArray[13][1] = 0; //y
	_vertexArray[13][2] = +depth;//z
	// bottom right vertex of bottom front triangle
	_texArray[14][0] = 1.0f;//u
	_texArray[14][1] = 0.0f;//v
	_vertexArray[14][0] = -width;//x
	_vertexArray[14][1] = 0;//y
	_vertexArray[14][2] = +depth;

	//face 5
	// top middle vertex of bottom right triangle
	_texArray[15][0] = 0.5f;//u
	_texArray[15][1] = 1.0f;//v
	_vertexArray[15][0] = 0;//x
	_vertexArray[15][1] = -height;//y
	_vertexArray[15][2] = 0;//z
	// bottom left vertex of bottom right triangle
	_texArray[16][0] = 0.0f;//u
	_texArray[16][1] = 0.0f;
	_vertexArray[16][0] = -width;//x
	_vertexArray[16][1] = 0;//y
	_vertexArray[16][2] = +depth;//z
	// bottom right vertex of bottom right triangle
	_texArray[17][0] = 1.0f;//u
	_texArray[17][1] = 0.0f;//v
	_vertexArray[17][0] = -width;//x
	_vertexArray[17][1] = 0;//y
	_vertexArray[17][2] = -depth;//z

	//face 6
	// top middle vertex of bottom back triangle
	_texArray[18][0] = 0.5f;//u
	_texArray[18][1] = 1.0f;//v
	_vertexArray[18][0] = 0;//x
	_vertexArray[18][1] = -height;//y
	_vertexArray[18][2] = 0;//z
	// bottom left vertex of bottom back triangle
	_texArray[19][0] = 0.0f;//u
	_texArray[19][1] = 0.0f;//v
	_vertexArray[19][0] = -width;//x
	_vertexArray[19][1] = 0;//y
	_vertexArray[19][2] = -depth;//z
	// bottom right vertex of bottom back triangle
	_texArray[20][0] = 1.0f;//u
	_texArray[20][1] = 0.0f;//v
	_vertexArray[20][0] = +width;//x
	_vertexArray[20][1] = 0;//y
	_vertexArray[20][2] = -depth;//z

	//face 7
	// top middle vertex of bottom left triangle
	_texArray[21][0] = 0.5f;//u
	_texArray[21][1] = 1.0f;//v
	_vertexArray[21][0] = 0;//x
	_vertexArray[21][1] = -height;//y
	_vertexArray[21][2] = 0;//z
	// bottom left vertex of bottom left triangle
	_texArray[22][0] = 0.0f;//u
	_texArray[22][1] = 0.0f;//v
	_vertexArray[22][0] = +width;//x
	_vertexArray[22][1] = 0;//y
	_vertexArray[22][2] = -depth;//z
	//bottom right vertex of bottom left triangle
	_texArray[23][0] = 1.0f;//u
	_texArray[23][1] = 0.0f;//v
	_vertexArray[23][0] = +width;//x
	_vertexArray[23][1] = 0;//y
	_vertexArray[23][2] = +depth;//z
	////// End Bottom Triangles ///////////

	int numberOfFaces = 8;
	int numberOfFaceConnectionsPerFace = 3;
	int numberOfVerticesPerFace = 3;

	CalculateVertexNormals(numberOfFaces, _normalArray, _vertexArray, _vertexArraySize, numberOfFaceConnectionsPerFace,
		numberOfVerticesPerFace);
	GeneratePhysicalNormals();

	this->SetHeightWidthDepth(&(Vector3f(size,size,size)));
	this->SetTextureEnabledStatus(textureEnabled);
	this->SetTexture(texLocation);
	this->SetPosition(*xyzw);

	return true;
}

void Octahedron::DeallocateMemory(void){
	delete [] _vertexArray;
	delete [] _normalArray;
	delete [] _indexArray;
}

void Octahedron::Draw(void) const{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, _vertexArray);
	glNormalPointer(GL_FLOAT, 0, _normalArray);
	glTexCoordPointer(2, GL_FLOAT, 0, _texArray);
	glDrawElements(GL_TRIANGLES, _indexArraySize, GL_UNSIGNED_INT, _indexArray);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Octahedron::DrawNormals(void)const{
	glDisable(GL_LIGHTING);
	glColor3f(1.0f,1.0f,1.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _normalVertexArray);
	glDrawElements(GL_LINES, _normalVertexIndexArraySize, GL_UNSIGNED_INT, _normalVertexIndexArray);//_normalVertexIndexArraySize
	glDisableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_LIGHTING);
}

void Octahedron::GeneratePhysicalNormals(void){
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

Vector3f Octahedron::GetHeightWidthDepth(void) const{
	return this->Shape::GetHeightWidthDepth();
}

const Vector4f &Octahedron::GetPosition(void) const{
	return this->Shape::GetPosition();
}

bool Octahedron::GetTextureEnabledStatus(void) const{
	return this->Shape::GetTextureEnabledStatus();
}

GLuint Octahedron::GetTextureID(void)const{
	return _textureID;
}

void Octahedron::SetAnimationCoefficients(const vector<Vector3f> &animation){
	this->Shape::SetAnimationCoefficients(animation);
}

void Octahedron::SetHeightWidthDepth(const Vector3f *hWD){
	this->Shape::SetHeightWidthDepth(hWD);
}

void Octahedron::SetTexture(std::string image){
	this->Shape::SetTexture(image);
}

void Octahedron::SetTextureEnabledStatus(bool status){
	this->Shape::SetTextureEnabledStatus(status);
}

void Octahedron::SetTextureID(GLuint texID){
	_textureID = texID;
}

void Octahedron::Update(){
}

void Octahedron::Update(float deltaTime, float timeElapsed){
}