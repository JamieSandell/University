//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////DIRECTX 9////////////////////////////////////////////////
//////////////////////////////////////////X FILES TUTORIAL 1//////////////////////////////////////////
///////////////////////////////////LOADING AND DISPLAYING AN X FILE///////////////////////////////////
/////////////////////////////////////////////JON PURDY////////////////////////////////////////////////
////////////////////////////////////////UNIVERSITY OF HULL////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include "DXUT.h"
#include "SDKmisc.h"
#include "resource.h"
#include "audio.h"
#include "Timer.h"
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <dinput.h>

using namespace std;

#define TITLE               "08356 ACW2 - Jamie Sandell"  //title for window



//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//*****************************Direct 3D Initialization***********************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
// global declarations

////////// Game
int score = 0; // player's score
float cubeXPos = 0.0; // X position of the cube
int maxXEmitterPos = 5; // Maximum X position (right) of the emitter
int minXEmitterPos = -5; // Minimum X position (left) of the emitter
bool newEmitter = false; // When this is true, the emitter is put in a new random position
Timer myTimer; // used to display the time in seconds since the start of the program
bool introDisplayed = true;
bool playGame = true;
//////////


///////// DirectX
LPDIRECTINPUT8 din;    // the pointer to our DirectInput interface
LPDIRECTINPUTDEVICE8 dinkeyboard;    // the pointer to the keyboard device
LPDIRECTINPUTDEVICE8 dinmouse;    // the pointer to the mouse device
LPDIRECT3D9						g_pD3D       = NULL; 
LPDIRECT3DDEVICE9				g_pd3dDevice = NULL; 
LPDIRECT3DDEVICE9 gD3dDevice = NULL;

LPD3DXMESH              g_pMesh          = NULL; // Our mesh object in sysmem   //New mesh code
D3DMATERIAL9*           g_pMeshMaterials = NULL; // Materials for our mesh      //New mesh code
LPDIRECT3DTEXTURE9*     g_pMeshTextures  = NULL; // Textures for our mesh       //New mesh code
DWORD                   g_dwNumMaterials = 0L;   // Number of mesh materials    //New mesh code  

LPD3DXFONT dxfont;    // the pointer to the font object
ID3DXSprite*                g_pTextSprite = NULL;   // Sprite for batching draw text calls
ID3DXFont*                  g_pFont = NULL;
ID3DXFont*                  g_pFont2 = NULL;
ID3DXFont*                  g_pStatsFont = NULL;
ID3DXMesh*                  g_pMesh3DText = NULL;
WCHAR*                      g_strTextBuffer = NULL;

TCHAR g_strFont[LF_FACESIZE];
int                         g_nFontSize;

//*****************************************************************************

D3DXMATRIX g_matProj;  
D3DXMATRIX g_matView;
D3DXMATRIX g_matWorld;
D3DXMATRIX matRotate, matTranslate, matScale;

// Direct3D 9 resources
ID3DXFont*                      g_pFont9 = NULL;
ID3DXSprite*                    g_pSprite9 = NULL;
ID3DXEffect*                    g_pEffect9 = NULL;
IDirect3DVertexDeclaration9*    g_pVertexDecl = NULL;
LPDIRECT3DVERTEXBUFFER9         g_pvbFloor = NULL;
LPDIRECT3DVERTEXBUFFER9         g_pvbSource = NULL;
LPDIRECT3DVERTEXBUFFER9         g_pvbListener = NULL;
LPDIRECT3DVERTEXBUFFER9         g_pvbGrid = NULL;


//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

struct D3DVERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR c;
};

const LPWSTR g_SOUND_NAMES[] =
{
	L"Heli.wav",
};

enum CONTROL_MODE
{
	CONTROL_SOURCE=0,
	CONTROL_LISTENER
}                               g_eControlMode = ( CONTROL_MODE )0;

// Must match order of g_PRESET_PARAMS
const LPWSTR g_PRESET_NAMES[ NUM_PRESETS ] =
{
	L"Default",
	L"Generic",
	L"Padded cell",
	L"Room",
	L"Bathroom",
	L"Living room",
	L"Stone room",
	L"Auditorium",
	L"Concert hall",
	L"Cave",
	L"Arena",
	L"Hangar",
	L"Carpeted hallway",
	L"Hallway",
	L"Stone Corridor",
	L"Alley",
	L"Forest",
	L"City",
	L"Mountains",
	L"Quarry",
	L"Plain",
	L"Parking lot",
	L"Sewer pipe",
	L"Underwater",
	L"Small room",
	L"Medium room",
	L"Large room",
	L"Medium hall",
	L"Large hall",
	L"Plate",
};

