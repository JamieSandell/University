#include <algorithm>
#include <cmath>
#include "Shape.h"

using std::vector;
using std::find;

Shape::Shape(void)
{
}

Shape::~Shape()
{
}

void Shape::CopyBaseMembers(const Shape &source){
	this->_heightWidthDepth = source._heightWidthDepth;
	this->_position = source._position;
	this->_textureEnabled = source._textureEnabled;
	this->_textureID = source._textureID;
	this->_color = source._color;
}