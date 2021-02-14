#include "MyCylinder.h"
#include <math.h>
#define PI  (float)3.1415926

using std::vector;

MyCylinder::MyCylinder() {
}

MyCylinder::~MyCylinder() {
	DeallocateMemory();
}

MyCylinder::MyCylinder(const MyCylinder &A){
	CopyNonPointerDataMembers(A);
	CopyPointerDataMembers(A);
}

MyCylinder& MyCylinder::operator =(const MyCylinder &A){
	if (&A != this) {
		CopyNonPointerDataMembers(A);
		DeallocateMemory();
		AllocateMemory();// make sure the pointer members have enough space allocated for the memcpy
		CopyPointerDataMembers(A);
	}
	return *this;
}

void MyCylinder::AllocateMemory(void){
	_vertexarrayTop = new float[_vertexarrayTopSize][3];
	_vertexarrayBody = new float[_vertexarrayBodySize][3];
	_vertexarrayBottom = new float[_vertexarrayBottomSize][3];
	_normalarrayTop = new float[_normalarrayTopSize][3];
	_normalarrayBody = new float[_normalarrayBodySize][3];
	_normalarrayBottom = new float[_normalarrayBottomSize][3];
	_normalVertexArrayTop = new float[_normalVertexArrayTopSize][3];//used for GeneratePhysicalNormals()
	_normalVertexArrayBody = new float[_normalVertexArrayBodySize][3];//used for GeneratePhysicalNormals()
	_normalVertexArrayBottom = new float[_normalVertexArrayBottomSize][3];//used for GeneratePhysicalNormals()
	_texarrayTop = new float[_texarrayTopSize][2];
	_texarrayBody = new float[_texarrayBodySize][2];
	_texarrayBottom = new float[_texarrayBottomSize][2];
	_indexarrayTop = new GLuint[_indexarrayTopSize];
	_indexarrayBody = new GLuint[_indexarrayBodySize];
	_indexarrayBottom = new GLuint[_indexarrayBottomSize];
	_normalVertexIndexArrayTop = new GLuint[_normalVertexIndexArrayTopSize];//used for GeneratePhysicalNormals()
	_normalVertexIndexArrayBody = new GLuint[_normalVertexIndexArrayBodySize];//used for GeneratePhysicalNormals()
	_normalVertexIndexArrayBottom = new GLuint[_normalVertexIndexArrayBottomSize];//used for GeneratePhysicalNormals()
}

void MyCylinder::Animate(float deltaTime, float timeElapsed){
	Vector4f pos = GetPosition();
	GetAnimation().Animate(pos, deltaTime, timeElapsed);
}

void MyCylinder::Assign(void){

}

void MyCylinder::Assign(const Vector4f *position, float bottomRadius, bool texture, std::string texLocation){
	DeallocateMemory(); // remove the old memory
	Create(position, bottomRadius, texture, texLocation);
}

MyCylinder* MyCylinder::CloneToAnEmptyObject() const{
	MyCylinder *p = new MyCylinder;
	p->Create();
	*p = *this;
	return p;
}

MyCylinder* MyCylinder::Clone() const{
	return new MyCylinder(*this);
}

void MyCylinder::CopyNonPointerDataMembers(const MyCylinder &A){
	// Copy non-pointer data members
	_indexarrayBottomSize = A._indexarrayBottomSize;
	_indexarrayBodySize = A._indexarrayBodySize;
	_indexarrayTopSize = A._indexarrayTopSize;
	_normalarrayBottomSize = A._normalarrayBottomSize;
	_normalarrayBodySize = A._normalarrayBodySize;
	_normalarrayTopSize = A._normalarrayTopSize;
	_texarrayBottomSize = A._texarrayBottomSize;
	_texarrayBodySize = A._texarrayBodySize;
	_texarrayTopSize = A._texarrayTopSize;
	_vertexarrayBottomSize = A._vertexarrayBottomSize;
	_vertexarrayBodySize = A._vertexarrayBodySize;
	_vertexarrayTopSize = A._vertexarrayTopSize;
	_normalVertexArrayBodySize = A._normalVertexArrayBodySize;
	_normalVertexArrayBottomSize = A._normalVertexArrayBottomSize;
	_normalVertexArrayTopSize = A._normalVertexArrayTopSize;
	_normalVertexIndexArrayBodySize = A._normalVertexIndexArrayBodySize;
	_normalVertexIndexArrayBottomSize = A._normalVertexIndexArrayBottomSize;
	_normalVertexIndexArrayTopSize = A._normalVertexIndexArrayTopSize;
	CopyBaseMembers(A);
}

