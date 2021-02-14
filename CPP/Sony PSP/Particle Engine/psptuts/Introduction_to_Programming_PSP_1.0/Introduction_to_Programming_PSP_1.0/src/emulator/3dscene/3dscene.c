/* SCE CONFIDENTIAL
$PSLibId$
*/
/*
* Introduction to Programming the PSP(TM)
*
* Copyright (C) 2005 Sony Computer Entertainment Europe
* All Rights Reserved.
*
* PSP Intro Emulator Sample two - 3dscene.c
*   This sample demonstrates 3D rendering of a lit scene consisting of a floor plane,
*	Two torii and a light representation
*
*   Date            Design      Log
*  ----------------------------------------------------
*   2005-20-01      csawyer 	initial implementation
*/

//-----------------------------------------------------------------------------
// I N C L U D E S
//-----------------------------------------------------------------------------
#include <libgu.h>
#include <libgum.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <libemu.h>

//-----------------------------------------------------------------------------
// T Y P E D E F S
//-----------------------------------------------------------------------------
typedef struct
{
	ScePspFVector3	rot;
	ScePspFVector3	trans;
}	pos_rot;

//-----------------------------------------------------------------------------
// P R O T O T Y P E S
//-----------------------------------------------------------------------------
static void Init(void);
static void InitGFX(void);
static void InitFloorPlaneData(void);
static void InitTorusData(void);
static void InitSphereData(void);
static void StartFrame(void);
static void Render(void);
static void EndFrame(void);
static void ReadPad(void);
static void ClampRot(SceFloat* element, SceFloat clampValue);

//-----------------------------------------------------------------------------
// C O N S T A N T S
//-----------------------------------------------------------------------------
static const SceUInt32	cPlaneDivs					= 10;		
static const SceUInt32	cNumFloorCPs				= 100;
static const SceUInt32	cPlaneDimensionsXZ	= 10;	
static const SceUInt32	cSphereU						= 4;	
static const SceUInt32	cSphereV						= 7;	
static const SceUInt32	cTorusU							= 7;	
static const SceUInt32	cTorusV							= 7;
static const SceFloat   gSpecular						= 40.0f;
static const SceFloat   gAngle								= 1.5f;
static const SceFloat   gMaxAngle						= 360.0f;
static const SceFloat	gDeadZone						= 0.3f;

//-----------------------------------------------------------------------------
// S T A T I C   V A R I A B L E S 
//-----------------------------------------------------------------------------
static char							gDisplayList[0x10000];
static ScePspFMatrix4	gMatrixStack[8+8+32+0];
static ScePspFVector3	gaTorusData[7*7];
static ScePspFVector3	gaSphereData[4*7];
static ScePspFVector3	gaFloorData[10*10];
static ScePspFMatrix4	gViewMatrix;
static ScePspFVector3	gLightPosVec;
static ScePspFVector3	gOffsetVec;
static ScePspFVector3	gTorus2PosVec;
static SceFloat					gRotY;
static pos_rot					gCamPosRot;
static ScePspFVector3	gSphereScale;

//-----------------------------------------------------------------------------
// P U B L I C   F U N C T I O N S
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//	\function   int main(void)
//	\date			20/01/05
//	\brief			Main loop - After initialization, cycles through the 
//						controller input and the render loop
//-----------------------------------------------------------------------------
int main(void)
{
	Init();

	while(1)
	{
		ReadPad();

		StartFrame();

		Render();

		EndFrame();
	}

	// Shutdown libGu
	sceGuTerm();

	// Shut down the Emulator
	sceEmuTerm();
	// The End
	return 0;
}

//-----------------------------------------------------------------------------
//	\function   void Init(void)
//	\date			20/01/05
//	\brief			Container function to initialise everything for the sample
//-----------------------------------------------------------------------------
static void Init(void)
{
	// gViewMatrix init
	gCamPosRot.trans.x		= 0.0f;
	gCamPosRot.trans.y		= 0.0f;
	gCamPosRot.trans.z		= 10.0f;
	gCamPosRot.rot.x			= -36.0f;
	gCamPosRot.rot.y			= 0.0f;
	gCamPosRot.rot.z			= 0.0f;

	// Init object positions
	gLightPosVec.x				= 3.0f;
	gLightPosVec.y				= 3.0f;
	gLightPosVec.z				= 0.0f;

	gTorus2PosVec.x			= 1.0f;
	gTorus2PosVec.y			= 0.0f;
	gTorus2PosVec.z			= 0.0f;

	gOffsetVec.x					= 0.0f;
	gOffsetVec.y					= 1.5f;
	gOffsetVec.z					= -2.0f;
	
	gRotY									= 0.0f;

	gSphereScale.x=gSphereScale.y=gSphereScale.z= 0.2f;

	InitGFX();
	InitFloorPlaneData();
	InitTorusData();
	InitSphereData();
}

