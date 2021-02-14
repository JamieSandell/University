//This code is just a skeleton for your own programs

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

/* The number of our GLUT window */
int window; 

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "FrameTimer.h"

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

/// the first particle in the linked list
Particle* start=0;

/// the next free particle
Particle* last=0;

/// the end of the memory allocation
Particle* end=0;


//------------------------------------------------------------	SetSize()
//
//	Allocates the static global particle buffer
//
void SetSize(unsigned int size) {

	// delete any previous data
	delete [] start;

	// allocate new particles 
	last = start = new Particle[size];

	// set end
	end = start+size;
}


//------------------------------------------------------------	IsEmpty()
//
//	returns true if the particle array is empty
//
bool IsEmpty() {
	return start==last; // if start equals last then it must be empty
}

//------------------------------------------------------------	IsFull()
//
//	returns true if the array is full
//
bool IsFull() {
	return last==end;
}

//------------------------------------------------------------	DrawParticles()
//
void DrawParticles() {

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


//------------------------------------------------------------	AddOne()
// this function 'adds' a particle into the array. In actual
// fact, all it does is move the pointer to the last element
// along by one position. This means we have not performed an
// expensive memory allocation.
//
void AddOne() {

	// if we have no more memory left for any particles, ignore
	// the request to creat one.
	if (!IsFull()) {
		*last = Particle();
		++last;
	}
}

//------------------------------------------------------------	EraseOne()
// Given a pointer to the particle that needs to be deleted,
// this function simply swaps the last particle with the one
// to be deleted. This means that all living particles are
// always tightly packed at the front of the array, and
// secondly we have no need to perform any memory allocations
//
void EraseOne(Particle* p) {
	if (!IsEmpty()) {
		*p = *(--last);
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
	life = rand()%30000/9500.0f;
}

//------------------------------------------------------------	UpdateParticles()
//
void UpdateParticles(float dt) {

	// traverse all particles and update
	Particle* p = start;
	while(p!=last) {
		// decrease lifespan
		p->life -= dt;

		// if we have life left
		if (p->life>0) {

			// apply gravity
			p->direction[1] -= 1.31f*dt;

			// modify position
			p->position[0] += dt * p->direction[0];
			p->position[1] += dt * p->direction[1];
			p->position[2] += dt * p->direction[2];

			p->colour[0] *= (1-0.3*dt);
			p->colour[1] *= (1-0.3*dt);
			p->colour[2] *= (1-0.3*dt);

			// goto next particle
			++p;
		}
		else {
			// if the particle is dead, erase it
			EraseOne(p);

			// make sure it wasn't the last particle in the array,
			// if it was, return
			if (p>=last) {
				return;
			}
		}

	}
}

//------------------------------------------------------------	OnReshape()
//
void OnReshape(int w, int h)
{
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

//------------------------------------------------------------	Draw()
//
void OnDraw() {

	// clear the screen & depth buffer
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	// clear the previous transform
	glLoadIdentity();

	// set the camera position
	gluLookAt(	1,-3,10,	//	eye pos
				0,-3,0,	//	aim point
				0,1,0);	//	up direction

	//
	DrawParticles();

	// currently we've been drawing to the back buffer, we need
	// to swap the back buffer with the front one to make the image visible
	glutSwapBuffers();
}

//------------------------------------------------------------	OnInit()
//
void OnInit() {
	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// set the maximum number of particles
	SetSize(10000000);
}

//------------------------------------------------------------	OnExit()
//
void OnExit() {
}

// used for frame counting
int count=0;

//------------------------------------------------------------	OnIdle()
//
void OnIdle() {

	if(++count == 1000) {
		std::cout << "num particles = " << ((int)(last-start)) << "   fps = " << (1.0f/FrameTime())<< "\n";
		count=0;
	}

	// update the frame time
	SortFrameTimer();

	// create a random number of new particles every frame
	int val = rand()%1000000;
	for(int i=0;i!=val;++i)
		AddOne();

	// update the particle simulation
	UpdateParticles(FrameTime());

	// redraw the screen
	glutPostRedisplay();
}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y) 
{
	switch (key) {
	case 'd':			/* delta, triangle */
		break;
	case 'o':			/* round */
		break;
	case 'q':			/* square*/
		break;
	case 'x':			/* cross */
		break;
	case 'n':			/* key with the music note */
		break;
	case 's':			/* select */
		break;
	case 'a':			/* startbutton */  /* If START is pressed, kill everything. */
 		/* exit the program...normal termination. */
		exit(0);                   
	default:
		;
	}
 }

/* The function called whenever a key is released. */
void keyReleased(unsigned char key, int x, int y) 
{
	switch (key) {
	case 'd':			/* delta, triangle */
		break;
	case 'o':			/* round */
		break;
	case 'q':			/* square*/
		break;
	case 'x':			/* cross */
		break;
	case 'n':			/* key with the music note */
		break;
	case 's':			/* select */
		break;
	case 'a':			/* startbutton */
		break;
	default:
		;
	}
 }

/* The function called whenever a special key is pressed. */
void specialKeyPressed(int key, int x, int y) 
{
    switch (key) {    
    case GLUT_KEY_UP: // pad arrow up
	break;

    case GLUT_KEY_DOWN: //  pad arrow down
	break;

    case GLUT_KEY_LEFT: //  pad arrow left
	break;
    
    case GLUT_KEY_RIGHT: //  pad arrow right
	break;

    case GLUT_KEY_HOME: // home
	break;
	
    default:
	break;
    }	
}

/* The function called whenever a special key is released. */
void specialKeyReleased(int key, int x, int y) 
{
    switch (key) {    
    case GLUT_KEY_UP: // pad arrow up
	break;

    case GLUT_KEY_DOWN: //  pad arrow down
	break;

    case GLUT_KEY_LEFT: //  pad arrow left
	break;
    
    case GLUT_KEY_RIGHT: //  pad arrow right
	break;

    case GLUT_KEY_HOME: // home
	break;
	
    default:
	break;
    }	
}

/* The function called whenever the joystick is moved. */
void joystickMoved (unsigned int buttonMask, int x, int y, int z)
{
	if (abs(x) > 150) // dead zone
	{	
		// use x value
	}

	if (abs(y) > 150) // dead zone
	{	
		// use y value
	}
}

/* The function called whenever the triggers are pressed. */
void triggerHandle (int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {  // left trigger...
		if (state == GLUT_DOWN) {  // ...is pressed
		}
		if (state == GLUT_UP) {  // ...is released
		}
	}

	if (button == GLUT_RIGHT_BUTTON) {  // right trigger...
		if (state == GLUT_DOWN) {  // ...is pressed
		}
		if (state == GLUT_DOWN) {  // ...is released
		}
	}
}

/* main function */
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
  glutInitWindowSize(480, 272); 

  /* the window starts at the upper left corner of the screen */
  glutInitWindowPosition(0, 0);  

  /* Open a window */  
  window = glutCreateWindow("Jeff Molofee's GL Code Tutorial ... NeHe '99");  

  /* Register the function to do all our OpenGL drawing. */
  glutDisplayFunc(&OnDraw);  

  /* Even if there are no events, redraw our gl scene. */
  glutIdleFunc(&OnIdle);

  /* Register the function called when our window is resized. */
  glutReshapeFunc(&OnReshape);

  /* Register the function called when the keyboard is pressed. */
  glutKeyboardFunc(&keyPressed);
  /* Register the function called when the keyboard is released. */
  glutKeyboardUpFunc(&keyReleased);
  /* Register the function called when special keys (arrows, page down, etc) are pressed. */
  glutSpecialFunc(&specialKeyPressed);
  /* Register the function called when special keys (arrows, page down, etc) are released. */
  glutSpecialUpFunc(&specialKeyReleased);
  /* Register the function called when joystick is moved. */
  glutJoystickFunc(&joystickMoved, 0); // 0 = Joystick polling interval in milliseconds
  /* Register the function called when Trigger_left or Trigger_right is pressed */
  glutMouseFunc(&triggerHandle);
  
  /* Initialize our window. */
  //InitGL(480, 272); 
  
  /* Start Event Processing Engine */  
  //glutMainLoop();  
  	// initialise the frame timer
	InitFrameTimer();

	// this function runs a while loop to keep the program running.
	glutMainLoop();

  return (0);
}
