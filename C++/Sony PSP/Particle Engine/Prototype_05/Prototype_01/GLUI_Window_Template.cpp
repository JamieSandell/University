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
#include <stdlib.h>
#include <iostream>
#include <string>
#include "FrameTimer.h"
#include "Vector3d.h"
//#include "Particle.h"
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

/// Enum to determine Particle shape
enum eParticleShapes{
shapePoint = 1,
shapeLine,
shapeTriangle
};
int particleShape = shapePoint;

/////////////////////////Particles
/// a structure to hold a particle
struct Particle {
	/// the current particle position
	float position[3];
	/// the direction of the particle
	float direction[3];

	/// the colour of the particle
	float colour[3];

	/// the lifespan
	float life;

	/// constructor
	Particle();
};

struct ParticlePoints{
	/// the current particle position
	float position[3];
	/// the direction of the particle
	float direction[3];

	/// the colour of the particle
	float colour[3];

	/// the lifespan
	float life;
	ParticlePoints();
};

struct ParticleTriangles {
	/// the current particle position
	float position[9];
	/// the direction of the particle
	float direction[3];

	/// the colour of the particle
	float colour[3];

	/// the lifespan
	float life;
	ParticleTriangles();
};

/// the first particle in the linked list
ParticlePoints* start=0;

/// the next free particle
ParticlePoints* last=0;

/// the end of the memory allocation
ParticlePoints* end=0;

/// the first particle in the linked list
ParticleTriangles* startTriangles=0;

/// the next free particle
ParticleTriangles* lastTriangles=0;

/// the end of the memory allocation
ParticleTriangles* endTriangles=0;

/// Sets the type of the particle, e.g. start, last, end become pointers to ParticleTriangles
template<typename T>
void SetParticleType(T *&inStart, T *&inLast, T *&inEnd)
{

	T* start = 0;
	T* last = 0;
	T* end = 0;
	inStart = start;
	inLast = last;
	inEnd = end;
}

//------------------------------------------------------------	SetSize()
//
//	Allocates the static global particle buffer
//
template<typename T>
void SetSize(unsigned int size, T *&inStart, T *&inLast, T *&inEnd) {

	// delete any previous data
	delete [] inStart;

	// allocate new particles
	inLast = inStart = new T[size];

	// set end
	inEnd = inStart+size;
}


//------------------------------------------------------------	IsEmpty()
//
//	returns true if the particle array is empty
//
template<typename T>
bool IsEmpty(T *&inStart, T *&inLast) {
	return inStart==inLast; // if start equals last then it must be empty
}

//------------------------------------------------------------	IsFull()
//
//	returns true if the array is full
//
bool IsFull() {
	switch(particleShape)
	{
		case shapePoint: // Points
			return last==end;
			break;
		case shapeLine: // Lines
			break;
		case shapeTriangle: // Triangles
			return lastTriangles==endTriangles;
			break;
		default:
			break;
	}
}

//------------------------------------------------------------	DrawParticles()
//
void DrawParticles() {

	if (particleShape==shapePoint)
	{
		// since the particles are all nicely packed into one place,
		// i can simply use vertex arrays to render the data. To do 
		// this we need to give the address of the first data element
		// in the array. We also need to specify a stride parameter,
		// ie the number of bytes between each data element. In this
		// case, each position is seperated by another particle. The
		// same is true of the colours.
		//
		//
		glVertexPointer(3,GL_FLOAT,sizeof(Particle),start->position);
		glColorPointer(3,GL_FLOAT,sizeof(Particle),start->colour);

		// enable vertex arrays
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		// draw the particles in one lovely function call. Note that 
		// this is faster than glBegin/glEnd() because it avoids the 
		// large amount of function call overhead.
		//
		glDrawArrays(GL_POINTS,0,last-start);

		// disable vertex arrays
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}
	if (particleShape==shapeTriangle)
	{
		// since the particles are all nicely packed into one place,
		// i can simply use vertex arrays to render the data. To do 
		// this we need to give the address of the first data element
		// in the array. We also need to specify a stride parameter,
		// ie the number of bytes between each data element. In this
		// case, each position is seperated by another particle. The
		// same is true of the colours.
		//
		//
		glVertexPointer(3,GL_FLOAT,sizeof(ParticleTriangles),startTriangles->position);
		glColorPointer(3,GL_FLOAT,sizeof(ParticleTriangles),startTriangles->colour);

		// enable vertex arrays
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		// draw the particles in one lovely function call. Note that 
		// this is faster than glBegin/glEnd() because it avoids the 
		// large amount of function call overhead.
		//
		glDrawArrays(GL_TRIANGLES,0,lastTriangles-startTriangles);

		// disable vertex arrays
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}
}


