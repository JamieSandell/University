#pragma once
//#include "..\..\..\..\..\SEED TFS\PSPDev Kit\PSPFramework.h"
//#include "..\..\..\..\..\SEED TFS\PSPDev Kit\PSPFramework.Utilities.h"
//#include "..\..\..\..\..\SEED TFS\PSPDev Kit\PSPFramework.Maths.h"
#include "F:\SEED TFS\PSPDev Kit\PSPFramework.h"
#include "F:\SEED TFS\PSPDev Kit\PSPFramework.Utilities.h"
#include "F:\SEED TFS\PSPDev Kit\PSPFramework.Maths.h"
class My_Particle :
	public App
{
	public:	
	Timer _timer;

	My_Particle(void);
	~My_Particle(void);

	struct ParticlePointsVertex{
	//float colour[4];
	float position[3];
};

	struct ParticleLinesVertex{
		float colour[4];
		float position[3];
	};

	struct ParticleTrianglesVertex{
		float colour[4];
		float position[3];
	};
	struct ParticlePointsState
	{
		/// the direction of the particle
		float direction[3];

		/// the lifespan
		float life;

		/// speed to act against gravity
		float speed[3];
		float fade;

	};

	struct ParticleLinesState{
	/// the direction of the particle
	float direction[3];

	/// the lifespan
	float life;

	/// speed to act against gravity
	float speed[3];
	float fade;

	struct ParticleLinesVertex *vtx;
};

	struct ParticleTrianglesState{
		/// the direction of the particle
		float direction[3];

		/// the lifespan
		float life;

		/// speed to act against gravity
		float speed[3];
		float fade;

		struct ParticleTrianglesVertex *vtx;
	};
	template<typename T, typename Y>
	void InitParticles(T *&inStartVertex, T *&inLastVertex, Y *&inStartState, Y *&inLastState, int startingPoint);
	template<typename T>
	int GetNumberOfParticles(T *&inLast, T *&inStart);
	template<typename T, typename Y>
	void AddOne(T *&inLast, Y *&inLastVertex);
	void AddAndInitParticles();
	template<typename T, typename Y>
	void SetParticleType(T *&inStart, T *&inLast, T *&inEnd, Y *&inStartVertex, Y *&inLastVertex, Y *&inEndVertex);
	template<typename T, typename Y>
	void SetSize(unsigned int stateSize, unsigned int vertexSize, T *&inStart, T *&inLast, T *&inEnd, Y *&inStartVertex,
		Y *&inLastVertex, Y *&inEndVertex);
	template<typename T>
	inline bool IsEmpty(T *&inStart, T *&inLast);
	inline bool IsFull();
	inline void DrawParticles();
	template<typename T, typename Y>
	inline void EraseOne(T* p, T *&inStart, T *&inLast, Y* pVertex, Y *&inStartVertex, Y *&inLastVertex);
	template<typename T, typename Y>
	void UpdateParticles(float dt, T *&inStart, T *&inLast, Y *&inStartVertex, Y *&inLastVertex);


	void Initalise();
	void Idle();
	void Render();

private:
	Camera3D _camera;
	 Vector3 _array[3];

	 //  Declare live variables (related to GLUI)
	int draw;				//  Related to Draw Check Box
	int presetListBoxItemId; // Id of the selected item in the list box
	int emitterShapeListboxItemId;	//  Id of the selected item in the list box
	int radiogroup_item_id; //  Id of the selcted radio button			
	int emitterHeight;
	int emitterWidth;
	int emitterDepth;
	int emitterPosition[3]; // x,y,z
	int emitterRadius;
	int emitterRadiusCentreX;
	int emitterRadiusCentreY;
	int emitterXMin;
	int emitterXMax;
	int emitterYMin;
	int emitterYMax;
	int emitterZMin;
	int emitterZMax;
	int emitterMaximumParticles;
	int emitterDurationSeconds;
	int emitterRepeat;
	int particleShapeListboxItemId;
	int particleHeight;
	int particleWidth;
	int particleDepth;
	int particleBlendingModeListboxItemId;
	float particleColourRateOfChange;
	float particleStartColour[3];
	float particleEndColour[3];
	int particleRandomColour;
	float particleGravity[3]; // x,y,z
	float particleSpeedMin[3]; // x,y,z
	float particleSpeedMax[3]; // x,y,z
	float particleMinimumFade;
	float particleMaximumFade;
	//Timer timeLeft;
	bool reset; // use this to set the initial colours of the particles
	//Timer timer;

	// an array of RGB components
	float color[3];

	/// the first particle in the linked list
	ParticlePointsState* startPoints;

	/// the next free particle
	ParticlePointsState* lastPoints;

	/// the end of the memory allocation
	ParticlePointsState* endPoints;

	/// the first particle in the linked list
	ParticleTrianglesState* startTriangles;

	/// the next free particle
	ParticleTrianglesState* lastTriangles;

	/// the end of the memory allocation
	ParticleTrianglesState* endTriangles;

	/// the first particle in the linked list
	ParticleLinesState* startLines;

	/// the next free particle
	ParticleLinesState* lastLines;

	/// the end of the memory allocation
	ParticleLinesState* endLines;

	// vertex data
	ParticlePointsVertex* startPointsVertex;
	ParticlePointsVertex* lastPointsVertex;
	ParticlePointsVertex* endPointsVertex;

	ParticleLinesVertex* startLinesVertex;
	ParticleLinesVertex* lastLinesVertex;
	ParticleLinesVertex* endLinesVertex;

	ParticleTrianglesVertex* startTrianglesVertex;
	ParticleTrianglesVertex* lastTrianglesVertex;
	ParticleTrianglesVertex* endTrianglesVertex;

	//Timer _timer;

};