//-----------------------------------------------------------------------------
//	\function   void InitGFX(void)
//	\date			20/01/05
//	\brief			Initialises libGu, screen etc
//-----------------------------------------------------------------------------
static void InitGFX(void)
{
	sceEmuInit();
	sceGuInit();

	sceGuStart(SCEGU_IMMEDIATE, gDisplayList, sizeof(gDisplayList));													// Set the start of the display list

	sceGuDrawBuffer(SCEGU_PF8888, SCEGU_VRAM_BP32_0, SCEGU_VRAM_WIDTH );						// Initialise the the back and front buffers, respectively
	sceGuDispBuffer(SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT, SCEGU_VRAM_BP32_1, SCEGU_VRAM_WIDTH );
	sceGuDepthBuffer(SCEGU_VRAM_BP32_2, SCEGU_VRAM_WIDTH );														// Initialise the Depth buffer

	sceGuDepthRange(50000, 10000);
	sceGuDepthFunc(SCEGU_GEQUAL);
	sceGuEnable(SCEGU_DEPTH_TEST);

	sceGuOffset(SCEGU_SCR_OFFSETX, SCEGU_SCR_OFFSETY);																	// Init Screen coordinates into the drawing space - or something....
	sceGuViewport(2048, 2048, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT);											// Init the viewport

	sceGuScissor(0, 0, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT);															// Initialise the scissor region
	sceGuEnable	(SCEGU_SCISSOR_TEST );
	
	sceGumSetMatrixStack(&gMatrixStack[0], 8, 8, 32, 0);
	sceGumMatrixMode (SCEGU_MATRIX_PROJECTION);
	sceGumPerspective(SCEGU_RAD(45.0f), SCEGU_SCR_ASPECT, 1.000000f, 100.000000f);
	
	sceGuClearColor(0xFF304035);																														// Set the clear colour
	sceGuClearDepth(0);																																				// Set the depth clearing value to 0
	sceGuShadeModel(SCEGU_SMOOTH);																												// Vertex Normal lighting
	sceGuPatchDivide(16, 16);																																	// Tesselation variable

	sceGuLightColor(0, SCEGU_AMBIENT, 0x00ffffff);
	sceGuLightColor(0, SCEGU_DIFFUSE, 0x00ffffff);
	sceGuLightColor(0, SCEGU_SPECULAR, 0x00ffffff);
	sceGuLight(0, SCEGU_LIGHT_POINT, SCEGU_DIFFUSE_AND_SPECULAR, &gLightPosVec);
	sceGuEnable(SCEGU_LIGHT0);
	sceGuEnable(SCEGU_LIGHTING);
	sceGuSpecular(gSpecular);																																	// Initialise the lights

	sceGuEnable(SCEGU_DEBUG_GL_TESSELATE);

	// Finish 
	sceGuFinish();
	sceGuSync(SCEGU_SYNC_FINISH, SCEGU_SYNC_WAIT);

	sceEmuVSync(SCEEMU_SYNC_WAIT);
}


//-----------------------------------------------------------------------------
//	\function   void InitFloorPlaneData(void)
//	\date			20/01/05
//	\brief			Initialises the vectors for the floor patch control points
//-----------------------------------------------------------------------------
static void InitFloorPlaneData(void)
{
	ScePspFVector3*	pVec	= gaFloorData;
	SceFloat vStep			= (SceFloat)cPlaneDimensionsXZ / cPlaneDivs;
	SceFloat start			= vStep * ((cPlaneDivs - 1)/2.0f);
	SceFloat zPos			= start;
	SceFloat xPos			= -start;

	SceUInt32 i	= 0, j = 0;
	
	// Set positions for the vertices in an XZ grid
	for	(i = 0, zPos = start; i < cNumFloorCPs; i+= cPlaneDivs, zPos -= vStep)
	{
		for	(j = 0, xPos = -start; j < cPlaneDivs; j++, pVec++, xPos += vStep)
		{
			pVec->x = xPos;
			pVec->y = 0;
			pVec->z = zPos;		
		}
	}	
}

