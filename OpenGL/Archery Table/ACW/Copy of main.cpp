/*
 *		This Code Was Created By Jeff Molofee 2000
 *		A HUGE Thanks To Fredric Echols For Cleaning Up
 *		And Optimizing The Base Code, Making It More Flexible!
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit My Site At nehe.gamedev.net
 *		Conversion to Visual Studio.NET done by Grant James(ZEUS)
 *		Modified for Win32 Console Project by Darren McKie
 */
#pragma once
#include <iostream>
#include <windows.h>		// Header File For Windows
#include <stdio.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glut.h>		// Header File For The Glaux Library
#include "Table.h"
#include "Disc.h"
#include "Player.h"
#include "Camera.h"
#include "Collision.h"
#include "Timer.h"
#include "Texture.h" // For loading textures, taken from nehe's example
#include "glext.h" // for opengl versions greater than 1.1 - i.e. spotlight lighting (on textures)

bool LoadTGA(Texture *, char *);

Texture texture[2];

HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

// Classes
Table myTable;
Player player[2];
Camera myCamera;
Collision myCollision;
Timer myTimer;

// Logistics
// Player
int activePlayer = 0; // 0 for player1, 1 for player2
int currentDisc;
// Camera
vector <Vector3d*> currentCamera;
vector <double> rotation;
// Discs
int discCounter = 0; // Used for checking all discs have stopped moving
// Obstructions
bool obstructionsEnabled = true; // Use 'o' to toggle obstructions on/off
vector<Disc> obstructions;
Disc obstruction1;
Disc obstruction2;
Disc obstruction3;
int obstructionRadius = 20;
double obstructionColour[3] = {1,1,1};
int obstruction1Position[3] = {600, 1200, 0};
int obstruction2Position[3] = {300, 1200, 0};
int obstruction3Position[3] = {900, 1200, 0};

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

// Taken from nehe
int LoadGLTextures()											// Load Bitmaps And Convert To Textures
{
	int Status=FALSE;											// Status Indicator

	// Load The Bitmap, Check For Errors.
	if (LoadTGA(&texture[0], "ball.tga") &&
		LoadTGA(&texture[1], "wood.tga"))
	{
		Status=TRUE;											// Set The Status To TRUE

		for (int loop=0; loop<2; loop++)						// Loop Through Both Textures
		{
			// Typical Texture Generation Using Data From The TGA ( CHANGE )
			glGenTextures(1, &texture[loop].texID);				// Create The Texture ( CHANGE )
			glBindTexture(GL_TEXTURE_2D, texture[loop].texID);
			//glTexImage2D(GL_TEXTURE_2D, 0, texture[loop].bpp / 8, texture[loop].width, texture[loop].height, 0, texture[loop].type, GL_UNSIGNED_BYTE, texture[loop].imageData);
			gluBuild2DMipmaps( GL_TEXTURE_2D, 3, texture[loop].width, texture[loop].height, texture[loop].type, GL_UNSIGNED_BYTE, texture[loop].imageData );
			//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );

			if (texture[loop].imageData)						// If Texture Image Exists ( CHANGE )
			{
				free(texture[loop].imageData);					// Free The Texture Image Memory ( CHANGE )
			}
		}
	}
	return Status;												// Return The Status
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,5000.0f);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	//gluLookAt(0,1275,4000, 0,1275,0, 0,1,0);
	currentCamera = myCamera.GetCurrentCamera();
	/*gluLookAt(currentCamera[0]->X(), currentCamera[0]->Y(), currentCamera[0]->Z(),
	currentCamera[1]->X(), currentCamera[1]->Y(), currentCamera[1]->Z(),
	currentCamera[2]->X(), currentCamera[2]->Y(), currentCamera[2]->Z());*/
	myCamera.ViewCamera(player[activePlayer].GetDiscPosition(currentDisc));
}