void MyCylinder::CopyPointerDataMembers(const MyCylinder &A){
	// C++ guarantee that elements of multidimensional arrays occupy contiguous memory addresses
	// this is quicker then the for-loop method
	// Copy pointer data members
	memcpy(_vertexarrayBottom, A._vertexarrayBottom, _vertexarrayBottomSize*sizeof(float)*3); // destination, source, size
	memcpy(_vertexarrayBody, A._vertexarrayBody, _vertexarrayBodySize*sizeof(float)*3); //*3 because array[][3]
	memcpy(_vertexarrayTop, A._vertexarrayTop, _vertexarrayTopSize*sizeof(float)*3);
	memcpy(_normalarrayBottom, A._normalarrayBottom, _normalarrayBottomSize*sizeof(float)*3); // destination, source, size
	memcpy(_normalarrayBody, A._normalarrayBody, _normalarrayBodySize*sizeof(float)*3);
	memcpy(_normalarrayTop, A._normalarrayTop, _normalarrayTopSize*sizeof(float)*3);
	memcpy(_texarrayBottom, A._texarrayBottom, _texarrayBottomSize*sizeof(float)*2); // destination, source, size
	memcpy(_texarrayBody, A._texarrayBody, _texarrayBodySize*sizeof(float)*2);
	memcpy(_texarrayTop, A._texarrayTop, _texarrayTopSize*sizeof(float)*2);
	memcpy(_indexarrayBottom, A._indexarrayBottom, _indexarrayBottomSize*sizeof(float)); // destination, source, size
	memcpy(_indexarrayBody, A._indexarrayBody, _indexarrayBodySize*sizeof(float));
	memcpy(_indexarrayTop, A._indexarrayTop, _indexarrayTopSize*sizeof(float));
	memcpy(_normalVertexIndexArrayBottom, A._normalVertexIndexArrayBottom, _normalVertexIndexArrayBottomSize*sizeof(float)); // destination, source, size
	memcpy(_normalVertexIndexArrayBody, A._normalVertexIndexArrayBody, _normalVertexIndexArrayBodySize*sizeof(float));
	memcpy(_normalVertexIndexArrayTop, A._normalVertexIndexArrayTop, _normalVertexIndexArrayTopSize*sizeof(float));
	memcpy(_normalVertexArrayBottom, A._normalVertexArrayBottom, _normalVertexArrayBottomSize*sizeof(float)*3); // destination, source, size
	memcpy(_normalVertexArrayBody, A._normalVertexArrayBody, _normalVertexArrayBodySize*sizeof(float)*3);
	memcpy(_normalVertexArrayTop, A._normalVertexArrayTop, _normalVertexArrayTopSize*sizeof(float)*3);
}

void MyCylinder::DeallocateMemory()
{
	delete [] _vertexarrayTop;
	delete [] _vertexarrayBody;
	delete [] _vertexarrayBottom;
	delete [] _normalarrayTop;
	delete [] _normalarrayBody;
	delete [] _normalarrayBottom;
	delete [] _indexarrayTop;//
	delete [] _indexarrayBody;//
	delete [] _indexarrayBottom;//
	delete [] _texarrayTop;
	delete [] _texarrayBody;
	delete [] _texarrayBottom;
	delete [] _normalVertexIndexArrayBottom;
	delete [] _normalVertexIndexArrayBody;
	delete [] _normalVertexIndexArrayTop;
	delete [] _normalVertexArrayBottom;
	delete [] _normalVertexArrayBody;
	delete [] _normalVertexArrayTop;
}

bool MyCylinder::Create() {
	_vertexarrayTopSize = 1;
	_vertexarrayBodySize = 1;
	_vertexarrayBottomSize = 1;
	_normalarrayTopSize = 1;
	_normalarrayBodySize = 1;
	_normalarrayBottomSize = 1;
	_indexarrayTopSize = 1;
	_indexarrayBodySize = 1;
	_indexarrayBottomSize = 1;
	_texarrayTopSize = 1;
	_texarrayBodySize = 1;
	_texarrayBottomSize = 1;
	_normalVertexArrayTopSize = 1;
	_normalVertexArrayBottomSize = 1;
	_normalVertexArrayBodySize = 1;
	_normalVertexIndexArrayBodySize = 1;
	_normalVertexIndexArrayBottomSize = 1;
	_normalVertexIndexArrayTopSize = 1;
	Create(&_defaultSpherePosition, 1.0f, false, "");
	return true;
}

