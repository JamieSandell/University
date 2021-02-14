#include "Player.h"

Player::Player()
{
	_score = 0;
	_throwingPower = 10;
	_maxForce = 80;
	_minForce = 10;
}

Player::~Player(void)
{
}

void Player::SetUpDiscs()
{
	if (_player == 1) // Set up player 1's discs
	{
		double colour[3] = {1,0,0};
		int position1[3] = {50, 20, 0};
		int position2[3] = {100, 20, 0};
		int position3[3] = {150, 20, 0};
		int position4[3] = {200, 20, 0};
		int position5[3] = {250, 20, 0};
		int position6[3] = {300, 20, 0};


		disc[0].SetPosition(position1);
		disc[0].SetColour(colour);
		disc[1].SetPosition(position2);
		disc[1].SetColour(colour);
		disc[2].SetPosition(position3);
		disc[2].SetColour(colour);
		disc[3].SetPosition(position4);
		disc[3].SetColour(colour);
		disc[4].SetPosition(position5);
		disc[4].SetColour(colour);
		disc[5].SetPosition(position6);
		disc[5].SetColour(colour);

	}
	else // Setup player 2's discs
	{
		double colour[3] = {0,0,1};
		int position1[3] = {1150, 20, 0}; // 1150
		int position2[3] = {1100, 20, 0};
		int position3[3] = {1050, 20, 0};
		int position4[3] = {1000, 20, 0};
		int position5[3] = {950, 20, 0};
		int position6[3] = {900, 20, 0};


		disc[0].SetPosition(position1);
		disc[0].SetColour(colour);
		disc[1].SetPosition(position2);
		disc[1].SetColour(colour);
		disc[2].SetPosition(position3);
		disc[2].SetColour(colour);
		disc[3].SetPosition(position4);
		disc[3].SetColour(colour);
		disc[4].SetPosition(position5);
		disc[4].SetColour(colour);
		disc[5].SetPosition(position6);
		disc[5].SetColour(colour);
	}
}

void Player::SetPlayer(const int &player, const string &name)
{
	_player = player;
	_name = name;
}

void Player::DrawDiscs(Texture texture[3]) const
{
	for (int i = 0; i < 6; i++)
	{
		disc[i].DrawDisc(texture);
	}
}
void Player::PrintScore()
{
	char playerString[500];
	if (_player == 1)
	{
		glColor3d(1,0,0);
		sprintf_s(playerString, "Player: %i Score: %i Throwing Power: %i",
			_player, _score, _throwingPower);
		renderBitmapString(0,1500, GLUT_BITMAP_HELVETICA_12, playerString);
	}
	else
	{
		_player = 2;
		glColor3d(0,0,1);
		sprintf_s(playerString, "Player: %i Score: %i Throwing Power: %i",
			_player, _score, _throwingPower);
		renderBitmapString(0,1400, GLUT_BITMAP_HELVETICA_12, playerString);
	}
}
void Player::UpdateScore(const int &score)
{
	_score += score;
}

void Player::IncreaseForce()
{
	_throwingPower += 10;
	if (_throwingPower > _maxForce)
	{
		_throwingPower = _maxForce;
	}
}
void Player::DecreaseForce()
{
	_throwingPower -= 10;
	if (_throwingPower < _minForce)
	{
		_throwingPower = _minForce;
	}
}
void Player::renderBitmapString(float x, float y, void *font,const char *string) const
{

	const char *c = string;
	glRasterPos2f(x, y);
	for (; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}  /* end renderBitmapString() */

Vector3d Player::GetDiscPosition(const int &whichDisc) const
{
	return disc[whichDisc].GetDiscPosition();
}

// Get the disc's radius
int Player::GetDiscRadius(const int &whichDisc) const
{
	return disc[whichDisc].GetRadius();
}
// Get the current disc
int Player::GetCurrentDisc() const
{
	return _currentDisc;
}

// Change the current disc
void Player::ChangeCurrentDisc()
{
	_currentDisc++;
}

// Move the disc to the throwing line
void Player::MoveDiscToThrowingLine(const int &whichDisc)
{
	disc[whichDisc].MoveDisc(600, 140);
}

// Get the discs fired status
bool Player::GetDiscFiredStatus(const int &whichDisc) const
{
	return disc[whichDisc].GetFiredStatus();
}
// Get the force
int Player::GetForce() const
{
	return _throwingPower;
}
// Fire the disc
void Player::FireDisc(const int &whichDisc)
{
	disc[whichDisc].FireDisc();
}
// Update the disc
void Player::UpdateDisc(const int &whichDisc, const float &dt, const double &angle, const double &surfaceFriction,
						const double &sideFriction)
{
	disc[whichDisc].Update(dt, angle, _throwingPower, surfaceFriction, sideFriction);
}
// Get the velocity vector
Vector3d Player::GetVelocityVector(const int &whichDisc) const
{
	return disc[whichDisc].GetVelocityVector();
}
// Set the velocity vector
void Player::SetVelocityVector(const int &whichDisc, const Vector3d &vector)
{
	disc[whichDisc].SetVelocityVector(vector);
}
// Get the collision normal
Vector3d Player::GetCollisionNormal(const int &whichDisc) const
{
	return disc[whichDisc].GetCollisionNormal();
}
// Set the collision normal
void Player::SetCollisionNormal(const int &whichDisc, const Vector3d &vector)
{
	disc[whichDisc].SetCollisionNormal(vector);
}
// Get the mass of the disc
double Player::GetDiscMass(const int &whichDisc) const
{
	return disc[whichDisc].GetMass();
}
// Set the fired status of the disc
void Player::SetDiscFiredStatus(const int &whichDisc, const bool &status)
{
	disc[whichDisc].SetFiredStatus(status);
}
// Get the disc's Y velocity
double Player::GetDiscYVelocity(const int &whichDisc) const
{
	return disc[whichDisc].GetYVelocity();
}
// Get the player's current score
int Player::GetScore() const
{
	return _score;
}
// Set the player's current score
void Player::SetScore(const int &score)
{
	_score = score;
}
// Set the player's current disc
void Player::SetCurrentDisc(const int &disc)
{
	_currentDisc = disc;
}
// Reset all the player's discs etc
void Player::Reset()
{
	_score = 0;
	_throwingPower = 10;
	SetUpDiscs();
	_currentDisc = 0;
	_maxForce = 100;
	_minForce = 10;
	for (int i = 0; i < 6; i++)
	{
		disc[0].SetFiredStatus(false);
	}
	
}
// Move the current disc left
void Player::MoveDiscLeft(const int &whichDisc)
{
	disc[whichDisc].MoveDiscLeft();
}
// Move the current disc right
void Player::MoveDiscRight(const int &whichDisc)
{
	disc[whichDisc].MoveDiscRight();
}
// Get the current disc's moved to start status, if true it can move left and right
bool Player::GetMovedToStartStatus(const int &whichDisc) const
{
	return disc[whichDisc].GetMovedToStartStatus();
}
// Set the current disc's moved to start status
void Player::SetMovedToStartStatus(const int &whichDisc, const bool &input)
{
	disc[whichDisc].SetMovedToStartStatus(input);
}