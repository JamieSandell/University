//From cygwin version of Nehe tutorial lesson 3

// This code was created by Jeff Molofee '99 (ported to Linux/GLUT by Richard Campbell '99)
//
// If you've found this code useful, please let me know.
//
// Visit me at www.demonews.com/hosted/nehe 
// (email Richard Campbell at ulmont@bellsouth.net)
//

// this was modified to work on PSP by Edorul (edorul@free.fr)
// Many Thanks to  jared bruni (jared@lostsidedead.com) for is
// MasterPiece3D port to PSP : it gave me a good sample and not
// the least a working makefile !

// important notes :  - all modified portion of code from cygwin version
//                                  of Nehe tutorial are marked with @@@

// Used keys :
// START = exit 


#include <stdlib.h> // needed in order to have "exit" function @@@

#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include "FrameTimer.h"
#include "CTimer.h"
//#include <unistd.h>     // Header File for sleeping.@@@

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
int emitterPosition[] = {0, 0, 0}; // x,y,z
int emitterXMin = 0;
int emitterXMax = 3;
int emitterYMin = 0;
int emitterYMax = 0;
int emitterZMin = 0;
int emitterZMax = 3;
int emitterMaximumParticles = 1000;
int emitterDurationSeconds = 1;
int emitterRepeat = true;
int particleShapeListboxItemId = 1;
int particleHeight = 5;
int particleWidth = 5;
int particleDepth = 5;
int particleBlendingModeListboxItemId = 1;
int particleStartColour[] = {0, 0, 0};
int particleEndColour[] = {255, 255, 255};
int particleRandomColour = false;
float particleGravity[] = {0.0, 1.31, 0.0}; // x,y,z
float particleSpeedMin[] = {0.0, 0.0, 0.0}; // x,y,z
float particleSpeedMax[] = {0.0, 0.0, 0.0}; // x,y,z
float particleMinimumFade = 30000.0;
float particleMaximumFade = 30000.0;
bool reset = true; // use this to set the initial colours of the particles
char  filename[1025]; // for the file operations

double dt;
CTimer timer;
int frames = 0;
char fps[100];

// an array of RGB components
unsigned char color[] = { 255, 255, 255 };

struct ParticlePointsVertex{
	unsigned char colour[4];
	float position[3];
};



struct ParticlePointsState{
	/// the direction of the particle
	float direction[3];

	/// the lifespan
	float life;

	/// speed to act against gravity
	float speed[3];
	float fade;

	/*struct ParticlePointsVertex *vtx;*/
	ParticlePointsState();
};

ParticlePointsState::ParticlePointsState()
{
	//vtx = (struct ParticlePointsVertex *)malloc(sizeof(struct ParticlePointsVertex));
	
	// set position
	///////// Add "jitter", this is for point emitter
	// x position, y position and z position = rand() % (upper_limit - lower_limit + 1) + lower_limit; 
	/////////
	///////// Add "jitter", this is for box emitter (e.g. rain, snow)
	// x position and z position = rand() % (upper_limit - lower_limit + 1) + lower_limit; 
	/////////

	switch (emitterShapeListboxItemId)
	{
	case 1: //emitterPoint: // If the emitter is a point emitter then randomise all planes
		//this->vtx->position[0] = emitterPosition[0];
		//this->vtx->position[0] += rand() % (emitterXMax - emitterXMin + 1) + emitterXMin;
		//this->vtx->position[1] = emitterPosition[1];
		//this->vtx->position[1] += rand() % (emitterYMax - emitterYMin + 1) + emitterYMin;
		//this->vtx->position[2] = emitterPosition[2];
		//this->vtx->position[2] += rand() % (emitterZMax - emitterZMin + 1) + emitterZMin;
		break;
	case 2: //emitterBox: // If the emitter is a box emitter then randomize in the XZ planes
		//this->vtx->position[0] = emitterPosition[0];
		//this->vtx->position[0] += rand() % (emitterXMax - emitterXMin + 1) + emitterXMin;
		//this->vtx->position[1] = emitterPosition[1];
		//this->vtx->position[2] = emitterPosition[2];
		//this->vtx->position[2] += rand() % (emitterZMax - emitterZMin + 1) + emitterZMin;
		break;
	case 3: //emitterCircle: // Circle
		break;
	default:
		break;
	}

	/*position[0] = position[2] = 0.0f;
	position[1] = 0.0f;*/

	// create random direction
	this->direction[0] = (10000 - rand()%20000)/10000.0f;
	this->direction[1] = (10000 - rand()%20000)/10000.0f;
	this->direction[2] = (10000 - rand()%20000)/10000.0f;

	//// create random colour
	//colour[0] = 0.8f;
	//colour[1] = rand()%15000/20000.0f;
	//colour[2] = 0.1f;
	//this->vtx->colour[0] = particleStartColour[0];
	//this->vtx->colour[1] = particleStartColour[1];
	//this->vtx->colour[2] = particleStartColour[2];
	//this->vtx->colour[3] = 0.0f;

	// set a random lifespan
	this->fade = rand () % (int(particleMaximumFade) - int(particleMinimumFade) + 1) +
		int(particleMinimumFade);
	this->life = rand()%int(this->fade)/9500.0f;
	this->speed[0] = rand () % (int(particleSpeedMax[0]) - int(particleSpeedMin[0]) + 1) +
		int(particleSpeedMin[0]);
	this->speed[1] = rand () % (int(particleSpeedMax[1]) - int(particleSpeedMin[1]) + 1) +
		int(particleSpeedMin[1]);
	this->speed[2] = rand () % (int(particleSpeedMax[2]) - int(particleSpeedMin[2]) + 1) +
		int(particleSpeedMin[2]);
}
/// the first particle in the linked list
ParticlePointsState* startPoints=0;