////////////////// function prototypes
void initDInput(HINSTANCE hInstance, HWND hWnd);    // sets up and initializes DirectInput
void detect_keys(void);    // gets the current keys being pressed
void detect_mousepos(void);    // gets the mouse movement and updates the static variables
void SetRandomEmitterPosition(void); // Sets a new random emitter position

HRESULT CreateD3DXTextMesh( IDirect3DDevice9* pd3dDevice, LPD3DXMESH* ppMesh, TCHAR* pstrFont, DWORD dwSize,						   BOOL bBold, BOOL bItalic );
HRESULT CreateD3DXFont( LPD3DXFONT* ppd3dxFont, TCHAR* pstrFont, DWORD dwSize );
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
									void* pUserContext );
/////////////////////////////////////

// Name: SetRandomEmitterPosition(void)
// Desc: Sets a new random emitter position
void SetRandomEmitterPosition(void)
{
	D3DXVECTOR3* vec = &g_audioState.vEmitterPos;
	int seed = time(NULL);
	srand(seed);
	while (vec->x == cubeXPos) // don't want the new emitter position to be in the same place
	{
		vec->x = rand () % (maxXEmitterPos - minXEmitterPos + 1) + minXEmitterPos;
	}
	newEmitter = false; // reset the flag so we don't get a new emitter
}

// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform matrices.
//-----------------------------------------------------------------------------

