#include "Vector3f.h"

Vector3f::Vector3f() {
	Assign(0.0f, 0.0f, 0.0f);
}

Vector3f::~Vector3f(){

}

Vector3f::Vector3f(GLfloat x, GLfloat y, GLfloat z) {
	Assign(x, y, z);
}

Vector3f::Vector3f(GLfloat xyz[]) {
	Assign(xyz[0], xyz[1], xyz[2]);
}
