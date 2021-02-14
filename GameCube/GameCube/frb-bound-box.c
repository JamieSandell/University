/*---------------------------------------------------------------------------*
   Header files
 *---------------------------------------------------------------------------*/
#include <demo.h>
#include <math.h>

/*---------------------------------------------------------------------------*
   Macro definitions
 *---------------------------------------------------------------------------*/
#define PI          3.14159265F

#define MAX_Z       0x00ffffff // max value of Z buffer

#define NUM_CUBES   8

#define Clamp(val,min,max) \
    ((val) = (((val) < (min)) ? (min) : ((val) > (max)) ? (max) : (val)))

//
#define NUM_LIGHTS        1
#define NUM_PANELTYPE     6
#define PANEL_ARRAY_SIZE  ( 16 * 16 * 3 )

/*---------------------------------------------------------------------------*
   Structure definitions
 *---------------------------------------------------------------------------*/
// for camera
typedef struct
{
    Vec    location;
    Vec    up;
    Vec    target;
    f32    left;
    f32    top;
    f32    znear;
    f32    zfar;
} CameraConfig;

typedef struct
{
    CameraConfig  cfg; 
    Mtx           view;
    Mtx44         proj;
} MyCameraObj;

// for lighting
typedef struct
{
    f32         a0;
    f32         a1;
    f32         a2;
} AngleAttn;

typedef struct
{
    GXLightObj  lobj;
    Vec         pos;
    s32         theta;
    s32         phi;
    u32         colorIdx;
    u32         attnType;
    u32         enable;
} MyLightObj;

typedef struct
{
    MyLightObj  light[NUM_LIGHTS];
    GXAttnFn    attnFunc;
} MyLightEnvObj;

// for cube objects
typedef struct
{
    Vec         pos;
    Vec         vel;
    Vec         axis;
    f32         deg;
} MyCubeObj;

// bounding box
typedef u16 MyBoundingBox[4];

// for entire scene control
typedef struct
{
    MyCameraObj cam;
    MyCubeObj   cube[NUM_CUBES];
    u16         screen_width;
    u16         screen_height;
	u32             cur;
    u32             mode;
    u32             mark;
	MyLightEnvObj   lightEnv;
    Mtx            modelCtrl;
    u32            modelType;
    GXTexObj       texture;
    u32            tevMode;
} MySceneCtrlObj;

/*---------------------------------------------------------------------------*
   Forward references
 *---------------------------------------------------------------------------*/
void        main                ( void );
static void DrawInit            ( MySceneCtrlObj* sc );
static void DrawTick            ( MySceneCtrlObj* sc );
static void AnimTick            ( MySceneCtrlObj* sc );
static void DrawCubes           ( MySceneCtrlObj* sc );
static void SetCamera           ( MyCameraObj* cam );
static void SetLight        ( MyLightEnvObj* le, Mtx view );
static void DisableLight    ( void );

/*---------------------------------------------------------------------------*
  Lighting and model parameters
 *---------------------------------------------------------------------------*/
#define BLACK        MyColors[4]
#define REG_MATERIAL MyColors[5]

static GXColor MyColors[] ATTRIBUTE_ALIGN(32) =
{
    {0xff, 0xff, 0xff, 0xff},  // white
    {0xff, 0x00, 0x00, 0xff},  // red
    {0x00, 0xff, 0x00, 0xff},  // green
    {0x00, 0x00, 0xff, 0xff},  // blue

    {0x00, 0x00, 0x00, 0x00},  // black
    {0xc0, 0xc0, 0xc0, 0xff},  // material
    {0x10, 0x10, 0x10, 0xff}   // ambient
};

static Vec DefaultLightPos[4] =
{
    {  0.0F,  0.0F, 10000.0F },
    {  200, -200, 10000.0F },
    { -200, -200, 10000.0F },
    { -200,  200, 10000.0F }
};

