//*************************************************************************
//
//  File Name	: GLUI Window Template
//  Author		: Ali BaderEddin
//  Created		: December 2003
//  Modified	: July 2007
//  
//  Description	: Openning an OpenGL GLUT window along with a GLUI window
//				  containing controls to manipulate objects in the OpenGL
//				  graphics context.
//  
//*************************************************************************

//  Include windows library in order to use the Sleep function
#include <windows.h>

//  For sqrt
#include <math.h>

//  Include GLUI, GLUT, OpenGL, and GLU libraries
#include <gl/glui.h>

// Others
#include <stdio.h>
#include <iostream>
#include "Vector3d.h"
#include "Particle.h"
#include "Timer.h"
#include "Texture.h" // For loading textures, taken from nehe's example
#include "glext.h" // for opengl versions greater than 1.1 - i.e. spotlight lighting (on textures)

// Link the lib files to the program. This is not necessary
// if you have added the lib names using Project/Settings/Link
#pragma comment (lib, "glui32.lib")
#pragma comment (lib, "glut32.lib")
#pragma comment (lib, "glu32.lib")
#pragma comment (lib, "opengl32.lib")

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // disable the console
// window

///////////PARTICLE
#define MAX_PARTICLES 1000 // Make this user definable

using namespace std;

bool LoadTGA(Texture *, char *);

Texture texture[2];

HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
bool firstRun = true;

// Classes
//Table myTable;
//Player player[2];
//Camera myCamera;
//Collision myCollision;
//Timer myTimer;
vector<Particle> particle(MAX_PARTICLES);

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

