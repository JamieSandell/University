#pragma once

#include <vector>
#include "Vector3f.h"
#include "Vector4f.h"
#include "Color.h"

class Shape
{
public:
	Shape(void);
	virtual ~Shape();//virtual destructor

	virtual void Assign(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture) = 0;//pure virtual must provide your own
	virtual Shape* CloneToAnEmptyObject()const = 0;//pure virtual must provide your own Calls create
	virtual Shape* Clone()const = 0;//pure virtual must provide your own Calls copy constructor
	virtual bool Create(void) = 0;//pure virtual must provide your own
	virtual bool Create(const Vector3f &position, const Vector3f &heightWidthDepth, bool texture) = 0;//pure virtual must provide your own
	virtual void Update(float deltaTime) = 0;//pure virtual must provide your own
	virtual void Draw() const = 0;//pure virtual must provide your own
	void CopyBaseMembers(const Shape &source);

public: // accessors

	inline const GLfloat *GetColorFloat(void) const{return _color.rgba();};
	inline const Color &GetColor(void) const{return _color;};
	inline void SetColor(Color &color) {_color=color;};

	inline const Vector3f &GetHeightWidthDepth(void) const{return _heightWidthDepth;};
	inline void SetHeightWidthDepth(const Vector3f &hWD){_heightWidthDepth = hWD;};

	inline void SetWidth(float width){_heightWidthDepth.AssignY(width);};

	inline const Vector3f &GetPosition(void) const{return _position;};
	inline void SetPosition(const Vector3f &position){_position=position;};

	inline void SetTextureEnabledStatus(bool status){_textureEnabled=status;};
	inline bool GetTextureEnabledStatus() const{return _textureEnabled;};

	inline virtual GLuint GetTextureID(void) const{return _textureID;}; // for binding textures
	inline virtual void SetTextureID(GLuint textureID){_textureID=textureID;};
private:
	Vector3f _heightWidthDepth, _position;
	bool _textureEnabled;
	GLuint _textureID;
	Color _color;
};