#define NUM_OF_ATTNS    20
static AngleAttn LightAttnSamples[NUM_OF_ATTNS] =
{
    {  -9.0F,  10.0F,   0.0F  },
    { -24.0F,  25.0F,   0.0F  },
    { -49.0F,  50.0F,   0.0F  },
    {  -4.0F,   5.0F,   0.0F  },
    { -18.5F,  20.0F,   0.0F  },
    { -47.0F,  50.0F,   0.0F  },
    {-299.0F, 200.0F, 100.0F  },
    { -74.0F,  50.0F,  25.0F  },
    { -26.0F,  18.0F,   9.0F  },
    {  -2.0F,   2.0F,   1.0F  },
    {-297.0F, 200.0F, 100.0F  },
    { -72.5F,  50.0F,  25.0F  },
    {   0.5F,   0.5F,   0.25F },
    {  -0.5F,   2.0F,   1.0F  },
    {   1.0F,  -2.0F,   1.0F  },
    {  38.5F, -40.0F,   0.0F  },
    { -17.0F,  48.0F, -32.0F  },
    {  -3.0F,   8.0F,  -4.0F  },
    {   0.0F,   1.0F,   0.0F  },
    {   0.5F,   0.0F,   0.0F  }
};

/*---------------------------------------------------------------------------*
  Model and texture data
 *---------------------------------------------------------------------------*/
// for cube models
#define REG_AMBIENT  ColorArray[NUM_CUBES]
#define LIGHT_COLOR  ColorArray[NUM_CUBES+1]
#define BG_COLOR     ColorArray[NUM_CUBES+2]

static GXColor ColorArray[NUM_CUBES+3] ATTRIBUTE_ALIGN(32) = 
{
    { 0xFF, 0xFF, 0x80, 0xFF },
    { 0x00, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0x00, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0x00, 0xFF },
    { 0x20, 0x20, 0xFF, 0x80 },
    { 0x20, 0xA0, 0x00, 0x80 },
    { 0xC0, 0xC0, 0xC0, 0x40 },
    { 0xFF, 0x80, 0x80, 0x40 },
    { 0x40, 0x40, 0x40, 0xFF },    // Gray  (Ambient etc.)
    { 0xFF, 0xFF, 0xFF, 0xFF },    // White (Light etc.)
    { 0x00, 0x00, 0x00, 0x00 }     // Background
};

static Vec CubeIniData[NUM_CUBES*3] =
{
    // Position          Velocity                 Rotation axis
    { 0, 0,  0 }, {  0.0F,  0.0F,  0.0F }, {  0.0F,  1.0F,  1.0F },
};

/*---------------------------------------------------------------------------*
   Camera configuration
 *---------------------------------------------------------------------------*/
static CameraConfig DefaultCamera =
{
    {   0.0F, 0.0F, 300.0F }, // location
    {   0.0F, 1.0F, 0.0F }, // up
    {   0.0F, 0.0F, 0.0F }, // target
    -160.0F,  // left
     120.0F,  // top
     200.0F,  // near
    2000.0F   // far
};

/*---------------------------------------------------------------------------*
   Global variables
 *---------------------------------------------------------------------------*/
static MySceneCtrlObj   SceneCtrl;                // scene control parameters

/*---------------------------------------------------------------------------*
   Application main loop
 *---------------------------------------------------------------------------*/
void main ( void )
{
    DEMOInit(NULL);       // Init the OS, game pad, graphics and video.

    DrawInit(&SceneCtrl); // Initialize vertex formats, array pointers
                          // and default scene settings.

    while(!(DEMOPadGetButton(0) & PAD_BUTTON_MENU))
    {   
		DEMOBeforeRender();
        DrawTick(&SceneCtrl);    // Draw the model.
        DEMODoneRender();
        DEMOPadRead();           // Read controller
        AnimTick(&SceneCtrl);    // Do animation
    }

    OSHalt("End of test");
}

/*---------------------------------------------------------------------------*
   Functions
 *---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*
    Name:           DrawInit
    
    Description:    Initializes the vertex attribute format and sets up
                    the array pointer for the indexed data.
                    This function also initializes scene control parameters.
                    
    Arguments:      sc : pointer to the structure of scene control parameters
    
    Returns:        none
 *---------------------------------------------------------------------------*/