// Taken from nehe
int LoadGLTextures()											// Load Bitmaps And Convert To Textures
{
	int Status=FALSE;											// Status Indicator

	// Load The Bitmap, Check For Errors.
	if (LoadTGA(&texture[0], "particle.tga") &&
		LoadTGA(&texture[1], "particle.tga"))
	{
		Status=TRUE;											// Set The Status To TRUE

		for (int loop=0; loop<2; loop++)						// Loop Through Textures
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
/////////// PARTICLE

//*************************************************************************
//  GLUT Declarations
//*************************************************************************

//  Initialization
void init ();

//  Callback functions
void display (void);
void reshape (int w, int h);
void mouse (int button, int state, int x, int y);
void motion (int x, int y);
void pmotion (int x, int y);
void keyboard (unsigned char key, int x, int y);
void special (int key, int x, int y);
void entry (int state);

//  define the window position on screen
int window_x;
int window_y;

//  variables representing the window size
int window_width = 512;
int window_height = 512;

//  variable representing the window title
char *window_title = "GLUI Window Template";

//  The id of the main window
GLuint main_window;

//  Tells whether to display the window full screen or not
//  Press Alt + Esc to exit a full screen.
int full_screen = 0;

//*************************************************************************
//  GLUI Declarations
//*************************************************************************

//  pointer to the GLUI window
GLUI * glui_window;

//  Declare live variables (related to GLUI)
int wireframe = 1;			//  Related to Wireframe Check Box
int draw = 1;				//  Related to Draw Check Box
int emitterShapeListboxItemId = 1;	//  Id of the selected item in the list box
int radiogroup_item_id = 0; //  Id of the selcted radio button
float rotation_matrix[16]	//  Rotation Matrix Live Variable Array
							= { 1.0, 0.0, 0.0, 0.0, 
								0.0, 1.0, 0.0, 0.0,
								0.0, 0.0, 1.0, 0.0, 
								0.0, 0.0, 0.0, 1.0 };	
float translate_xy[2]		//  Translation XY Live Variable
							= {0, 0};			
float translate_z = 0;		//  Translation Z Live Variable
float scale = 0.0240318;			//  Spinner Scale Live Variable
int emitterHeight = 0;
int emitterWidth = 0;
int emitterDepth = 0;
int emitterPosition[] = {0.0, 0.0, 0.0}; // x,y,z
int emitterMaximumParticles = 1000;
int emitterDurationSeconds = 0;
int emitterRepeat = true;
int particleShapeListboxItemId = 1;
int particleHeight = 5;
int particleWidth = 5;
int particleDepth = 5;
int particleBlendingModeListboxItemId = 1;
int particleStartColour[] = {0.5, 0.5, 0.5};
int particleEndColour[] = {0.5, 0.5, 0.5};
int particleRandomColour = false;
int particleGravity[] = {0.0, -9.8, 0.0}; // x,y,z
int particleSpeed[] = {0.0, 100.0, 0.0}; // x,y,z
int particleMinimumFade = 0;
int particleMaximumFade = 99;

// an array of RGB components
float color[] = { 1.0, 1.0, 1.0 };

//  Set up the GLUI window and its components
void setupGLUI ();

//  Idle callack function
void idle ();

//  Declare callbacks related to GLUI
void glui_callback (int arg);

//  Declare the IDs of controls generating callbacks
enum
{
	EMITTER_SHAPE_LISTBOX = 0,
	OBJECTYPE_RADIOGROUP,
	TRANSLATION_XY,
	TRANSLATION_Z,
	ROTATION,
	SCALE_SPINNER,
	EMITTER_HEIGHT_SPINNER,
	EMITTER_WIDTH_SPINNER,
	EMITTER_DEPTH_SPINNER,
	EMITTER_POSITIONX_EDITABLETEXT,
	EMITTER_POSITIONY_EDITABLETEXT,
	EMITTER_POSITIONZ_EDITABLETEXT,
	EMITTER_MAXIMUMPARTICLES_EDITABLETEXT,
	EMITTER_DIRECTIONX_EDITABLETEXT,
	EMITTER_DIRECTIONY_EDITABLETEXT,
	EMITTER_DIRECTIONZ_EDITABLETEXT,
	EMITTER_ANGLEDEGREES_EDITABLETEXT,
	EMITTER_DURATIONSECONDS_SPINNER,
	EMITTER_REPEAT_CHECKBOX,
	PARTICLE_SHAPE_LISTBOX,
	PARTICLE_HEIGHT_SPINNER,
	PARTICLE_WIDTH_SPINNER,
	PARTICLE_DEPTH_SPINNER,
	PARTICLE_BLENDINGMODE_LISTBOX,
	PARTICLE_STARTCOLOURRED_SPINNER,
	PARTICLE_STARTCOLOURGREEN_SPINNER,
	PARTICLE_STARTCOLOURBLUE_SPINNER,
	PARTICLE_ENDCOLOURRED_SPINNER,
	PARTICLE_ENDCOLOURGREEN_SPINNER,
	PARTICLE_ENDCOLOURBLUE_SPINNER,
	PARTICLE_RANDOMCOLOUR_CHECKBOX,
	PARTICLE_GRAVITYX_SPINNER,
	PARTICLE_GRAVITYY_SPINNER,
	PARTICLE_GRAVITYZ_SPINNER,
	PARTICLE_SPEEDX_SPINNER,
	PARTICLE_SPEEDY_SPINNER,
	PARTICLE_SPEEDZ_SPINNER,
	PARTICLE_FADEMINIMUM_SPINNER,
	PARTICLE_FADEMAXIMUM_SPINNER,
	QUIT_BUTTON
};

//  Support Functions
void centerOnScreen ();
void drawObject ();
void printMatrixf (float *matrix);

//*************************************************************************
//  GLUT Functions.
//*************************************************************************

//-------------------------------------------------------------------------
//  Set OpenGL program initial state.
//-------------------------------------------------------------------------
void init ()
{	
	//  Set the frame buffer clear color to black. 
	glClearColor (0.0, 0.0, 0.0, 0.0);
	if (!LoadGLTextures())										// Jump To Texture Loading Routine ( NEW )
	{
		//return FALSE;											// If Texture Didn't Load Return FALSE
	}

	// Init obstructions
	//obstruction1.SetColour(obstructionColour);
	//obstruction1.SetDiscHeight(40);
	//obstruction1.SetPosition(obstruction1Position);
	//obstruction2.SetColour(obstructionColour);
	//obstruction2.SetDiscHeight(40);
	//obstruction2.SetPosition(obstruction2Position);
	//obstruction3.SetColour(obstructionColour);
	//obstruction3.SetDiscHeight(40);
	//obstruction3.SetPosition(obstruction3Position);
	//obstructions.push_back(obstruction1);
	//obstructions.push_back(obstruction2);
	//obstructions.push_back(obstruction3);
	// Init obstructions
	// Init players
	//player[0].SetPlayer(1, "Player 1");
	//player[1].SetPlayer(2, "Player 2");
	//player[0].SetUpDiscs();
	//player[1].SetUpDiscs();
	// Init players
	// Init Camera
	//currentCamera = myCamera.GetCurrentCamera();
	// Init Camera

	// Texture code
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glShadeModel(GL_SMOOTH);						// Enables Smooth Shading
	glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
	glClearDepth(1.0f);							// Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);						// Disables Depth Testing
	glEnable(GL_BLEND);							// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);			// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);					// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);						// Enable Texture Mapping


	// Init particles
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		int low = 100;
		int high = 200;
		particle[i].SetAliveStatus(true);
		particle[i].SetLife(1.0f);
		particle[i].SetColour(Vector3d(rand()/(float(RAND_MAX)+1), rand()/(float(RAND_MAX)+1), rand()/(float(RAND_MAX)+1)));
		particle[i].SetFade(float(rand()%100)/1000.0f+10.0f);
		particle[i].SetGravity(Vector3d(0.0f,0.8f,0.0f));
		particle[i].SetPosition(Vector3d(0,0,0));
		particle[i].SetSpeed(Vector3d((rand () % (high - low + 1) + low)*10,(rand () % (high - low + 1) + low)*10,(rand () % (high - low + 1) + low)*10));
	}
}

GLvoid UpdateGLScene(GLvoid) // Update code
{

	// Timer code
	//float dt = myTimer.Tick();
	// Timer code

	// Camera code
	//currentCamera = myCamera.GetCurrentCamera();
	// Camera code

	// If the particle is alive then update it
	for (int i = 0; i < MAX_PARTICLES; i++) // draw particles if they are alive
	{
		if (particle[i].GetLife()>0.0f)
		{
			particle[i].Update();
		}
	}



}

GLvoid DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
	//glLoadIdentity(); // Reset The Current Modelview Matrix
	//gluLookAt(0, 0,50, 0, 0, 0, 0, 1, 0);

	glBegin(GL_TRIANGLE_STRIP); // Add glTex later
	for (int i = 0; i < MAX_PARTICLES; i++) // draw particles if they are alive
	{
		if (particle[i].GetLife()>0.0f)
		{
			particle[i].Draw(texture);
			//particle[i].Draw();
		}
	}
	glEnd();


}

