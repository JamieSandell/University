/* SCE CONFIDENTIAL
$PSLibId$
*/
/*
* Introduction to Programming the PSP(TM)
*
* Copyright (C) 2005 Sony Computer Entertainment Europe
* All Rights Reserved.
*
* PSP Intro Hardware Tool Sample one - hellotriangle.c
*   This sample demonstrates 2D rendering of a triangle, and prints some text to the screen.
*
*   Date            Design      Log
*  ----------------------------------------------------
*   2005-20-01      csawyer 	initial implementation
*/

//-----------------------------------------------------------------------------
// I N C L U D E S
//-----------------------------------------------------------------------------
#include <displaysvc.h>				// Needed for VSync
#include <psptypes.h>					// Some Handy typedefs and structures
#include <libgu.h>						// The graphics library
#include <moduleexport.h>		// Required for the module name info:

//-----------------------------------------------------------------------------
// M A C R O S 
//-----------------------------------------------------------------------------
SCE_MODULE_INFO( hellotriangle, 0, 1, 1 );

//-----------------------------------------------------------------------------
// T Y P E D E F S
//-----------------------------------------------------------------------------
typedef struct  {	
	SceUShort16 x, y, z;
} shortVector;

//-----------------------------------------------------------------------------
// P R O T O T Y P E S
//-----------------------------------------------------------------------------
static void Init(void);
static void StartFrame(void);
static void EndFrame(void);
static void Render(void);

//-----------------------------------------------------------------------------
// C O N S T A N T S
//-----------------------------------------------------------------------------
const char *gMsg = "Hello Triangle!";

//-----------------------------------------------------------------------------
// S T A T I C   V A R I A B L E S 
//-----------------------------------------------------------------------------
static char	disp_list[0x10000];
static shortVector gVectors[3];

//-----------------------------------------------------------------------------
// P U B L I C   F U N C T I O N S
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//	\function   main(void)
//	\date       20/01/05
//	\brief		After calling the relevant initialization functions,
//					Loops round continually calling the render function
//-----------------------------------------------------------------------------
int main(void)
{
	// Our Initialization function
	Init();

	// The render loop
	while(1){

		// Start the display list & clear the screen
		StartFrame();

		// Draw the triangle
		Render();

		// Finish drawing, Sync, Wait, Swap
		EndFrame();
	}

	// Shutdown libGu
	sceGuTerm();

	// The End
	return 0;
}

//-----------------------------------------------------------------------------
//	\function   Init(void)
//	\date			20/01/05
//	\brief			Initialises libGu, screen etc
//-----------------------------------------------------------------------------
static void Init(void)
{
	// Initialise libGu
	sceGuInit();

	// Set the start of the display list
	sceGuStart(SCEGU_IMMEDIATE, disp_list, sizeof(disp_list));
	sceGuDisplay(SCEGU_DISPLAY_ON);

	// Initialise the the back and front buffers, respectively
	sceGuDrawBuffer(SCEGU_PF5551, SCEGU_VRAM_BP_0, SCEGU_VRAM_WIDTH);
	sceGuDispBuffer(SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT, SCEGU_VRAM_BP_1, SCEGU_VRAM_WIDTH);

	// Init Screen coordinates into the drawing space - or something....
	sceGuOffset(SCEGU_SCR_OFFSETX, SCEGU_SCR_OFFSETY);

	// Init the viewport
	sceGuViewport(2048, 2048, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT);

	// Initialise the scissor region
	sceGuScissor(0, 0, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT);
	sceGuEnable(SCEGU_SCISSOR_TEST);

	// Create the background colour
	SceUInt32 alpha		= 255 << 24;
	SceUInt32 blue		= 127 << 16;
	SceUInt32 green		= 127 <<  8;
	SceUInt32 red		= 127 <<  0;	
	SceUInt32 colour	= alpha | blue | green | red; 

	// Set the clear colour
	sceGuClearColor(colour);

	// Something a little brighter for the triangle
	green	= 255 << 8;
	colour	|= green; 

	// Set the drawing colour
	sceGuColor(colour);
	// Finish 
	sceGuFinish();
	sceGuSync(SCEGU_SYNC_FINISH, SCEGU_SYNC_WAIT);
	sceDisplayWaitVblankStart();

	// Initialise the vertices with screen coordinates
	gVectors[0].x = SCEGU_SCR_WIDTH		/ 4;
	gVectors[0].y = SCEGU_SCR_HEIGHT	/ 5 * 4;
	gVectors[0].z = 0;

	gVectors[1].x = SCEGU_SCR_WIDTH		/ 2;
	gVectors[1].y = SCEGU_SCR_HEIGHT	/ 5;
	gVectors[1].z = 0;
	
	gVectors[2].x = SCEGU_SCR_WIDTH		/ 4 * 3;
	gVectors[2].y = SCEGU_SCR_HEIGHT	/ 5 * 4;
	gVectors[2].z = 0;
}

//-----------------------------------------------------------------------------
//	\function   StartFrame(void)
//	\date			20/01/05
//	\brief			Sets the start of the display list, and clears the colour buffer
//-----------------------------------------------------------------------------
static void StartFrame(void)
{
	// Start of the display list
	sceGuStart(SCEGU_IMMEDIATE, disp_list, sizeof(disp_list));

	// Clear the screen
	sceGuClear(SCEGU_CLEAR_COLOR);
}

//-----------------------------------------------------------------------------
//	\function   Render(void)
//	\date			20/01/05
//	\brief			Writes some text to the screen, and draws a triangle
//-----------------------------------------------------------------------------
static void Render(void)
{
	// Our screen text coordinates
	static SceUInt32 x = SCEGU_SCR_WIDTH  / 4;
	static SceUInt32 y = SCEGU_SCR_HEIGHT / 9 * 8;

	// Print our message
	sceGuDebugPrint(x, y, 0xFF00FFFF, gMsg);

	// Draw the triangle
	sceGuDrawArray(SCEGU_PRIM_TRIANGLES, SCEGU_VERTEX_SHORT | SCEGU_THROUGH, 3, 0, gVectors);
}

//-----------------------------------------------------------------------------
//	\function   EndFrame(void)
//	\date			20/01/05
//	\brief			Signals the end of drawing, syncs to this, waits for the V-Blank, then swaps buffers
//-----------------------------------------------------------------------------
static void EndFrame(void)
{
	// Finish Drawing
	sceGuFinish();

	// Sync 
	sceGuSync(SCEGU_SYNC_FINISH, SCEGU_SYNC_WAIT);

	// Wait for V-Blank
	sceDisplayWaitVblankStart();

	// Swap
	sceGuSwapBuffers();
}
