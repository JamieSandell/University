#pragma once

class Ship
{
public:
	Ship(void);
	virtual ~Ship(void); // So they get cleaned up properly when out of scope

	virtual void Draw(void) const;
	void SetPos(const float &x, const float &y);
	void SetDimensions(const float &width, const float &height);
	void SetColour(const float &red, const float &green, const float &blue);
	void Update(const float &dt, const int &leftX, const int &rightX);
	void SetVelocity(const float &xVelocity, const float &yVelocity);
	void SinkShip(const float &dt);
	void SetAlive(const bool &status);
	void SetSinking(const bool &status);

	bool GetAliveStatus(void) const;
	bool GetSinkingStatus(void) const;

	float GetXPos(void) const;
	float GetYPos(void) const;
	float GetWidth(void) const;
	float GetHeight(void) const;
	void GetVelocity(float &xVelocity, float &yVelocity) const;
	const float* GetColour(void) const;

private:
	float _xPos, _yPos, _width, _height;
	float _colour[3];
	float _xVelocity, _yVelocity;
	int _direction;
	bool _shipIsSinking, _shipIsAlive;
};
