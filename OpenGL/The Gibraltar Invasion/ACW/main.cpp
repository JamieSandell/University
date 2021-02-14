/*Minimum Specification (45%)
6. If the cannonball hits the ship then the ship will sink. At which point another ship will sail into
	view from one of the sides of the screen.

Bonus Specification (25%):
3. Multiple boats based on a base Ship class containing virtual draw functions. For example two different
	ships.
4. Limit the drawing routines to a certain fps
6. Pass in by reference not value
7. Make use of const

Quality of Code (25%):
1. Design approach and class design (e.g. Object Orientated Design). Include a class diagram in the report
	(see below).

Short Report (5%):
1. Maximum of two sides of A4.
2. Summary of the main algorithms that you have used to tackle the ACW.
3. Include a list of all bonus and novel elements implemented.
4. Design approach and class design. Include a class diagram.
*/

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include <atlstr.h>
#include <iomanip>
#include <vector>
#include <iostream>
using namespace std;

#include "Box.h"
#include "Ship.h"
#include "Cannon.h"
#include "Ball.h"
#include "Timer.h"
#include "Collision.h"
#include "ShipModified.h"

void DrawScene(void);
void renderBitmapString(float x, float y, void *font,const char *string);


// Set the size of the OpenGL Window
double winL = 0;
double winR = 400;
double winB = 0;
double winT = 400;

// Your class objects here
Box cliff;
Box sea;
Ship ship;
ShipModified shipModified;
Cannon cannon;
Ball cannonBall;
Timer myTimer;
Collision myCollision;

// Logistics
// FPS variables
float duration = 0;
float frames = 0;
float FPS = 0;
clock_t fpsStart;
clock_t fpsFinish;
// Ship variables
vector <Ship*> vectorShips;
int currentShip = 0; // 0 for ship, 1 for shipModified


float CalculateFPS()
{
	fpsFinish = clock() ;
	duration += (double)(fpsFinish - fpsStart) / CLOCKS_PER_SEC ;
	frames ++ ;
	FPS = frames / duration ;
	fpsStart = clock() ;
	return FPS;
}

void Init(void)
{ 
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glOrtho(winL, winR, winB, winT,-1,1);
	glMatrixMode(GL_MODELVIEW);

	// Your initializations
	vectorShips.push_back(&ship);
	vectorShips.push_back(&shipModified);

	cliff.SetPos(0, 75);
	cliff.SetDimensions(60, 250);
	cliff.SetColour(0.0f, 0.5f, 0.0f);	// mid green

	sea.SetPos(0, 0);
	sea.SetDimensions(400, 75);
	sea.SetColour(0.0f, 0.0f, 0.85f);	// mid blue

	ship.SetPos(400, 75);
	ship.SetDimensions(50, 50);
	ship.SetColour(0.0f, 0.0f, 0.0f);	// black

	shipModified.SetPos(400, 75);
	shipModified.SetDimensions(50, 50);
	shipModified.SetColour(0.0f, 0.0f, 0.0f);	// black

	cannon.SetPos(50, 325);
	cannon.SetDimensions(15, 50);
	cannon.SetColour(0.0f, 0.0f, 0.0f);	// black
	cannon.SetAngleDegrees(45);

	cannonBall.SetPos(100, 300);
	cannonBall.SetRadius(5);
	cannonBall.SetColour(0.0f, 0.0f, 0.0f);	// black

	// Init FPS timer
	fpsStart = clock();
}

void UpdateScene(void)
{
	float deltaTime = myTimer.Tick();

	// Ship code
	int cliffRightEdgeX = cliff.GetXPos(); // got the x pos so add it to the width
	cliffRightEdgeX += cliff.GetWidth();

	for (int i = 0; i < vectorShips.size(); i++)
	{
		if (vectorShips[i]->GetAliveStatus()) // If the ship is alive
		{
			vectorShips[i]->Update(deltaTime, cliffRightEdgeX, winR);
		}
	}

	// Cannonball code
	int cannonWidth = cannon.GetWidth();
	int cannonX = cannon.GetXPos();
	int cannonHeight = cannon.GetHeight();
	int cannonY = cannon.GetYPos();

	cannonBall.UpdatePos(deltaTime, cannon, winR, winB);

	// Collision code
	for (int i = 0; i < vectorShips.size(); i++)
	{
		if (vectorShips[i]->GetAliveStatus())
		{
			bool collision = myCollision.WasThereACollision(cannonBall, *vectorShips[i]);

			if (collision)
			{
				vectorShips[currentShip]->SetSinking(true);
				if (currentShip==1)
				{
					currentShip = 0;
				}
				else
				{
					currentShip = 1;
				}
				vectorShips[currentShip]->SetAlive(true);
				cannonBall.SetAliveStatus(false);
			}
		}

	}

	// FPS code
	CalculateFPS();
}

void DrawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Your drawing code here
	cliff.Draw();
	sea.Draw();
	vectorShips[0]->Draw();
	vectorShips[1]->Draw();
	cannon.Draw();
	cannonBall.Draw(cannon.GetAngle(), cannon.GetHeight(), cannon.GetWidth());

	// FPS
	char fpsString[30];

	sprintf_s(fpsString, "FPS: %.2f", FPS); // Print the fps
	renderBitmapString(320,380, GLUT_BITMAP_HELVETICA_18, fpsString);

	// Timer
	char timeString[10];
	int time = myTimer.GetRunTime();

	sprintf_s(timeString, "Time: %is", time); // Print the time passed since the start of the game
	renderBitmapString(320,365, GLUT_BITMAP_HELVETICA_18, timeString);

	// Force
	char forceString[30];
	int force = cannon.GetForce();

	sprintf_s(forceString, "Force: %i", force); // Print the force of the cannon
	renderBitmapString(320,350, GLUT_BITMAP_HELVETICA_18, forceString);

	// End drawing code

	glutSwapBuffers();
}



// This function is continuously called.
void Idle(void)
{

	UpdateScene();
	DrawScene();
}


void renderBitmapString(float x, float y, void *font,const char *string)
{
  
  const char *c = string;
  glRasterPos2f(x, y);
  for (; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}  /* end renderBitmapString() */


void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}

/* ARGSUSED1 */
void Key(unsigned char key, int x, int y)
{
	switch (key) {
  case 27:
	  exit(0);
	  break;
  case 32: // spacebar
	  cannonBall.ChangeFirstCreationFlag();
	  break;
  //case ' ':
	 // glutIdleFunc(Idle);
	 // break;
	default:
		break;
		
	}
}

void ArrowKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		if (!(cannonBall.GetAliveStatus())) // If the ball is still alive don't allow the cannon to move
		{
			cannon.IncreaseAngleRadians();
			break;
		}
		break;
	case GLUT_KEY_DOWN:
		if (!(cannonBall.GetAliveStatus())) // If the ball is still alive don't allow the cannon to move
		{
			cannon.DecreaseAngleRadians();
			break;
		}
		break;
	case GLUT_KEY_LEFT:
		cannon.DecreaseForce(10);
		break;
	case GLUT_KEY_RIGHT:
		cannon.IncreaseForce(10);
		break;
	default:
		break;
	}
}



int main(int argc, char **argv)
{
	glutInitWindowSize(600, 600);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutCreateWindow("Gibraltar");

	Init();

	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Key);
	glutSpecialFunc(ArrowKeys); // arrow key presses
	glutDisplayFunc(DrawScene);
	glutIdleFunc(Idle);

	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}