bool InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	if (!LoadGLTextures())										// Jump To Texture Loading Routine ( NEW )
	{
		return FALSE;											// If Texture Didn't Load Return FALSE
	}

	// Init obstructions
	obstruction1.SetColour(obstructionColour);
	obstruction1.SetDiscHeight(40);
	obstruction1.SetPosition(obstruction1Position);
	obstruction2.SetColour(obstructionColour);
	obstruction2.SetDiscHeight(40);
	obstruction2.SetPosition(obstruction2Position);
	obstruction3.SetColour(obstructionColour);
	obstruction3.SetDiscHeight(40);
	obstruction3.SetPosition(obstruction3Position);
	obstructions.push_back(obstruction1);
	obstructions.push_back(obstruction2);
	obstructions.push_back(obstruction3);
	// Init obstructions
	// Init players
	player[0].SetPlayer(1, "Player 1");
	player[1].SetPlayer(2, "Player 2");
	player[0].SetUpDiscs();
	player[1].SetUpDiscs();
	// Init players
	// Init Camera
	currentCamera = myCamera.GetCurrentCamera();
	// Init Camera

	// Texture code
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// Draw specular highlights on top of textures
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR );
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	return true;										// Initialization Went OK
}

GLvoid ChangeActivePlayer(GLvoid)
{
	if (activePlayer == 0)
	{
		activePlayer = 1; // Player 2;
	}
	else
	{
		activePlayer = 0; // Player 1
	}
}

GLvoid DrawObstructions(GLvoid)
{
	obstruction1.DrawDisc(texture);
	obstruction2.DrawDisc(texture);
	obstruction3.DrawDisc(texture);
}