/// the next free particle
ParticlePointsState* lastPoints=0;

/// the end of the memory allocation
ParticlePointsState* endPoints=0;

ParticlePointsVertex* startPointsVertex = 0;
ParticlePointsVertex* lastPointsVertex = 0;
ParticlePointsVertex* endPointsVertex = 0;

/// Sets the type of the particle, e.g. start, last, end become pointers to ParticleTriangles
template<typename T, typename Y>
void SetParticleType(T *&inStart, T *&inLast, T *&inEnd, Y *&inStartVertex, Y *&inLastVertex,
					 Y *&inEndVertex)
{

	T* start = 0;
	T* last = 0;
	T* end = 0;
	inStart = start;
	inLast = last;
	inEnd = end;

	Y* startV = 0;
	Y* lastV = 0;
	Y* endV = 0;
	inStartVertex = startV;
	inLastVertex = lastV;
	inEndVertex = endV;
}

//------------------------------------------------------------	SetSize()
//
//	Allocates the static global particle buffer
//
template<typename T, typename Y>
void SetSize(unsigned int size, T *&inStart, T *&inLast, T *&inEnd, Y *&inStartVertex, Y *&inLastVertex,
			 Y *&inEndVertex) {

	// delete any previous data
	delete [] inStart;
	delete [] inStartVertex;

	// allocate new particles
	inLast = inStart = new T[size];
	inLastVertex = inStartVertex = new Y[size];

	// set end
	inEnd = inStart+size;
	inEndVertex = inStartVertex+size;
}


//------------------------------------------------------------	IsEmpty()
//
//	returns true if the particle array is empty
//
template<typename T>
inline bool IsEmpty(T *&inStart, T *&inLast) {
	return inStart==inLast; // if start equals last then it must be empty
}

//------------------------------------------------------------	IsFull()
//
//	returns true if the array is full
//
inline bool IsFull() {
	switch(particleShapeListboxItemId)
	{
		case 1: //shapePoint: // Points
			return lastPoints==endPoints;
			break;
		default:
			break;
	}
}

//------------------------------------------------------------	DrawParticles()
//
void DrawParticles() {
     
     //timer.IncreaseFramesPerSec();
     //frames = timer.GetFramesPerSec();
     //sprintf(fps, "FPS: %d", frames);
     

	if (!emitterRepeat) // if the repeat option isn't ticked then
						// check that there is still time remaining
	{
		//if (timeLeft.getTime() > emitterDurationSeconds)
		//{
			//return; // No time remaining so don't draw any particles
		//}
	}
	if (particleShapeListboxItemId==1)
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
		glDisable(GL_TEXTURE_2D);
		//glPointSize((float)particleHeight);
		glVertexPointer(3,GL_FLOAT,sizeof(ParticlePointsVertex),startPointsVertex->position);
		glColorPointer(4,GL_UNSIGNED_BYTE,sizeof(ParticlePointsVertex),startPointsVertex->colour);

		// draw the particles in one lovely function call. Note that 
		// this is faster than glBegin/glEnd() because it avoids the 
		// large amount of function call overhead.
		//
		glDrawArrays(GL_POINTS,0,lastPointsVertex-startPointsVertex);

	}
}