//-----------------------------------------------------------------------------
//	\function   void InitTorusData(void)
//	\date			20/01/05
//	\brief			Initialises vectors for the torus control points
//-----------------------------------------------------------------------------
static void InitTorusData(void)
{
	SceInt32	i, cnt;
	SceFloat	dist;
	const SceFloat inner = 0.5f;
	const SceFloat outer = 1.0f;
	SceFloat table[] =	
	{
		-1.0f,	 0.0f,
		-1.0f,	 1.3333333f,
		 1.0f,	 1.3333333f,
		 1.0f,	 0.0f,
		 1.0f,	-1.3333333f,
		-1.0f,	-1.3333333f,
		-1.0f,	 0.0f,
	};

	SceFloat *pdata = (SceFloat*)gaTorusData;

	cnt = 0;
	for (i=0; i<7; i++) 
	{
		dist=outer+inner*cosf(0.0f);
 		pdata[cnt+0 ]=pdata[cnt+3]=table[i*2+0]*dist;
		pdata[cnt+1 ]=pdata[cnt+4]=table[i*2+1]*dist;
		pdata[cnt+2 ]=0.0f;
		pdata[cnt+5 ]=inner*1.333333f;

		dist=outer+inner*cosf(SCEGU_PI);
		pdata[cnt+6 ]=pdata[cnt+ 9]=table[i*2+0]*dist;
		pdata[cnt+7 ]=pdata[cnt+10]=table[i*2+1]*dist;
		pdata[cnt+8 ]=inner*1.333333f;
		pdata[cnt+11]=0.0f;

		pdata[cnt+12]= pdata[cnt+6];
		pdata[cnt+13]= pdata[cnt+7];
		pdata[cnt+14]=-pdata[cnt+8];

		pdata[cnt+15]= pdata[cnt+3];
		pdata[cnt+16]= pdata[cnt+4];
		pdata[cnt+17]=-pdata[cnt+5];

		pdata[cnt+18]=pdata[cnt+0];
		pdata[cnt+19]=pdata[cnt+1];
		pdata[cnt+20]=pdata[cnt+2];
		cnt+=21;
	}
}

//-----------------------------------------------------------------------------
//	\function   void InitSphereData(void)
//	\date			20/01/05
//	\brief			Initialises vectors for the light-sphere control points
//-----------------------------------------------------------------------------
static void InitSphereData(void)
{
	SceInt32 numPoints = cSphereU * cSphereV, i = 0;

	ScePspFVector3	sphere[28] =	
	{
		{ 0.000000f,  1.000000f,  0.000000f, },
		{ 1.333333f,  1.000000f,  0.000000f, },
		{ 1.333333f, -1.000000f,  0.000000f, },
		{ 0.000000f, -1.000000f,  0.000000f, },
		{ 0.000000f,  1.000000f,  0.000000f, },
		{ 1.333333f,  1.000000f, -1.777777f, },
		{ 1.333333f, -1.000000f, -1.777777f, },
		{ 0.000000f, -1.000000f,  0.000000f, },
		{ 0.000000f,  1.000000f,  0.000000f, },
		{-1.333333f,  1.000000f, -1.777777f, },
		{-1.333333f, -1.000000f, -1.777777f, },
		{ 0.000000f, -1.000000f,  0.000000f, },
		{ 0.000000f,  1.000000f,  0.000000f, },
		{-1.333333f,  1.000000f,  0.000000f, },
		{-1.333333f, -1.000000f,  0.000000f, },
		{ 0.000000f, -1.000000f,  0.000000f, },
		{ 0.000000f,  1.000000f,  0.000000f, },
		{-1.333333f,  1.000000f,  1.777777f, },
		{-1.333333f, -1.000000f,  1.777777f, },
		{ 0.000000f, -1.000000f,  0.000000f, },
		{ 0.000000f,  1.000000f,  0.000000f, },
		{ 1.333333f,  1.000000f,  1.777777f, },
		{ 1.333333f, -1.000000f,  1.777777f, },
		{ 0.000000f, -1.000000f,  0.000000f, },
		{ 0.000000f,  1.000000f,  0.000000f, },
		{ 1.333333f,  1.000000f,  0.000000f, },
		{ 1.333333f, -1.000000f,  0.000000f, },
		{ 0.000000f, -1.000000f,  0.000000f, },
	};

	for (i = 0; i < numPoints; i++)
	{
		gaSphereData[i] = sphere[i];
	}
}