VOID SetupMatrices()
{
  // For our world matrix, we will just leave it as the identity
  D3DXMatrixIdentity( &g_matWorld );
  D3DXMatrixRotationYawPitchRoll( &matRotate, timeGetTime()/1000.0f, 
	timeGetTime()/700.0f, timeGetTime()/850.0f ); // Rotate the Cube
  D3DXMatrixTranslation(&matTranslate, cubeXPos, 0.0, 0.0); // Translate the cube
  D3DXMatrixMultiply(&g_matWorld,&matRotate,&matTranslate);
  g_pd3dDevice->SetTransform( D3DTS_WORLD, &g_matWorld );
  
  // Set up our view matrix. A view matrix can be defined given an eye point,
  // a point to lookat, and a direction for which way is up. Here, we set the
  // eye five units back along the z-axis and up three units, look at the
  // origin, and define "up" to be in the y-direction.
  D3DXMatrixLookAtLH( &g_matView, &D3DXVECTOR3( 0.0f, 0.0f,-15.0f ),
                                &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
                                &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
   g_pd3dDevice->SetTransform( D3DTS_VIEW, &g_matView );
  
  // For the projection matrix, we set up a perspective transform (which
  // transforms geometry from 3D view space to 2D viewport space, with
  // a perspective divide making objects smaller in the distance). To build
  // a perpsective transform, we need the field of view (1/4 pi is common),
  // the aspect ratio, and the near and far clipping planes (which define at
  // what distances geometry should be no longer be rendered).
  D3DXMatrixPerspectiveFovLH( &g_matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &g_matProj );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//*****************************Release objects ***********************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

VOID Cleanup()
{
	CleanupAudio(); // Cleanup the audio resources

	    if( g_pMeshMaterials != NULL ) 
        delete[] g_pMeshMaterials;

    if( g_pMeshTextures )
    {
        for( DWORD i = 0; i < g_dwNumMaterials; i++ )
        {
            if( g_pMeshTextures[i] )
                g_pMeshTextures[i]->Release();
        }
        delete[] g_pMeshTextures;
    }
    if( g_pMesh != NULL )
        g_pMesh->Release();
    if( g_pd3dDevice != NULL)
        g_pd3dDevice->Release();
    if( g_pD3D != NULL)
        g_pD3D->Release();

	// mouse and keyboard
	dinkeyboard->Unacquire();    // make sure the keyboard is unacquired
	dinmouse->Unacquire();    // make sure the mouse is unacquired
	din->Release();    // close DirectInput before exiting
	SAFE_DELETE_ARRAY( g_strTextBuffer );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//*****************************end of Release objects ***********************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//*****************************Initialise Direct 3D ***********************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

void InitializeDX(HWND hwnd)
{ 
	if(!( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		MessageBoxA(hwnd,"Direct3d Create problem", NULL, NULL);

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if(FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
									  D3DCREATE_SOFTWARE_VERTEXPROCESSING,
									  &d3dpp, &g_pd3dDevice ) ) )
			 MessageBoxA(hwnd,"CreateDevice problem", NULL, NULL);

	D3DXCreateFont(g_pd3dDevice,    // the D3D Device
				   30,    // font height of 30
				   0,    // default font width
				   FW_NORMAL,    // font weight
				   1,    // not using MipLevels
				   true,    // italic font
				   DEFAULT_CHARSET,    // default character set
				   OUT_DEFAULT_PRECIS,    // default OutputPrecision,
				   DEFAULT_QUALITY,    // default Quality
				   DEFAULT_PITCH | FF_DONTCARE,    // default pitch and family
				   L"Arial",    // use Facename Arial
				   &dxfont);    // the font object



 // Turn on the zbuffer
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    // Turn on ambient lighting 
    g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0xffffffff );

	// Create a D3DX font object
	D3DXCreateFont( gD3dDevice, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &g_pFont9 );

	StringCchCopy( g_strFont, 32, L"Arial" );

	HRSRC rsrc;
	HGLOBAL hgData;
	LPVOID pvData;
	DWORD cbData;

	rsrc = FindResource( NULL, MAKEINTRESOURCE( IDR_TXT ), L"TEXT" );
	if( rsrc != NULL )
	{
		cbData = SizeofResource( NULL, rsrc );
		if( cbData > 0 )
		{
			hgData = LoadResource( NULL, rsrc );
			if( hgData != NULL )
			{
				pvData = LockResource( hgData );
				if( pvData != NULL )
				{
					int nSize = cbData / sizeof( WCHAR ) + 1;
					g_strTextBuffer = new WCHAR[nSize];
					memcpy( g_strTextBuffer, ( WCHAR* )pvData, cbData );
					g_strTextBuffer[nSize - 1] = 0;
				}
			}
		}
	}

}

//--------------------------------------------------------------------------------------
// Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED)
// and aren't tied to the back buffer size
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
									void* pUserContext )
{
	HRESULT hr;

	// Read the D3DX effect file
	WCHAR str[MAX_PATH];
	DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;
#ifdef DEBUG_VS
	dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
	dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif
	V_RETURN( DXUTFindDXSDKMediaFileCch( str, MAX_PATH, L"XAudio2Sound3D.fx" ) );
	V_RETURN( D3DXCreateEffectFromFile( pd3dDevice, str, NULL, NULL, dwShaderFlags,
		NULL, &g_pEffect9, NULL ) );

	//
	// Create render elements
	//

	// Define the vertex elements.
	D3DVERTEXELEMENT9 VertexElements[ 3 ] =
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
		D3DDECL_END()
	};

	// Create a vertex declaration from the element descriptions.
	V_RETURN( pd3dDevice->CreateVertexDeclaration( VertexElements, &g_pVertexDecl ) );

	// Create our vertex buffers
	V_RETURN( pd3dDevice->CreateVertexBuffer( 4 * sizeof( D3DVERTEX ), 0, 0, D3DPOOL_MANAGED, &g_pvbFloor, NULL ) );
	V_RETURN( pd3dDevice->CreateVertexBuffer( 4 * sizeof( D3DVERTEX ), 0, 0, D3DPOOL_MANAGED, &g_pvbSource, NULL ) );
	V_RETURN( pd3dDevice->CreateVertexBuffer( 3 * sizeof( D3DVERTEX ), 0, 0, D3DPOOL_MANAGED, &g_pvbListener, NULL ) );

	const UINT lcount = 2 * ( ( ZMAX - ZMIN + 1 ) + ( XMAX - XMIN + 1 ) );
	V_RETURN( pd3dDevice->CreateVertexBuffer( 2 * sizeof( D3DVERTEX ) * lcount, 0, 0, D3DPOOL_MANAGED, &g_pvbGrid,
		NULL ) );

	return S_OK;
}

