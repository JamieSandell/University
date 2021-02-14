#include "Circle.h"
#include <cmath>
#define PI  (float)3.1415926

Circle::Circle() {
}

Circle::~Circle() {
	DeallocateMemory();
}

Circle::Circle(const Circle &A){
	CopyNonPointerDataMembers(A);
	CopyPointerDataMembers(A);
}

Circle& Circle::operator =(const Circle &A){
	if (&A != this){
		CopyNonPointerDataMembers(A);
		DeallocateMemory();
		AllocateMemory();// make sure the pointer members have enough space allocated for the memcpy
		CopyPointerDataMembers(A);
	}
	return *this;
}

void Circle::AllocateMemory(void){
	_vertexarray = new float[_vertexarraySize][3];
	_indexarray = new GLuint[_indexarraySize];
	_texarray = new float[_texarraySize][2];
}

void Circle::Assign(void){

}

void Circle::Assign(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture){
	DeallocateMemory(); // remove the old memory
	Create(position, heightWidthDepth, texture);
}

Circle* Circle::CloneToAnEmptyObject()const{
	Circle *p = new Circle;
	p->Create();
	*p = *this;
	return p;
}

void Circle::CopyNonPointerDataMembers(const Circle &A){
	// Copy non-pointer data members
	_texarraySize = A._texarraySize;
	_vertexarraySize = A._vertexarraySize;
	_indexarraySize = A._indexarraySize;
	CopyBaseMembers(A);
}

void Circle::CopyPointerDataMembers(const Circle &A){
	// C++ guarantee that elements of multidimensional arrays occupy contiguous memory addresses
	// this is quicker then the for-loop method
	// Copy pointer data members
	memcpy(_vertexarray, A._vertexarray, _vertexarraySize*sizeof(float)*3);//*3 because array[][3]
	memcpy(_texarray, A._texarray, _texarraySize*sizeof(float)*2);
	memcpy(_indexarray, A._indexarray, _indexarraySize*sizeof(float));
}
bool Circle::Create(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture) {
	int array_size;
	float stack_inc;
	float slice_inc;
	float x, y , z;
	int vertex_count;
	int index_count;
	int temp_vc;
	float temp_tex;
	//float temp_rad;

	_vertexarraySize = _texarraySize = array_size = (_slices+1)*(_stacks-1)+1;	// +2 is for the top and bottom vertex
	_indexarraySize = 1+_slices+1 +((_stacks-2)*((_slices+1)*2));

	_vertexarray = new float[array_size][3];
	_indexarray = new GLuint[_indexarraySize];
	_texarray = new float[array_size][2];

	stack_inc = 1.0f/(float)(_stacks-1);
	slice_inc = PI*2.0f/_slices;

	float radiusInc( heightWidthDepth.y()/(_stacks-1));
	float currentRadius(0);

	float textRadius = 0;
	// top point
	vertex_count = 0;
	_vertexarray[vertex_count][0] = 0.0f; 
	_vertexarray[vertex_count][1] = currentRadius; 
	_vertexarray[vertex_count][2] = 0.0f;

	//_texarray[vertex_count][0] = 0; 
	//_texarray[vertex_count++][1] = 1; 

	_texarray[vertex_count][0] = 0.5f*100.0f; 
	_texarray[vertex_count++][1] = 0.5f*100.0f; 

	textRadius += (0.5f/(_stacks-1));

	currentRadius+= radiusInc;

	//create the middle section of the Ball
	for (int i = 1; i < _stacks; i++) {
		y = sin(PI*(1/2.0f - stack_inc*(float)i));
		//temp_rad = cos(PI*(1/2.0f - stack_inc*(float)i));
		//		temp_rad =temp_rad + 0.1f;
		temp_vc = vertex_count;
		temp_tex = 1.0f - stack_inc*(float)i;
		for(int j = 0; j < _slices; j++) {
			x = cos((float)j*slice_inc); 
			z = -sin((float)j*slice_inc);  
			_vertexarray[vertex_count][0] = currentRadius*x;//*temp_rad;
			_vertexarray[vertex_count][1] = 0;
			_vertexarray[vertex_count][2] = currentRadius*z;//*temp_rad;
			_texarray[vertex_count][0] = ((textRadius*x)+0.5f)*100;
			_texarray[vertex_count++][1] =((textRadius*z)+0.5f)*100;		
		};
		_vertexarray[vertex_count][0] = _vertexarray[temp_vc][0];
		_vertexarray[vertex_count][1] = _vertexarray[temp_vc][1];
		_vertexarray[vertex_count][2] = _vertexarray[temp_vc][2];
		_texarray[vertex_count][0] = _texarray[temp_vc][0];
		_texarray[vertex_count++][1] = _texarray[temp_vc][1];
		currentRadius+= radiusInc;		
		textRadius += (0.5f/(_stacks-1));
	};

	index_count = 0;
	vertex_count =1;
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

	this->SetHeightWidthDepth(heightWidthDepth);
	this->SetTextureEnabledStatus(texture);
	this->SetPosition(position);

	return true;
}

void Circle::Draw(void) const {
	float radius = this->Shape::GetHeightWidthDepth().y();
	Vector3f position = this->Shape::GetPosition();
	if (GetTextureEnabledStatus()){
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, _texarray);
		glBindTexture(GL_TEXTURE_2D, GetTextureID());
	}

	glColor4fv(GetColorFloat());
	Color _color = GetColor();
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _vertexarray);
	glDrawElements(GL_TRIANGLE_FAN, _slices+2, GL_UNSIGNED_INT, &_indexarray[0]);
	for (int i = 0; i < (_stacks-2); i++) { 
		glDrawElements(GL_TRIANGLE_STRIP, (_slices+1)*2, GL_UNSIGNED_INT, &_indexarray[(2+_slices)+(i*(_slices+1)*2 )]);
	};

	if (GetTextureEnabledStatus()){
		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

