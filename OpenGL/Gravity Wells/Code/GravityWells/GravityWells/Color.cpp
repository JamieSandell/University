#include "Color.h"

using std::vector;

Color::Color() { 
	Assign(0.0, 0.0, 0.0, 0.0);
}

Color::Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	Assign(r, g, b, a);
}

Color::Color(vector<Vector4f> &rgba){
	Assign(rgba[0].x(), rgba[0].y(), rgba[0].z(), rgba[0].w());
}

Color::Color(GLfloat rgba[]) {
	Assign(rgba[0], rgba[1], rgba[2], rgba[3]);
}