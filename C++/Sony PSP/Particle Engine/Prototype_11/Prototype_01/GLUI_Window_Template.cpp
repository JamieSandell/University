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
#include "wglext.h"

// Link the lib files to the program. This is not necessary
// if you have added the lib names using Project/Settings/Link
#pragma comment (lib, "glui32.lib")
#pragma comment (lib, "glut32.lib")
#pragma comment (lib, "glu32.lib")
#pragma comment (lib, "opengl32.lib")

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // disable the console
// window

//*************************************************************************
//  GLUI Declarations
//*************************************************************************

//  pointer to the GLUI window
GLUI * glui_window;
GLUI_Listbox *emitterShapeListbox;
GLUI_Spinner *emitterHeightSpinner;
GLUI_Spinner *emitterWidthSpinner;
GLUI_Spinner *emitterDepthSpinner;
GLUI_Spinner *emitterPositionXEditText;
GLUI_Spinner *emitterPositionYEditText;
GLUI_Spinner *emitterPositionZEditText;
GLUI_Spinner *emitterPositionXMinSpinner;
GLUI_Spinner *emitterPositionXMaxSpinner;
GLUI_Spinner *emitterPositionYMinSpinner;
GLUI_Spinner *emitterPositionYMaxSpinner;
GLUI_Spinner *emitterPositionZMinSpinner;
GLUI_Spinner *emitterPositionZMaxSpinner;
GLUI_Spinner *emitterMaximumParticlesEditText;
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
GLUI_Spinner *particleSpeedXSpinnerMin;
GLUI_Spinner *particleSpeedYSpinnerMin;
GLUI_Spinner *particleSpeedZSpinnerMin;
GLUI_Spinner *particleSpeedXSpinnerMax;
GLUI_Spinner *particleSpeedYSpinnerMax;
GLUI_Spinner *particleSpeedZSpinnerMax;
GLUI_Spinner *particleFadeMinimumSpinner;
GLUI_Spinner *particleFadeMaximumSpinner;
GLUI_Listbox *presetListBox;

//  Declare live variables (related to GLUI)
int wireframe = 1;			//  Related to Wireframe Check Box
int draw = 1;				//  Related to Draw Check Box
int presetListBoxItemId = 1; // Id of the selected item in the list box
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
int emitterXMin = 0;
int emitterXMax = 3;
int emitterYMin = 0;
int emitterYMax = 0;
int emitterZMin = 0;
int emitterZMax = 3;
int emitterMaximumParticles = 100000;
int emitterDurationSeconds = 1;
int emitterRepeat = true;
int particleShapeListboxItemId = 1;
int particleHeight = 5;
int particleWidth = 5;
int particleDepth = 5;
int particleBlendingModeListboxItemId = 1;
float particleStartColour[] = {0.0, 0.0, 0.0};
float particleEndColour[] = {1.0, 1.0, 1.0};
int particleRandomColour = false;
float particleGravity[] = {0.0, 1.31, 0.0}; // x,y,z
float particleSpeedMin[] = {0.0, 0.0, 0.0}; // x,y,z
float particleSpeedMax[] = {0.0, 0.0, 0.0}; // x,y,z
float particleMinimumFade = 30000.0;
float particleMaximumFade = 30000.0;
Timer timeLeft;

// an array of RGB components
float color[] = { 1.0, 1.0, 1.0 };

/// Enum to determine Particle shape
enum eParticleShapes{
shapePoint = 1,
shapeLine,
shapeTriangle
};
int particleShape = shapePoint;
/// Enum to determine Emitter Shape
enum eEmitterShapes{
	emitterPoint = 1,
	emitterBox,
	emitterCircle
};
int emitterShape = emitterPoint;
// Enum to determine selected Preset
enum ePreset{
	presetSnow = 1,
	presetRain
};
int presetSelected = presetSnow;
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

	/// speed to act against gravity
	float speed[3];

	float fade;
	/// constructor
	Particle();
};

struct ParticlePoints{
	/// the current particle position
	float position[3];
	/// the direction of the particle
	float direction[3];

	/// the colour of the particle
	float colour[4];

	/// the lifespan
	float life;

	/// speed to act against gravity
	float speed[3];
	float fade;
	ParticlePoints();
};

struct ParticleLines{
	/// the current particle position
	float position[6]; //2 vertices = 6 points, xyz---xyz
	/// the direction of the particle
	float direction[3];

	/// the colour of the particle
	float colour[4];

	/// the lifespan
	float life;

	/// speed to act against gravity
	float speed[3];
	float fade;
	ParticleLines();
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