bool MyCylinder::Create(const Vector4f *position, float bottomRadius, bool texture, std::string texLocation) {
	float slice_inc;
	float stack_inc;
	float halfHeight;
	float currentHeight;
	int vertex_count;
	int index_count;

	const float _topRadius(0.0f);
	float height = bottomRadius / 0.5f;

	this->SetPosition(*position);

	if (_slices < 3 || _stacks < 2) return false;

	_vertexarrayTopSize = _slices;
	_vertexarrayBodySize = _slices*_stacks;
	_vertexarrayBottomSize = _slices;
	_normalarrayTopSize = _slices;
	_normalarrayBodySize = _slices*_stacks;
	_normalarrayBottomSize = _slices;
	_texarrayTopSize = _slices;
	_texarrayBodySize = _slices*_stacks;
	_texarrayBottomSize = _slices;
	_indexarrayTopSize = _slices;
	_indexarrayBodySize = _slices*(_stacks-1)*4;
	_indexarrayBottomSize = _slices;
	_normalVertexIndexArrayTopSize = _indexarrayTopSize * 2;//used for GeneratePhysicalNormals()
	_normalVertexIndexArrayBodySize = _indexarrayBodySize * 2;//used for GeneratePhysicalNormals()
	_normalVertexIndexArrayBottomSize = _indexarrayBottomSize * 2;//used for GeneratePhysicalNormals()
	_normalVertexArrayTopSize = _vertexarrayTopSize * 2;//used for GeneratePhysicalNormals()
	_normalVertexArrayBodySize = _vertexarrayBodySize * 2;//used for GeneratePhysicalNormals()
	_normalVertexArrayBottomSize = _vertexarrayBottomSize * 2;//used for GeneratePhysicalNormals()

	AllocateMemory();


	slice_inc = PI*2.0f/_slices;
 
	halfHeight = currentHeight = height*0.5f;// bottomRadius = height
	stack_inc = height/(_stacks-1); // bottomRadius = height


	// **** define the vertex/normal/texture arrays ****
	// Top
	vertex_count = 0;
	float angle = 0.0f;
	for(int slice = 0; slice < _slices; slice++)
	{
		_vertexarrayTop[vertex_count][0] = _topRadius*cos(angle); 
		_vertexarrayTop[vertex_count][1] = halfHeight; 
		_vertexarrayTop[vertex_count][2] = -_topRadius*sin(angle); 

		_normalarrayTop[vertex_count][0] = 0.0f; 
		_normalarrayTop[vertex_count][1] = 1.0f; 
		_normalarrayTop[vertex_count][2] = 0.0f;

		_texarrayTop[vertex_count][0] = cos(angle)*0.25f; 
		_texarrayTop[vertex_count++][1] = sin(angle)*0.25f; 

		angle += slice_inc;
	}

	// Body
//	STEP = (MAX - MIN) / (NUM + 1)
//
//Then you can calculate the values as
//
//VALUE(1) = MIN + STEP
//VALUE(2) = VALUE(1) + STEP
//....
//VALUE(NUM) = VALUE(NUM-1) + STEP
//
//and you will have MAX = VALUE(NUM) + STEP
	float min;
	float max;
	if (bottomRadius<_topRadius){
		min = bottomRadius;
		max = _topRadius;
	}
	else {
		min = _topRadius;
		max = bottomRadius;
	}

	float step = (max-min)/(_stacks+1);
	float radius;

	vertex_count = 0;
	angle = 0.0f;
	for(int stack = 0; stack < _stacks; stack++)
	{
		radius = min + step;
		for(int slice = 0; slice < _slices; slice++)
		{
			_vertexarrayBody[vertex_count][0] = radius*cos(angle); 
			_vertexarrayBody[vertex_count][1] = currentHeight; 
			_vertexarrayBody[vertex_count][2] = radius*sin(angle); 

			_normalarrayBody[vertex_count][0] = cos(angle); 
			_normalarrayBody[vertex_count][1] = 0.0f; 
			_normalarrayBody[vertex_count][2] = -sin(angle);

			_texarrayBody[vertex_count][0] = cos(angle)*0.25f; 
			_texarrayBody[vertex_count++][1] = sin(angle)*0.25f; 

			angle += slice_inc;
		}
		step = step + step;
		currentHeight -= stack_inc;
	}

	// Bottom
	vertex_count = 0;
	angle = 0.0f;
	for(int slice = 0; slice < _slices; slice++)
	{
		_vertexarrayBottom[vertex_count][0] = bottomRadius*cos(angle); 
		_vertexarrayBottom[vertex_count][1] = -halfHeight; 
		_vertexarrayBottom[vertex_count][2] = -bottomRadius*sin(angle); 

		_normalarrayBottom[vertex_count][0] = 0.0f; 
		_normalarrayBottom[vertex_count][1] = -1.0f; 
		_normalarrayBottom[vertex_count][2] = 0.0f;

		_texarrayBottom[vertex_count][0] = 1.0f - cos(angle)*0.25f; 
		_texarrayBottom[vertex_count++][1] = 1.0f - sin(angle)*0.25f; 

		angle += slice_inc;
	}

	// **** define the index array ****
	// Top 
	index_count = 0;
	for(int slice = 0; slice < _slices; slice++)
	{
		_indexarrayTop[index_count] = index_count++;
	}
	// Body
	index_count = 0;
	for(int stack = 0; stack < _stacks-1; stack++)
	{
		for(int slice = 0; slice < _slices-1; slice++)
		{
			_indexarrayBody[index_count++] = (_slices*stack)+slice;
			_indexarrayBody[index_count++] = (_slices*stack)+slice+_slices;
			_indexarrayBody[index_count++] = (_slices*stack)+slice+1+_slices;
			_indexarrayBody[index_count++] = (_slices*stack)+slice+1;
		}
		_indexarrayBody[index_count++] = (_slices*stack)-1+_slices;
		_indexarrayBody[index_count++] = (_slices*stack)-1+_slices*2;
		_indexarrayBody[index_count++] = (_slices*stack)+_slices;
		_indexarrayBody[index_count++] = (_slices*stack);
	}
	// Bottom 
	index_count = 0;
	for(int slice = 0; slice < _slices; slice++)
	{
		_indexarrayBottom[index_count++] = _slices - 1 - slice;
	}

	return true;
}

