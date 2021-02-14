#include <algorithm>
#include "TextureManager.h"

using std::find;
using std::vector;
using std::string;

TextureManager *TextureManager::p_singleton = NULL;

TextureManager::TextureManager(void)
{
	_errorMessage = "";
	_numberOfTextures = 0;
}

TextureManager::~TextureManager(void)
{
	//Destroy();
}

void TextureManager::FreeAllTextures(void){
	GLuint *texIDs = new GLuint[_numberOfTextures];
	for (int i = 0; i < _numberOfTextures; i++){
		texIDs[i] = _textureIDs[i];
	}
	glDeleteTextures(p_singleton->_numberOfTextures, texIDs);

	_numberOfTextures = 0;
	_textureIDs.clear();
}

void TextureManager::FreeTexture(int textureID){
	vector<GLuint>::iterator result = find(_textureIDs.begin(), _textureIDs.end(), textureID);
	if (result!=_textureIDs.end()){
		glDeleteTextures(1, &_textureIDs[textureID]);
		_textureIDs.erase(result);
		_numberOfTextures--;
	}
}



GLuint TextureManager::LoadTexture(const string &textures, const string &WRAP){
	Image image;
	if (!image.Load(textures.c_str())){
		_errorMessage = "Failed to load: " + textures;
		image.Free();
	}
	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture( GL_TEXTURE_2D, texID );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	if (WRAP=="CLAMP"){ //repeat is default in OpenGL
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}
	image.gluBuild2DMipmaps();
	image.Free();
	_textureIDs.push_back(texID);
	_numberOfTextures++;

	return texID;
}