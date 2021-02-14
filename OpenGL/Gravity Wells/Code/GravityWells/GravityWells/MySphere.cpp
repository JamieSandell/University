#include "MySphere.h"
#include <math.h>

using std::vector;

#define PI  (float)3.1415926

MySphere::MySphere() {
}

MySphere::~MySphere() {
	DeallocateMemory();
}

MySphere::MySphere(const MySphere &A){
	CopyNonPointerDataMembers(A);
	CopyPointerDataMembers(A);
}

MySphere& MySphere::operator =(const MySphere &A){
	if (&A != this){
		CopyNonPointerDataMembers(A);
		DeallocateMemory();
		AllocateMemory();// make sure the pointer members have enough space allocated for the memcpy
		CopyPointerDataMembers(A);
	}
	return *this;
}

void MySphere::AllocateMemory(void){
	/*_vertexarray = new float[_vertexarraySize][3];
	_normalarray = new float[_normalarraySize][3];
	_indexarray = new GLuint[_indexarraySize];
	_texarray = new float[_texarraySize][2];
	_normalVertexArray = new GLfloat [_normalVertexArraySize][3];
	_normalVertexIndexArray = new GLuint [_normalVertexIndexArraySize];*/
}

void MySphere::CopyNonPointerDataMembers(const MySphere &A){
	// Copy non-pointer data members
	//_indexarraySize = A._indexarraySize;
	//_normalarraySize = A._normalarraySize;
	//_vertexarraySize = A._vertexarraySize;
	_radius = A._radius;
	//_normalVertexIndexArraySize = A._normalVertexIndexArraySize;
	//_normalVertexArraySize = A._normalVertexArraySize;
	CopyBaseMembers(A);
}

void MySphere::CopyPointerDataMembers(const MySphere &A){
	// C++ guarantee that elements of multidimensional arrays occupy contiguous memory addresses
	// this is quicker then the for-loop method
	// Copy pointer data members
	//memcpy(_vertexarray, A._vertexarray, _vertexarraySize*sizeof(float)*3);//*3 because array[][3]
	//memcpy(_normalarray, A._normalarray, _normalarraySize*sizeof(float)*3);
	//memcpy(_texarray, A._texarray, _texarraySize*sizeof(float)*2);
	//memcpy(_indexarray, A._indexarray, _indexarraySize*sizeof(float));
	//memcpy(_normalVertexArray, A._normalVertexArray, _normalVertexArraySize*sizeof(float)*3); // *3 because array[][3]
	//memcpy(_normalVertexIndexArray, A._normalVertexIndexArray, _normalVertexIndexArraySize*sizeof(GLuint)); // *3 because array[][3]
}

void MySphere::DeallocateMemory(void){
	//delete [] _vertexarray;
	//delete [] _normalarray;
	//delete [] _indexarray;
	//delete [] _texarray;
	//delete [] _normalVertexArray;
	//delete [] _normalVertexIndexArray;
}

