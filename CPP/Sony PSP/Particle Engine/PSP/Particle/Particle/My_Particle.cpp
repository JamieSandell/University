#include "My_Particle.h"
My_Particle::My_Particle(void)	{}
My_Particle::~My_Particle(void)	{}

void My_Particle::Initalise()
{
	//  Declare live variables (related to GLUI)
	draw = 1;				//  Related to Draw Check Box
	presetListBoxItemId = 1; // Id of the selected item in the list box
	emitterShapeListboxItemId = 1;	//  Id of the selected item in the list box
	radiogroup_item_id = 0; //  Id of the selcted radio button
	emitterHeight = 0;
	emitterWidth = 0;
	emitterDepth = 0;
	emitterPosition[0] = 0; // x,y,z
	emitterPosition[1] = 0; // x,y,z
	emitterPosition[2] = 0; // x,y,z
	emitterRadius = 1;
	emitterRadiusCentreX = 0;
	emitterRadiusCentreY = 0;
	emitterXMin = 0;
	emitterXMax = 3;
	emitterYMin = 0;
	emitterYMax = 0;
	emitterZMin = 0;
	emitterZMax = 3;
	emitterMaximumParticles = 100;
	emitterDurationSeconds = 1;
	emitterRepeat = true;
	particleShapeListboxItemId = 1;
	particleHeight = 5;
	particleWidth = 5;
	particleDepth = 5;
	particleBlendingModeListboxItemId = 1;
	particleColourRateOfChange = 0.4f;
	particleStartColour[0] = 0.0;
	particleStartColour[1] = 0.0;
	particleStartColour[2] = 0.0;
	particleEndColour[0] = 1.0;
	particleEndColour[1] = 1.0;
	particleEndColour[2] = 1.0;
	particleRandomColour = false;
	particleGravity[0] = 0.0;
	particleGravity[1] = 1.31;
	particleGravity[2] = 0.0;
	particleSpeedMin[0] = 0.0; // x,y,z
	particleSpeedMin[1] = 0.0; // x,y,z
	particleSpeedMin[2] = 0.0; // x,y,z
	particleSpeedMax[0] = 0.0; // x,y,z
	particleSpeedMax[1] = 0.0; // x,y,z
	particleSpeedMax[2] = 0.0; // x,y,z
	particleMinimumFade = 30000.0;
	particleMaximumFade = 30000.0;
	reset = true; // use this to set the initial colours of the particles

	_timer.Tick();

	// an array of RGB components
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;

	/// the first particle in the linked list
	startPoints=0;

	/// the next free particle
	lastPoints=0;

	/// the end of the memory allocation
	endPoints=0;

	/// the first particle in the linked list
	startTriangles=0;

	/// the next free particle
	lastTriangles=0;

	/// the end of the memory allocation
	endTriangles=0;

	/// the first particle in the linked list
	startLines=0;

	/// the next free particle
	lastLines=0;

	/// the end of the memory allocation
	endLines=0;

	// vertex data
	startPointsVertex = 0;
	lastPointsVertex = 0;
	endPointsVertex = 0;

	startLinesVertex = 0;
	lastLinesVertex = 0;
	endLinesVertex = 0;

	startTrianglesVertex = 0;
	lastTrianglesVertex = 0;
	endTrianglesVertex = 0;

	// Set Background colour
	//sceGuClearColor(0xff00000ff);
	Colour colour;
	sceGuClearColor(colour.Set(200,133,0,225));
	
	// Create View array and Display array
	int view[4] = {2048, 2048, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT};
	float disp[6] = {
			-6.0f,
			6.0f,
			-3.0f*((float)SCEGU_SCR_HEIGHT*2)/(float)SCEGU_SCR_WIDTH,
			3.0f*((float)SCEGU_SCR_HEIGHT*2)/(float)SCEGU_SCR_WIDTH,
			-10.0f,
			10.0f};

	// Pass to Camera
	_camera = Camera3D(view,disp);

	// Create Triangle points to draw later
	_array[0] = Vector3(-25,-25,0);
	_array[1] = Vector3(0,25,0);
	_array[2] = Vector3(25,-25,0);

	// Update the Camera Position
	_camera.Set(Vector3(0, 0, 50), Vector3( 0, 0, 0 ), 0, 0);
	_camera.Update();
	//sceGumMatrixMode( SCEGU_MATRIX_VIEW ) ;
	//sceGumLoadIdentity() ;
	//Vector3 _pos = Vector3(0,0,50);
	//Vector3 _lookAt = Vector3(0,0,0);
	//Vector3 _up =(Vector3(0,1,0));
	//sceGumLookAt(	(ScePspFVector3*)&_pos, 
	//				(ScePspFVector3*)&_lookAt, 
	//				(ScePspFVector3*)&_up);

	// set the maximum number of particles
	My_Particle::SetSize(emitterMaximumParticles, emitterMaximumParticles,
		startPoints, lastPoints, endPoints, startPointsVertex, lastPointsVertex, endPointsVertex);

	My_Particle::AddAndInitParticles();

	// Give the particles initial positions, colour, etc
	switch (particleShapeListboxItemId)
	{
	case 1: // point
		//InitParticles(startPointsVertex, lastPointsVertex);
		break;
	case 2: // point
		//
		break;
	case 3: // point
		//InitParticles(startLinesVertex)
	default :
		break;
	}

}
void My_Particle::Idle()
{
	float dt = _timer.Tick();
	//UpdateParticles(dt, startPoints, lastPoints, startPointsVertex, lastPointsVertex);
	My_Particle::UpdateParticles(1, startPoints, lastPoints, startPointsVertex, lastPointsVertex);
}