// this is the function that initializes DirectInput
void initDInput(HINSTANCE hInstance, HWND hWnd)
{
	// create the DirectInput interface
	DirectInput8Create(hInstance,    // the handle to the application
		DIRECTINPUT_VERSION,    // the compatible version
		IID_IDirectInput8,    // the DirectInput interface version
		(void**)&din,    // the pointer to the interface
		NULL);    // COM stuff, so we'll set it to NULL

	// create the keyboard device
	din->CreateDevice(GUID_SysKeyboard,    // the default keyboard ID being used
		&dinkeyboard,    // the pointer to the device interface
		NULL);    // COM stuff, so we'll set it to NULL

	// create the mouse device
	din->CreateDevice(GUID_SysMouse,    // the default mouse ID being used
		&dinmouse,    // the pointer to the device interface
		NULL);    // COM stuff, so we'll set it to NULL

	dinkeyboard->SetDataFormat(&c_dfDIKeyboard); // set the data format to keyboard format
	dinmouse->SetDataFormat(&c_dfDIMouse);    // set the data format to mouse format

	// set the control you will have over the keyboard
	dinkeyboard->SetCooperativeLevel(hWnd,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	// set the control you will have over the mouse
	dinmouse->SetCooperativeLevel(hWnd,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

	dinmouse->Acquire();    // Acquire the mouse only once

	return;    // return to WinMain()
}

// this is the function that detects keystrokes and displays them in a message box
void detect_keys(void)
{
	static BYTE keystate[256];    // create a static storage for the key-states
	dinkeyboard->Acquire();    // get access if we don't have it already
	dinkeyboard->GetDeviceState(256, (LPVOID)keystate);    // fill keystate with values

	if (keystate[DIK_LEFTARROW] & 0x80)
	{
		cubeXPos -= 1.0f; // move the cube left
		if (cubeXPos <= minXEmitterPos-1) // If the new position is not valid, move our cube back
		{
			cubeXPos += 1.0f;
		}
		else // if the new position was valid move the listener so it is at the same position as the cube
		{
			D3DXVECTOR3* vec = &g_audioState.vListenerPos;
			vec->x-=1.0f;
		}
		return;
	}
	if (keystate[DIK_RIGHTARROW] & 0x80)
	{
		cubeXPos += 1.0f; // move the cube right
		if (cubeXPos >= maxXEmitterPos+1) // If the new position is not valid, move our cube back
		{
			cubeXPos -= 1.0f;
		}
		else // if the new position was valid move the listener so it is at the same position as the cube
		{
			D3DXVECTOR3* vec = &g_audioState.vListenerPos;
			vec->x+=1.0f;
		}
		return;
	}

	if(keystate[DIK_SPACE] & 0x80)
	{
		if (introDisplayed) // if the intro is been displayed then disable it so the game is displayed
		{
			introDisplayed = false;
			myTimer.start(); // Start the game timer because the game has now begun
			return;
		}
		D3DXVECTOR3* vec = &g_audioState.vEmitterPos;
		if (cubeXPos == vec->x) // Have they scored a point?
		{
			score++; // Increase the score
			newEmitter = true; // Set the flag so the emitter is given a new random position
			return;
		}
	}
	return;
}

// this is the function that detets mouse movements and mouse buttons
void detect_mousepos(void)
{
	static DIMOUSESTATE mousestate;    // create a static storage for the mouse-states

	dinmouse->Acquire();    // get access if we don't have it already

	// fill the mousestate with values
	dinmouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mousestate);

	return;
} 

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//*****************************Initialise Direct 3D ***********************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//*****************************Load X File ***********************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

void InitGeometry()
{
    LPD3DXBUFFER pD3DXMtrlBuffer;

    // Load the mesh from the specified file
    if( FAILED( D3DXLoadMeshFromXA( "Cube.x", D3DXMESH_SYSTEMMEM, 
                                   g_pd3dDevice, NULL, 
                                   &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials, 
                                   &g_pMesh ) ) )
            MessageBoxA(NULL, "Could not find X file", NULL , MB_OK);
      

    // We need to extract the material properties and texture names from the 
    // pD3DXMtrlBuffer
    D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
    g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
    g_pMeshTextures  = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];

    for( DWORD i=0; i<g_dwNumMaterials; i++ )
    {
        // Copy the material
        g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

        // Set the ambient color for the material (D3DX does not do this)
        g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;

        g_pMeshTextures[i] = NULL;
        if( d3dxMaterials[i].pTextureFilename != NULL && 
            lstrlenA(d3dxMaterials[i].pTextureFilename) > 0 )
        {
            // Create the texture
            if( FAILED( D3DXCreateTextureFromFileA( g_pd3dDevice, 
                                                d3dxMaterials[i].pTextureFilename, 
                                                &g_pMeshTextures[i] ) ) )
				{
                    MessageBoxA(NULL, "Could not find texture map", "Meshes.exe", MB_OK);
                }

           
        }
    }

    // Done with the material buffer
    pD3DXMtrlBuffer->Release();


}





//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//*****************************Load X File ***********************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////