GLvoid UpdateGLScene(GLvoid) // Update code
{

	/// Algorithm:
	/// See who the current player is
	/// Get the current disc
	/// If the current disc is 6 (disc 7), then that player is gameover
	/// If gameover show the scores and winner for a 4 seconds and then restart the game
	/// Display a countdown timer for this
	/// move disc to the firing position
	/// show the firing line
	/// firing line length = player's firing force
	/// when the disc is fired change it's velocity
	/// update all disc's positions based on their velocity
	/// check for collisions
	/// once all the discs have stopped moving check to see if the disc is on a target
	///		and update the currentPlayer's score accordingly
	/// once all discs have stopped moving and the current disc has been fired  change the player's current
	///		disc
	/// then change the current player

	// Timer code
	float dt = myTimer.Tick();
	// Timer code

	// Camera code
	currentCamera = myCamera.GetCurrentCamera();
	// Camera code

	currentDisc = player[activePlayer].GetCurrentDisc();
	// Is that player gameover?
	if (currentDisc == 6)
	{
		// change the currently active player
		ChangeActivePlayer();
		// Is that player gameover? If so reset everything
		if (currentDisc == 6) // Are both players gameover?
		{
			while(true);
			// TODO: - Reset code
		}
	}
	// Move disc to the firing position if it hasn't been fired
	if (!player[activePlayer].GetDiscFiredStatus(currentDisc)) // Not been fired
	{
		player[activePlayer].MoveDiscToThrowingLine(currentDisc);
	}
	else // Has been fired so change the current disc
	{
		for (int i = 0; i < 2; i++) // Cycle the players
		{
			for (int j = 0; j < 6; j++) // Cycle and update the player's discs
			{
				player[i].UpdateDisc(j, dt, myTable.GetThrowingAngle(),
					myTable.GetSurfaceFriction(), myTable.GetSideFriction());
				if (player[i].GetDiscYVelocity(j) == 0) // stopped moving
				{
					discCounter++;
				}
			}
		}
		// Have all the discs stopped moving?
		if (discCounter==12) // Yes they have stopped moving
		{
			//reset the counter
			discCounter = 0;
			// Change the active player
			ChangeActivePlayer();
			if (activePlayer == 0)// back to player1 so change the current disc to the next one
			{
				// Increase the players' current disc
				player[0].SetCurrentDisc(player[0].GetCurrentDisc()+1);
				player[1].SetCurrentDisc(player[1].GetCurrentDisc()+1);
			}
			// reset the score
			player[0].SetScore(0);
			player[1].SetScore(0);
			// check for scoring
			for (int i = 0; i < 2; i++) // Cycle through the players
			{
				for (int j = 0; j < 6; j++) // Cycle the discs
				{
					int result = myCollision.SphereTargetCollision(player[i].GetDiscPosition(j), 
						myTable.GetTargetsCentres(), 20, myTable.GetTargetRadii());
					switch (result)
					{
					case 0: // innermost target
						player[i].SetScore(player[i].GetScore()+100);
						break;
					case 1: // inner target
						player[i].SetScore(player[i].GetScore()+200);
						break;
					case 2: // outermost target
						player[i].SetScore(player[i].GetScore()+500);
						break;
					default:
						break;
					}
				}
			}
		}
		else // Some discs are still moving
		{
			discCounter = 0; // reset the disc moving counter else it can go passed 12
		}
	}
	
	// Collision detection code
	for (int i = 0; i < 2; i++) // Go through each player
	{
		for (int j = 0; j < 6; j++) // Go through each player's disc
		{
			Vector3d normHit;
			if (myCollision.SpherePlaneCollision(player[i].GetDiscPosition(j), player[i].GetDiscRadius(j), 
				myTable.GetSides(), myTable.GetSidesNorm(), j, normHit))
			{
				if (normHit.Y() == 1)
				{
					// 0,1,0 = top, 1,0,0 = left/right, 0,1,0 = bottom
					Vector3d vectorOriginal = player[i].GetVelocityVector(j);
					// VR = VI - 2(VI.N)N
					// VR = VI - (1+e)(VI.N)N - Elasticity taken into account
					Vector3d vectorNew;
					double dotProduct = vectorOriginal.dotProduct(normHit); // (VI.N)
					Vector3d vectorTemp = normHit * vectorOriginal; // (VI.N)N
					vectorTemp = vectorTemp * (1+myTable.GetDiscToSideElasticity()); // 1+e(VI.N)N
					vectorTemp.SetVector(vectorOriginal.X() - vectorTemp.X(),
						vectorOriginal.Y() - vectorTemp.Y(), vectorOriginal.Z() - vectorTemp.Z());

					player[i].SetVelocityVector(j, vectorTemp);

				}
				if (normHit.X() == 1)
				{
					Vector3d vectorOriginal = player[i].GetVelocityVector(j);
					//VR = VI - (1+e)(VI.N)N
					Vector3d vectorNew;
					double dotProduct = vectorOriginal.dotProduct(normHit); // (VI.N)
					Vector3d vectorTemp = normHit * vectorOriginal; // (VI.N)N
					vectorTemp = vectorTemp * (1+myTable.GetDiscToSideElasticity()); // 1+e(VI.N)N
					vectorTemp.SetVector(vectorOriginal.X() - vectorTemp.X(),
						vectorOriginal.Y() - vectorTemp.Y(), vectorOriginal.Z() - vectorTemp.Z());

					player[i].SetVelocityVector(j, vectorTemp);
				}
			}
		}
	}

	for (int i = 0; i < 6; i++) // Check collision of player1's discs against player2's discs
	{
		for (int j = 0; j < 6; j++)
		{
			if (myCollision.SphereSphereCollision(player[0].GetDiscPosition(i),
				player[1].GetDiscPosition(j), 20, 20))
			{
				// TODO::
				// Put this into a method
				/////////// Algorithm taken from the nehe website.
				Vector3d pb1,pb2,xaxis,U1x,U1y,U2x,U2y,V1x,V1y,V2x,V2y;
				double a,b;
				pb1=player[0].GetDiscPosition(i);			// Find Position Of Ball1
				pb2=player[1].GetDiscPosition(j);			// Find Position Of Ball2
				xaxis=(pb2-pb1).Normalise();							// Find X-Axis
				a=xaxis.dotProduct(player[0].GetVelocityVector(i));					// Find Projection
				U1x=xaxis*a;								// Find Projected Vectors
				U1y=player[0].GetVelocityVector(i)-U1x;
				xaxis=(pb1-pb2).Normalise();							// Do The Same As Above
				b=xaxis.dotProduct(player[1].GetVelocityVector(j));					// To Find Projection
				U2x=xaxis*b;								// Vectors For The Other Ball
				U2y=player[1].GetVelocityVector(j)-U2x;
				V1x=(U1x+U2x-(U1x-U2x))*0.5;						// Now Find New Velocities
				V2x=(U1x+U2x-(U2x-U1x))*0.5;
				V1y=U1y;
				V2y=U2y;

				player[0].SetDiscFiredStatus(i, true);
				player[1].SetDiscFiredStatus(j, true);
				player[0].SetVelocityVector(i, V1x+V1y);
				player[1].SetVelocityVector(j, V2y+V2x);
				/////////// Algorithm taken from the nehe website.
			}
		}
	}

	for (int p = 0; p < 2; p++) // Cycle through the players
	{
		for (int i = 0; i < 6; i++) // Check collision of player[p]'s discs against player[p]'s discs
		{
			for (int j = 0; j < 6; j++)
			{
				if (j != i) // Don't check the disc against itself
				{
					if (myCollision.SphereSphereCollision(player[p].GetDiscPosition(i),
						player[p].GetDiscPosition(j), 20, 20))
					{
						// TODO::
						// Put this into a method
						/////////// Algorithm taken from the nehe website.
						Vector3d pb1,pb2,xaxis,U1x,U1y,U2x,U2y,V1x,V1y,V2x,V2y;
						double a,b;
						pb1=player[p].GetDiscPosition(i);			// Find Position Of Ball1
						pb2=player[p].GetDiscPosition(j);			// Find Position Of Ball2
						xaxis=(pb2-pb1).Normalise();							// Find X-Axis
						a=xaxis.dotProduct(player[p].GetVelocityVector(i));					// Find Projection
						U1x=xaxis*a;								// Find Projected Vectors
						U1y=player[p].GetVelocityVector(i)-U1x;
						xaxis=(pb1-pb2).Normalise();							// Do The Same As Above
						b=xaxis.dotProduct(player[p].GetVelocityVector(j));					// To Find Projection
						U2x=xaxis*b;								// Vectors For The Other Ball
						U2y=player[p].GetVelocityVector(j)-U2x;
						V1x=(U1x+U2x-(U1x-U2x))*0.5;						// Now Find New Velocities
						V2x=(U1x+U2x-(U2x-U1x))*0.5;
						V1y=U1y;
						V2y=U2y;

						player[p].SetDiscFiredStatus(i, true);
						player[p].SetDiscFiredStatus(j, true);
						player[p].SetVelocityVector(i, V1x+V1y);
						player[p].SetVelocityVector(j, V2y+V2x);
						player[p].UpdateDisc(i, dt, myTable.GetThrowingAngle(),
							myTable.GetSurfaceFriction(), myTable.GetSideFriction());
						player[p].UpdateDisc(j, dt, myTable.GetThrowingAngle(),
							myTable.GetSurfaceFriction(), myTable.GetSideFriction());
						// Update their positions now else the loop will count another hit on the same
						// two discs
	
						/////////// Algorithm taken from the nehe website.
					}
				}
			}
		}
	}

	if (obstructionsEnabled)
	{
		for (int p = 0; p < 2; p++) // Cycle through the players
		{
			for (int i = 0; i < 6; i++) // Check collision of player[p]'s discs against player[p]'s discs
			{
				for (int j = 0; j < 3; j++)
				{
					//if (j != i) // Don't check the disc against itself
					//{
						if (myCollision.SphereSphereCollision(player[p].GetDiscPosition(i),
							obstructions[j].GetDiscPosition(), 20, 20))
						{
							// TODO::
							// Put this into a method
							/////////// Algorithm taken from the nehe website.
							Vector3d pb1,pb2,xaxis,U1x,U1y,U2x,U2y,V1x,V1y,V2x,V2y;
							double a,b;
							pb1=player[p].GetDiscPosition(i);			// Find Position Of Ball1
							pb2=obstructions[j].GetDiscPosition();			// Find Position Of Ball2
							xaxis=(pb2-pb1).Normalise();							// Find X-Axis
							a=xaxis.dotProduct(player[p].GetVelocityVector(i));					// Find Projection
							U1x=xaxis*a;								// Find Projected Vectors
							U1y=player[p].GetVelocityVector(i)-U1x;
							xaxis=(pb1-pb2).Normalise();							// Do The Same As Above
							b=xaxis.dotProduct(obstructions[j].GetVelocityVector());					// To Find Projection
							U2x=xaxis*b;								// Vectors For The Other Ball
							U2y=obstructions[j].GetVelocityVector()-U2x;
							V1x=(U1x+U2x-(U1x-U2x))*0.5;						// Now Find New Velocities
							V2x=(U1x+U2x-(U2x-U1x))*0.5;
							V1y=U1y;
							V2y=U2y;

							player[p].SetDiscFiredStatus(i, true);
							//player[p].SetDiscFiredStatus(j, true);
							player[p].SetVelocityVector(i, V1x+V1y);
							//player[p].SetVelocityVector(j, V2y+V2x);
							player[p].UpdateDisc(i, dt, myTable.GetThrowingAngle(),
								myTable.GetSurfaceFriction(), myTable.GetSideFriction());
							//player[p].UpdateDisc(j, dt, myTable.GetThrowingAngle(),
								//myTable.GetSurfaceFriction(), myTable.GetSideFriction());
							// Update their positions now else the loop will count another hit on the same
							// two discs

							/////////// Algorithm taken from the nehe website.
						}
					//}
				}
			}
		}
	}
	// Collision detection code

}