void My_Particle::Render()
{
	
	//// Set Some Debug Text to title the Application
	//sceGuDebugPrint(0, 30, 0x00ff00ff, 
	//			"PSP-Tutorial 1: Basic Triangle");

	////Set Colour to Green
	//sceGuColor(0xff00ff00);

	////Draw the array above defined
	//sceGumDrawArray(	SCEGU_PRIM_TRIANGLES,
	//					SCEGU_VERTEX_FLOAT,
	//					3,
	//					NULL,
	//					(ScePspFVector3*)_array);

	My_Particle::DrawParticles();

	//sceGumPushMatrix();
	//	sceGumTranslate((const ScePspFVector3 *)&_trans);
	//	//Draw the array above defined
	//	switch (_mode)
	//	{
	//	case Basic:
	//		sceGuColor(Colour::Green());
	//		sceGumDrawArray(	SCEGU_PRIM_TRIANGLES,
	//							VER_FORM,
	//							3,
	//							NULL,
	//							(ScePspFVector3*)_array);
	//		break;
	//	}

	//sceGumPopMatrix();

	//DrawParticles();
}
template<typename T, typename Y>
void My_Particle::InitParticles(T *&inStartVertex, T *&inLastVertex, Y *&inStartState, Y *&inLastState, int startingPoint)
{
	// TODO:
	/*
	need a switch statement, swicth(particleShape),
	then for say a triangle need to initialise p[0] p[1] and p[2]
	then move the pointer 3 places forward.
	could modoulo (inLastVertex - inStartVertex+startingPoint) / 3 (e.g. for triangles)
	*/

		// traverse all particles and init them
	T* p = inStartVertex+startingPoint; // point to the startPoint because
										// don't wanna reinitialise already initialised particles
										// so start from the first uninitialised one
	Y* s = inStartState+startingPoint;
	T* p2 = inStartVertex+startingPoint+1; // p, p2, and p3 will represent the 3 vertex info of a
											// triangle shape
	T* p3 = inStartVertex+startingPoint+2;
	if (particleShapeListboxItemId==1) // point shape
	{
		switch (emitterShapeListboxItemId)
		{
		case 1: // If the emitter is a point emitter then randomise all planes
			while(p!=inLastVertex)
			{

				// Init state
				s->direction[0] = (10000 - rand()%20000)/10000.0f;
				s->direction[1] = (10000 - rand()%20000)/10000.0f;
				s->direction[2] = (10000 - rand()%20000)/10000.0f;

				// set a random lifespan
				s->fade = rand () % (int(particleMaximumFade) - int(particleMinimumFade) + 1) +
					int(particleMinimumFade);
				s->life = rand()%int(s->fade)/9500.0f;
				s->speed[0] = rand () % (int(particleSpeedMax[0]) - int(particleSpeedMin[0]) + 1) +
					int(particleSpeedMin[0]);
				s->speed[1] = rand () % (int(particleSpeedMax[1]) - int(particleSpeedMin[1]) + 1) +
					int(particleSpeedMin[1]);
				s->speed[2] = rand () % (int(particleSpeedMax[2]) - int(particleSpeedMin[2]) + 1) +
					int(particleSpeedMin[2]);

				// Init Vertex
				p->position[0] = emitterPosition[0];
				p->position[0] += rand() % (emitterXMax - emitterXMin + 1) + emitterXMin;
				p->position[1] = emitterPosition[1];
				p->position[1] += rand() % (emitterYMax - emitterYMin + 1) + emitterYMin;
				p->position[2] = emitterPosition[2];
				p->position[2] += rand() % (emitterZMax - emitterZMin + 1) + emitterZMin;

				if (particleRandomColour) // set a random colour
				{
					//p->colour[0] = float(rand()%255)/255.0f;
					//p->colour[1] = float(rand()%255)/255.0f;
					//p->colour[2] = float(rand()%255)/255.0f;
					//p->colour[3] = 0.0f;
				}
				else // don't set a random colour
				{
					//p->colour[0] = particleStartColour[0];
					//p->colour[1] = particleStartColour[1];
					//p->colour[2] = particleStartColour[2];
					//p->colour[3] = 0.0f;
				}

				++p; // point to the next particle
				++s;
			}
			break;
		case 2: // If the emitter is a box emitter then randomize in the XZ planes
			while(p!=inLastVertex)
			{
				// Init state
				s->direction[0] = (10000 - rand()%20000)/10000.0f;
				s->direction[1] = (10000 - rand()%20000)/10000.0f;
				s->direction[2] = (10000 - rand()%20000)/10000.0f;

				// set a random lifespan
				s->fade = rand () % (int(particleMaximumFade) - int(particleMinimumFade) + 1) +
					int(particleMinimumFade);
				s->life = rand()%int(s->fade)/9500.0f;
				s->speed[0] = rand () % (int(particleSpeedMax[0]) - int(particleSpeedMin[0]) + 1) +
					int(particleSpeedMin[0]);
				s->speed[1] = rand () % (int(particleSpeedMax[1]) - int(particleSpeedMin[1]) + 1) +
					int(particleSpeedMin[1]);
				s->speed[2] = rand () % (int(particleSpeedMax[2]) - int(particleSpeedMin[2]) + 1) +
					int(particleSpeedMin[2]);

				//Init vertex
				p->position[0] = emitterPosition[0];
				p->position[0] += rand() % (emitterXMax - emitterXMin + 1) + emitterXMin;
				p->position[1] = emitterPosition[1];
				p->position[2] = emitterPosition[2];
				p->position[2] += rand() % (emitterZMax - emitterZMin + 1) + emitterZMin;

				//if (particleRandomColour) // set a random colour
				//{
				//	p->colour[0] = rand() % (255 - 0 + 0) + 0;
				//	p->colour[1] = rand()% (255 - 0 + 0) + 0;
				//	p->colour[2] = rand()% (255 - 0 + 0) + 0;
				//	p->colour[3] = 0.0f;
				//}
				//else // don't set a random colour
				//{
				//	p->colour[0] = particleStartColour[0];
				//	p->colour[1] = particleStartColour[1];
				//	p->colour[2] = particleStartColour[2];
				//	p->colour[3] = 0.0f;
				//}

				++p; // point to the next particle
				++s;
			}
			break;
		case 3: // Circle
			/*You have the radius R of the circle and its center Xo, Yo

			Then, any possible particle must be in this range of x:
			CODE
			Xo - R < x < Xo + R

			However, y must be within the circle, so by Pythagoras' theorem, its possible values should be:
			CODE
			Yo - sqrt(R² - x²) < y < Yo + sqrt(R² - x²)


			Just give random values to x in its valid range and then give random values to y in the indicated range...*/
			while(p!=inLastVertex)
			{
				//init state
				// Init state
				s->direction[0] = (10000 - rand()%20000)/10000.0f;
				s->direction[1] = (10000 - rand()%20000)/10000.0f;
				s->direction[2] = (10000 - rand()%20000)/10000.0f;

				// set a random lifespan
				s->fade = rand () % (int(particleMaximumFade) - int(particleMinimumFade) + 1) +
					int(particleMinimumFade);
				s->life = rand()%int(s->fade)/9500.0f;
				s->speed[0] = rand () % (int(particleSpeedMax[0]) - int(particleSpeedMin[0]) + 1) +
					int(particleSpeedMin[0]);
				s->speed[1] = rand () % (int(particleSpeedMax[1]) - int(particleSpeedMin[1]) + 1) +
					int(particleSpeedMin[1]);
				s->speed[2] = rand () % (int(particleSpeedMax[2]) - int(particleSpeedMin[2]) + 1) +
					int(particleSpeedMin[2]);

				// init vertex
				p->position[0] = emitterPosition[0];
				int minX = emitterRadiusCentreX - emitterRadius;
				int maxX = emitterRadiusCentreX + emitterRadius;
				p->position[0] += rand() % (maxX - minX + 1) + minX;

				int minY = emitterRadiusCentreY - sqrtf(powf(emitterRadius, 2) - powf(p->position[0],2));
				int maxY = emitterRadiusCentreY + sqrtf(powf(emitterRadius, 2) - powf(p->position[0],2));
				p->position[1] = emitterPosition[1];
				p->position[1] += rand() % (maxY - minY + 1) + minY;
				p->position[2] = emitterPosition[2];

				//if (particleRandomColour) // set a random colour
				//{
				//	p->colour[0] = rand() % (255 - 0 + 0) + 0;
				//	p->colour[1] = rand()% (255 - 0 + 0) + 0;
				//	p->colour[2] = rand()% (255 - 0 + 0) + 0;
				//	p->colour[3] = 0.0f;
				//}
				//else // don't set a random colour
				//{
				//	p->colour[0] = particleStartColour[0];
				//	p->colour[1] = particleStartColour[1];
				//	p->colour[2] = particleStartColour[2];
				//	p->colour[3] = 0.0f;
				//}

				++s; // point to the next particle
			}
			break;
		}
	}
	if (particleShapeListboxItemId==3) // triangle
	{
		switch (emitterShapeListboxItemId)
		{
		case 1: // If the emitter is a point emitter then randomise all planes
			while(p!=inLastVertex)
			{
				// bottom left of the triangle
				p->position[0] = emitterPosition[0];
				p->position[0] += rand() % (emitterXMax - emitterXMin + 1) + emitterXMin;
				p->position[1] = emitterPosition[1];
				p->position[1] += rand() % (emitterYMax - emitterYMin + 1) + emitterYMin;
				p->position[2] = emitterPosition[2];
				p->position[2] += rand() % (emitterZMax - emitterZMin + 1) + emitterZMin;
				// middle top of the triangle
				p2->position[0] = (p->position[0] + particleWidth) / 2;
				p2->position[1] = p->position[1] + particleHeight;
				p2->position[2] = p->position[2];
				// bottom right of the triangle

				p+=3; // point to the next particle
				p2+=3;
				p3+=3;
			}
			break;
		case 2: // If the emitter is a box emitter then randomize in the XZ planes
			while(p!=inLastVertex)
			{
				p->position[0] = emitterPosition[0];
				p->position[0] += rand() % (emitterXMax - emitterXMin + 1) + emitterXMin;
				p->position[1] = emitterPosition[1];
				p->position[2] = emitterPosition[2];
				p->position[2] += rand() % (emitterZMax - emitterZMin + 1) + emitterZMin;

				++p; // point to the next particle
			}
			break;
		case 3: // Circle
			/*You have the radius R of the circle and its center Xo, Yo

			Then, any possible particle must be in this range of x:
			CODE
			Xo - R < x < Xo + R

			However, y must be within the circle, so by Pythagoras' theorem, its possible values should be:
			CODE
			Yo - sqrt(R² - x²) < y < Yo + sqrt(R² - x²)


			Just give random values to x in its valid range and then give random values to y in the indicated range...*/
			while(p!=inLastVertex)
			{
				p->position[0] = emitterPosition[0];
				int minX = emitterRadiusCentreX - emitterRadius;
				int maxX = emitterRadiusCentreX + emitterRadius;
				p->position[0] += rand() % (maxX - minX + 1) + minX;

				int minY = emitterRadiusCentreY - sqrtf(powf(emitterRadius, 2) - powf(p->position[0],2));
				int maxY = emitterRadiusCentreY + sqrtf(powf(emitterRadius, 2) - powf(p->position[0],2));
				p->position[1] = emitterPosition[1];
				p->position[1] += rand() % (maxY - minY + 1) + minY;
				p->position[2] = emitterPosition[2];
				++p; // point to the next particle
			}
			break;
		}
	}
}
template<typename T>
int My_Particle::GetNumberOfParticles(T *&inLast, T *&inStart)
{
	int numberParticles = (int)(inLast-inStart);
	return numberParticles;
}
template<typename T, typename Y>
void My_Particle::AddOne(T *&inLast, Y *&inLastVertex) {

	// if we have no more memory left for any particles, ignore
	// the request to creat one.
	if (particleShapeListboxItemId==1) // point
	{
		if (!IsFull()) {
			*inLast = T(); // create the particles state
			++inLast;
			*inLastVertex = Y(); // create the particles vertex information
			++inLastVertex;
		}
	}
	if (particleShapeListboxItemId==3) // triangle
	{
		// when adding one for the triangle, add one inLast, and three inLastVertex
		// because a particle of shape triangle has one state, but three lots of vertex info
		// e.g. x,y,z position for bottomLeft, topMiddle, bottomRight
		if (!IsFull()) {
			*inLast = T(); // create the particles state
			++inLast;
			*inLastVertex = Y(); // create the particles vertex information
			inLastVertex+=3;
		}
	}

}