//-----------------------------------------------------------------------------
//	\function   void Invert43(ScePspFMatrix4* pCurr)
//	\date			20/01/05
//	\brief			4x3 Inverse matrix function
//-----------------------------------------------------------------------------
void Invert43(ScePspFMatrix4* pCurr)
{
		ScePspFMatrix4	invert;
		register float	det;

		invert.x.x	=	pCurr->y.y*pCurr->z.z - pCurr->y.z*pCurr->z.y;
		invert.x.y	=	pCurr->z.y*pCurr->x.z - pCurr->z.z*pCurr->x.y;
		invert.x.z	=	pCurr->x.y*pCurr->y.z - pCurr->x.z*pCurr->y.y;
		invert.x.w	=	0.0f;
		invert.y.x	=	pCurr->y.z*pCurr->z.x - pCurr->y.x*pCurr->z.z;
		invert.y.y	=	pCurr->z.z*pCurr->x.x - pCurr->z.x*pCurr->x.z;
		invert.y.z	=	pCurr->x.z*pCurr->y.x - pCurr->x.x*pCurr->y.z;
		invert.y.w	=	0.0f;
		invert.z.x	=	pCurr->y.x*pCurr->z.y - pCurr->y.y*pCurr->z.x;
		invert.z.y	=	pCurr->z.x*pCurr->x.y - pCurr->z.y*pCurr->x.x;
		invert.z.z	=	pCurr->x.x*pCurr->y.y - pCurr->x.y*pCurr->y.x;
		invert.z.w	=	0.0f;

		invert.z.w	=	0.0f;

		det			=	(invert.x.x*pCurr->x.x + invert.x.y*pCurr->y.x + invert.x.z*pCurr->z.x);

		if	(det != 0.0f)
		{
			det			=	1.0f / det;
			invert.x.x	*=	det;
			invert.x.y	*=	det;
			invert.x.z	*=	det;
			invert.y.x	*=	det;
			invert.y.y	*=	det;
			invert.y.z	*=	det;
			invert.z.x	*=	det;
			invert.z.y	*=	det;
			invert.z.z	*=	det;
		}

		invert.w.x	=	-(invert.x.x*pCurr->w.x + invert.y.x*pCurr->w.y + invert.z.x*pCurr->w.z);
		invert.w.y	=	-(invert.x.y*pCurr->w.x + invert.y.y*pCurr->w.y + invert.z.y*pCurr->w.z);
		invert.w.z	=	-(invert.x.z*pCurr->w.x + invert.y.z*pCurr->w.y + invert.z.z*pCurr->w.z);
		invert.w.w	=	1.0f;

		*pCurr		=	invert;
}

//-----------------------------------------------------------------------------
//	\function   void StartFrame(void)
//	\date			20/01/05
//	\brief			Sets the start of the display list for sceGu functions this frame & clears the screen
//-----------------------------------------------------------------------------
static void StartFrame(void)
{
	// Start of the display list
	sceGuStart(SCEGU_IMMEDIATE, gDisplayList, sizeof(gDisplayList));

	// Clear the screen
	sceGuClear(SCEGU_CLEAR_COLOR | SCEGU_CLEAR_DEPTH);
}