static void DrawInit( MySceneCtrlObj* sc )
{
    GXRenderModeObj *rmp;
    u32             i;
    // Get framebuffer size of current rendering mode
    rmp = DEMOGetRenderModeObj();
    sc->screen_width  = rmp->fbWidth;
    sc->screen_height = rmp->efbHeight;

    //  Vertex Attribute
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);

    //  Array Pointers and Strides
    GXSetArray(GX_VA_CLR0, ColorArray, 4 * sizeof(u8));

    // Z compare, pixel format and background color
    GXSetCopyClear(BG_COLOR, MAX_Z);


    // Default scene control parameter settings

    // camera
    sc->cam.cfg   = DefaultCamera;

    // cube objects
    for ( i = 0 ; i < NUM_CUBES ; ++i )
    {
        sc->cube[i].pos  = CubeIniData[i*3];
        sc->cube[i].vel  = CubeIniData[i*3+1];
        sc->cube[i].axis = CubeIniData[i*3+2];
        sc->cube[i].deg  = 0.0F;
    }

	    // light parameters
    for ( i = 0 ; i < 4 ; ++i )
    {
        sc->lightEnv.light[i].pos      = DefaultLightPos[i];
        sc->lightEnv.light[i].theta    = 0;
        sc->lightEnv.light[i].phi      = 0;
        sc->lightEnv.light[i].attnType = 0;
        sc->lightEnv.light[i].enable   = TRUE;
        sc->lightEnv.light[i].colorIdx = i;
    }
    sc->lightEnv.attnFunc = GX_AF_SPOT;
    
    //  current control object and control mode
    sc->cur  = 0;
    sc->mode = 0;
    sc->mark = 1;
}

/*---------------------------------------------------------------------------*
    Name:           DrawTick
    
    Description:    Draw the model by using given scene parameters 
                    
    Arguments:      sc : pointer to the structure of scene control parameters
    
    Returns:        none
 *---------------------------------------------------------------------------*/
static void DrawTick( MySceneCtrlObj* sc )
{
    static u16      token = 0;

    // Clear bounding box on HW
    GXClearBoundingBox();
    
    // Set up camera
    SetCamera(&sc->cam);
    
    // Draw cube models
    DrawCubes(sc);
    
    // Make sure every cubes are drawn
    GXSetDrawSync(++token);
    while ( GXReadDrawSync() != token )
    {}
}

/*---------------------------------------------------------------------------*
    Name:           AnimTick
    
    Description:    Changes scene parameters according to the pad status.
                    
    Arguments:      sc  : pointer to the structure of scene control parameters
    
    Returns:        none
 *---------------------------------------------------------------------------*/

static void AnimTick( MySceneCtrlObj* sc )
{
    u32  i;

    // Animate cubes
    if ( !(DEMOPadGetButton(0) & PAD_BUTTON_A) )
    {
        for ( i = 0 ; i < NUM_CUBES ; ++i )
        {
            // rotation
            sc->cube[i].deg += 5;
            if ( sc->cube[i].deg > 360 )
            {
                sc->cube[i].deg -= 360;
            }
            
            // position
			sc->cube[i].vel.x = DEMOPadGetStickX(0)/10;
			sc->cube[i].vel.y = DEMOPadGetStickY(0)/10;
            VECAdd(&sc->cube[i].pos, &sc->cube[i].vel, &sc->cube[i].pos);
            
         }
    }
}

/*---------------------------------------------------------------------------*
    Name:           DrawCubes
    
    Description:    Draw cube models
                    
    Arguments:      sc  : pointer to the structure of scene control parameters
 
    Returns:        none
 *---------------------------------------------------------------------------*/