//------------------------------------------------------------	AddOne()
// this function 'adds' a particle into the array. In actual
// fact, all it does is move the pointer to the last element
// along by one position. This means we have not performed an
// expensive memory allocation.
//
template<typename T, typename Y>
void AddOne(T *&inLast, Y *&inLastVertex) {

	// if we have no more memory left for any particles, ignore
	// the request to creat one.
	if (!IsFull()) {
		*inLast = T();
		++inLast;
		*inLastVertex = Y();
		++inLastVertex;
	}
}

//------------------------------------------------------------	EraseOne()
// Given a pointer to the particle that needs to be deleted,
// this function simply swaps the last particle with the one
// to be deleted. This means that all living particles are
// always tightly packed at the front of the array, and
// secondly we have no need to perform any memory allocations
//
template<typename T, typename Y>
inline void EraseOne(T* p, T *&inStart, T *&inLast, Y* pVertex, Y *&inStartVertex, Y *&inLastVertex) {
	if (!IsEmpty(inStart, inLast)) {
		*p = *(--inLast);
	}
	if (!IsEmpty(inStartVertex, inLastVertex)) {
		*pVertex = *(--inLastVertex);
	}
}

//------------------------------------------------------------	UpdateParticles()
//
template<typename T, typename Y>
void UpdateParticles(float dt, T *&inStart, T *&inLast, Y *&inStartVertex, Y *&inLastVertex) {

	//if ((timeLeft.getTime() <= emitterDurationSeconds) || (emitterRepeat))
	//{
		// traverse all particles and update
		T* p = inStart;
		Y* pVertex = inStartVertex;
		while(p!=inLast) {
			// decrease lifespan
			p->life -= dt;

			// if we have life left
			if (p->life>0.0f) {
				//{($end_r - $start_r) / $life}
				// if the start colour is greater then the end colour then minus them, else add
				//for (int i = 0; i < 3; i++)
				//	// the alpha value
				//{

				//	if (particleStartColour[i]>particleEndColour[i])
				//	{
				//		if (particleEndColour[i]>0) // no point taking away if taking away 0
				//		{
				//			p->colour[i] -= (particleStartColour[i] - particleEndColour[i])*dt; // p->life;
				//			if (p->colour[i]<particleEndColour[i])
				//			{
				//				// Make sure the new colour is not less then the end colour
				//				p->colour[i] = particleEndColour[i];
				//			}
				//		}
				//	}
				//	else
				//	{
				//		if (particleEndColour[i]>0) // no point adding if taking away 0
				//		{
				//			p->colour[i] += (particleStartColour[i] + particleEndColour[i]);//*dt; // p->life;
				//			if (p->colour[i]>particleEndColour[i])
				//			{
				//				// Make sure the new colour is not greater then the end colour
				//				p->colour[i] = particleEndColour[i];
				//			}
				//		}
				//	}
				//}
				// TODO: Needs uncommenting when fixed
				//p->vtx->colour[0] += (particleStartColour[0] + particleEndColour[0])*dt; // p->life;
				//p->vtx->colour[1] += (particleStartColour[1] + particleEndColour[1])*dt; // p->life;
				//p->vtx->colour[2] += (particleStartColour[2] + particleEndColour[2])*dt; // p->life;
				//p->colour[3] = p->life;
				pVertex->colour[3] = 150;

				// make sure the new colour does not exceed the EndColour
				// TODO: Needs uncommenting when fixed
				//for (int i = 0; i < 3; i++)
				//												// the alpha value
				//{
				//	if (p->colour[i]>particleEndColour[i])
				//	{
				//		p->colour[i] = particleEndColour[i];
				//	}
				//}

				// TODO: Remove this temp code
				for (unsigned char i = 0; i < 3; i++)
					// the alpha value
				{
					pVertex->colour[i] = particleEndColour[i];
				}
				// temp code

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
				pVertex->position[0] += dt * (p->direction[0]); // x TriangleTop
				pVertex->position[1] += dt * (p->direction[1]); // y
				pVertex->position[2] += dt * (p->direction[2]); // z

				// TODO: Look at this, not using floats
				//p->colour[0] *= (1-0.3*dt);
				//p->colour[1] *= (1-0.3*dt);
				//p->colour[2] *= (1-0.3*dt);

				// goto next particle
				++p;
				++pVertex;
			}
			else {
				// if the particle is dead, erase it
				/// TODO:
				/// Add code for other particle shapes such as ParticleTriangles
				EraseOne(p, inStart, inLast, pVertex, inStartVertex, inLastVertex);

				// make sure it wasn't the last particle in the array,
				// if it was, return
				if (p>=inLast) {
					reset = false; // all colours will have been set to the initial value
					return;
				}
			}

		}
	//}
	
}
/////////////////////////Particles