//------------------------------------------------------------	AddOne()
// this function 'adds' a particle into the array. In actual
// fact, all it does is move the pointer to the last element
// along by one position. This means we have not performed an
// expensive memory allocation.
//
template<typename T>
void AddOne(T *&inLast) {

	// if we have no more memory left for any particles, ignore
	// the request to creat one.
	if (!IsFull()) {
		*inLast = T();
		++inLast;
	}
}

//------------------------------------------------------------	EraseOne()
// Given a pointer to the particle that needs to be deleted,
// this function simply swaps the last particle with the one
// to be deleted. This means that all living particles are
// always tightly packed at the front of the array, and
// secondly we have no need to perform any memory allocations
//
template<typename T>
void EraseOne(T* p, T *&inStart, T *&inLast) {
	if (!IsEmpty(inStart, inLast)) {
		*p = *(--inLast);
	}
}



//------------------------------------------------------------	Particle::Particle()
/// constructor
Particle::Particle() {

	// set position
	position[0] = position[2] = 0.0f;
	position[1] = 0.0f;

	// create random direction
	direction[0] = (10000 - rand()%20000)/10000.0f;
	direction[1] = (10000 - rand()%20000)/10000.0f;
	direction[2] = (10000 - rand()%20000)/10000.0f;

	// create random colour
	colour[0] = 0.8f;
	colour[1] = rand()%15000/20000.0f;
	colour[2] = 0.1f;

	// set a random lifespan
	//life = rand()%30000/9500.0f;
	life = rand()%30000/950.0f;
}

ParticlePoints::ParticlePoints()
{
	// set position
	position[0] = position[2] = 0.0f;
	position[1] = 0.0f;

	// create random direction
	direction[0] = (10000 - rand()%20000)/10000.0f;
	direction[1] = (10000 - rand()%20000)/10000.0f;
	direction[2] = (10000 - rand()%20000)/10000.0f;

	// create random colour
	colour[0] = 0.8f;
	colour[1] = rand()%15000/20000.0f;
	colour[2] = 0.1f;

	// set a random lifespan
	//life = rand()%30000/9500.0f;
	life = rand()%30000/950.0f;
}

ParticleTriangles::ParticleTriangles()
{
	// set position
	// top, x,y,z
	position[0] = 0.0f;
	position[1] = 0.0001f;
	position[2] = 0.0f;
	// bottom right, x,y,z
	position[3] = 0.0001f;
	position[4] = 0.0f;
	position[5] = 0.0f;
	// bottom left, x,y,z
	position[6] = -0.0001f;
	position[7] = 0.0f;
	position[8] = 0.0f;

	// create random direction
	direction[0] = (10000 - rand()%20000)/10000.0f;
	direction[1] = (10000 - rand()%20000)/10000.0f;
	direction[2] = (10000 - rand()%20000)/10000.0f;

	// create random colour
	colour[0] = 0.8f;
	colour[1] = rand()%15000/20000.0f;
	colour[2] = 0.1f;

	// set a random lifespan
	//life = rand()%30000/9500.0f;
	life = rand()%30000/950.0f;
}