//-------------------------------------------------------------------------
//  This function sets the window x and y coordinates
//  such that the window becomes centered
//-------------------------------------------------------------------------
void centerOnScreen ()
{
	window_x = (glutGet (GLUT_SCREEN_WIDTH) - window_width)/2;
	window_y = (glutGet (GLUT_SCREEN_HEIGHT) - window_height)/2;
}

//-------------------------------------------------------------------------
//  Function to print matrix on command prompt.
//-------------------------------------------------------------------------
void printMatrixf (float *matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf ("%f%\t", matrix[i*4 + j]);
		}

		printf ("\n");
	}
}

//-------------------------------------------------------------------------
//  This function is passed to glutDisplayFunc in order to display 
//	OpenGL contents on the window.
//-------------------------------------------------------------------------
void display (void)
{
	//  Notify that this is a GLUT Callback
	//printf ("GLUT: ");

	//  Show when are displaying an object
	//printf ("Displaying object...\n");

	//  Clear the window 
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//(NEW) setup our buffers

	//  Set the color
	glColor3fv (color);
	
	//  Draw object
	drawObject ();

	//  Swap contents of backward and forward frame buffers
	glutSwapBuffers ();
}

//-------------------------------------------------------------------------
//  Draws our object.
//-------------------------------------------------------------------------
void drawObject ()
{
	//  Draw the object only if the Draw check box is selected
	if (draw)
	{
		//  Push the current matrix into the model view stack
		glPushMatrix ();

		//  Apply the translation
		glTranslatef (translate_xy[0], translate_xy[1], -translate_z);

		//  Apply the rotation matrix
		glMultMatrixf (rotation_matrix);

		//  Apply the scaling
		glScalef (scale, scale, scale);

		DrawGLScene();

		//  Pop our matrix from the model view stack after we finish drawing
		glPopMatrix ();
	}
}

//-------------------------------------------------------------------------
//  This function is passed to the glutReshapeFunc and is called 
//  whenever the window is resized.
//-------------------------------------------------------------------------
void reshape (int w, int h)
{
	//  Notify that this is a GLUT Callback
	printf ("GLUT: ");

	//  Stay updated with the window width and height
	window_width = w;
	window_height = h;

	//  Reset viewport
	glViewport(0, 0, window_width, window_height);

	//  Print current width and height on the screen
	printf ("Window Width: %d, Window Height: %d.\n", window_width, window_height);
}