void My_Particle::AddAndInitParticles()
{
	//InitParticle(startPoints, lastPoints);
	// add particles before initialising them
	// before adding any particles, get the current amount of particles
	// that it will be known which particles need initialising.
	int numberOfParticlesBefore = 0;
	int numberOfParticlesAfter = 0;
	int val = rand()%100000;
	switch (particleShapeListboxItemId)
	{
	case 1: // point
		numberOfParticlesBefore = GetNumberOfParticles(lastPoints, startPoints);
		for(int i=0;i!=val;++i)
		{
			AddOne(lastPoints, lastPointsVertex);
		}
		InitParticles(startPointsVertex, lastPointsVertex, startPoints, lastPoints, numberOfParticlesBefore);
		break;
	case 2: // line
		numberOfParticlesBefore = GetNumberOfParticles(lastLines, startLines);
		for(int i=0;i!=val;++i)
		{
			AddOne(lastLines, lastLinesVertex);
		}
		InitParticles(startLinesVertex, lastLinesVertex, startLines, lastLines, numberOfParticlesBefore);
		break;
	case 3: // triangle
		numberOfParticlesBefore = GetNumberOfParticles(lastTriangles, startTriangles);
		for(int i=0;i!=val;++i)
		{
			AddOne(lastTriangles, lastTrianglesVertex);
		}
		InitParticles(startTrianglesVertex, lastTrianglesVertex, startTriangles, lastTriangles, numberOfParticlesBefore);
	default :
		break;
	}
}
/// Sets the type of the particle, e.g. start, last, end become pointers to ParticleTriangles
template<typename T, typename Y>
void My_Particle::SetParticleType(T *&inStart, T *&inLast, T *&inEnd, Y *&inStartVertex, Y *&inLastVertex,
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
void My_Particle::SetSize(unsigned int stateSize, unsigned int vertexSize, T *&inStart, T *&inLast, T *&inEnd, Y *&inStartVertex, Y *&inLastVertex,
			 Y *&inEndVertex) {

	// delete any previous data
	delete [] inStart;
	delete [] inStartVertex;
	delete [] inLast;
	delete [] inLastVertex;
	delete [] inEnd;
	delete [] inEndVertex;

	// allocate new particles
	inLast = inStart = new T[stateSize];
	inLastVertex = inStartVertex = new Y[vertexSize];

	// set end
	inEnd = inStart+stateSize;
	inEndVertex = inStartVertex+vertexSize;
}
//------------------------------------------------------------	IsEmpty()
//
//	returns true if the particle array is empty
//
template<typename T>
inline bool My_Particle::IsEmpty(T *&inStart, T *&inLast) {
	return inStart==inLast; // if start equals last then it must be empty
}
//------------------------------------------------------------	IsFull()
//
//	returns true if the array is full
//
inline bool My_Particle::IsFull() {
	switch(particleShapeListboxItemId)
	{
		case 1: // Points
			return lastPoints==endPoints;
			break;
		case 2: // Lines
			return lastLines==endLines-2; // because a line needs two lots of vertex info
			break;
		case 3: // Triangles
			// TODO: Might need to look at this
			return lastTriangles==endTriangles; // because a triangle needs three lots of vertex info
			break;
		default:
			break;
	}
}
//------------------------------------------------------------	DrawParticles()
//
inline void My_Particle::DrawParticles() {

	//if (!emitterRepeat) // if the repeat option isn't ticked then
	//					// check that there is still time remaining
	//{
	//	if (timeLeft.getTime() > emitterDurationSeconds)
	//	{
	//		return; // No time remaining so don't draw any particles
	//	}
	//}

	if (particleShapeListboxItemId==1) // points
	{
		//// since the particles are all nicely packed into one place,
		//// i can simply use vertex arrays to render the data. To do 
		//// this we need to give the address of the first data element
		//// in the array. We also need to specify a stride parameter,
		//// ie the number of bytes between each data element. In this
		//// case, each position is seperated by another particle. The
		//// same is true of the colours.
		////
		////
		//glDisable(GL_TEXTURE_2D);
		//glPointSize((float)particleHeight);
		//glVertexPointer(3,GL_FLOAT,sizeof(ParticlePointsVertex),startPointsVertex->position);
		//glColorPointer(4,GL_FLOAT,sizeof(ParticlePointsVertex),startPointsVertex->colour);

		//float quadratic[] = {0.0f, 3.0f, 0.0f};
		//glTexEnvf(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
		//glEnable(GL_POINT_SPRITE_ARB);

		//// draw the particles in one lovely function call. Note that 
		//// this is faster than glBegin/glEnd() because it avoids the 
		//// large amount of function call overhead.
		////
		//glDrawArrays(GL_POINTS,0,lastPointsVertex-startPointsVertex);

		//glDisable(GL_POINT_SPRITE_ARB);

		// Set Some Debug Text to title the Application
	sceGuDebugPrint(0, 30, 0x00ff00ff, 
				"PSP-Tutorial 1: Basic Triangle");

	//Set Colour to Green
	//sceGuColor(0xff00ff00);

	//Draw the array above defined
	sceGumDrawArray(	SCEGU_PRIM_POINTS,
						SCEGU_NORMAL_FLOAT,
						sizeof(ParticlePointsVertex),
						NULL,
						(ScePspFVector3*)startPointsVertex->position);

	}
	//if (particleShape==shapeLine)
	//{
	//	// since the particles are all nicely packed into one place,
	//	// i can simply use vertex arrays to render the data. To do 
	//	// this we need to give the address of the first data element
	//	// in the array. We also need to specify a stride parameter,
	//	// ie the number of bytes between each data element. In this
	//	// case, each position is seperated by another particle. The
	//	// same is true of the colours.
	//	//
	//	//
	//	//glDisable(GL_TEXTURE_2D);
	//	//glVertexPointer(3,GL_FLOAT,sizeof(ParticleLinesVertex),startLines->vtx->position);
	//	//glColorPointer(4,GL_UNSIGNED_BYTE,sizeof(ParticleLinesVertex),startLines->vtx->colour);

	//	//// enable vertex arrays
	//	//glEnableClientState(GL_VERTEX_ARRAY);
	//	//glEnableClientState(GL_COLOR_ARRAY);

	//	//// draw the particles in one lovely function call. Note that 
	//	//// this is faster than glBegin/glEnd() because it avoids the 
	//	//// large amount of function call overhead.
	//	////
	//	//glDrawArrays(GL_LINES,0,lastLines-startLines);

	//	//// disable vertex arrays
	//	//glDisableClientState(GL_VERTEX_ARRAY);
	//	//glDisableClientState(GL_COLOR_ARRAY);
	//}
	//if (particleShape==shapeTriangle)
	//{
	//	// since the particles are all nicely packed into one place,
	//	// i can simply use vertex arrays to render the data. To do 
	//	// this we need to give the address of the first data element
	//	// in the array. We also need to specify a stride parameter,
	//	// ie the number of bytes between each data element. In this
	//	// case, each position is seperated by another particle. The
	//	// same is true of the colours.
	//	//
	//	//
	//	glDisable(GL_TEXTURE_2D);
	//	glVertexPointer(3,GL_FLOAT,sizeof(ParticleTrianglesVertex)*3,startTrianglesVertex->position);
	//	glColorPointer(4,GL_UNSIGNED_BYTE,sizeof(ParticleTrianglesVertex)*3,startTrianglesVertex->colour);

	//	//// enable vertex arrays
	//	//glEnableClientState(GL_VERTEX_ARRAY);
	//	//glEnableClientState(GL_COLOR_ARRAY);

	//	// draw the particles in one lovely function call. Note that 
	//	// this is faster than glBegin/glEnd() because it avoids the 
	//	// large amount of function call overhead.
	//	//
	//	glDrawArrays(GL_TRIANGLES,0,lastTrianglesVertex-startTrianglesVertex);

	//	// disable vertex arrays
	//	/*glDisableClientState(GL_VERTEX_ARRAY);
	//	glDisableClientState(GL_COLOR_ARRAY);*/
	//}
}
//------------------------------------------------------------	EraseOne()
// Given a pointer to the particle that needs to be deleted,
// this function simply swaps the last particle with the one
// to be deleted. This means that all living particles are
// always tightly packed at the front of the array, and
// more importantly there is no need to perform any memory allocations!
//
template<typename T, typename Y>
inline void My_Particle::EraseOne(T* p, T *&inStart, T *&inLast, Y* pVertex, Y *&inStartVertex, Y *&inLastVertex) {
	//if (!IsEmpty(inStart, inLast)) {
		//*p = *(--inLast);
	//}
	if (particleShapeListboxItemId==1) // points
	{
		if (!IsEmpty(inStart, inLast)) {
			*p = *(--inLast);
		}
		if (!IsEmpty(inStartVertex, inLastVertex)) {
			*pVertex = *(--inLastVertex);
		}
	}
	if (particleShapeListboxItemId==2) // lines
	{
		// TODO: Use a forloop
		if (!IsEmpty(inStart, inLast)) {
			*p = *(--inLast);
		}
		if (!IsEmpty(inStartVertex, inLastVertex)) {
			*pVertex = *(--inLastVertex);
		}
		if (!IsEmpty(inStart, inLast)) {
			*p = *(--inLast);
		}
		if (!IsEmpty(inStartVertex, inLastVertex)) {
			*pVertex = *(--inLastVertex);
		}
	}
	if (particleShapeListboxItemId==3) // triangles
	{
		// TODO: Use a forloop
		if (!IsEmpty(inStart, inLast)) {
			*p = *(--inLast);
		}
		if (!IsEmpty(inStartVertex, inLastVertex)) {
			*pVertex = *(--inLastVertex);
		}
		if (!IsEmpty(inStart, inLast)) {
			*p = *(--inLast);
		}
		if (!IsEmpty(inStartVertex, inLastVertex)) {
			*pVertex = *(--inLastVertex);
		}
		if (!IsEmpty(inStart, inLast)) {
			*p = *(--inLast);
		}
		if (!IsEmpty(inStartVertex, inLastVertex)) {
			*pVertex = *(--inLastVertex);
		}
	}
}
template<typename T, typename Y>
void My_Particle::UpdateParticles(float dt, T *&inStart, T *&inLast, Y *&inStartVertex, Y *&inLastVertex) {

	//if ((timeLeft.getTime() <= emitterDurationSeconds) || (emitterRepeat))
	//{
		// traverse all particles and update
		T* p = inStart;
		Y* pVertex = inStartVertex;
		while(p!=inLast) { // TODO: this needs looking at, need to make sure all vertex info is traversed
								// eg all vertex info for the triangles
			// decrease lifespan
			p->life -= dt;

			// if we have life left
			if (p->life>0.0f) {
				//{($end_r - $start_r) / $life}
				// if the start colour is greater then the end colour then minus them, else add
				for (int i = 0; i < 3; i++)
					// the alpha value
				{

					if (particleStartColour[i]>particleEndColour[i]) // Then we want to decrease the
																		//colour
					{
						if (particleEndColour[i]>0) // no point taking away if taking away 0
						{
							//pVertex->colour[i] -= (particleColourRateOfChange*dt);//(particleStartColour[i] - particleEndColour[i]);
								//*particleColourRateOfChange;
							//if (pVertex->colour[i]<particleEndColour[i])
							//{
							//	// Make sure the new colour is not less then the end colour
							//	pVertex->colour[i] = particleEndColour[i];
							//}
						}
					}
					else // Then we want to increase the colour
					{
						if (particleEndColour[i]>0) // no point adding if taking away 0
						{
							//pVertex->colour[i] += (particleColourRateOfChange*dt);
							//if (pVertex->colour[i]>particleEndColour[i])
							//{
							//	// Make sure the new colour is not greater then the end colour
							//	pVertex->colour[i] = particleEndColour[i];
							//}
						}
					}
				}
				// TODO: Needs uncommenting when fixed
				//p->vtx->colour[0] += (particleStartColour[0] + particleEndColour[0])*dt; // p->life;
				//p->vtx->colour[1] += (particleStartColour[1] + particleEndColour[1])*dt; // p->life;
				//p->vtx->colour[2] += (particleStartColour[2] + particleEndColour[2])*dt; // p->life;
				//pVertex->colour[3] = p->life;

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
				//if (!particleRandomColour)
				//{
				//	for (unsigned char i = 0; i < 3; i++)
				//		// the alpha value
				//	{
				//		pVertex->colour[i] = particleEndColour[i];
				//	}
				//	// temp code
				//}

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