//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//**************************Render and display the scene********************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateANDRender()
{

	///////////////////// UPDATE THE SCENE ////////////////////
	if (newEmitter) // has the flag been set to set a new emitter position?
	{
		SetRandomEmitterPosition();
	}
	if(cubeXPos == g_audioState.emitter.Position.x) // if the cube is in the same position as the emitter
		// set the volume of the emitter to a higher value
	{
		g_audioState.emitter.pCone->OuterVolume = 10.0f;
	}
	else // otherwise set the emitter's volume to a lower value
	{
		g_audioState.emitter.pCone->OuterVolume = 1.0f;
	}
	UpdateAudio(); // Update the audio
	////////////////////////////////////////////////////////////

	////////////////////  RENDER THE SCENE /////////////////////
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );
	// Begin the scene.
	SetupMatrices();

	g_pd3dDevice->BeginScene();
	if (!introDisplayed) // If the intro flag is false then don't display it, display the game instead
	{
		// Rendering of scene objects happens here.
		for( DWORD i=0; i<g_dwNumMaterials; i++ )
        {
            // Set the material and texture for this subset
           g_pd3dDevice->SetMaterial( &g_pMeshMaterials[i] );
           g_pd3dDevice->SetTexture( 0, g_pMeshTextures[i] );
        
            // Draw the mesh subset
           g_pMesh->DrawSubset( i );
        }

		// create a RECT to contain the texts
		static RECT textbox; SetRect(&textbox, 0, 0, 640, 480); 

		// Draw the Score text
		char buffer[32];
		sprintf( buffer, "Score: %d", score );
		dxfont->DrawTextA(NULL,
			buffer,
			-1,
			&textbox,
			DT_TOP | DT_RIGHT,
			D3DCOLOR_ARGB(255, 255, 0, 255));
		// Draw the Timer text
		char timeString[10];
		int time = myTimer.getTime(); // Get the current time elapsed
		sprintf(timeString, "Time: %is", time); // Print the time passed since the start of the game
		dxfont->DrawTextA(NULL,
			timeString,
			-1,
			&textbox,
			DT_TOP | DT_LEFT,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else // If the intro flag is set to true then display the intro and game instructions
	{
		static RECT textbox; SetRect(&textbox, 0, 0, 640, 480);
		char introString[500];
		sprintf(introString, "If playing the GameCube use the GameCube controller\n to control the cube. If playing on the PC use the left and\nright arrows to control the cube. The sound will\nbecome louder once the cube is positioned over the\nemitter. Once over the emitter press the spacebar to\nscore a point. Score 10 points to complete the game\nPress the Spacebar to begin.", NULL); // Print the time passed since the start of the game
		dxfont->DrawTextA(NULL,
			introString,
			-1,
			&textbox,
			DT_TOP | DT_LEFT,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	g_pd3dDevice->EndScene();
	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );

	if (score >= 10) // Have they completed the game?
	{
		// Ask them if they would like to play again - Yes/No
		int reply = MessageBoxA(NULL, "Congratulations you've completed the game. Would you like to continue?","ACW",MB_YESNO);
		switch (reply)
		{
		case IDNO:
			playGame = false;
			break;
		default:
			myTimer.reset();
			score = 0;
			break;
		}
	}

}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//**************************end of Render and display the scene**************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

//****************************************MESSAGE HANDLER*********************************************

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK WindowProc(HWND hwnd, 
					UINT msg, 
                    WPARAM wparam, 
                    LPARAM lparam)
{
	// this is the main message handler of the system
	PAINTSTRUCT		ps;		// used in WM_PAINT
	HDC				hdc;	// handle to a device context

	if (!playGame)
	{
		PostMessage(hwnd, WM_DESTROY, 0, 0);
	}
	// what is the message 
	switch(msg)
		{	

		case WM_ACTIVATEAPP:
			{
				if( wparam == TRUE && !DXUTIsActive() ) // Handle only if previously not active 
				{
					if( !DXUTIsWindowed() )
						PauseAudio( true );
				}
				else if( wparam == FALSE && DXUTIsActive() ) // Handle only if previously active 
				{
					if( !DXUTIsWindowed() )
						PauseAudio( false );
				}
			}

		case WM_CREATE: 
        			{
			// do initialization stuff here
			return(0);
			} break;

		case WM_PAINT: 
			{
			// validate the window
			hdc = BeginPaint(hwnd,&ps);	 
			EndPaint(hwnd,&ps);
			return(0);
   			} break;

		case WM_KEYDOWN:
            			// Handle any non-accelerated key commands
            			switch (wparam)
            			{
                		case VK_ESCAPE:
                		case VK_F12:
                    		PostMessage(hwnd, WM_CLOSE, 0, 0);
                   		 return 0L;
           			}
				break;
		case WM_DESTROY: 
			{
			// kill the application	
			Cleanup();
			PostQuitMessage(0);
		
			return(0);
			} break;

		default:break;

		} // end switch

	// process any messages that we didn't take care of 
	return (DefWindowProc(hwnd, msg, wparam, lparam));

} // end WinProc

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************END OF MESSAGE HANDLER******************************************

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************ WIN MAIN*******************************************************

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

int WINAPI WinMain(	HINSTANCE hinstance,
			HINSTANCE hprevinstance,
			LPSTR lpcmdline,
			int ncmdshow)
{

	WNDCLASS		winclass;	// this will hold the class we create
	HWND			hwnd;		// generic window handle
	MSG			msg;		// generic message

	// first fill in the window class stucture
	winclass.style			= CS_HREDRAW | CS_VREDRAW;                  
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName	= NULL;
	winclass.lpszClassName	= L"DX9WinClass";


	//******************Timing variables*************
	LONGLONG time_now;		//Current time
	LONGLONG time_next;		//Time of the next update
	LONGLONG time_last;		//Time of last update.

	double time_scale;
	DWORD time_count;

	BOOL perf_count;
	LONGLONG perf_frequ;
	//*******************end of timeing variables**********

	//*******************INITAILISATIONS***************************


	//Timer initialisation

	if (QueryPerformanceFrequency((LARGE_INTEGER *)  &perf_frequ)){
		perf_count=TRUE;
		time_count=perf_frequ/60;
		QueryPerformanceCounter((LARGE_INTEGER *) &time_last);
		time_scale=1.0/perf_frequ;
	}
	else
	{
		time_last=timeGetTime();	//Set the initial time;
		time_scale=0.001;		//millisecond time scale;
		time_count=33;		//number of milliseconds between frames
	}
	time_next=time_last+time_count;		//set time update interval
	//**************************************************************



	// register the window class
	if (!RegisterClass(&winclass))
		return(0);
 
	// create the window

	if (!(hwnd = CreateWindowA( "DX9WinClass", // class
				TITLE,	     // title
				WS_OVERLAPPEDWINDOW | WS_VISIBLE,
				0,
				0,	 
				800,  ////Set the size of the window
                600,
				NULL,	   // handle to parent 
				NULL,	   // handle to menu
				hinstance,	// instance
				NULL)))	// creation parms
	return(0);

	// set up and initialize DirectInput
	initDInput(hinstance, hwnd);
	InitializeDX(hwnd);   ///Initialise 
	InitGeometry();
	HRESULT hr = InitAudio(); // Init the audio
	if( FAILED( hr ) )
	{
		OutputDebugString( L"InitAudio() failed.  Disabling audio support\n" );
	}

	hr = PrepareAudio( g_SOUND_NAMES[0] );
	if( FAILED( hr ) )
	{
		OutputDebugString( L"PrepareAudio() failed\n" );
	}

	SetRandomEmitterPosition();

	// enter main event loop
	ZeroMemory( &msg, sizeof(msg) );

	while(1)
	{
		Sleep(30);
		//if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		//	{ 
		//	if (msg.message == WM_QUIT) // test if this is a quit
		//		//ReleaseAllObjects();
	 //         		 break;
		//	TranslateMessage(&msg);   // translate any accelerator keys
		//	DispatchMessage(&msg); // send the message to the window proc
		//	}  //end if
		//else{
			if (perf_count)
				QueryPerformanceCounter((LARGE_INTEGER *) &time_now);
			else
				time_now=timeGetTime();

			if (playGame) // If playGame is true then render/update the game, else quit
			{
				if (time_now>time_next) 
				{
					UpdateANDRender();   //Do the game Stuff
					time_next=time_now + time_count;  //Reset the timer
					detect_keys();
					detect_mousepos();
				}
			}
			if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
			{ 
				if (msg.message == WM_QUIT) // test if this is a quit
				{
					break;
				}
				TranslateMessage(&msg);   // translate any accelerator keys
				DispatchMessage(&msg); // send the message to the window proc
			}
	} // end while


	// return to Windows like this
	return(msg.wParam);
} // end WinMain

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************ END OF WIN MAIN******************************************

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