	/// speed to act against gravity
	float speed[3];
	float fade;
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

/// the first particle in the linked list
ParticleLines* startLines=0;

/// the next free particle
ParticleLines* lastLines=0;

/// the end of the memory allocation
ParticleLines* endLines=0;

void renderBitmapString(float x, float y, void *font,const char *string)
{

	const char *c = string;
	glRasterPos2f(x, y);
	for (; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}  /* end renderBitmapString() */

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
			return lastLines==endLines;
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

	if (!emitterRepeat) // if the repeat option isn't ticked then
						// check that there is still time remaining
	{
		if (timeLeft.getTime() > emitterDurationSeconds)
		{
			return; // No time remaining so don't draw any particles
		}
	}
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
		glPointSize((float)particleHeight);
		//float atten[] = {0.0f, 1.0f, 0.0f};
		//glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, atten);
		glVertexPointer(3,GL_FLOAT,sizeof(ParticlePoints),start->position);
		glColorPointer(4,GL_FLOAT,sizeof(ParticlePoints),start->colour);

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
	if (particleShape==shapeLine)
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
		glVertexPointer(3,GL_FLOAT,sizeof(ParticleLines),startLines->position);
		glColorPointer(4,GL_FLOAT,sizeof(ParticleLines),startLines->colour);

		// enable vertex arrays
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		// draw the particles in one lovely function call. Note that 
		// this is faster than glBegin/glEnd() because it avoids the 
		// large amount of function call overhead.
		//
		glDrawArrays(GL_LINES,0,lastLines-startLines);

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
		glColorPointer(4,GL_FLOAT,sizeof(ParticleTriangles),startTriangles->colour);

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
Particle::Particle() { // Not used at the moment, only points, lines, and triangles are

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
	speed[0] = rand () % (int(particleSpeedMax[0]) - int(particleSpeedMin[0]) + 1) +
		int(particleSpeedMin[0]);
	speed[1] = rand () % (int(particleSpeedMax[1]) - int(particleSpeedMin[1]) + 1) +
		int(particleSpeedMin[1]);
	speed[2] = rand () % (int(particleSpeedMax[2]) - int(particleSpeedMin[2]) + 1) +
		int(particleSpeedMin[2]);
}

ParticlePoints::ParticlePoints()
{
	// set position
	///////// Add "jitter", this is for point emitter
	// x position, y position and z position = rand() % (upper_limit - lower_limit + 1) + lower_limit; 
	/////////
	///////// Add "jitter", this is for box emitter (e.g. rain, snow)
	// x position and z position = rand() % (upper_limit - lower_limit + 1) + lower_limit; 
	/////////

	switch (emitterShape)
	{
	case emitterPoint: // If the emitter is a point emitter then randomise all planes
		position[0] = emitterPosition[0];
		position[0] += rand() % (emitterXMax - emitterXMin + 1) + emitterXMin;
		position[1] = emitterPosition[1];
		position[1] += rand() % (emitterYMax - emitterYMin + 1) + emitterYMin;
		position[2] = emitterPosition[2];
		position[2] += rand() % (emitterZMax - emitterZMin + 1) + emitterZMin;
		break;
	case emitterBox: // If the emitter is a box emitter then randomize in the XZ planes
		position[0] = emitterPosition[0];
		position[0] += rand() % (emitterXMax - emitterXMin + 1) + emitterXMin;
		position[1] = emitterPosition[1];
		position[2] = emitterPosition[2];
		position[2] += rand() % (emitterZMax - emitterZMin + 1) + emitterZMin;
		break;
	case emitterCircle: // Circle
		break;
	default:
		break;
	}

	/*position[0] = position[2] = 0.0f;
	position[1] = 0.0f;*/

	// create random direction
	direction[0] = (10000 - rand()%20000)/10000.0f;
	direction[1] = (10000 - rand()%20000)/10000.0f;
	direction[2] = (10000 - rand()%20000)/10000.0f;

	//// create random colour
	//colour[0] = 0.8f;
	//colour[1] = rand()%15000/20000.0f;
	//colour[2] = 0.1f;
	colour[0] = particleStartColour[0];
	colour[1] = particleStartColour[1];
	colour[2] = particleStartColour[2];
	colour[3] = 0.0f;

	// set a random lifespan
	fade = rand () % (int(particleMaximumFade) - int(particleMinimumFade) + 1) +
		int(particleMinimumFade);
	life = rand()%int(fade)/9500.0f;
	speed[0] = rand () % (int(particleSpeedMax[0]) - int(particleSpeedMin[0]) + 1) +
		int(particleSpeedMin[0]);
	speed[1] = rand () % (int(particleSpeedMax[1]) - int(particleSpeedMin[1]) + 1) +
		int(particleSpeedMin[1]);
	speed[2] = rand () % (int(particleSpeedMax[2]) - int(particleSpeedMin[2]) + 1) +
		int(particleSpeedMin[2]);
}

ParticleLines::ParticleLines()
{
	// set position
	///////// Add "jitter", this is for point emitter
	// x position, y position and z position = rand() % (upper_limit - lower_limit + 1) + lower_limit; 
	/////////
	///////// Add "jitter", this is for box emitter (e.g. rain, snow)
	// x position and z position = rand() % (upper_limit - lower_limit + 1) + lower_limit; 
	/////////

	switch (emitterShape)
	{
	case emitterPoint: // Point
		position[0] = emitterPosition[0];
		position[0] += rand() % (emitterXMax - emitterXMin + 1) + emitterXMin;
		position[1] = emitterPosition[1];
		position[1] += rand() % (emitterYMax - emitterYMin + 1) + emitterYMin;
		position[2] = emitterPosition[2];
		position[2] += rand() % (emitterZMax - emitterZMin + 1) + emitterZMin;
		position[3] = position[0]; // bottom x
		position[4] = position[1]; // bottom y
		position[5] = position[2]; // bottom z
		break;
	case emitterBox: // Box
		position[0] = emitterPosition[0];
		position[0] += rand() % (emitterXMax - emitterXMin + 1) + emitterXMin;
		position[1] = emitterPosition[1];
		position[2] = emitterPosition[2];
		position[2] += rand() % (emitterZMax - emitterZMin + 1) + emitterZMin;
		position[3] = position[0]; // bottom x
		position[4] = position[1]; //- particleHeight; // bottom y
		position[5] = position[2]; //- particleDepth; // bottom z
		break;
	case emitterCircle: // Circle
		break;
	default:
		break;
	}

	/*position[0] = position[2] = 0.0f;
	position[1] = 0.0f;*/

	// create random direction
	direction[0] = (10000 - rand()%20000)/10000.0f;
	direction[1] = (10000 - rand()%20000)/10000.0f;
	direction[2] = (10000 - rand()%20000)/10000.0f;

	//// create random colour
	//colour[0] = 0.8f;
	//colour[1] = rand()%15000/20000.0f;
	//colour[2] = 0.1f;
	colour[0] = particleStartColour[0];
	colour[1] = particleStartColour[1];
	colour[2] = particleStartColour[2];
	colour[3] = 0.0f;

	// set a random lifespan
	fade = rand () % (int(particleMaximumFade) - int(particleMinimumFade) + 1) +
		int(particleMinimumFade);
	life = rand()%int(fade)/9500.0f;
	speed[0] = rand () % (int(particleSpeedMax[0]) - int(particleSpeedMin[0]) + 1) +
		int(particleSpeedMin[0]);
	speed[1] = rand () % (int(particleSpeedMax[1]) - int(particleSpeedMin[1]) + 1) +
		int(particleSpeedMin[1]);
	speed[2] = rand () % (int(particleSpeedMax[2]) - int(particleSpeedMin[2]) + 1) +
		int(particleSpeedMin[2]);
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
	speed[0] = rand () % (int(particleSpeedMax[0]) - int(particleSpeedMin[0]) + 1) +
		int(particleSpeedMin[0]);
	speed[1] = rand () % (int(particleSpeedMax[1]) - int(particleSpeedMin[1]) + 1) +
		int(particleSpeedMin[1]);
	speed[2] = rand () % (int(particleSpeedMax[2]) - int(particleSpeedMin[2]) + 1) +
		int(particleSpeedMin[2]);
}

//------------------------------------------------------------	UpdateParticles()
//
template<typename T>
void UpdateParticles(float dt, T *&inStart, T *&inLast) {

	if ((timeLeft.getTime() <= emitterDurationSeconds) || (emitterRepeat))
	{
		// traverse all particles and update
		T* p = inStart;
		while(p!=inLast) {
			// decrease lifespan
			p->life -= dt;

			// if we have life left
			if (p->life>0.0f) {

				//{($end_r - $start_r) / $life}
				p->colour[0] = (particleEndColour[0] - particleStartColour[0]); // p->life;
				p->colour[1] = (particleEndColour[1] - particleStartColour[1]); // p->life;
				p->colour[2] = (particleEndColour[2] - particleStartColour[2]); // p->life;
				p->colour[3] = p->life;

				p->speed[0] += particleGravity[0] * dt;
				p->speed[1] += particleGravity[1] * dt;
				p->speed[2] += particleGravity[2] * dt;

				// apply gravity
				p->direction[0] -= (particleGravity[0]+p->speed[0])*dt;
				p->direction[1] -= (particleGravity[1]+p->speed[1])*dt;
				p->direction[2] -= (particleGravity[2]+p->speed[2])*dt;

				// modify position
				//// TODO:
				//// Take into account triangles will have more than 3 positions
				p->position[0] += dt * (p->direction[0]); // x TriangleTop
				p->position[1] += dt * (p->direction[1]); // y
				p->position[2] += dt * (p->direction[2]); // z

				if (particleShape == shapeLine) // update all vertices of the line
				{
					p->position[3] += dt * (p->direction[0]); // x
					p->position[4] += dt * (p->direction[1]); // y
					p->position[5] += dt * (p->direction[2]); // z 
				}

				if (particleShape == shapeTriangle) // update all vertices of the triangle
				{
					// Each set of vertices (012,345,etc) must go in the same direction
					// so 0 and 3 correspond to 0 (x), 1 and 4 correspond to 1 (y)
					// and 2 and 5 correspond to 2 (z).
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
	EMITTER_POSITIONXMIN_SPINNER,
	EMITTER_POSITIONXMAX_SPINNER,
	EMITTER_POSITIONYMIN_SPINNER,
	EMITTER_POSITIONYMAX_SPINNER,
	EMITTER_POSITIONZMIN_SPINNER,
	EMITTER_POSITIONZMAX_SPINNER,
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
	PARTICLE_SPEEDX_SPINNER_MIN,
	PARTICLE_SPEEDY_SPINNER_MIN,
	PARTICLE_SPEEDZ_SPINNER_MIN,
	PARTICLE_SPEEDX_SPINNER_MAX,
	PARTICLE_SPEEDY_SPINNER_MAX,
	PARTICLE_SPEEDZ_SPINNER_MAX,
	PARTICLE_FADEMINIMUM_SPINNER,
	PARTICLE_FADEMAXIMUM_SPINNER,
	PRESET_PRESETS_LISTBOX,
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
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glShadeModel(GL_SMOOTH);						// Enables Smooth Shading
	//glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
	//glClearDepth(1.0f);							// Depth Buffer Setup
	////glDisable(GL_DEPTH_TEST);						// Disables Depth Testing
	glEnable(GL_BLEND);							// Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);					// Type Of Blending To Perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);			// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);					// Really Nice Point Smoothing
	//glDisable(GL_TEXTURE_2D);						// Enable Texture Mapping

	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// set the maximum number of particles
	SetSize(emitterMaximumParticles, start, last, end);


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
			for(int i=0;i!=val;++i)
				AddOne(lastLines);
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
			UpdateParticles(FrameTime(), startLines, lastLines);
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
	// Number of Particles on the screen
	char particleString[30];

	int numberParticles = (int)(last-start);
	sprintf_s(particleString, "Particles: %i", numberParticles); // Print the fps
	glColor3f(1.0f,0.0f,0.0f);
	renderBitmapString(-5, 1, GLUT_BITMAP_HELVETICA_18, particleString);
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
	// 'Preset Properties' Panel
	//---------------------------------------------------------------------

	//  Add the 'Preset Properties' Panel to the GLUI window
	GLUI_Panel *prp_rollout = glui_window->add_rollout ("Preset Properties");

	//  Add the Preset listbox to the 'Preset Properties' Panel
	presetListBox = glui_window->add_listbox_to_panel (prp_rollout, 
		"Presets", &presetListBoxItemId, PRESET_PRESETS_LISTBOX, glui_callback);

	//  Add the items to the listbox
	presetListBox->add_item (1, "Snow");
	presetListBox->add_item (2, "Rain");

	//  Select Snow by default
	presetListBox->set_int_val (presetSnow);

	//  Add a separator
	glui_window->add_separator_to_panel (prp_rollout);


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
	emitterShapeListbox->add_item (2, "Box");
	emitterShapeListbox->add_item (3, "Circle");

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
	emitterPositionXEditText = glui_window->add_spinner_to_panel(ep_rollout,
		"PositionX:", GLUI_SPINNER_INT, &emitterPosition[0], EMITTER_POSITIONX_EDITABLETEXT,
			glui_callback);

	// Add the PositionY EditText to the 'Emitter Properties' Panel
	emitterPositionYEditText = glui_window->add_spinner_to_panel(ep_rollout,
		"PositionY:", GLUI_SPINNER_INT, &emitterPosition[1], EMITTER_POSITIONY_EDITABLETEXT,
		glui_callback);

	// Add the PositionZ EditText to the 'Emitter Properties' Panel
	emitterPositionZEditText = glui_window->add_spinner_to_panel(ep_rollout,
		"PositionZ:", GLUI_SPINNER_INT, &emitterPosition[2], EMITTER_POSITIONZ_EDITABLETEXT,
		glui_callback);

	// Add the PositionXMin Spinner to the 'Emitter Properties' Panel
	emitterPositionXMinSpinner = glui_window->add_spinner_to_panel(ep_rollout,
		"Position X Min:", GLUI_SPINNER_INT, &emitterXMin, EMITTER_POSITIONXMIN_SPINNER,
		glui_callback);

	// Add the PositionXMax Spinner to the 'Emitter Properties' Panel
	emitterPositionXMaxSpinner = glui_window->add_spinner_to_panel(ep_rollout,
		"Position X Max:", GLUI_SPINNER_INT, &emitterXMax, EMITTER_POSITIONXMAX_SPINNER,
		glui_callback);

	// Add the PositionYMin Spinner to the 'Emitter Properties' Panel
	emitterPositionYMinSpinner = glui_window->add_spinner_to_panel(ep_rollout,
		"Position Y Min:", GLUI_SPINNER_INT, &emitterYMin, EMITTER_POSITIONYMIN_SPINNER,
		glui_callback);

	// Add the PositionYMax Spinner to the 'Emitter Properties' Panel
	emitterPositionYMaxSpinner = glui_window->add_spinner_to_panel(ep_rollout,
		"Position Y Max:", GLUI_SPINNER_INT, &emitterYMax, EMITTER_POSITIONYMAX_SPINNER,
		glui_callback);

	// Add the PositionZMin Spinner to the 'Emitter Properties' Panel
	emitterPositionZMinSpinner = glui_window->add_spinner_to_panel(ep_rollout,
		"Position Z Min:", GLUI_SPINNER_INT, &emitterZMin, EMITTER_POSITIONZMIN_SPINNER,
		glui_callback);

	// Add the PositionXMax Spinner to the 'Emitter Properties' Panel
	emitterPositionZMaxSpinner = glui_window->add_spinner_to_panel(ep_rollout,
		"Position Z Max:", GLUI_SPINNER_INT, &emitterZMax, EMITTER_POSITIONZMAX_SPINNER,
		glui_callback);

	//  Add a separator
	glui_window->add_separator_to_panel (ep_rollout);

	// Add the MaximumParticles EditText to the 'Emitter Properties' Panel
	emitterMaximumParticlesEditText = glui_window->add_spinner_to_panel(ep_rollout,
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
		"Start Colour Red:", GLUI_SPINNER_FLOAT, &particleStartColour[0], PARTICLE_STARTCOLOURRED_SPINNER,
			glui_callback);

	// Add the StartColourGreen to the 'Particle Properties' panel
	particleStartColourGreenSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Start Colour Green:", GLUI_SPINNER_FLOAT, &particleStartColour[1], PARTICLE_STARTCOLOURGREEN_SPINNER,
			glui_callback);

	// Add the StartColourBlue to the 'Particle Properties' panel
	particleStartColourBlueSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Start Colour Blue:", GLUI_SPINNER_FLOAT, &particleStartColour[2], PARTICLE_STARTCOLOURBLUE_SPINNER,
			glui_callback);

	// Add the EndColourRed to the 'Particle Properties' panel
	particleEndColourRedSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"End Colour Red:", GLUI_SPINNER_FLOAT, &particleEndColour[0], PARTICLE_ENDCOLOURRED_SPINNER,
			glui_callback);

	// Add the EndColourGreen to the 'Particle Properties' panel
	particleEndColourGreenSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"End Colour Green:", GLUI_SPINNER_FLOAT, &particleEndColour[1], PARTICLE_ENDCOLOURGREEN_SPINNER,
			glui_callback);

	// Add the EndColourBlue to the 'Particle Properties' panel
	particleEndColourBlueSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"End Colour Blue:", GLUI_SPINNER_FLOAT, &particleEndColour[2], PARTICLE_ENDCOLOURBLUE_SPINNER,
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

	// Add the SpeedX Min Spinner to the 'Particle Properties' panel
	particleSpeedXSpinnerMin = glui_window->add_spinner_to_panel(pp_rollout,
		"Speed X Min:", GLUI_SPINNER_FLOAT, &particleSpeedMin[0], PARTICLE_SPEEDX_SPINNER_MIN, glui_callback);

	// Add the SpeedX Max Spinner to the 'Particle Properties' panel
	particleSpeedXSpinnerMax = glui_window->add_spinner_to_panel(pp_rollout,
		"Speed X Max:", GLUI_SPINNER_FLOAT, &particleSpeedMax[0], PARTICLE_SPEEDX_SPINNER_MIN, glui_callback);

	// Add the SpeedY Min Spinner to the 'Particle Properties' panel
	particleSpeedYSpinnerMin = glui_window->add_spinner_to_panel(pp_rollout,
		"Speed Y Min:", GLUI_SPINNER_FLOAT, &particleSpeedMin[1], PARTICLE_SPEEDY_SPINNER_MIN, glui_callback);

	// Add the SpeedY Max Spinner to the 'Particle Properties' panel
	particleSpeedYSpinnerMax = glui_window->add_spinner_to_panel(pp_rollout,
		"Speed Y Max:", GLUI_SPINNER_FLOAT, &particleSpeedMax[1], PARTICLE_SPEEDY_SPINNER_MAX, glui_callback);

	// Add the SpeedZ Min Spinner to the 'Particle Properties' panel
	particleSpeedZSpinnerMin = glui_window->add_spinner_to_panel(pp_rollout,
		"Speed Z Min:", GLUI_SPINNER_FLOAT, &particleSpeedMin[2], PARTICLE_SPEEDZ_SPINNER_MAX, glui_callback);

	// Add the SpeedZ Max Spinner to the 'Particle Properties' panel
	particleSpeedZSpinnerMax = glui_window->add_spinner_to_panel(pp_rollout,
		"Speed Z Max:", GLUI_SPINNER_FLOAT, &particleSpeedMax[2], PARTICLE_SPEEDZ_SPINNER_MAX, glui_callback);

	//  Add a separator
	glui_window->add_separator_to_panel (pp_rollout);

	// Add the FadeMinimum to the 'Particle Properties' panel
	particleFadeMinimumSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Fade Minimum:", GLUI_SPINNER_FLOAT, &particleMinimumFade, PARTICLE_FADEMINIMUM_SPINNER,
			glui_callback);

	// Add the FadeMaximum to the 'Particle Properties' panel
	particleFadeMaximumSpinner = glui_window->add_spinner_to_panel(pp_rollout,
		"Fade Maximum:", GLUI_SPINNER_FLOAT, &particleMaximumFade, PARTICLE_FADEMAXIMUM_SPINNER,
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
				case 1:
					emitterShape = emitterPoint;
					break;
				case 2:
					emitterShape = emitterBox;
					break;
				case 3:	
					emitterShape = emitterCircle;
					break;
				default:
					break;
			}

			printf ("Item %d selected.\n", emitterShapeListboxItemId);

		break;

		case PARTICLE_STARTCOLOURRED_SPINNER:
			// error checking - don't want min values to exceed max values
			if (!(particleStartColourRedSpinner->get_float_val() <
				1.0f))
			{
				particleStartColour[0] = 1.0f;
				particleStartColourRedSpinner->set_float_val(1.0f);
			}
			if (particleStartColourRedSpinner->get_float_val() < 0.0f)
			{
				particleStartColour[0] = 0.0f;
				particleStartColourRedSpinner->set_float_val(0.0f);
			}
			break;

		case PARTICLE_STARTCOLOURGREEN_SPINNER:
			// error checking - don't want min values to exceed max values
			if (!(particleStartColourGreenSpinner->get_float_val() <
				1.0f))
			{
				particleStartColour[1] = 1.0f;
				particleStartColourGreenSpinner->set_float_val(1.0f);
			}
			if (particleStartColourGreenSpinner->get_float_val() < 0.0f)
			{
				particleStartColour[1] = 0.0f;
				particleStartColourGreenSpinner->set_float_val(0.0f);
			}
			break;

		case PARTICLE_STARTCOLOURBLUE_SPINNER:
			// error checking - don't want min values to exceed max values
			if (!(particleStartColourBlueSpinner->get_float_val() <
				1.0f))
			{
				particleStartColour[2] = 1.0f;
				particleStartColourBlueSpinner->set_float_val(1.0f);
			}
			if (particleStartColourBlueSpinner->get_float_val() < 0.0f)
			{
				particleStartColour[2] = 0.0f;
				particleStartColourBlueSpinner->set_float_val(0.0f);
			}
			break;

		case PARTICLE_ENDCOLOURRED_SPINNER:
			// error checking - don't want min values to exceed max values
			if (!(particleEndColourRedSpinner->get_float_val() <
				1.0f))
			{
				particleEndColour[0] = 1.0f;
				particleEndColourRedSpinner->set_float_val(1.0f);
			}
			if (particleEndColourRedSpinner->get_float_val() < 0.0f)
			{
				particleEndColour[0] = 0.0f;
				particleEndColourRedSpinner->set_float_val(0.0f);
			}
			break;

		case PARTICLE_ENDCOLOURGREEN_SPINNER:
			// error checking - don't want min values to exceed max values
			if (!(particleEndColourGreenSpinner->get_float_val() <
				1.0f))
			{
				particleEndColour[1] = 1.0f;
				particleEndColourGreenSpinner->set_float_val(1.0f);
			}
			if (particleEndColourGreenSpinner->get_float_val() < 0.0f)
			{
				particleEndColour[1] = 0.0f;
				particleEndColourGreenSpinner->set_float_val(0.0f);
			}
			break;

		case PARTICLE_ENDCOLOURBLUE_SPINNER:
			// error checking - don't want min values to exceed max values
			if (!(particleEndColourBlueSpinner->get_float_val() <
				1.0f))
			{
				particleEndColour[2] = 1.0f;
				particleEndColourBlueSpinner->set_float_val(1.0f);
			}
			if (particleEndColourBlueSpinner->get_float_val() < 0.0f)
			{
				particleEndColour[2] = 0.0f;
				particleEndColourBlueSpinner->set_float_val(0.0f);
			}
			break;

		case PARTICLE_HEIGHT_SPINNER:
			// error checking - don't want a size lower than 1
			if (particleHeightSpinner->get_int_val() < 1)
			{
				particleHeight++;
				particleHeightSpinner->set_int_val(particleHeight);
			}

		case PARTICLE_WIDTH_SPINNER:
			// error checking - don't want a size lower than 1
			if (particleWidthSpinner->get_int_val() < 1)
			{
				particleWidth++;
				particleWidthSpinner->set_int_val(particleWidth);
			}

		case PARTICLE_DEPTH_SPINNER:
			// error checking - don't want a size lower than 1
			if (particleDepthSpinner->get_int_val() < 1)
			{
				particleDepth++;
				particleDepthSpinner->set_int_val(particleDepth);
			}

		case EMITTER_POSITIONXMIN_SPINNER:
			// error checking - don't want min values to exceed max values
			if (emitterPositionXMinSpinner->get_int_val() > emitterPositionXMaxSpinner->get_int_val())
			{
				emitterXMin -= 1;
				emitterPositionXMinSpinner->set_int_val(emitterXMin);
			}

		case EMITTER_POSITIONXMAX_SPINNER:
			// error checking - don't want max values to be below min values
			if (emitterPositionXMaxSpinner->get_int_val() < emitterPositionXMinSpinner->get_int_val())
			{
				emitterXMax += 1;
				emitterPositionXMaxSpinner->set_int_val(emitterXMax);
			}

		case EMITTER_POSITIONYMIN_SPINNER:
			// error checking - don't want min values to exceed max values
			if (emitterPositionYMinSpinner->get_int_val() > emitterPositionYMaxSpinner->get_int_val())
			{
				emitterYMin -= 1;
				emitterPositionYMinSpinner->set_int_val(emitterYMin);
			}

		case EMITTER_POSITIONYMAX_SPINNER:
			// error checking - don't want max values to be below min values
			if (emitterPositionYMaxSpinner->get_int_val() < emitterPositionYMinSpinner->get_int_val())
			{
				emitterYMax += 1;
				emitterPositionYMaxSpinner->set_int_val(emitterYMax);
			}

		case EMITTER_POSITIONZMIN_SPINNER:
			// error checking - don't want min values to exceed max values
			if (emitterPositionZMinSpinner->get_int_val() > emitterPositionZMaxSpinner->get_int_val())
			{
				emitterZMin -= 1;
				emitterPositionZMinSpinner->set_int_val(emitterZMin);
			}

		case EMITTER_POSITIONZMAX_SPINNER:
			// error checking - don't want max values to be below min values
			if (emitterPositionZMaxSpinner->get_int_val() < emitterPositionZMinSpinner->get_int_val())
			{
				emitterZMax += 1;
				emitterPositionZMaxSpinner->set_int_val(emitterZMax);
			}

		case PARTICLE_GRAVITYX_SPINNER:
			particleGravity[0] = particleGravityXSpinner->get_float_val();
			break;
		case PARTICLE_GRAVITYY_SPINNER:
			particleGravity[1] = particleGravityYSpinner->get_float_val();
			break;
		case PARTICLE_GRAVITYZ_SPINNER:
			particleGravity[2] = particleGravityZSpinner->get_float_val();
			break;

		case PARTICLE_FADEMINIMUM_SPINNER:
			// error checking - don't want min values to exceed max values
			if (!(particleFadeMinimumSpinner->get_float_val() >
				particleFadeMaximumSpinner->get_float_val()))
			{
				particleMinimumFade = particleFadeMinimumSpinner->get_float_val();
			}
			else
			{
				particleFadeMinimumSpinner->set_float_val(particleFadeMaximumSpinner->get_float_val());
			}
			break;

		case PARTICLE_FADEMAXIMUM_SPINNER:
			particleMaximumFade = particleFadeMaximumSpinner->get_float_val();
			break;

		case PARTICLE_SPEEDX_SPINNER_MIN:
			// error checking - don't want min values to exceed max values
			if (!(particleSpeedXSpinnerMin->get_float_val() > particleSpeedXSpinnerMax->get_float_val()))
			{
				particleSpeedMin[0] = particleSpeedXSpinnerMin->get_float_val();
			}
			else
			{
				particleSpeedXSpinnerMin->set_float_val(particleSpeedXSpinnerMax->get_float_val());
			}
			break;
		case PARTICLE_SPEEDY_SPINNER_MIN:
			if (!(particleSpeedYSpinnerMin->get_float_val() > particleSpeedYSpinnerMax->get_float_val()))
			{
				particleSpeedMin[1] = particleSpeedYSpinnerMin->get_float_val();
			}
			else
			{
				particleSpeedYSpinnerMin->set_float_val(particleSpeedYSpinnerMax->get_float_val());
			}
			break;
		case PARTICLE_SPEEDZ_SPINNER_MIN:
			if (!(particleSpeedZSpinnerMin->get_float_val() > particleSpeedZSpinnerMax->get_float_val()))
			{
				particleSpeedMin[2] = particleSpeedZSpinnerMin->get_float_val();
			}
			else
			{
				particleSpeedZSpinnerMin->set_float_val(particleSpeedZSpinnerMax->get_float_val());
			}
			break;

		case PARTICLE_SPEEDX_SPINNER_MAX:
			particleSpeedMax[0] = particleSpeedXSpinnerMax->get_int_val();
			break;
		case PARTICLE_SPEEDY_SPINNER_MAX:
			particleSpeedMax[1] = particleSpeedYSpinnerMax->get_int_val();
			break;
		case PARTICLE_SPEEDZ_SPINNER_MAX:
			particleSpeedMax[2] = particleSpeedZSpinnerMax->get_int_val();
			break;

		case PARTICLE_SHAPE_LISTBOX:
			/*particleShapeListbox->add_item (1, "Point");
			particleShapeListbox->add_item (2, "Line");
			particleShapeListbox->add_item (3, "Triangle");*/
			switch(particleShapeListboxItemId)
			{
				case 1:
					SetParticleType(start, last, end);
					SetSize(emitterMaximumParticles, start, last, end);
					particleShape = shapePoint;
					break;
				case 2:
					SetParticleType(startLines, lastLines, endLines);
					SetSize(emitterMaximumParticles, startLines, lastLines, endLines);
					particleShape = shapeLine;
					break;
				case 3:
					SetParticleType(startTriangles, lastTriangles, endTriangles);
					SetSize(emitterMaximumParticles, startTriangles, lastTriangles, endTriangles);
					particleShape = shapeTriangle;
					break;
				default:
					break;
			}
			break;
			
		case PARTICLE_BLENDINGMODE_LISTBOX:
			switch (particleBlendingModeListboxItemId)
			{
				case 1: // 1 = filtered
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					break;
				case 2: // 2 = additive
					glBlendFunc(GL_SRC_ALPHA,GL_ONE);
					break;
			}
			break;

		case EMITTER_DURATIONSECONDS_SPINNER:
			// error checking - don't want lower than 1 seconds
			if (emitterDurationSecondsSpinner->get_int_val() < 1)
			{
				emitterDurationSeconds++;
				emitterDurationSecondsSpinner->set_int_val(emitterDurationSeconds);
			}
			if(!emitterRepeat) // No point doing anything if the repeat is set to true
			{
				timeLeft.start();
				timeLeft.reset();
				switch(particleShapeListboxItemId)
				{
				case 1:
					SetParticleType(start, last, end);
					SetSize(emitterMaximumParticles, start, last, end);
					particleShape = shapePoint;
					break;
				case 2:
					SetParticleType(startLines, lastLines, endLines);
					SetSize(emitterMaximumParticles, startLines, lastLines, endLines);
					particleShape = shapeLine;
					break;
				case 3:
					SetParticleType(startTriangles, lastTriangles, endTriangles);
					SetSize(emitterMaximumParticles, startTriangles, lastTriangles, endTriangles);
					particleShape = shapeTriangle;
					break;
				}
			}
			break;

		case EMITTER_REPEAT_CHECKBOX:
			{
				if (!emitterRepeat)
				{
					timeLeft.start();
					timeLeft.reset();
					switch(particleShapeListboxItemId)
					{
					case 1:
						SetParticleType(start, last, end);
						SetSize(emitterMaximumParticles, start, last, end);
						particleShape = shapePoint;
						break;
					case 2:
						SetParticleType(startLines, lastLines, endLines);
						SetSize(emitterMaximumParticles, startLines, lastLines, endLines);
						particleShape = shapeLine;
						break;
					case 3:
						SetParticleType(startTriangles, lastTriangles, endTriangles);
						SetSize(emitterMaximumParticles, startTriangles, lastTriangles, endTriangles);
						particleShape = shapeTriangle;
						break;
					}
				}
			}

		case EMITTER_MAXIMUMPARTICLES_EDITABLETEXT:
			// error checking - don't want lower than 1 particle
			if (emitterMaximumParticlesEditText->get_int_val() < 1)
			{
				emitterMaximumParticles++;
				emitterMaximumParticlesEditText->set_int_val(emitterMaximumParticles);
			}
			else
			{
				switch(particleShapeListboxItemId)
				{
				case 1:
					SetParticleType(start, last, end);
					SetSize(emitterMaximumParticles, start, last, end);
					particleShape = shapePoint;
					break;
				case 2:
					SetParticleType(startLines, lastLines, endLines);
					SetSize(emitterMaximumParticles, startLines, lastLines, endLines);
					particleShape = shapeLine;
					break;
				case 3:
					SetParticleType(startTriangles, lastTriangles, endTriangles);
					SetSize(emitterMaximumParticles, startTriangles, lastTriangles, endTriangles);
					particleShape = shapeTriangle;
					break;
				default:
					break;
				}
				break;
			}


		case PRESET_PRESETS_LISTBOX:
			switch (presetListBoxItemId)
			{
				case presetSnow:
					emitterShape = emitterBox;
					emitterShapeListboxItemId = emitterBox;
					emitterPositionXMinSpinner->set_int_val(-2);
					emitterPositionXMaxSpinner->set_int_val(2);
					emitterPositionYMinSpinner->set_int_val(0);
					emitterPositionYMaxSpinner->set_int_val(0);
					emitterPositionZMinSpinner->set_int_val(0);
					emitterPositionZMaxSpinner->set_int_val(3);
					emitterPositionXEditText->set_int_val(0);
					emitterPositionYEditText->set_int_val(2);
					emitterPositionZEditText->set_int_val(0);
					// Height Width and Depth need adding
					particleShape = shapePoint;
					particleShapeListboxItemId = shapePoint;
					// Width and Depth need adding
					particleHeightSpinner->set_int_val(2);
					particleBlendingModeListboxItemId = 1;
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					particleStartColour[0] = 0.0f;
					particleStartColour[1] = 0.0f;
					particleStartColour[2] = 0.0f;
					particleEndColour[0] = 1.0f;
					particleEndColour[1] = 1.0f;
					particleEndColour[2] = 1.0f;
					particleStartColourRedSpinner->set_float_val(particleStartColour[0]);
					particleStartColourGreenSpinner->set_float_val(particleStartColour[1]);
					particleStartColourBlueSpinner->set_float_val(particleStartColour[2]);
					particleEndColourRedSpinner->set_float_val(particleEndColour[0]);
					particleEndColourGreenSpinner->set_float_val(particleEndColour[1]);
					particleEndColourBlueSpinner->set_float_val(particleEndColour[2]);
					particleGravity[0] = 0.0f;
					particleGravity[1] = 1.31f;
					particleGravity[2] = 0.0f;
					particleGravityXSpinner->set_float_val(particleGravity[0]);
					particleGravityYSpinner->set_float_val(particleGravity[1]);
					particleGravityZSpinner->set_float_val(particleGravity[2]);
					particleSpeedMin[0] = 0.0f;
					particleSpeedMin[1] = 0.0f;
					particleSpeedMin[2] = 0.0f;
					particleSpeedMax[0] = 0.0f;
					particleSpeedMax[1] = 0.0f;
					particleSpeedMax[2] = 0.0f;
					particleSpeedXSpinnerMin->set_float_val(particleSpeedMin[0]);
					particleSpeedXSpinnerMax->set_float_val(particleSpeedMax[0]);
					particleSpeedYSpinnerMin->set_float_val(particleSpeedMin[1]);
					particleSpeedYSpinnerMax->set_float_val(particleSpeedMax[1]);
					particleSpeedZSpinnerMin->set_float_val(particleSpeedMin[2]);
					particleSpeedZSpinnerMax->set_float_val(particleSpeedMax[2]);
					particleMinimumFade = 30000.0f;
					particleMaximumFade = 30000.0f;
					particleFadeMinimumSpinner->set_float_val(particleMinimumFade);
					particleFadeMaximumSpinner->set_float_val(particleMaximumFade);
					glui_window->sync_live();
					break;
				case presetRain:
					emitterShape = emitterBox;
					emitterShapeListboxItemId = emitterBox;
					emitterPositionXMinSpinner->set_int_val(-2);
					emitterPositionXMaxSpinner->set_int_val(2);
					emitterPositionYMinSpinner->set_int_val(0);
					emitterPositionYMaxSpinner->set_int_val(0);
					emitterPositionZMinSpinner->set_int_val(0);
					emitterPositionZMaxSpinner->set_int_val(3);
					emitterPositionXEditText->set_int_val(0);
					emitterPositionYEditText->set_int_val(2);
					emitterPositionZEditText->set_int_val(0);
					// Height Width and Depth need adding
					// Maximum Particles need adding
					// Duration in seconds need adding
					// Repeat need adding
					particleShape = shapePoint;
					particleShapeListboxItemId = shapePoint;
					// Width and Depth need adding
					particleHeightSpinner->set_int_val(2);
					particleBlendingModeListboxItemId = 1;
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					particleStartColour[0] = 0.0f;
					particleStartColour[1] = 0.0f;
					particleStartColour[2] = 0.0f;
					particleEndColour[0] = 0.196100f;
					particleEndColour[1] = 0.600000f;
					particleEndColour[2] = 0.800000f;
					particleStartColourRedSpinner->set_float_val(particleStartColour[0]);
					particleStartColourGreenSpinner->set_float_val(particleStartColour[1]);
					particleStartColourBlueSpinner->set_float_val(particleStartColour[2]);
					particleEndColourRedSpinner->set_float_val(particleEndColour[0]);
					particleEndColourGreenSpinner->set_float_val(particleEndColour[1]);
					particleEndColourBlueSpinner->set_float_val(particleEndColour[2]);
					particleGravity[0] = 0.0f;
					particleGravity[1] = 1.31f;
					particleGravity[2] = 0.0f;
					particleGravityXSpinner->set_float_val(particleGravity[0]);
					particleGravityYSpinner->set_float_val(particleGravity[1]);
					particleGravityZSpinner->set_float_val(particleGravity[2]);
					particleSpeedMin[0] = 0.0f;
					particleSpeedMin[1] = 0.0f;
					particleSpeedMin[2] = 0.0f;
					particleSpeedMax[0] = 0.0f;
					particleSpeedMax[1] = 0.0f;
					particleSpeedMax[2] = 0.0f;
					particleSpeedXSpinnerMin->set_float_val(particleSpeedMin[0]);
					particleSpeedXSpinnerMax->set_float_val(particleSpeedMax[0]);
					particleSpeedYSpinnerMin->set_float_val(particleSpeedMin[1]);
					particleSpeedYSpinnerMax->set_float_val(particleSpeedMax[1]);
					particleSpeedZSpinnerMin->set_float_val(particleSpeedMin[2]);
					particleSpeedZSpinnerMax->set_float_val(particleSpeedMax[2]);
					particleMinimumFade = 30000.0f;
					particleMaximumFade = 30000.0f;
					particleFadeMinimumSpinner->set_float_val(particleMinimumFade);
					particleFadeMaximumSpinner->set_float_val(particleMaximumFade);
					glui_window->sync_live();
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