//-----------------------------------------------------------------------------
//	\function   void Render(void)
//	\date			20/01/05
//	\brief				
//-----------------------------------------------------------------------------
static void Render(void)
{
	// Set the View Matrix
	sceGumMatrixMode(SCEGU_MATRIX_VIEW);
	sceGumLoadIdentity();
	sceGumRotateY(SCEGU_RAD(gCamPosRot.rot.y));
	sceGumRotateX(SCEGU_RAD(gCamPosRot.rot.x));
	sceGumTranslate(&gCamPosRot.trans);
	sceGumStoreMatrix(&gViewMatrix);
	Invert43(&gViewMatrix);
	sceGumLoadMatrix(&gViewMatrix);

	// World Matrix
	sceGuEnable(SCEGU_LIGHTING);
	sceGumMatrixMode(SCEGU_MATRIX_WORLD);
	sceGumLoadIdentity();

	// Plane
	sceGuMaterial(SCEGU_AMBIENT , 0xFF000800);
	sceGuMaterial(SCEGU_DIFFUSE , 0x0055FF04);
	sceGuMaterial(SCEGU_SPECULAR, 0x00c0c0c0);
	sceGumDrawSpline(SCEGU_VERTEX_FLOAT, cPlaneDivs , cPlaneDivs, SCEGU_OPEN_OPEN, SCEGU_OPEN_OPEN, NULL, gaFloorData);

	// For both Torii
	sceGumTranslate(&gOffsetVec);													
	sceGuMaterial(SCEGU_AMBIENT, 0xFF202020);		// Material colours
	sceGuMaterial(SCEGU_DIFFUSE , 0x009999cc);
	sceGuMaterial(SCEGU_SPECULAR, 0x00242424);

	// Torus 1
	sceGumPushMatrix();														// store current matrix
	sceGumRotateX(SCEGU_RAD(90.0f));							// set local rotation 
	sceGumDrawBezier(SCEGU_VERTEX_FLOAT, cTorusU, cTorusV, NULL, gaTorusData);
	sceGumPopMatrix();															// restore the matrix
	
	// Torus 2
	gRotY += gAngle;
	ClampRot(&gRotY, gMaxAngle);

	sceGuMaterial(SCEGU_DIFFUSE , 0x00cc9999);

	sceGumRotateY(SCEGU_RAD(gRotY));						// rotation around the other torus ring
	sceGumTranslate(&gTorus2PosVec);							// column matrix order - postmultiplied
	sceGumDrawBezier(SCEGU_VERTEX_FLOAT, cTorusU, cTorusV, NULL, gaTorusData);

	// Light representation
	sceGuDisable(SCEGU_LIGHTING);
	sceGuColor(0xFFFFFFFF);
	sceGumLoadIdentity();
	sceGumTranslate(&gLightPosVec);
	sceGumScale(&gSphereScale);
	sceGumDrawBezier(SCEGU_VERTEX_FLOAT, cSphereU, cSphereV, NULL, gaSphereData);
}

//-----------------------------------------------------------------------------
//	\function   void EndFrame(void)
//	\date			20/01/05
//	\brief			Finished drawing for this frame, sync, wait, swap.
//-----------------------------------------------------------------------------
static void EndFrame(void)
{
	// Finish Drawing
	sceGuFinish();

	// Sync 
	sceGuSync(SCEGU_SYNC_FINISH, SCEGU_SYNC_WAIT);

	// Wait for V-Blank
	sceEmuVSync(SCEEMU_SYNC_WAIT);

	// Swap
	sceGuSwapBuffers();
}

//-----------------------------------------------------------------------------
//	\function   void ClampRot(SceFloat* element, SceFloat clampValue)
//	\date			20/01/05
//	\brief			Clamps rotation 
//-----------------------------------------------------------------------------
static void ClampRot(SceFloat* element, SceFloat clampValue)
{
	if(*element > clampValue) 
		*element -= clampValue;

	if(*element < 0.0f) 
		*element += clampValue;
}

//-----------------------------------------------------------------------------
//	\function   void ReadPad(void)
//	\date			20/01/05
//	\brief			Reads controller input and sets the camera variables accordingly
//-----------------------------------------------------------------------------
static void ReadPad(void)
{
	SceUInt32 padd;
	SceUChar8 buffer[4];
	SceFloat dx, dy;

	padd = sceEmuAnalogRead(buffer);

	dx = ( (SceInt32)buffer[2] - 128 ) / 128.0f;
	dy = ( (SceInt32)buffer[3] - 128 ) / 128.0f;

	if ( dx > -gDeadZone && dx < gDeadZone ) dx = 0.0f;
	if ( dy > -gDeadZone && dy < gDeadZone ) dy = 0.0f;

	gCamPosRot.rot.x += gAngle * dx;
	gCamPosRot.rot.y += gAngle * dy;	

	if (padd & SCEEMU_PAD_UP)		
		gCamPosRot.rot.x -= gAngle;
	if (padd & SCEEMU_PAD_DOWN) 	
		gCamPosRot.rot.x += gAngle;		
	if (padd & SCEEMU_PAD_LEFT) 	
		gCamPosRot.rot.y -= gAngle;		
	if (padd & SCEEMU_PAD_RIGHT)	
		gCamPosRot.rot.y += gAngle;
	
	ClampRot(&gCamPosRot.rot.x, gMaxAngle);
	ClampRot(&gCamPosRot.rot.y, gMaxAngle);
}

