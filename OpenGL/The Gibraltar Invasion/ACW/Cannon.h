#pragma once

class Cannon
{
public:
	Cannon(void);
	~Cannon(void);

	void Draw(void) const;
	void SetPos(const float &x, const float &y);
	void SetDimensions(const float &width, const float &height);
	void SetColour(const float &red, const float &green, const float &blue);
	void SetAngleRadians(const float &rad);
	void SetAngleDegrees(const float &deg);
	void IncreaseAngleRadians(void);
	void DecreaseAngleRadians(void);
	void IncreaseForce(const float &force);
	void DecreaseForce(const float &force);

	float GetXPos(void) const;
	float GetYPos(void) const;
	float GetWidth(void) const;
	float GetHeight(void) const;
	float GetAngle(void) const;
	float GetAngleRadians(void) const;
	int GetForce(void) const;
	const float* GetColour(void) const;

private:
	float _xPos, _yPos, _width, _height, _angle;
	int _force;
	float _colour[3];
};