GLvoid DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	static double angle = 0;

 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
	glLoadIdentity(); // Reset The Current Modelview Matrix
	gluLookAt(0, 0,4000, 0, 0, 0, 0, 1, 0);
	player[0].PrintScore(); // Needs fixing so that it is visible
	player[1].PrintScore();
	myTable.PrintFrictionInfo();
	glLoadIdentity();
	glPushMatrix();
	currentCamera = myCamera.GetCurrentCamera();
	if (myCamera.GetRotationStatus())
	{
		rotation = myCamera.GetRotationNumbers();
		glRotated(rotation[0], rotation[1], rotation[2], rotation[3]);
	}
		myCamera.ViewCamera(player[activePlayer].GetDiscPosition(currentDisc));
		myTable.DrawTable(texture);
		if (!player[activePlayer].GetDiscFiredStatus(currentDisc)) // Not been fired so draw the throwing 
			// line
		{
			myTable.DrawThrowingLine(player[activePlayer].GetForce());
		}
		player[0].DrawDiscs(texture);
		player[1].DrawDiscs(texture);
		// If obstructions are turned on draw them
		if (obstructionsEnabled)
		{
			DrawObstructions();
		}
	glPopMatrix();

}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
bool CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;											// Return FALSE
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return false;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	return true;									// Success
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int main (int argc, char **argv)
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("08214 - ACW",640,480,16,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (!active || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
			{
				done=TRUE;							// ESC or DrawGLScene Signalled A Quit
			}
			else									// Not Time To Quit, Update Screen
			{
				UpdateGLScene();
				DrawGLScene();
				SwapBuffers(hDC);					// Swap Buffers (Double Buffering)
			}

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1]=FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("08214 - ACW",640,480,16,fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
			if (keys[VK_UP])
			{
				player[activePlayer].IncreaseForce();
				keys[VK_UP]=FALSE;
			}
			if (keys[VK_DOWN])
			{
				player[activePlayer].DecreaseForce();
				keys[VK_DOWN]=FALSE;
			}
			if (keys[67]) // c
			{
				myCamera.ChangeCurrentCamera(player[activePlayer].GetDiscPosition(currentDisc));
				keys[67]=FALSE;
			}
			if (keys[81]) // q - Variable coefficient of friction between the table top surface and each
				//disk
			{
				myTable.IncreaseSurfaceFriction();
				keys[81]=FALSE;
			}
			if (keys[65]) // a - Variable coefficient of friction between the table top surface and each
				//disk
			{
				myTable.DecreaseSurfaceFriction();
				keys[65]=FALSE;
			}
			if (keys[87]) // w - Variable coefficient of friction between the table table sides and each
				// disk
			{
				myTable.IncreaseSideFriction();
				keys[87]=FALSE;
			}
			if (keys[83]) // w - Variable coefficient of friction between the table table sides and each
				// disk
			{
				myTable.DecreaseSideFriction();
				keys[83]=FALSE;
			}
			if (keys[69]) // e - Disk to sides of the table impact
			{
				myTable.IncreaseDiscToSideElasticity();
				keys[69]=FALSE;
			}
			if (keys[68]) // d - Disk to sides of the table impact
			{
				myTable.DecreaseDiscToSideElasticity();
				keys[68]=FALSE;
			}
			if (keys[VK_RIGHT])
			{
				myTable.IncreaseAngle();
				keys[VK_RIGHT]=FALSE;
			}
			if (keys[VK_LEFT])
			{
				myTable.DecreaseAngle();
				keys[VK_LEFT]=FALSE;
			}
			if (keys[VK_SPACE])
			{
				player[activePlayer].FireDisc(currentDisc);
				keys[VK_SPACE] = FALSE;
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}
