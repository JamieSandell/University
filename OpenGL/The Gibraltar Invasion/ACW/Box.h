#pragma once

class Box
{
public:
	Box(void);
	~Box(void);

	void Draw(void) const;
	void SetPos(const float &x, const float &y);
	void SetDimensions(const float &width, const float &height);
	void SetColour(const float &red, const float &green, const float &blue);

	float GetXPos(void) const;
	float GetYPos(void) const;
	float GetWidth(void) const;
	float GetHeight(void) const;
	const float* GetColour(void) const;

private:
	float _xPos, _yPos, _width, _height;
	float _colour[3];
};