void MyCylinder::Draw() const {

	glRotatef( yAngle, 0.0f, 1.0f,0.0f); //yAngle
	glRotatef( xAngle, 1.0f, 0.0f,0.0f); //xAngle

	// Body
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _vertexarrayBody);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, _texarrayBody);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, _normalarrayBody);
	glDrawElements(GL_QUADS, _slices*(_stacks-1)*4, GL_UNSIGNED_INT, _indexarrayBody);

	// Top
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _vertexarrayTop);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, _texarrayTop);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, _normalarrayTop);
	glDrawElements(GL_POLYGON, _slices, GL_UNSIGNED_INT, _indexarrayTop);
 
	// Bottom
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _vertexarrayBottom);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, _texarrayBottom);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, _normalarrayBottom);
	glDrawElements(GL_POLYGON, _slices, GL_UNSIGNED_INT, _indexarrayBottom);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

}

void MyCylinder::DrawNormals(void)const{

}

void MyCylinder::GeneratePhysicalNormals(void){
	/*for(int stack = 0; stack < _stacks; stack++)
	{
		radius = min + step;
		for(int slice = 0; slice < _slices; slice++)
		{
			_vertexarrayBody[vertex_count][0] = radius*cos(angle); 
			_vertexarrayBody[vertex_count][1] = currentHeight; 
			_vertexarrayBody[vertex_count][2] = radius*sin(angle); 

			_normalarrayBody[vertex_count][0] = cos(angle); 
			_normalarrayBody[vertex_count][1] = 0.0f; 
			_normalarrayBody[vertex_count][2] = -sin(angle);

			_texarrayBody[vertex_count][0] = cos(angle)*0.25f; 
			_texarrayBody[vertex_count++][1] = sin(angle)*0.25f; 

			angle += slice_inc;
		}
		step = step + step;
		currentHeight -= stack_inc;
	}*/
	int counter = 0; // used to point to the correct _normalVertexArray index when initialising the loop
	// can't just use 'i' because that will end up overwriting values
	for (GLuint i = 0; i < _normalVertexArrayBodySize; i++){
		_normalVertexArrayBody[i+counter][0] = _vertexarrayBody[i][0]; // x - start of the line
		_normalVertexArrayBody[i+counter][1] = _vertexarrayBody[i][1]; // y - start of the line
		_normalVertexArrayBody[i+counter][2] = _vertexarrayBody[i][2]; // z - start of the line

		_normalVertexArrayBody[i+counter+1][0] = _vertexarrayBody[i][0]+_normalarrayBody[i][0]; // x - end of the line
		_normalVertexArrayBody[i+counter+1][1] = _vertexarrayBody[i][1]+_normalarrayBody[i][1]; // x - end of the line
		_normalVertexArrayBody[i+counter+1][2] = _vertexarrayBody[i][2]+_normalarrayBody[i][2]; // x - end of the line

		counter++;
	}
	counter = 0;
	for (GLuint i = 0; i < _normalVertexArrayBottomSize; i++){
		_normalVertexArrayBottom[i+counter][0] = _vertexarrayBottom[i][0]; // x - start of the line
		_normalVertexArrayBottom[i+counter][1] = _vertexarrayBottom[i][1]; // y - start of the line
		_normalVertexArrayBottom[i+counter][2] = _vertexarrayBottom[i][2]; // z - start of the line

		_normalVertexArrayBottom[i+counter+1][0] = _vertexarrayBottom[i][0]+_normalarrayBottom[i][0]; // x - end of the line
		_normalVertexArrayBottom[i+counter+1][1] = _vertexarrayBottom[i][1]+_normalarrayBottom[i][1]; // x - end of the line
		_normalVertexArrayBottom[i+counter+1][2] = _vertexarrayBottom[i][2]+_normalarrayBottom[i][2]; // x - end of the line

		counter++;
	}
	counter = 0;
	for (GLuint i = 0; i < _normalVertexArrayTopSize; i++){
		_normalVertexArrayTop[i+counter][0] = _vertexarrayTop[i][0]; // x - start of the line
		_normalVertexArrayTop[i+counter][1] = _vertexarrayTop[i][1]; // y - start of the line
		_normalVertexArrayTop[i+counter][2] = _vertexarrayTop[i][2]; // z - start of the line

		_normalVertexArrayTop[i+counter+1][0] = _vertexarrayTop[i][0]+_normalarrayTop[i][0]; // x - end of the line
		_normalVertexArrayTop[i+counter+1][1] = _vertexarrayTop[i][1]+_normalarrayTop[i][1]; // x - end of the line
		_normalVertexArrayTop[i+counter+1][2] = _vertexarrayTop[i][2]+_normalarrayTop[i][2]; // x - end of the line

		counter++;
	}
	for (GLuint i = 0; i < _normalVertexIndexArrayBodySize; i++){ // populate the index array for the normalvertex
		_normalVertexIndexArrayBody[i] = i;
	}
	for (GLuint i = 0; i < _normalVertexIndexArrayBottomSize; i++){ // populate the index array for the normalvertex
		_normalVertexIndexArrayBottom[i] = i;
	}
	for (GLuint i = 0; i < _normalVertexIndexArrayTopSize; i++){ // populate the index array for the normalvertex
		_normalVertexIndexArrayTop[i] = i;
	}
}

