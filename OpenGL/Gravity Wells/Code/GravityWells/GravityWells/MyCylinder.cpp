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
bool MyCylinder::Create() {
	_vertexarraySize = 1;
	_indexarraySize = 1;
	_texarraySize = 1;
	Create(Vector3f(0.0f,0.0f,0.0f), Vector3f(1.0f,1.0f,1.0f), false);
	return true;
}

bool MyCylinder::Create(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture) {
	this->Shape::SetPosition(position);
	this->Shape::SetHeightWidthDepth(heightWidthDepth);
	this->Shape::SetTextureEnabledStatus(texture);

	int array_size;
	float stack_inc;
	float slice_inc;
	float x, y , z;
	int vertex_count;
	int index_count;
	int temp_vc;
	float temp_tex;
	//float temp_rad;
	float height = heightWidthDepth.x();
	float heightinc = height/(_stacks-1);
	array_size = (_slices+1)*(_stacks); // +2 is for the top and bottom vertex
	_vertexarraySize = _indexarraySize = _texarraySize = array_size;
	_vertexarray = new float[array_size][3];
	_indexarray = new GLuint[(_stacks)*(_slices+1)*2];
	_texarray = new float[array_size][2];
	vertex_count = 0;
	stack_inc = 1.0f/(float)(_stacks-1);
	slice_inc = PI*2.0f/_slices;
	float radius = heightWidthDepth.y();
	for (int i = 0; i < _stacks; i++) {
		y = sin(PI*(1/2.0f - stack_inc*(float)i));
		// temp_rad = cos(PI*(1/2.0f - stack_inc*(float)i));
		// temp_rad =temp_rad + 0.1f;
		temp_vc = vertex_count;
		temp_tex = 1.0f - stack_inc*(float)i;
		for(int j = 0; j < _slices; j++) {
			x = cos((float)j*slice_inc);
			z = -sin((float)j*slice_inc);
			_vertexarray[vertex_count][0] = radius*x;
			_vertexarray[vertex_count][1] = height;
			_vertexarray[vertex_count][2] = radius*z;
			//_texarray[vertex_count][0] = ((float)j/(float)_slices/2);
			_texarray[vertex_count][0] = ((float)j/(float)_slices/2) * 420;
			_texarray[vertex_count++][1] = temp_tex;
		};
		_vertexarray[vertex_count][0] = _vertexarray[temp_vc][0];
		_vertexarray[vertex_count][1] = _vertexarray[temp_vc][1];
		_vertexarray[vertex_count][2] = _vertexarray[temp_vc][2];
		_texarray[vertex_count][0] = _texarray[temp_vc][0];
		_texarray[vertex_count++][1] = _texarray[temp_vc][1];
		height -= heightinc;
	};
	index_count = 0;
	vertex_count =0;
	for(int i = 0; i< (_stacks); i++) {
		for(int j = 0; j<= _slices; j++) {
			_indexarray[index_count++] = vertex_count++;
			_indexarray[index_count++] = _slices+vertex_count;
		};
	};

	return true;
}

void MyCylinder::Draw() const {
	if (GetTextureEnabledStatus()){
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, _texarray);
		glBindTexture(GL_TEXTURE_2D, GetTextureID());
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _vertexarray);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glCullFace(GL_BACAK);
	glColor4fv(GetColorFloat());
	glDisable(GL_CULL_FACE);
	for (int i = 0; i < (_stacks-1); i++) {
		glDrawElements(GL_TRIANGLE_STRIP, (_slices+1)*2, GL_UNSIGNED_INT, &_indexarray[(i*(_slices+1)*2)]);
	};
	glEnable(GL_CULL_FACE);

	if (GetTextureEnabledStatus()){
		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

}