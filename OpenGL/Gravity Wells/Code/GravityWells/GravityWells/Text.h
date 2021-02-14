#pragma once
#include <string>
#include <vector>
#include "Color.h"

class Text
{
public:
	Text(void);
	~Text(void);

	inline const std::string& GetFormat(void)const{return _format;};
	inline const std::vector<float>& GetPosition(void)const{return _xy;};//return x, and y, in that order
	inline const std::string& GetText(void)const{return _text;};
	inline const Color& GetColor(void)const{return _color;};
	inline const float* GetColorFloatArray(void)const{return _color.rgba();};
	inline float GetX(void)const{return _xy[0];};
	inline float GetY(void)const{return _xy[1];};
	inline void SetColor(float r, float g, float b, float a){_color.Assign(r,g,b,a);};
	inline void SetColor(std::vector<float>& floatVec4){_color.Assign(floatVec4[0],floatVec4[1],
		floatVec4[2],floatVec4[3]);};
	inline void SetFormat(const std::string &format){_format=format;};//See stdio printf
	inline void SetPosition(float x, float y){_xy[0]=x;_xy[1]=y;};
	inline void SetPosition(std::vector<float> &xy){_xy=xy;};// set the position of xy, in that order
	inline void SetText(const std::string &text){_text=text;};

private:
	std::vector<float> _xy;
	std::string _text;
	std::string _format;
	Color _color;
};