//------------------------------------------------------------	UpdateParticles()
//
template<typename T>
void UpdateParticles(float dt, T *&inStart, T *&inLast) {

	// traverse all particles and update
	T* p = inStart;
	while(p!=inLast) {
		// decrease lifespan
		p->life -= dt;

		// if we have life left
		if (p->life>0) {

			// apply gravity
			p->direction[0] -= particleGravity[0]*dt;
			p->direction[1] -= particleGravity[1]*dt;
			p->direction[2] -= particleGravity[2]*dt;

			// modify position
			//// TODO:
			//// Take into account triangles will have more than 3 positions
			p->position[0] += dt * p->direction[0]; // x TriangleTop
			p->position[1] += dt * p->direction[1]; // y
			p->position[2] += dt * p->direction[2]; // z
			if (particleShape == shapeTriangle) // update all vertices of the triangle
			{
				p->position[3] += dt * p->direction[0]; // x TriangleBottomRight
				p->position[4] += dt * p->direction[1]; // y
				p->position[5] += dt * p->direction[2]; // z
				p->position[6] += dt * p->direction[0]; // x TriangleBottomLeft
				p->position[7] += dt * p->direction[1]; // y
				p->position[8] += dt * p->direction[2]; // z
			}

			p->colour[0] *= (1-0.3*dt);
			p->colour[1] *= (1-0.3*dt);
			p->colour[2] *= (1-0.3*dt);

			// goto next particle
			++p;
		}
		else {
			// if the particle is dead, erase it
			/// TODO:
			/// Add code for other particle shapes such as ParticleTriangles
			EraseOne(p, inStart, inLast);

			// make sure it wasn't the last particle in the array,
			// if it was, return
			if (p>=inLast) {
				return;
			}
		}

	}
}
/////////////////////////Particles


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
GLUI_Listbox *emitterShapeListbox;
GLUI_Spinner *emitterHeightSpinner;
GLUI_Spinner *emitterWidthSpinner;
GLUI_Spinner *emitterDepthSpinner;
GLUI_EditText *emitterPositionXEditText;
GLUI_EditText *emitterPositionYEditText;
GLUI_EditText *emitterPositionZEditText;
GLUI_EditText *emitterMaximumParticlesEditText;
GLUI_Spinner *emitterDurationSecondsSpinner;
GLUI_Checkbox *emitterRepeatCheckbox;
GLUI_Listbox *particleShapeListbox;
GLUI_Spinner *particleHeightSpinner;
GLUI_Spinner *particleWidthSpinner;
GLUI_Spinner *particleDepthSpinner;
GLUI_Listbox *particleBlendingModeListbox;
GLUI_Spinner *particleStartColourRedSpinner;
GLUI_Spinner *particleStartColourGreenSpinner;
GLUI_Spinner *particleStartColourBlueSpinner;
GLUI_Spinner *particleEndColourRedSpinner;
GLUI_Spinner *particleEndColourGreenSpinner;
GLUI_Spinner *particleEndColourBlueSpinner;
GLUI_Checkbox *particleRandomColourCheckbox;
GLUI_Spinner *particleGravityXSpinner;
GLUI_Spinner *particleGravityYSpinner;
GLUI_Spinner *particleGravityZSpinner;
GLUI_Spinner *particleSpeedXSpinner;
GLUI_Spinner *particleSpeedYSpinner;
GLUI_Spinner *particleSpeedZSpinner;
GLUI_Spinner *particleFadeMinimumSpinner;
GLUI_Spinner *particleFadeMaximumSpinner;

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
float particleGravity[] = {0.0, 1.31, 0.0}; // x,y,z
float particleSpeed[] = {0.0, 100.0, 0.0}; // x,y,z
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

	// Texture code
	//glEnable(GL_TEXTURE_2D);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glShadeModel(GL_SMOOTH);						// Enables Smooth Shading
	//glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
	//glClearDepth(1.0f);							// Depth Buffer Setup
	////glDisable(GL_DEPTH_TEST);						// Disables Depth Testing
	glEnable(GL_BLEND);							// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);			// Really Nice Perspective Calculations
	//glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);					// Really Nice Point Smoothing
	//glDisable(GL_TEXTURE_2D);						// Enable Texture Mapping

	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// set the maximum number of particles
	SetSize(100000, start, last, end);


	//// Init particles
	//for (int i = 0; i < MAX_PARTICLES; i++)
	//{
	//	int low = 100;
	//	int high = 200;
	//	particle[i].SetAliveStatus(true);
	//	particle[i].SetLife(1.0f);
	//	particle[i].SetColour(Vector3d(rand()/(float(RAND_MAX)+1), rand()/(float(RAND_MAX)+1), rand()/(float(RAND_MAX)+1)));
	//	particle[i].SetFade(float(rand()%100)/1000.0f+10.0f);
	//	particle[i].SetGravity(Vector3d(0.0f,0.8f,0.0f));
	//	particle[i].SetPosition(Vector3d(0,0,0));
	//	particle[i].SetSpeed(Vector3d((rand () % (high - low + 1) + low)*10,(rand () % (high - low + 1) + low)*10,(rand () % (high - low + 1) + low)*10));
	//}
}
// used for frame counting
int count = 0;
GLvoid UpdateGLScene(GLvoid) // Update code
{

	// Timer code
	//float dt = myTimer.Tick();
	// Timer code

	// Camera code
	//currentCamera = myCamera.GetCurrentCamera();
	// Camera code

	//// If the particle is alive then update it
	//for (int i = 0; i < MAX_PARTICLES; i++) // draw particles if they are alive
	//{
	//	if (particle[i].GetLife()>0.0f)
	//	{
	//		particle[i].Update();
	//	}
	//}

	//if(++count == 1000) {
	int particleCount = (int)(last-start);
		std::cout << "num particles = " << ((int)(last-start)) << "   fps = " << (1.0f/FrameTime())<< "\n";
		count=0;
	//}

	// update the frame time
	SortFrameTimer();

	// create a random number of new particles every frame
	int val = rand()%100000;
	switch (particleShape)
	{
		case shapePoint:
			for(int i=0;i!=val;++i)
				AddOne(last);
			break;
		case shapeLine:
			break;
		case shapeTriangle:
			for(int i=0;i!=val;++i)
				AddOne(lastTriangles);
		default :
			break;
	}

	// update the particle simulation
	switch(particleShape)
	{
		case shapePoint:
			UpdateParticles(FrameTime(), start, last);
			break;
		case shapeLine:
			break;
		case shapeTriangle:
			UpdateParticles(FrameTime(), startTriangles, lastTriangles);
			break;
		default:
			break;
	}



}