//-------------------------------------------------------------------------
//  This function is passed to the glutMouseFunc and is called 
//  whenever the mouse is clicked.
//-------------------------------------------------------------------------
void mouse (int button, int state, int x, int y)
{
	//  Notify that this is a GLUT Callback
	printf ("GLUT: ");

	switch (button)
	{
		//  Left Button Clicked
		case GLUT_LEFT_BUTTON:

			switch (state)
			{
				//  Pressed 
				case GLUT_DOWN:
					printf ("Mouse Left Button Pressed (Down)...\n");
					break;
				//  Released
				case GLUT_UP:
					printf ("Mouse Left Button Released (Up)...\n");
					break;
			}

			break;

		//  Middle Button clicked
		case GLUT_MIDDLE_BUTTON:
			
			switch (state)
			{
				//  Pressed
				case GLUT_DOWN:
					printf ("Mouse Middle Button Pressed (Down)...\n");
					break;
				//  Released
				case GLUT_UP:
					printf ("Mouse Middle Button Released (Up)...\n");
					break;
			}

			break;

		//  Right Button Clicked
		case GLUT_RIGHT_BUTTON:
			
			switch (state)
			{
				//  Pressed
				case GLUT_DOWN:
					printf ("Mouse Right Button Pressed (Down)...\n");
					break;
				//  Released
				case GLUT_UP:
					printf ("Mouse Right Button Released (Up)...\n");
					break;
			}

			break;

	}
}

//-------------------------------------------------------------------------
//  This function is passed to the glutMotionFunc and is called 
//  whenever the mouse is dragged.
//-------------------------------------------------------------------------
void motion (int x, int y)
{
	//  Notify that this is a GLUT Callback
	printf ("GLUT: ");

	//  Print the mouse drag position
	printf ("Mouse Drag Position: %d, %d.\n", x, y);
}

//-------------------------------------------------------------------------
//  This function is passed to the glutPassiveMotionFunc and is called 
//  whenever the mouse is moved.
//-------------------------------------------------------------------------
void pmotion (int x, int y)
{
	//  Notify that this is a GLUT Callback
	//printf ("GLUT: ");

	//  Print mouse move positopn
	//printf ("Mouse Move Position: %d, %d.\n", x, y);
}

//-------------------------------------------------------------------------
//  This function is passed to the glutKeyboardFunc and is called 
//  whenever the user hits a key.
//-------------------------------------------------------------------------
void keyboard (unsigned char key, int x, int y)
{
	//  Notify that this is a GLUT Callback
	printf ("GLUT: ");

	//  Print what key the user is hitting
	printf ("User is hitting the '%c' key.\n", key);
	printf ("ASCII code is %d.\n", key);
	
	switch (key)
	{
		//  User hits A key
		case 'a':
			
			break;

		//  User hits Shift + A key
		case 'A':
			
			break;

		//  User hits Enter
		case '\r':
			printf ("User is hitting the Return key.\n"); 
			break;

		//  User hits Space
		case ' ':
			printf ("User is hitting the Space key.\n"); 
			break;

		//  User hits back space
		case 8:
			printf ("User is hitting the Back Space key.\n"); 
			break;

		//  User hits ESC key
		case 27:
			exit (1);
			break;
	}

	glutPostRedisplay ();
}

//-------------------------------------------------------------------------
//  This function is passed to the glutSpecialFunc and is called 
//  whenever the user hits a special key.
//-------------------------------------------------------------------------
void special (int key, int x, int y)
{
	//  Notify that this is a GLUT Callback
	printf ("GLUT: ");

	switch (key)
	{
		case GLUT_KEY_F1 :
			printf ("F1 function key.\n"); 
			break;
		case GLUT_KEY_F2 :
			printf ("F2 function key. \n");  
			break;
		case GLUT_KEY_F3 :
			printf ("F3 function key. \n");  
			break;
		case GLUT_KEY_F4 :
			printf ("F4 function key. \n");  
			break;
		case GLUT_KEY_F5 :
			printf ("F5 function key. \n");  
			break;
		case GLUT_KEY_F6 :
			printf ("F6 function key. \n");  
			break;
		case GLUT_KEY_F7 :
			printf ("F7 function key. \n");  
			break;
		case GLUT_KEY_F8 :
			printf ("F8 function key. \n");  
			break;
		case GLUT_KEY_F9 :
			printf ("F9 function key. \n");  
			break;
		case GLUT_KEY_F10 :
			printf ("F10 function key. \n");  
			break;
		case GLUT_KEY_F11 :
			printf ("F11 function key. \n");  
			break;
		case GLUT_KEY_F12 :
			printf ("F12 function key. \n");  
			break;
		case GLUT_KEY_LEFT :
			printf ("Left directional key. \n");  
			break;
		case GLUT_KEY_UP :
			printf ("Up directional key. \n");  
			break;
		case GLUT_KEY_RIGHT :
			printf ("Right directional key. \n");  
			break;
		case GLUT_KEY_DOWN :
			printf ("Down directional key. \n");  
			break;
		case GLUT_KEY_PAGE_UP :
			printf ("Page up directional key. \n");  
			break;
		case GLUT_KEY_PAGE_DOWN :
			printf ("Page down directional key. \n");  
			break;
		case GLUT_KEY_HOME :
			printf ("Home directional key. \n");  
			break;
		case GLUT_KEY_END :
			printf ("End directional key. \n");  
			break;
		case GLUT_KEY_INSERT :
			printf ("Insert directional key. \n");  
			break;
	}
	
	glutPostRedisplay ();
}

