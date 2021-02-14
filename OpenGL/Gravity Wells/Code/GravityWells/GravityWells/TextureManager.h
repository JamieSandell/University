#pragma once
#include <vector>
#include <string>
#include "GXBase.h"

using namespace gxbase;

//TextureManager is a Singleton class
class TextureManager
{
public:
	TextureManager(void);// Call GetSingleton to initialize the class properly
	~TextureManager(void);
	static TextureManager &GetSingleton(void){
		if (p_singleton==NULL){ //isn't created so create it
			p_singleton = new TextureManager;
			Initialize();
		}

		return *p_singleton;
	};
	static void Destroy(void){
		p_singleton->FreeAllTextures();
		delete p_singleton;
		p_singleton = NULL;
	};
	GLuint LoadTexture (const std::string &textures, const std::string &WRAP);
	void FreeTexture(int textureID);
	void FreeAllTextures(void);

private:
	static void Initialize(void){
		p_singleton->_errorMessage = "";
		p_singleton->_numberOfTextures = 0;
	}; //Called via GetSingleton, don't call it yourself
	std::string _errorMessage;
	int _numberOfTextures;
	std::vector<GLuint> _textureIDs;
	static TextureManager *p_singleton;
};
