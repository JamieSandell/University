#pragma once

#include "GXBase.h"
using namespace gxbase;

class Shader : public GLWindowEx{
public:
	bool Apply(void);
	char *textFileRead(char *fn)const;
private:
	GLuint _createProgram, _createVertexShader, _createFragmentShader;
};