//-------------------------------------------------------------------------
//  Main Window Entry Function.
//
//	This function is called whenever the mouse pointer enters or leaves
//  the main window.
//-------------------------------------------------------------------------
void entry (int state)
{
	//  Notify that this is a GLUT Callback
	printf ("GLUT: ");

	//  Notify theat we entered the window
	if (state == GLUT_ENTERED)
		printf ("Mouse entered GLUT window...\n");
	//  Notify that we left the window
	else if (state == GLUT_LEFT)
		printf ("Mouse left GLUT window...\n");
}

//*************************************************************************
//  GLUI Functions.
//*************************************************************************

//-------------------------------------------------------------------------
//  Setup GLUI stuff.
//-------------------------------------------------------------------------
void setupGLUI ()
{
	//  Set idle function
	GLUI_Master.set_glutIdleFunc (idle);
	
	//  Create GLUI window
	glui_window = GLUI_Master.create_glui ("Options", 0, window_x - 235, window_y);
	
	//---------------------------------------------------------------------
	// 'Emitter Properties' Panel
	//---------------------------------------------------------------------

	//  Add the 'Emitter Properties' Panel to the GLUI window
	GLUI_Panel *ep_rollout = glui_window->add_rollout ("Emitter Properties");

	//  Add the Shape listbox to the 'Emitter Properties' Panel
	GLUI_Listbox *emitterShapeListbox = glui_window->add_listbox_to_panel (ep_rollout, 
		"Shape", &emitterShapeListboxItemId, EMITTER_SHAPE_LISTBOX, glui_callback);

	//  Add the items to the listbox
	emitterShapeListbox->add_item (1, "Point");
	emitterShapeListbox->add_item (2, "Line");
	emitterShapeListbox->add_item (3, "Triangle");

	//  Select the Point Emitter by default
	emitterShapeListbox->set_int_val (1);

	//  Add a separator
	glui_window->add_separator_to_panel (ep_rollout);

	// Add the Height Spinner to the 'Emitter Properties' Panel
	GLUI_Spinner *emitterHeightSpinner = glui_window->add_spinner_to_panel(ep_rollout,
		"Height:", GLUI_SPINNER_INT, &emitterHeight, EMITTER_HEIGHT_SPINNER ,glui_callback);

	// Add the Width Spinner to the 'Emitter Properties' Panel
	GLUI_Spinner *emitterWidthSpinner = glui_window->add_spinner_to_panel(ep_rollout,
		"Width:", GLUI_SPINNER_INT, &emitterWidth, EMITTER_WIDTH_SPINNER ,glui_callback);

	// Add the Depth Spinner to the 'Emitter Properties' Panel
	GLUI_Spinner *emitterDepthSpinner = glui_window->add_spinner_to_panel(ep_rollout,
		"Depth:", GLUI_SPINNER_INT, &emitterHeight, EMITTER_DEPTH_SPINNER ,glui_callback);

	//  Add a separator
	glui_window->add_separator_to_panel (ep_rollout);

	// Add the PositionX EditText to the 'Emitter Properties' Panel
	GLUI_EditText *emitterPositionXEditText = glui_window->add_edittext_to_panel(ep_rollout,
		"PositionX:", GLUI_SPINNER_INT, &emitterPosition[0], EMITTER_POSITIONX_EDITABLETEXT,
			glui_callback);

	// Add the PositionY EditText to the 'Emitter Properties' Panel
	GLUI_EditText *emitterPositionYEditText = glui_window->add_edittext_to_panel(ep_rollout,
		"PositionY:", GLUI_SPINNER_INT, &emitterPosition[1], EMITTER_POSITIONY_EDITABLETEXT,
		glui_callback);

	// Add the PositionZ EditText to the 'Emitter Properties' Panel
	GLUI_EditText *emitterPositionZEditText = glui_window->add_edittext_to_panel(ep_rollout,
		"PositionZ:", GLUI_SPINNER_INT, &emitterPosition[2], EMITTER_POSITIONZ_EDITABLETEXT,
		glui_callback);

	//  Add a separator
	glui_window->add_separator_to_panel (ep_rollout);

	// Add the MaximumParticles EditText to the 'Emitter Properties' Panel
	GLUI_EditText *emitterMaximumParticlesEditText = glui_window->add_edittext_to_panel(ep_rollout,
		"Maximum Particles:", GLUI_SPINNER_INT, &emitterMaximumParticles,
			EMITTER_MAXIMUMPARTICLES_EDITABLETEXT, glui_callback);

	//  Add a separator
	glui_window->add_separator_to_panel (ep_rollout);

	// Add the DurationSeconds EditText to the 'Emitter Properties' Panel
	GLUI_Spinner *emitterDurationSecondsSpinner = glui_window->add_spinner_to_panel(ep_rollout,
		"Duration in Seconds:", GLUI_SPINNER_INT, &emitterDurationSeconds,
			EMITTER_DURATIONSECONDS_SPINNER, glui_callback);

	//  Add a separator
	glui_window->add_separator_to_panel (ep_rollout);

	// Add the Repeat Checkbox to the 'Emitter Properties' Panel
	GLUI_Checkbox *emitterRepeatCheckbox = glui_window->add_checkbox_to_panel(ep_rollout,
		"Repeat:", &emitterRepeat, EMITTER_REPEAT_CHECKBOX, glui_callback);

	//---------------------------------------------------------------------
	// 'Particle Properties' Panel
	//---------------------------------------------------------------------

	//  Add the 'Particle Properties' Panel to the GLUI window
	GLUI_Panel *pp_rollout = glui_window->add_rollout ("Particle Properties");

	// Add the particleShape Listbox to the 'Particle Properties' panel
	GLUI_Listbox *particleShapeListbox = glui_window->add_listbox_to_panel(pp_rollout,
		"Shape:", &particleShapeListboxItemId, PARTICLE_SHAPE_LISTBOX, glui_callback);

	//  Add the items to the listbox
	particleShapeListbox->add_item (1, "Point");
	particleShapeListbox->add_item (2, "Line");
	particleShapeListbox->add_item (3, "Triangle");

	//  Select the Point Shape by default
	particleShapeListbox->set_int_val (1);

	//  Add a separator
	glui_window->add_separator_to_panel (pp_rollout);

	// Add the Height Spinner to the 'Particle Properties' panel
	GLUI_Spinner *particleHeightSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Height:", GLUI_SPINNER_INT, &particleHeight, PARTICLE_HEIGHT_SPINNER, glui_callback);

	// Add the Width Spinner to the 'Particle Properties' panel
	GLUI_Spinner *particleWidthSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Width:", GLUI_SPINNER_INT, &particleWidth, PARTICLE_WIDTH_SPINNER, glui_callback);

	// Add the Depth Spinner to the 'Particle Properties' panel
	GLUI_Spinner *particleDepthSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Height:", GLUI_SPINNER_INT, &particleDepth, PARTICLE_DEPTH_SPINNER, glui_callback);

	//  Add a separator
	glui_window->add_separator_to_panel (pp_rollout);

	// Add BlendingMode Listbox to the 'Particle Properties' panel
	GLUI_Listbox *particleBlendingModeListbox = glui_window->add_listbox_to_panel(pp_rollout,
		"Blending Mode:", &particleBlendingModeListboxItemId, PARTICLE_BLENDINGMODE_LISTBOX,
			glui_callback);

	//  Add the items to the listbox
	particleBlendingModeListbox->add_item (1, "Filtered");
	particleBlendingModeListbox->add_item (2, "Additive");

	//  Select the Point Shape by default
	particleBlendingModeListbox->set_int_val (1);

	//  Add a separator
	glui_window->add_separator_to_panel (pp_rollout);

	// Add the StartColourRed to the 'Particle Properties' panel
	GLUI_Spinner *particleStartColourRedSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Start Colour Red:", GLUI_SPINNER_INT, &particleStartColour[0], PARTICLE_STARTCOLOURRED_SPINNER,
			glui_callback);

	// Add the StartColourGreen to the 'Particle Properties' panel
	GLUI_Spinner *particleStartColourGreenSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Start Colour Green:", GLUI_SPINNER_INT, &particleStartColour[1], PARTICLE_STARTCOLOURGREEN_SPINNER,
			glui_callback);

	// Add the StartColourBlue to the 'Particle Properties' panel
	GLUI_Spinner *particleStartColourBlueSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Start Colour Blue:", GLUI_SPINNER_INT, &particleStartColour[2], PARTICLE_STARTCOLOURBLUE_SPINNER,
			glui_callback);

	// Add the EndColourRed to the 'Particle Properties' panel
	GLUI_Spinner *particleEndColourRedSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"End Colour Red:", GLUI_SPINNER_INT, &particleEndColour[0], PARTICLE_ENDCOLOURRED_SPINNER,
			glui_callback);

	// Add the EndColourGreen to the 'Particle Properties' panel
	GLUI_Spinner *particleEndColourGreenSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"End Colour Green:", GLUI_SPINNER_INT, &particleEndColour[1], PARTICLE_ENDCOLOURGREEN_SPINNER,
			glui_callback);

	// Add the EndColourBlue to the 'Particle Properties' panel
	GLUI_Spinner *particleEndColourBlueSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"End Colour Blue:", GLUI_SPINNER_INT, &particleEndColour[2], PARTICLE_ENDCOLOURBLUE_SPINNER,
			glui_callback);

	// Add the RandomColour Checkbox to the 'Particle Properties' panel
	GLUI_Checkbox *particleRandomColourCheckbox = glui_window->add_checkbox_to_panel(pp_rollout,
		"Random Colour:", &particleRandomColour, PARTICLE_RANDOMCOLOUR_CHECKBOX, glui_callback);

	//  Add a separator
	glui_window->add_separator_to_panel (pp_rollout);

	// Add the GravityX Spinner to the 'Particle Properties' panel
	GLUI_Spinner *particleGravityXSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Gravity X:", GLUI_SPINNER_INT, &particleGravity[0], PARTICLE_GRAVITYX_SPINNER, glui_callback);

	// Add the GravityY Spinner to the 'Particle Properties' panel
	GLUI_Spinner *particleGravityYSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Gravity Y:", GLUI_SPINNER_INT, &particleGravity[1], PARTICLE_GRAVITYY_SPINNER, glui_callback);

	// Add the GravityZ Spinner to the 'Particle Properties' panel
	GLUI_Spinner *particleGravityZSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Gravity Z:", GLUI_SPINNER_INT, &particleGravity[2], PARTICLE_GRAVITYZ_SPINNER, glui_callback);

	//  Add a separator
	glui_window->add_separator_to_panel (pp_rollout);

	// Add the SpeedX Spinner to the 'Particle Properties' panel
	GLUI_Spinner *particleSpeedXSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Speed X:", GLUI_SPINNER_INT, &particleSpeed[0], PARTICLE_SPEEDX_SPINNER, glui_callback);

	// Add the SpeedY Spinner to the 'Particle Properties' panel
	GLUI_Spinner *particleSpeedYSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Speed Y:", GLUI_SPINNER_INT, &particleSpeed[1], PARTICLE_SPEEDY_SPINNER, glui_callback);

	// Add the SpeedZ Spinner to the 'Particle Properties' panel
	GLUI_Spinner *particleSpeedZSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Speed Z:", GLUI_SPINNER_INT, &particleSpeed[2], PARTICLE_SPEEDZ_SPINNER, glui_callback);

	//  Add a separator
	glui_window->add_separator_to_panel (pp_rollout);

	// Add the FadeMinimum to the 'Particle Properties' panel
	GLUI_Spinner *particleFadeMinimumSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Fade Minimum:", GLUI_SPINNER_INT, &particleMinimumFade, PARTICLE_FADEMINIMUM_SPINNER,
			glui_callback);

	// Add the FadeMaximum to the 'Particle Properties' panel
	GLUI_Spinner *particleFadeMaximumSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Fade Maximum:", GLUI_SPINNER_INT, &particleMaximumFade, PARTICLE_FADEMAXIMUM_SPINNER,
		glui_callback);

	//  Add a separator
	glui_window->add_separator_to_panel (pp_rollout);

	//---------------------------------------------------------------------
	// 'Transformation' Panel
	//---------------------------------------------------------------------

	//  Add the 'Transformation' Panel to the GLUI window
	GLUI_Panel *transformation_panel = glui_window->add_panel ("Transformation");

	//  Create transformation panel 1 that will contain the Translation controls
	GLUI_Panel *transformation_panel1 = glui_window->add_panel_to_panel (transformation_panel, "");

	//  Add the xy translation control
	GLUI_Translation *translation_xy = glui_window->add_translation_to_panel (transformation_panel1, "Translation XY", GLUI_TRANSLATION_XY, translate_xy, TRANSLATION_XY, glui_callback );
	
	//  Set the translation speed
	translation_xy->set_speed( 0.005 );

	//  Add column, but don't draw it
	glui_window->add_column_to_panel (transformation_panel1, false);

	//  Add the z translation control
	GLUI_Translation *translation_z = glui_window->add_translation_to_panel (transformation_panel1, "Translation Z", GLUI_TRANSLATION_Z, &translate_z, TRANSLATION_Z, glui_callback );

	//  Set the translation speed
	translation_z->set_speed( 0.005 );

	//  Create transformation panel 2 that will contain the rotation and spinner controls
	GLUI_Panel *transformation_panel2 = glui_window->add_panel_to_panel (transformation_panel, "");

	//  Add the rotation control
	glui_window->add_rotation_to_panel (transformation_panel2, "Rotation", rotation_matrix, ROTATION, glui_callback);
	
	//  Add separator
	glui_window->add_separator_to_panel (transformation_panel2);

	//  Add the scale spinner
	GLUI_Spinner *spinner = glui_window->add_spinner_to_panel (transformation_panel2, "Scale", GLUI_SPINNER_FLOAT, &scale, SCALE_SPINNER, glui_callback);
	
	//  Set the limits for the spinner
	spinner->set_float_limits ( -4.0, 4.0 );

	//---------------------------------------------------------------------
	// 'Quit' Button
	//---------------------------------------------------------------------

	//  Add the Quit Button
	glui_window->add_button ("Quit", QUIT_BUTTON, glui_callback);

	//  Let the GLUI window know where its main graphics window is
	glui_window->set_main_gfx_window( main_window );
}

