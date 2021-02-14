#include <iostream>
#include <fstream>
#include "Shader.h"

char* Shader::textFileRead(char *fn)const {
	FILE *fp = NULL;
	char *content = NULL;

	int count=0;

	if (fn != NULL) {
		//fp = fopen(fn,"rt"); //deprecated
		errno_t fileOpenError = fopen_s(&fp, fn, "rt");

		if (fp != NULL) {

			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

bool Shader::Apply(void){
	GLWindowEx::OnCreate();
	GLint done=0;

	//-- load shader source from disk
	const GLcharARB *vertSource, *fragSource;
	vertSource = textFileRead("Vertex.txt");
	fragSource = textFileRead("Fragment.txt");
	if (!vertSource || !fragSource) {
		App::MsgPrintf("Failed to load shader(s)\n");
		delete [] vertSource;
		delete [] fragSource;
	}

	//-- vertex shader
	// create vertex shader object
	GLhandleARB vert = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	// load vertex shader source into object, and compile it
	glShaderSourceARB(vert, 1, &vertSource, NULL);
	glCompileShaderARB(vert);
	// check if it compiled
	glGetObjectParameterivARB(vert, GL_OBJECT_COMPILE_STATUS_ARB, &done);
	if (!done) {
		App::MsgPrintf("Failed to compile vertex shader\n");
		return false;
	}

	//-- fragment shader
	// create fragment shader object
	GLhandleARB frag = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	// load fragment shader source into object, and compile it
	glShaderSourceARB(frag, 1, &fragSource, NULL);
	glCompileShaderARB(frag);
	// check if it compiled
	glGetObjectParameterivARB(frag, GL_OBJECT_COMPILE_STATUS_ARB, &done);
	if (!done) {
		App::MsgPrintf("Failed to compile fragment shader\n");
		return false;
	}

	//-- program object
	// create program object
	GLhandleARB prog = glCreateProgramObjectARB();
	glAttachObjectARB(prog, vert);	// attach vertex shader
	glAttachObjectARB(prog, frag);	// attach fragment shader

	//-- link the program object
	glLinkProgramARB(prog);
	// check if it linked
	glGetObjectParameterivARB(prog, GL_OBJECT_LINK_STATUS_ARB, &done);
	if (!done) {
		App::MsgPrintf("Failed to link shader program\n");
		return false;
	}

	// use this program (apply it to current OpenGL state)
	glUseProgramObjectARB(prog);

	// setup uniform values, which are passed to the shader program
	//glUniform3fARB(GetUniform(prog, "Colour1"), 1.0f, 0.0f, 0.0f);
	//glUniform3fARB(GetUniform(prog, "Colour2"), 1.0f, 1.0f, 1.0f);
	//glUniform1fARB(GetUniform(prog, "GridSize"), 0.5f);
	//glUniform3fARB(GetUniform(prog, "LightPosition"), 0.0f, 0.0f, 4.0f);

	// free shader source
	delete [] vertSource;
	delete [] fragSource;

	// success
	return true;
}