/* ASCII code for the escape key. */
//#define ESCAPE 27 @@@

/* The number of our GLUT window */
int window; 

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				// Reset The Projection Matrix

  gluPerspective(45.0f,(float)Width/(float)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window

  glMatrixMode(GL_MODELVIEW);
  
  // set the maximum number of particles
	SetSize(emitterMaximumParticles, startPoints, lastPoints, endPoints, startPointsVertex,
		lastPointsVertex, endPointsVertex);
 // add particles before initialising them
	int val = rand()%100000;
	switch (particleShapeListboxItemId)
	{
	case 1: //shapePoint:
		for(int i=0;i!=val;++i)
			AddOne(lastPoints, lastPointsVertex);
		break;
	case 2: //shapeLine:
		//TODO: Set pointsvertex to corresponding type
		for(int i=0;i!=val;++i)
			AddOne(lastLines, lastPointsVertex);
		break;
	case 3: //shapeTriangle:
		for(int i=0;i!=val;++i)
			AddOne(lastTriangles, lastPointsVertex);
	default :
		break;
	}

	glVertexPointer(3,GL_FLOAT,sizeof(ParticlePointsVertex),startPointsVertex->position);
	glColorPointer(4,GL_UNSIGNED_BYTE,sizeof(ParticlePointsVertex),startPointsVertex->colour);

	// enable vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
  if (Height==0)				// Prevent A Divide By Zero If The Window Is Too Small
    Height=1;

  glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f,(float)Width/(float)Height,0.1f,100.0f); 
  glMatrixMode(GL_MODELVIEW);
}

/* The main drawing function. */
void DrawGLScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
  glLoadIdentity();				// Reset The View

// set the camera position
	gluLookAt(	1,-2,10,	//	eye pos
				0,-2,0,	//	aim point
				0,1,0);	//	up direction

DrawParticles();

  // we need to swap the buffer to display our drawing.
  glutSwapBuffers();
}

void OnIdle()
{
     	// update the frame time
	SortFrameTimer();

	// create a random number of new particles every frame
	int val = rand()%100000;
	switch (particleShapeListboxItemId)
	{
		case 1: //shapePoint:
			for(int i=0;i!=val;++i)
				// TODO change pointsvertex to corresponding type 
				AddOne(lastPoints, lastPointsVertex);
			break;
		default :
			break;
	}

	// update the particle simulation
	switch(particleShapeListboxItemId)
	{
		case 1: // shapePoint:
			//UpdateParticles(FrameTime(), start, last);
			UpdateParticles(timer.GetDeltaTime(), startPoints, lastPoints, startPointsVertex, lastPointsVertex);
			break;
		default:
			break;
	}

	// redraw the screen
	glutPostRedisplay();
}

/* The function called whenever a key is pressed. */
// @@@ this function is  modified to use PSP pad
void keyPressed(unsigned char key, int x, int y) 
{
 	switch (key) {
	case 'a':			/* startbutton */ /* If START is pressed, kill everything. */
		/* shut down our window */
		// but don't exist in pspgl
//		glutDestroyWindow(window);  @@@
	
		/* exit the program...normal termination. */
		exit(0);                   
	default:
		;
	}
}

int main(int argc, char **argv) 
{  
  /* Initialize GLUT state - glut will take any command line arguments that pertain to it or 
     X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */  
  glutInit(&argc, argv);  

  /* Select type of Display mode:   
     Double buffer 
     RGBA color
     Alpha components supported 
     Depth buffer */  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  

  /* get a 640 x 480 window */
  glutInitWindowSize(480, 272);  // @@@

  /* the window starts at the upper left corner of the screen */
  glutInitWindowPosition(0, 0);  

  /* Open a window */  
  window = glutCreateWindow("Jeff Molofee's GL Code Tutorial ... NeHe '99");  

  /* Register the function to do all our OpenGL drawing. */
  glutDisplayFunc(&DrawGLScene);  

  /* Go fullscreen.  This is as soon as possible. */
//  glutFullScreen(); @@@ there is no glutFullScreen in pspgl

  /* Even if there are no events, redraw our gl scene. */
  glutIdleFunc(&OnIdle);

  /* Register the function called when our window is resized. */
  glutReshapeFunc(&ReSizeGLScene);

  /* Register the function called when the keyboard is pressed. */
  glutKeyboardFunc(&keyPressed);

  /* Initialize our window. */
  InitGL(480, 272); // @@@
  
  /* Start Event Processing Engine */  
  glutMainLoop();  

  return 1;
}
