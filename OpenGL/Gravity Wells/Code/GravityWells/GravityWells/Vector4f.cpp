#include "Vector4f.h"

Vector4f::Vector4f() {
	Assign(0.0f, 0.0f, 0.0f, 0.0f);
}

Vector4f::~Vector4f(){

}

Vector4f::Vector4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	Assign(x, y, z, w);
}

Vector4f::Vector4f(GLfloat xyzw[]) {
	Assign(xyzw[0], xyzw[1], xyzw[2], xyzw[3]);
}