bool MySphere::Create(){
	//_vertexarraySize = 1;
	//_texarraySize = 1;
	//_normalarraySize = 1;
	//_indexarraySize = 1;
	//_normalVertexArraySize = 1;
	//_normalVertexIndexArraySize = 1;
	Create(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f,1.0f,1.0f), false);
	return true;
}
bool MySphere::Create(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture) {
	float stack_inc;
	float slice_inc;
	float x, y , z;
	int vertex_count;
	int index_count;
	int temp_vc;
	float temp_tex;
	float temp_rad;

	//_vertexarraySize = array_size;
	//_normalarraySize = array_size;
	//_indexarraySize = 2+(_stacks-1)*(_slices+1)*2;
	//_texarraySize = array_size;
	//_normalVertexIndexArraySize = array_size*2;
	//_normalVertexArraySize = _normalVertexIndexArraySize;
	AllocateMemory();

	if ((_stacks < 2) & (_slices <2)) return false;

	stack_inc = 1.0f/(float)_stacks;
	slice_inc = PI*2.0f/_slices;

	// define the vertex array
	float radius = heightWidthDepth.y();
	// top point
	vertex_count = 0;
	_vertexarray[vertex_count][0] = 0.0f; 
	_vertexarray[vertex_count][1] = radius; 
	_vertexarray[vertex_count][2] = 0.0f; 

	_normalarray[vertex_count][0] = 0.0f; 
	_normalarray[vertex_count][1] = 1.0f; 
	_normalarray[vertex_count][2] = 0.0f;

	_texarray[vertex_count][0] = 0; 
	_texarray[vertex_count++][1] = 1; 

	// bottom point
	_vertexarray[vertex_count][0] = 0.0f; 
	_vertexarray[vertex_count][1] = -radius; 
	_vertexarray[vertex_count][2] = 0.0f;

	_normalarray[vertex_count][0] = 0.0f; 
	_normalarray[vertex_count][1] = -1.0f; 
	_normalarray[vertex_count][2] = 0.0f;

	_texarray[vertex_count][0] = 0; 
	_texarray[vertex_count++][1] = 0; 


	for (int i = 1; i < _stacks; i++) {
		y = sin(PI*(1/2.0f - stack_inc*(float)i));
		temp_rad = cos(PI*(1/2.0f - stack_inc*(float)i));
		temp_vc = vertex_count;
		temp_tex = 1.0f - stack_inc*(float)i;
		for(int j = 0; j < _slices; j++) {
			x = cos((float)j*slice_inc); 
			z = -sin((float)j*slice_inc);  
			_vertexarray[vertex_count][0] = radius*temp_rad*x;
			_vertexarray[vertex_count][1] = radius*y;
			_vertexarray[vertex_count][2] = radius*temp_rad*z;
			_normalarray[vertex_count][0] = temp_rad*x;
			_normalarray[vertex_count][1] = y;
			_normalarray[vertex_count][2] = temp_rad*z;
			_texarray[vertex_count][0] = (float)j/(float)_slices;
			_texarray[vertex_count++][1] = temp_tex;
		};
		_vertexarray[vertex_count][0] = _vertexarray[temp_vc][0];
		_vertexarray[vertex_count][1] = _vertexarray[temp_vc][1];
		_vertexarray[vertex_count][2] = _vertexarray[temp_vc][2];
		_normalarray[vertex_count][0] = _normalarray[temp_vc][0];
		_normalarray[vertex_count][1] = _normalarray[temp_vc][1];
		_normalarray[vertex_count][2] = _normalarray[temp_vc][2];
		_texarray[vertex_count][0] = 1;
		_texarray[vertex_count++][1] = temp_tex;
	};

	// now generate the index array
	// start with triangle fans for the top
	index_count = 0;
	vertex_count =2;
	_indexarray[index_count++] = 0; // very top vertex
	for(int j = 0; j<= _slices; j++) {
		_indexarray[index_count++] = vertex_count++;
	};
	vertex_count -= (_slices+1);
	// now do the main strips
	for(int i = 0; i< (_stacks-2); i++) {
		for(int j = 0; j<= _slices; j++) {
			_indexarray[index_count++] = vertex_count++;
			_indexarray[index_count++] = _slices+vertex_count;
		};
	};

	_indexarray[index_count++] = 1; // very bottom vertex
	for(int j = 0; j<= _slices; j++) {
		_indexarray[index_count++] = vertex_count+_slices-j;
	};

	this->SetPosition(position);
	this->SetTextureEnabledStatus(texture);
	this->SetHeightWidthDepth(heightWidthDepth);
	_radius = radius;

	return true;
}

void MySphere::Draw(void) const {
	if (GetTextureEnabledStatus()){
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, _texarray);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, GetTextureID());
	}
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, _normalarray);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _vertexarray);

	Color _color = GetColor();
	glColor4fv(GetColorFloat());

	glDrawElements(GL_TRIANGLE_FAN, _slices+2, GL_UNSIGNED_INT, &_indexarray[0]);
	for (int i = 0; i < (_stacks-2); i++) { 
		glDrawElements(GL_TRIANGLE_STRIP, (_slices+1)*2, GL_UNSIGNED_INT, &_indexarray[_slices+2+i*(_slices+1)*2]);
	};
	glDrawElements(GL_TRIANGLE_FAN, _slices+2, GL_UNSIGNED_INT, &_indexarray[_slices+2+(_stacks-2)*(_slices+1)*2]);

	if (GetTextureEnabledStatus()){
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, _texarray);
		glDisable(GL_TEXTURE_2D);
	}
	glDisableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, _normalarray);
	glDisableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _vertexarray);
}