//-------------------------------------------------------------------------
//  GLUI callback function.
//-------------------------------------------------------------------------
void glui_callback (int control_id)
{
	//  Notify that this is a GLUI Callback
	printf ("GLUI: ");

	//  Behave based on control ID
	switch (control_id)
	{
		//  Color Listbox item changed
		case EMITTER_SHAPE_LISTBOX:

			printf ("Color List box item changed: ");

			switch (emitterShapeListboxItemId)
			{
				//  Select black color
				case 1:
					color[0] = 255/255.0;
					color[1] = 255/255.0;
					color[2] = 255/255.0;
					break;
				//  Select blue color
				case 2:
					color[0] = 0/255.0;
					color[1] = 0/255.0;
					color[2] = 255/255.0;
					break;
				//  Select cyan color
				case 3:	
					color[0] = 0/255.0;
					color[1] = 255/255.0;
					color[2] = 255/255.0;
					break;
			}

			printf ("Item %d selected.\n", emitterShapeListboxItemId);

		break;

		//  A Radio Button in the radio group is selected
		case OBJECTYPE_RADIOGROUP:

			printf ("Radio Button %d selected.\n", radiogroup_item_id);

		break;

		//  Translation XY control
		case TRANSLATION_XY:

			printf ("Translating X and Y coordinates: ");
			printf ("X: %f, Y: %f.\n", translate_xy[0], translate_xy[1]);

			break;

		//  Translation Z control
		case TRANSLATION_Z:

			printf ("Translating Z coordinate: ");
			printf ("Z: %f.\n", translate_z);

			break;

		//  rotation control is being rotated
		case ROTATION:

			printf ("Rotating archball!\n");
			printMatrixf (rotation_matrix);

		break;

		//  Scaling
		case SCALE_SPINNER:

			printf ("Scaling Object: %f.\n", scale);

		break;

		//  Quit Button clicked
		case QUIT_BUTTON:
		
			printf ("Quit Button clicked... Exit!\n");

			exit (1);

		break;

	}
}