static void DrawCubes( MySceneCtrlObj* sc )
{
    u32     i;
    Mtx     mt, mr, ms, mv, mvi;

    
    // set Tev operation to use vertex color
    GXSetNumTexGens(0);
	GXSetNumChans(1);
	GXSetNumTevStages(1);

	// enable lighting
    SetLight(&sc->lightEnv, sc->cam.view);

    for ( i = 0 ; i < NUM_CUBES ; ++i )
    {
        MTXTrans(mt, sc->cube[i].pos.x, sc->cube[i].pos.y, sc->cube[i].pos.z);
        MTXConcat(sc->cam.view, mt, mv);
        MTXScale(ms, 100.0F, 100.0F, 100.0F);
        MTXConcat(mv, ms, mv);
        MTXRotAxisDeg(mr, &sc->cube[i].axis, sc->cube[i].deg);
        MTXConcat(mv, mr, mv);
        GXLoadPosMtxImm(mv, GX_PNMTX0);
        MTXInverse(mv, mvi); 
        MTXTranspose(mvi, mv);
        GXLoadNrmMtxImm(mv, GX_PNMTX0);
        
        GXSetChanMatColor(GX_COLOR0A0, ColorArray[i]);
        
        GXDrawCube();	
    }

	// Tev mode = one color / no texture
    GXSetNumTexGens(0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    // disable lighting
    DisableLight();
}

/*---------------------------------------------------------------------------*
    Name:           SetCamera
    
    Description:    set view matrix and load projection matrix into hardware
                    
    Arguments:      cam : pointer to the MyCameraObj structure
                    
    Returns:        none
 *---------------------------------------------------------------------------*/
static void SetCamera( MyCameraObj* cam )
{
    MTXLookAt(
        cam->view,
        &cam->cfg.location,
        &cam->cfg.up,
        &cam->cfg.target );

    MTXFrustum(
        cam->proj,
        cam->cfg.top,
        - (cam->cfg.top),
        cam->cfg.left,
        - (cam->cfg.left),
        cam->cfg.znear,
        cam->cfg.zfar );
    GXSetProjection(cam->proj, GX_PERSPECTIVE);
}

/*---------------------------------------------------------------------------*
    Name:           SetLight
    
    Description:    Sets light objects and color channels
                    
    Arguments:      le   : pointer to a MyLightEnvObj structure
                    view : view matrix.
    
    Returns:        none
 *---------------------------------------------------------------------------*/
static void SetLight( MyLightEnvObj* le, Mtx view )
{
    f32 theta, phi;
    Vec ldir, lpos;
    AngleAttn attn;
    u32 i;
    u32 lmask = 0;

    for ( i = 0 ; i < NUM_LIGHTS ; ++i )
    {
        // direction
        theta = (f32)le->light[i].theta * PI / 180.0F;
        phi   = (f32)le->light[i].phi   * PI / 180.0F;
        ldir.x = sinf(theta);
        ldir.y = sinf(phi) * cosf(theta);
        ldir.z = - cosf(phi) * cosf(theta);
        
        // convert direction into view space
        MTXMultVecSR(view, &ldir, &ldir);
        
        // convert position into view space
        lpos = le->light[i].pos;
        MTXMultVec(view, &lpos, &lpos);
        
        // angular attenuation parameters
        attn = LightAttnSamples[le->light[i].attnType];

        // set parameters for one light
        GXInitLightDirv(&le->light[i].lobj, &ldir);
        GXInitLightPosv(&le->light[i].lobj, &lpos);
        GXInitLightColor(&le->light[i].lobj, MyColors[le->light[i].colorIdx]);
        GXInitLightAttn(
            &le->light[i].lobj,
            attn.a0,
            attn.a1,
            attn.a2,
            1.0F,
            0.0F,
            0.0F );
    }

    // loads each light object
    GXLoadLightObjImm(&le->light[0].lobj, GX_LIGHT0);
    GXLoadLightObjImm(&le->light[1].lobj, GX_LIGHT1);
    GXLoadLightObjImm(&le->light[2].lobj, GX_LIGHT2);
    GXLoadLightObjImm(&le->light[3].lobj, GX_LIGHT3);

    // light mask control
    lmask = le->light[0].enable ? ( lmask | GX_LIGHT0 ) : lmask;
    lmask = le->light[1].enable ? ( lmask | GX_LIGHT1 ) : lmask;
    lmask = le->light[2].enable ? ( lmask | GX_LIGHT2 ) : lmask;
    lmask = le->light[3].enable ? ( lmask | GX_LIGHT3 ) : lmask;

    // channel setting
    GXSetNumChans(1);     // number of active color channels
    GXSetChanCtrl(
        GX_COLOR0,
        GX_ENABLE,        // enable channel
        GX_SRC_REG,       // amb source
        GX_SRC_REG,       // mat source
        lmask,            // light mask
        GX_DF_CLAMP,      // diffuse function
        le->attnFunc);    // attenuation function
    GXSetChanCtrl(
        GX_ALPHA0,
        GX_DISABLE,       // disable channel
        GX_SRC_REG,       // amb source
        GX_SRC_REG,       // mat source
        0,                // light mask
        GX_DF_NONE,       // diffuse function
        GX_AF_NONE);      // attenuation function
    // set up ambient color
    GXSetChanAmbColor(GX_COLOR0A0, REG_AMBIENT);
    // set up material color
    GXSetChanMatColor(GX_COLOR0A0, REG_MATERIAL);
}

/*---------------------------------------------------------------------------*
    Name:           DisableLight
    
    Description:    Disables lighting
                    
    Arguments:      none
    
    Returns:        none
 *---------------------------------------------------------------------------*/
static void DisableLight( void )
{
    GXSetNumChans(1);
    GXSetChanCtrl(
        GX_COLOR0A0,
        GX_DISABLE,  // disable channel
        GX_SRC_VTX,  // amb source
        GX_SRC_VTX,  // mat source
        0,           // light mask
        GX_DF_NONE,  // diffuse function
        GX_AF_NONE);
}
