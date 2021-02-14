#pragma once
#include <string>
#include "Disc.h"

using namespace std;

class Player
{
public:
	Player();
	~Player(void);

	void SetUpDiscs();
	void SetPlayer(const int &player, const string &name);
	void DrawDiscs(Texture texture[3]) const;
	void PrintScore();
	void UpdateScore(const int &score);
	void IncreaseForce();
	void DecreaseForce();
	void renderBitmapString(float x, float y, void *font,const char *string) const;
	void ChangeCurrentDisc();
	void MoveDiscToThrowingLine(const int &whichDisc);
	void FireDisc(const int &whichDisc);
	void UpdateDisc(const int &whichDisc, const float &dt, const double &angle, const double &surfaceFriction,
		const double &sideFriction);
	void SetVelocityVector(const int &whichDisc, const Vector3d &vector);
	void SetCollisionNormal(const int &whichDisc, const Vector3d &vector);
	void SetDiscFiredStatus(const int &whichDisc, const bool &status);
	void SetScore(const int &score);
	void SetCurrentDisc (const int &disc);
	void Reset();
	void MoveDiscLeft(const int &whichDisc);
	void MoveDiscRight(const int &whichDisc);
	void SetMovedToStartStatus(const int &whichDisc, const bool &input);

	Vector3d GetDiscPosition(const int &whichDisc) const;
	Vector3d GetVelocityVector(const int &whichDisc) const;
	Vector3d GetCollisionNormal(const int &whichDisc) const;

	int GetDiscRadius(const int &whichDisc) const;
	int GetCurrentDisc() const;
	int GetForce() const;
	int GetScore() const;

	double GetDiscMass(const int &whichDisc) const;
	double GetDiscYVelocity(const int &whichDisc) const ;

	bool GetDiscFiredStatus(const int &whichDisc) const;
	bool GetMovedToStartStatus(const int &whichDisc) const;

private:
	int _score;
	int _player; // 1 for player 1, 2 for player 2, for position/colouring the discs
	int _throwingPower;
	int _minForce;
	int _maxForce;
	int _currentDisc; // 6 discs, first disc is at 0
	string _name;
	Disc disc[6];
};