//-------------------------------------------------------------------------
//  Idle Callback function.
//
//  Set the main_window as the current window to avoid sending the
//  redisplay to the GLUI window rather than the GLUT window. 
//  Call the Sleep function to stop the GLUI program from causing
//  starvation.
//-------------------------------------------------------------------------
void idle ()
{
	glutSetWindow (main_window);
	UpdateGLScene();
	glutPostRedisplay ();
	Sleep (10);
}


//*************************************************************************
//  Program Main method.
//*************************************************************************
void main (int argc, char **argv)
{
	//  Set the window x and y coordinates such that the 
	//  window becomes centered
	centerOnScreen ();

	//  Connect to the windowing system + create a window
	//  with the specified dimensions and position
	//  + set the display mode + specify the window title.
	glutInit(&argc, argv);
	glutInitWindowSize (window_width, window_height);
	glutInitWindowPosition (window_x, window_y);
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE);
	main_window = glutCreateWindow (window_title);

	//  View in full screen if the full_screen flag is on
	if (full_screen)
		glutFullScreen ();

	//  Set OpenGL context initial state.
	init();
	
	// Set the GLUT callback functions
	glutDisplayFunc (display);
	glutReshapeFunc  (reshape);
	glutMouseFunc (mouse);
	glutMotionFunc (motion);
	glutPassiveMotionFunc (pmotion);
	glutKeyboardFunc (keyboard);
	glutSpecialFunc (special);
	glutEntryFunc (entry);

	//  Setup all GLUI stuff
	setupGLUI ();

	//  Start GLUT event processing loop
	glutMainLoop();
}

