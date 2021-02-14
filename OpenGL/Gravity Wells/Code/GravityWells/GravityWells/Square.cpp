#include "Square.h"

Square::Square() {
}

Square::~Square() {
	DeallocateMemory();
}

Square::Square(const Square &A){
	CopyNonPointerDataMembers(A);
	CopyPointerDataMembers(A);
}

Square& Square::operator =(const Square &A){
	if (&A != this){
		CopyNonPointerDataMembers(A);
		DeallocateMemory();
		AllocateMemory();// make sure the pointer members have enough space allocated for the memcpy
		CopyPointerDataMembers(A);
	}
	return *this;
}

void Square::AllocateMemory(void){
	_vertexarray = new float[_vertexarraySize][3];
	_indexarray = new GLuint[_indexarraySize];
	_texarray = new float[_texarraySize][2];
}

void Square::Assign(void){

}

void Square::Assign(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture){
	DeallocateMemory(); // remove the old memory
	Create(position, heightWidthDepth, texture);
}

Square* Square::CloneToAnEmptyObject()const{
	Square *p = new Square;
	p->Create();
	*p = *this;
	return p;
}

Square* Square::Clone()const{
	return new Square(*this);
}

void Square::CopyNonPointerDataMembers(const Square &A){
	// Copy non-pointer data members
	_indexarraySize = A._indexarraySize;
	_vertexarraySize = A._vertexarraySize;
	CopyBaseMembers(A);
}

void Square::CopyPointerDataMembers(const Square &A){
	// C++ guarantee that elements of multidimensional arrays occupy contiguous memory addresses
	// this is quicker then the for-loop method
	// Copy pointer data members
	memcpy(_vertexarray, A._vertexarray, _vertexarraySize*sizeof(float)*3);//*3 because array[][3]
	memcpy(_texarray, A._texarray, _texarraySize*sizeof(float)*2);
	memcpy(_indexarray, A._indexarray, _indexarraySize*sizeof(float));
}

void Square::DeallocateMemory(void){
	delete [] _vertexarray;
	delete [] _indexarray;
	delete [] _texarray;
}

bool Square::Create(){
	_vertexarraySize = 1;
	_texarraySize = 1;
	_indexarraySize = 1;
	Create(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f,1.0f,1.0f), false);
	return true;
}
bool Square::Create(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture) {
	float height = heightWidthDepth.x() / 2.0f; // divide hWD by 2 so when drawing, we are drawing from the centre of the object
	float width = height;
	float depth = height;
	int arraySize = 4; //4 sets of coords, bottomleft, bottomright, topright, topleft of the square
	_vertexarraySize = arraySize;
	_indexarraySize = arraySize;
	_texarraySize = arraySize;
	AllocateMemory();

	for (int i = 0; i < arraySize; i++){
		_indexarray[i] = i;
	}

	//initially the square will be faced flat (as if it was the bottom of a cube, but raised up to the middle of the cube)
	//bottom right corner
	_texarray[0][0] = 1.0f;
	_texarray[0][1] = 0.0f;
	_vertexarray[0][0] = +width; //x
	_vertexarray[0][1] = 0.0f; //y
	_vertexarray[0][2] = +depth; //z
	//top right corner
	_texarray[1][0] = 1.0f;
	_texarray[1][1] = 1.0f;
	_vertexarray[1][0] = +width; //x
	_vertexarray[1][1] = 0.0f; //y
	_vertexarray[1][2] = -depth; //z
	// top left corner
	_texarray[2][0] = 0.0f;
	_texarray[2][1] = 1.0f;
	_vertexarray[2][0] = -width;//x
	_vertexarray[2][1] = 0.0f;//y
	_vertexarray[2][2] = -depth;//z
	// bottom left corner
	_texarray[3][0] = 0.0f;
	_texarray[3][1] = 0.0f;
	_vertexarray[3][0] = -width;//x
	_vertexarray[3][1] = 0.0f;//y
	_vertexarray[3][2] = +depth;//z

	this->SetHeightWidthDepth(heightWidthDepth);
	this->SetTextureEnabledStatus(texture);
	this->SetPosition(position);

	return true;
}

void Square::Draw(void) const {
	if (GetTextureEnabledStatus()){
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, _texarray);
		glEnable(GL_TEXTURE_2D);
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _vertexarray);

	glDrawElements(GL_QUADS, _indexarraySize, GL_UNSIGNED_INT, _indexarray);

	if (GetTextureEnabledStatus()){
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, _texarray);
		glDisable(GL_TEXTURE_2D);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _vertexarray);
}
GLfloat Square::GetSize(void)const{
	return this->Shape::GetHeightWidthDepth().x();
}

const Vector3f& Square::GetPosition(void) const{
	return this->Shape::GetPosition();
}

bool Square::GetTextureEnabledStatus(void) const{
	return this->Shape::GetTextureEnabledStatus();
}

GLuint Square::GetTextureID(void)const{
	return this->Shape::GetTextureID();
}

void Square::SetPosition(const Vector3f &position) {
	this->Shape::SetPosition(position);
}
void Square::SetTextureEnabledStatus(bool status){
	this->Shape::SetTextureEnabledStatus(status);
}

void Square::SetTextureID(GLuint texID){
	this->Shape::SetTextureID(texID);
}

void Square::Update(float deltaTime){
}