#pragma once

#include<vector>
#include "GXBase.h"
#include "Vector4f.h"

class Color {
private:
	GLfloat _rgba[4];

public:
	inline void Assign(GLfloat r, GLfloat g, GLfloat b, GLfloat a){_rgba[0] = r;_rgba[1] = g;_rgba[2] = b;_rgba[3] = a;};

	Color();

	Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	Color(GLfloat rgba[]);

	Color(std::vector<Vector4f> &rgba);

	inline const GLfloat* rgba() const{return _rgba;};

	inline static Color black(){return Color(0.0, 0.0, 0.0, 1.0);};

	inline static Color white(){return Color(1.0, 1.0, 1.0, 1.0);};

	inline static Color red(){return Color(1.0, 0.0, 0.0, 1.0);};

	inline static Color green(){return Color(0.0, 1.0, 0.0, 1.0);};

	inline static Color blue(){return Color(0.0, 0.0, 1.0, 1.0);};

	inline static Color yellow(){return Color(1.0, 1.0, 0.0, 1.0);};

	inline static Color null(){return Color(0.0, 0.0, 0.0, 0.0);};
};