void MyCylinder::SetAnimationCoefficients(const vector<Vector3f> &animation){
	this->Shape::SetAnimationCoefficients(animation);
}

void MyCylinder::SetPosition(const Vector4f &position) {
	this->Shape::SetPosition(position);
}

const Vector4f& MyCylinder::GetPosition() {
	return this->Shape::GetPosition();
}

void MyCylinder::Update(){
}

void MyCylinder::Update(const Vector4f &objectToPointAt){
	Vector4f obDirection = objectToPointAt.Subtract(GetPosition());
	float xLength = sqrt(obDirection.x()*obDirection.x() + obDirection.y()*obDirection.y() );
	xAngle = (float)(180/3.142) * (atan(xLength/(obDirection.y())));	
	yAngle = (float)(180/3.142) * (atan(obDirection.x()/(obDirection.z())));
//
//	yrotaio	
	if(objectToPointAt.z() > GetPosition().z())
	{
		yAngle += 180; 
	}
//	xrotation
	xAngle = ((objectToPointAt.y() > GetPosition().y()) ? (-180 - xAngle): -xAngle);


	//if (pointAt.xyz()[1] > GetPosition().xyz()[1])
	//{			
	//	xAngle = -180 - xAngle; 
	//}
	//else
	//{		
	//	xAngle = -xAngle; 
	//}
}

void MyCylinder::Update(float deltaTime, float timeElapsed){

}