GLvoid DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
	//glLoadIdentity(); // Reset The Current Modelview Matrix
	//gluLookAt(0, 0,50, 0, 0, 0, 0, 1, 0);

	//glBegin(GL_TRIANGLE_STRIP); // Add glTex later
	//for (int i = 0; i < MAX_PARTICLES; i++) // draw particles if they are alive
	//{
	//	if (particle[i].GetLife()>0.0f)
	//	{
	//		particle[i].Draw(texture);
	//		//particle[i].Draw();
	//	}
	//}
	//glEnd();
	// clear the screen & depth buffer
	//glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	//// clear the previous transform
	//glLoadIdentity();

	//// set the camera position
	//gluLookAt(	1,-3,10,	//	eye pos
	//	0,-3,0,	//	aim point
	//	0,1,0);	//	up direction

	//
	gluLookAt(	1,-3,10,	//	eye pos
		0,-3,0,	//	aim point
		0,1,0);	//	up direction
	DrawParticles();

	// currently we've been drawing to the back buffer, we need
	// to swap the back buffer with the front one to make the image visible
	//glutSwapBuffers();


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
	////  Notify that this is a GLUT Callback
	//printf ("GLUT: ");

	////  Stay updated with the window width and height
	//window_width = w;
	//window_height = h;

	////  Reset viewport
	//glViewport(0, 0, window_width, window_height);

	////  Print current width and height on the screen
	//printf ("Window Width: %d, Window Height: %d.\n", window_width, window_height);

	// prevents a division by zero when calculating aspect
	// ratio below. This can happen when the window gets
	// minimised.
	if (h==0)
		h=1;

	// set the drawable region of the window
	glViewport(0,0,w,h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// just use a perspective projection
	gluPerspective(45,(float)w/h,0.1,100);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
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
	emitterShapeListbox = glui_window->add_listbox_to_panel (ep_rollout, 
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
	emitterHeightSpinner = glui_window->add_spinner_to_panel(ep_rollout,
		"Height:", GLUI_SPINNER_INT, &emitterHeight, EMITTER_HEIGHT_SPINNER ,glui_callback);

	// Add the Width Spinner to the 'Emitter Properties' Panel
	emitterWidthSpinner = glui_window->add_spinner_to_panel(ep_rollout,
		"Width:", GLUI_SPINNER_INT, &emitterWidth, EMITTER_WIDTH_SPINNER ,glui_callback);

	// Add the Depth Spinner to the 'Emitter Properties' Panel
	emitterDepthSpinner = glui_window->add_spinner_to_panel(ep_rollout,
		"Depth:", GLUI_SPINNER_INT, &emitterHeight, EMITTER_DEPTH_SPINNER ,glui_callback);

	//  Add a separator
	glui_window->add_separator_to_panel (ep_rollout);

	// Add the PositionX EditText to the 'Emitter Properties' Panel
	emitterPositionXEditText = glui_window->add_edittext_to_panel(ep_rollout,
		"PositionX:", GLUI_SPINNER_INT, &emitterPosition[0], EMITTER_POSITIONX_EDITABLETEXT,
			glui_callback);

	// Add the PositionY EditText to the 'Emitter Properties' Panel
	emitterPositionYEditText = glui_window->add_edittext_to_panel(ep_rollout,
		"PositionY:", GLUI_SPINNER_INT, &emitterPosition[1], EMITTER_POSITIONY_EDITABLETEXT,
		glui_callback);

	// Add the PositionZ EditText to the 'Emitter Properties' Panel
	emitterPositionZEditText = glui_window->add_edittext_to_panel(ep_rollout,
		"PositionZ:", GLUI_SPINNER_INT, &emitterPosition[2], EMITTER_POSITIONZ_EDITABLETEXT,
		glui_callback);

	//  Add a separator
	glui_window->add_separator_to_panel (ep_rollout);

	// Add the MaximumParticles EditText to the 'Emitter Properties' Panel
	emitterMaximumParticlesEditText = glui_window->add_edittext_to_panel(ep_rollout,
		"Maximum Particles:", GLUI_SPINNER_INT, &emitterMaximumParticles,
			EMITTER_MAXIMUMPARTICLES_EDITABLETEXT, glui_callback);

	//  Add a separator
	glui_window->add_separator_to_panel (ep_rollout);

	// Add the DurationSeconds EditText to the 'Emitter Properties' Panel
	emitterDurationSecondsSpinner = glui_window->add_spinner_to_panel(ep_rollout,
		"Duration in Seconds:", GLUI_SPINNER_INT, &emitterDurationSeconds,
			EMITTER_DURATIONSECONDS_SPINNER, glui_callback);

	//  Add a separator
	glui_window->add_separator_to_panel (ep_rollout);

	// Add the Repeat Checkbox to the 'Emitter Properties' Panel
	emitterRepeatCheckbox = glui_window->add_checkbox_to_panel(ep_rollout,
		"Repeat:", &emitterRepeat, EMITTER_REPEAT_CHECKBOX, glui_callback);

	//---------------------------------------------------------------------
	// 'Particle Properties' Panel
	//---------------------------------------------------------------------

	//  Add the 'Particle Properties' Panel to the GLUI window
	GLUI_Panel *pp_rollout = glui_window->add_rollout ("Particle Properties");

	// Add the particleShape Listbox to the 'Particle Properties' panel
	particleShapeListbox = glui_window->add_listbox_to_panel(pp_rollout,
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
	particleHeightSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Height:", GLUI_SPINNER_INT, &particleHeight, PARTICLE_HEIGHT_SPINNER, glui_callback);

	// Add the Width Spinner to the 'Particle Properties' panel
	particleWidthSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Width:", GLUI_SPINNER_INT, &particleWidth, PARTICLE_WIDTH_SPINNER, glui_callback);

	// Add the Depth Spinner to the 'Particle Properties' panel
	particleDepthSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Height:", GLUI_SPINNER_INT, &particleDepth, PARTICLE_DEPTH_SPINNER, glui_callback);

	//  Add a separator
	glui_window->add_separator_to_panel (pp_rollout);

	// Add BlendingMode Listbox to the 'Particle Properties' panel
	particleBlendingModeListbox = glui_window->add_listbox_to_panel(pp_rollout,
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
	particleStartColourRedSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Start Colour Red:", GLUI_SPINNER_INT, &particleStartColour[0], PARTICLE_STARTCOLOURRED_SPINNER,
			glui_callback);

	// Add the StartColourGreen to the 'Particle Properties' panel
	particleStartColourGreenSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Start Colour Green:", GLUI_SPINNER_INT, &particleStartColour[1], PARTICLE_STARTCOLOURGREEN_SPINNER,
			glui_callback);

	// Add the StartColourBlue to the 'Particle Properties' panel
	particleStartColourBlueSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Start Colour Blue:", GLUI_SPINNER_INT, &particleStartColour[2], PARTICLE_STARTCOLOURBLUE_SPINNER,
			glui_callback);

	// Add the EndColourRed to the 'Particle Properties' panel
	particleEndColourRedSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"End Colour Red:", GLUI_SPINNER_INT, &particleEndColour[0], PARTICLE_ENDCOLOURRED_SPINNER,
			glui_callback);

	// Add the EndColourGreen to the 'Particle Properties' panel
	particleEndColourGreenSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"End Colour Green:", GLUI_SPINNER_INT, &particleEndColour[1], PARTICLE_ENDCOLOURGREEN_SPINNER,
			glui_callback);

	// Add the EndColourBlue to the 'Particle Properties' panel
	particleEndColourBlueSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"End Colour Blue:", GLUI_SPINNER_INT, &particleEndColour[2], PARTICLE_ENDCOLOURBLUE_SPINNER,
			glui_callback);

	// Add the RandomColour Checkbox to the 'Particle Properties' panel
	particleRandomColourCheckbox = glui_window->add_checkbox_to_panel(pp_rollout,
		"Random Colour:", &particleRandomColour, PARTICLE_RANDOMCOLOUR_CHECKBOX, glui_callback);

	//  Add a separator
	glui_window->add_separator_to_panel (pp_rollout);

	// Add the GravityX Spinner to the 'Particle Properties' panel
	particleGravityXSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Gravity X:", GLUI_SPINNER_FLOAT, &particleGravity[0], PARTICLE_GRAVITYX_SPINNER, glui_callback);
	//particleGravityXSpinner->get_float_val();

	// Add the GravityY Spinner to the 'Particle Properties' panel
	particleGravityYSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Gravity Y:", GLUI_SPINNER_FLOAT, &particleGravity[1], PARTICLE_GRAVITYY_SPINNER, glui_callback);

	// Add the GravityZ Spinner to the 'Particle Properties' panel
	particleGravityZSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Gravity Z:", GLUI_SPINNER_FLOAT, &particleGravity[2], PARTICLE_GRAVITYZ_SPINNER, glui_callback);

	//  Add a separator
	glui_window->add_separator_to_panel (pp_rollout);

	// Add the SpeedX Spinner to the 'Particle Properties' panel
	particleSpeedXSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Speed X:", GLUI_SPINNER_INT, &particleSpeed[0], PARTICLE_SPEEDX_SPINNER, glui_callback);

	// Add the SpeedY Spinner to the 'Particle Properties' panel
	particleSpeedYSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Speed Y:", GLUI_SPINNER_INT, &particleSpeed[1], PARTICLE_SPEEDY_SPINNER, glui_callback);

	// Add the SpeedZ Spinner to the 'Particle Properties' panel
	particleSpeedZSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Speed Z:", GLUI_SPINNER_INT, &particleSpeed[2], PARTICLE_SPEEDZ_SPINNER, glui_callback);

	//  Add a separator
	glui_window->add_separator_to_panel (pp_rollout);

	// Add the FadeMinimum to the 'Particle Properties' panel
	particleFadeMinimumSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Fade Minimum:", GLUI_SPINNER_INT, &particleMinimumFade, PARTICLE_FADEMINIMUM_SPINNER,
			glui_callback);

	// Add the FadeMaximum to the 'Particle Properties' panel
	particleFadeMaximumSpinner = glui_window->add_spinner_to_panel(pp_rollout,
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

		case PARTICLE_GRAVITYX_SPINNER:
			particleGravity[0] = particleGravityXSpinner->get_float_val();
			break;
		case PARTICLE_GRAVITYY_SPINNER:
			particleGravity[1] = particleGravityYSpinner->get_float_val();
			break;
		case PARTICLE_GRAVITYZ_SPINNER:
			particleGravity[2] = particleGravityZSpinner->get_float_val();
			break;

		case PARTICLE_SHAPE_LISTBOX:
			/*particleShapeListbox->add_item (1, "Point");
			particleShapeListbox->add_item (2, "Line");
			particleShapeListbox->add_item (3, "Triangle");*/
			switch(particleShapeListboxItemId)
			{
				case 1:
					SetParticleType(start, last, end);
					SetSize(100000, start, last, end);
					particleShape = shapePoint;
					break;
				case 2:
					particleShape = shapeLine;
					break;
				case 3:
					SetParticleType(startTriangles, lastTriangles, endTriangles);
					SetSize(100000, startTriangles, lastTriangles, endTriangles);
					particleShape = shapeTriangle;
					break;
				default:
					break;
			}
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
	//glutInitWindowSize (window_width, window_height);
	// set the initial window size
	glutInitWindowSize(640,480);
	glutInitWindowPosition (window_x, window_y);
	//glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE);
	// request a depth buffer, RGBA display mode, and we want double buffering
	glutInitDisplayMode(GLUT_DEPTH|GLUT_RGBA|GLUT_DOUBLE);
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

	// initialise the frame timer
	InitFrameTimer();

	//  Start GLUT event processing loop
	glutMainLoop();
}

