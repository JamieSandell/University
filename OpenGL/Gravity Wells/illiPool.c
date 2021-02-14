/*****************************2002*************************************/
/****       skel.c = OpenSkelGlut.c = Noosh97 with CAVE removed    ****/
/****      (C) 1994--2002 Board of Trustees University of Illinois ****/ 
/****      A Model Real-Time Interactive  C/OpenGL/GLUT  Animator  ****/
/****    George Francis, Stuart Levy, Glenn Chappell, Chris Hartman****/
/****    e-mail  gfrancis@math.uiuc.edu : revised 2jan02 by gkf    ****/
/****                                                              ****/
/****    modified Apr03 by Brian Townsend                          ****/
/****    to be used with illiPool                                  ****/
/**********************************************************************/
#include <stdlib.h>
#include <stdio.h>

#define UNIX 1  /* to simplify transfers from PC to REL */

#if (UNIX)
#include <glut.h>
#include <sys/time.h>
#else
#include <gl\glut.h>
#include <sys/timeb.h>
#endif

#include <math.h>
#pragma warning (disable:4305)       /* constant double-to-float  */
#define  MAX(x,y)         (((x)<(y))?(y):(x))
#define  MIN(x,y)         (((x)<(y))?(x):(y))
#define  CLAMP(x,u,v)     (x<u? u : (x>v ? v: x))
#define  ABS(u)           ((u)<0 ? -(u): (u))
#define  FOR(a,b,c)       for((a)=(b);(a)<(c);(a)++)
#define  DOT(p,q)         ((p)[0]*(q)[0]+(p)[1]*(q)[1]+(p)[2]*(q)[2])
#define  NRM(p)           sqrt(DOT((p),(p)))
#define  M_PI             (355./113)   /* sgi already defins \pi   */
#define  DG            M_PI/180
#define  S(u)          sin(u*DG)
#define  C(u)          cos(u*DG)
#define  CLAMP(x,u,v) (x<u? u : (x>v ? v: x))
#define  random        rand        /* library dependent name  */
#define IFCLICK(K,a){static ff=1; if(getbutton(K))ff=1-ff; if(ff){a} }
#define MERIDIANS 32    
#define LATITUDES 32  
#define MANYSTARS 10000


/**************************************************************************/
/************************* begin my illiPool code *************************/


/************************ global constants ************************/

int NUM_BALLS = 7;

/* for presentation purposes */
int demo_stage = 0;

float TIME_STEP = .1;      /* 1/approx number of frames per second */
float SCALE_RATIO = .5;    /* scale everything to appropriate size */

/* Pool table measurements in meters */
float TABLE_LENGTH = 108.0*2.54/100.0,
      TABLE_WIDTH = 54.0*2.54/100.0,
      TABLE_PLAYING_LENGTH = 100.0*2.54/100.0,
      TABLE_PLAYING_WIDTH = 50.0*2.54/100.0;

float BALL_RADIUS = 57.15e-3/2.0,  /* in meters */
      BALL_MASS = 0.5;            /* mass of each ball in kg */

float BALL_COLORS[11][3] = {{1.,1.,1.},
                            {1.,1.,0.},
                            {0.,0.,1.},
                            {1.,0.,0.},
                            {.5,0.,.5},
                            {1.,.5,0.},
                            {0.,.5,0.},
                            {.7,0.,.3},
                            {0.,0.,0.},
                            {.3,.7,.9},
                            {.7,.0,.9}};

/* to keep track of shot */  
int SHOT_IN_PROGRESS = 0;

/* variables to control cue */
int SHOW_CUE_AIM = 0;
float AIM_BALL_RADIUS = .1;
float cuePower = 1.0,
      cueAngle = 0.0,
      cueHeight = 0.0;

/******************************************************************/


/*************************** vector math **************************/

struct Vector {
  float x;
  float y;
  float z;
};

struct Vector makeVector(float x, float y, float z)
{
  struct Vector result;
  result.x = x;
  result.y = y;
  result.z = z;
  return result;
}

struct Vector vecNeg(struct Vector v)
{
  struct Vector result;
  result.x = -v.x;
  result.y = -v.y;
  result.z = -v.z;
  return result;
}

struct Vector vecAdd(struct Vector a, struct Vector b)
{
  struct Vector result;
  result.x = a.x + b.x;
  result.y = a.y + b.y;
  result.z = a.z + b.z;
  return result;
}

struct Vector vecDiff(struct Vector a, struct Vector b)
{
  struct Vector result;
  result.x = a.x - b.x;
  result.y = a.y - b.y;
  result.z = a.z - b.z;
  return result;
}

float vecMag(struct Vector v)
{
  return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}

struct Vector vecAbs(struct Vector v)
{
  return makeVector(ABS(v.x),ABS(v.y),ABS(v.z));
}

struct Vector vecScale(float a, struct Vector v)
{
  return makeVector(a*v.x,a*v.y,a*v.z);
}

float vecDot(struct Vector a, struct Vector b)
{
  return a.x*b.x+a.y*b.y+a.z*b.z;
}

struct Vector vecCross(struct Vector a, struct Vector b)
{
  struct Vector result;
  result.x = a.y*b.z-b.y*a.z;
  result.y = a.z*b.x-b.z*a.x;
  result.z = a.x*b.y-b.x*a.y;
  return result;
}

struct Vector vecUnit(struct Vector v)
{
  return vecScale(1/vecMag(v),v);
}

/******************************************************************/


/************************* ball structure *************************/

enum motion_type {STATIONARY,SLIDE,ROLL};

struct Ball {

  /* movement trackers */
  struct Vector r;
  struct Vector v;
  struct Vector w;

  /* state trackers */
  enum motion_type movement;
  int inGame;

  /* necessary constants */
  float radius;
  float color[3];             /* (R,G,B) */

};

/******************************************************************/


/************************* table structure ************************/

struct Table {
  struct Ball balls[16];  /* cue ball, balls 1-15 */
  double length;
  double width;
  double playing_length;
  double playing_width;
};

struct Table gameTable;

/******************************************************************/


/******************** initialization functions ********************/

/* initializes balls at beginning of game */
void initializeBall(int ball_num)
{
  int i;
  gameTable.balls[ball_num].radius = BALL_RADIUS/SCALE_RATIO;
  for(i=0;i<3;i++)
    gameTable.balls[ball_num].color[i] = BALL_COLORS[ball_num][i];
  gameTable.balls[ball_num].r = makeVector(0.0,0.0,0.0);
  gameTable.balls[ball_num].v = makeVector(0.0,0.0,0.0);
  gameTable.balls[ball_num].w = makeVector(0.0,0.0,0.0);
  gameTable.balls[ball_num].movement = STATIONARY;
  gameTable.balls[ball_num].inGame = 1;
}

/* positions the balls at start of game */
void rackBalls()
{
  float radius = gameTable.balls[0].radius;
  
  /* position cue ball at start of game */
  gameTable.balls[0].r.x = -gameTable.playing_length/4;
  gameTable.balls[0].r.y = 0;
  gameTable.balls[0].r.z = 0;
  
  /* position 1 ball with other balls behind it in rack */
  gameTable.balls[1].r.x = gameTable.playing_length/4;
  gameTable.balls[1].r.y = 0;
  gameTable.balls[1].r.z = 0;
  gameTable.balls[2].r.x = gameTable.balls[1].r.x + sqrt(3)*radius;
  gameTable.balls[2].r.y = gameTable.balls[1].r.y + radius;
  gameTable.balls[2].r.z = 0;
  gameTable.balls[3].r.x = gameTable.balls[1].r.x + sqrt(3)*radius;
  gameTable.balls[3].r.y = gameTable.balls[1].r.y - radius;
  gameTable.balls[3].r.z = 0;
  gameTable.balls[4].r.x = gameTable.balls[2].r.x + sqrt(3)*radius;
  gameTable.balls[4].r.y = gameTable.balls[2].r.y + radius;
  gameTable.balls[4].r.z = 0;
  gameTable.balls[5].r.x = gameTable.balls[2].r.x + sqrt(3)*radius;
  gameTable.balls[5].r.y = 0;
  gameTable.balls[5].r.z = 0;
  gameTable.balls[6].r.x = gameTable.balls[2].r.x + sqrt(3)*radius;
  gameTable.balls[6].r.y = gameTable.balls[3].r.y - radius;
  gameTable.balls[6].r.z = 0;
  gameTable.balls[7].r.x = gameTable.balls[4].r.x + sqrt(3)*radius;
  gameTable.balls[7].r.y = gameTable.balls[4].r.y + radius;
  gameTable.balls[7].r.z = 0;
  gameTable.balls[8].r.x = gameTable.balls[4].r.x + sqrt(3)*radius;
  gameTable.balls[8].r.y = gameTable.balls[4].r.y - radius;
  gameTable.balls[8].r.z = 0;
  gameTable.balls[9].r.x = gameTable.balls[6].r.x + sqrt(3)*radius;
  gameTable.balls[9].r.y = gameTable.balls[6].r.y + radius;
  gameTable.balls[9].r.z = 0;
  gameTable.balls[10].r.x = gameTable.balls[6].r.x + sqrt(3)*radius;
  gameTable.balls[10].r.y = gameTable.balls[6].r.y - radius;
  gameTable.balls[10].r.z = 0;
}

/* initializes table at beginning of game */
void createTable()
{
  int i;
  for(i=0;i<16;i++) initializeBall(i);
  gameTable.length = TABLE_LENGTH/SCALE_RATIO; 
  gameTable.width = TABLE_WIDTH/SCALE_RATIO;
  gameTable.playing_length = TABLE_PLAYING_LENGTH/SCALE_RATIO;
  gameTable.playing_width = TABLE_PLAYING_WIDTH/SCALE_RATIO;
  SHOW_CUE_AIM = 0;
  rackBalls();
}

/******************************************************************/


/************************ drawing functions ***********************/

void drawVertex(int th, int ta, struct Ball *ball)
{
  float rr,gg,bb;
  float nn[3];

  nn[0] = ball->radius*S(th)*C(ta)+ball->r.x;
  nn[1] = ball->radius*C(th)*C(ta)+ball->r.y;
  nn[2] = ball->radius*S(ta)+ball->r.z;

  rr = ball->color[0];
  gg = ball->color[1];
  bb = ball->color[2];

  glColor3f(rr,gg,bb);

  glVertex3f(nn[0],nn[1],nn[2]);

}

void drawBall(struct Ball *ball)
{
  int th, ta;
  int dth = 10, dta = 10;

  if(ball->inGame)
    for(th=0;th<360;th+=dth)
    {
      glBegin(GL_TRIANGLE_STRIP);
        for(ta=0;ta<360;ta+=dta)
        {
          drawVertex(th,ta,ball);
          drawVertex(th+dth,ta,ball);
        }
      glEnd();
    }
}

void drawCue()
{
  glEnable(GL_LINE_STIPPLE);
  glLineWidth(10.0);
  glBegin(GL_TRIANGLE_STRIP);
    /* chalk */
    glColor3f(0.,1,.0);
    glVertex3f(-(.1+cuePower),cueHeight-.015,0.0);
    glVertex3f(-(.1+cuePower),cueHeight-.035,0.0);   
    /* front */
    glColor3f(1.0,.8,.8);
    glVertex3f(-(.1+cuePower)-.04,cueHeight-.015,0.0);
    glVertex3f(-(.1+cuePower)-.04,cueHeight-.035,0.0);    
    glColor3f(1.0,.8,.8);
    glVertex3f(-(.1+cuePower)-.05,cueHeight-.015,0.0);
    glVertex3f(-(.1+cuePower)-.05,cueHeight-.035,0.0);
    glColor3f(1.0,.5,0.);
    glVertex3f(-(.1+cuePower)-.05,cueHeight-.01,0.0);
    glVertex3f(-(.1+cuePower)-.05,cueHeight-.04,0.0);
    /* handle */
    glColor3f(1.0,.5,0.);
    glVertex3f(-(.1+cuePower+1.8),cueHeight-.01,0.0);
    glVertex3f(-(.1+cuePower+1.8),cueHeight-.04,0.0);
    /* stripe */ 
    glColor3f(1.,1.,0.);
    glVertex3f(-(.1+cuePower+1.8),cueHeight-.01,0.0);
    glVertex3f(-(.1+cuePower+1.8),cueHeight-.04,0.0);
    glColor3f(1.,1.,0.);
    glVertex3f(-(.1+cuePower+1.85),cueHeight-.01,0.0);
    glVertex3f(-(.1+cuePower+1.85),cueHeight-.04,0.0);
    /* handle */
    glColor3f(1.0,.5,0.);
    glVertex3f(-(.1+cuePower+1.8),cueHeight-.01,0.0);
    glVertex3f(-(.1+cuePower+1.8),cueHeight-.04,0.0);
    /* stripe */ 
    glColor3f(0.7,0.,0.);
    glVertex3f(-(.1+cuePower+1.8),cueHeight-.02,0.0);
    glVertex3f(-(.1+cuePower+1.8),cueHeight-.03,0.0);
    glColor3f(0.7,0.,0.);
    glVertex3f(-(.1+cuePower+3.5),cueHeight-.02,0.0);
    glVertex3f(-(.1+cuePower+3.5),cueHeight-.03,0.0);
    /* handle */
    glColor3f(1.0,.5,0.);
    glVertex3f(-(.1+cuePower+1.8),cueHeight-.01,0.0);
    glVertex3f(-(.1+cuePower+1.8),cueHeight-.04,0.0);
    glColor3f(1.0,.1,0.);
    glVertex3f(-(.1+cuePower+3.5),cueHeight,0.0);
    glVertex3f(-(.1+cuePower+3.5),cueHeight-.05,0.0);
  glEnd();
  glLineWidth(1.0);
}

void drawCueAim()
{
  float x = gameTable.balls[0].r.x,
        y = gameTable.balls[0].r.y,
        z = 0;
  glBegin(GL_LINE_STRIP);
    glColor3f(1.0,0.2,0.2);
    glVertex3f(x,y,z);
    glVertex3f(x+cuePower*C(cueAngle),y+cuePower*S(cueAngle),z);
  glEnd();
}

void drawTable()
{
  float length = gameTable.length,
        width = gameTable.width,
        plength = gameTable.playing_length,
        pwidth = gameTable.playing_width,
        radius = gameTable.balls[0].radius;
  int i;

  glBegin(GL_QUAD_STRIP);
    glColor3d(0.,.7,0.);
    glVertex3d(-plength/2,pwidth/2,-radius);
    glVertex3d(plength/2,pwidth/2,-radius);
    glVertex3d(-plength/2,-pwidth/2,-radius);
    glVertex3d(plength/2,-pwidth/2,-radius);
  glEnd();

  glColor3f(0.,0.,0.);  
    glTranslatef(plength/2-.05, pwidth/2-.05, -radius+.01);
    glutWireSphere(radius*1.5, 10, 10);
    glTranslatef(-plength/2+.05, -pwidth/2+.05, radius-.01);
    
    glTranslatef(plength/2-.05, -pwidth/2+.05, -radius+.01);
    glutWireSphere(radius*1.5, 10, 10);
    glTranslatef(-plength/2+.05, pwidth/2-.05, radius-.01);
    
    glTranslatef(-plength/2+.05, pwidth/2-.05, -radius+.01);
    glutWireSphere(radius*1.5, 10, 10);
    glTranslatef(plength/2-.05, -pwidth/2+.05, radius-.01);
    
    glTranslatef(-plength/2+.05, -pwidth/2+.05, -radius+.01);
    glutWireSphere(radius*1.5, 10, 10);
    glTranslatef(plength/2-.05, pwidth/2-.05, radius-.01);
    
    glTranslatef(0, pwidth/2, -radius+.01);
    glutWireSphere(radius*1.5, 10, 10);
    glTranslatef(0, -pwidth/2, radius-.01);
    
    glTranslatef(0, -pwidth/2, -radius+.01);
    glutWireSphere(radius*1.5, 10, 10);
    glTranslatef(0, pwidth/2, radius-.01);
 
  /* draw rails,etc. */
  glBegin(GL_QUAD_STRIP);
    glColor3d(.7,.3,0.);
    glVertex3d(-length/2,pwidth/2,-radius-.005);
    glVertex3d(-plength/2,width/2,-radius-.005);
    glVertex3d(plength/2,width/2,-radius-.005);
    glVertex3d(length/2,pwidth/2,-radius-.005);
    glVertex3d(length/2,-pwidth/2,-radius-.005);
    glVertex3d(plength/2,-width/2,-radius-.005);
    glVertex3d(-plength/2,-width/2,-radius-.005);
    glVertex3d(-length/2,-pwidth/2,-radius-.005);
    glVertex3d(-length/2,pwidth/2,-radius-.005);
    glVertex3d(-plength/2,width/2,-radius-.005);
  glEnd();
    glBegin(GL_QUAD_STRIP);
    glColor3d(0.4,.2,0.);
    glVertex3d(-length/2,pwidth/2,-radius-.01);
    glVertex3d(length/2,pwidth/2,-radius-.01);
    glVertex3d(-length/2,-pwidth/2,-radius-.01);
    glVertex3d(length/2,-pwidth/2,-radius-.01);
    glVertex3d(-plength/2,width/2,-radius-.01);
    glVertex3d(plength/2,width/2,-radius-.01);
    glVertex3d(-plength/2,-width/2,-radius-.01);
    glVertex3d(plength/2,-width/2,-radius-.01);
  glEnd();
  
  for(i=0;i<NUM_BALLS;i++) drawBall(&(gameTable.balls[i]));

  if(SHOW_CUE_AIM)
  { 
    drawCueAim();
    /* draw cue ball for spin purposes */
    glTranslatef(1.7,1.7,0);
    glColor3f(1.0,1.0,1.0);
    glutSolidSphere(AIM_BALL_RADIUS,100,100);
    drawCue();
  }
}

/******************************************************************/


/*************************** ball movement ************************/

#define GRAVITY 9.81
#define MU_BALL 0.1
void collideBalls(int a, int b)
{
  struct Vector an,at,bn,bt,normVec;
  /*struct Vector vp1,vp2,vpr1,vpr2,ff1,ff2,dw1,dw2;*/
  float radius = gameTable.balls[a].radius;
  float impulse_time = .05;

  if(demo_stage == 3)
    gameTable.balls[a].movement = gameTable.balls[b].movement = STATIONARY;
  else
  {
    normVec = vecUnit(vecDiff(gameTable.balls[a].r,gameTable.balls[b].r));
  
    /*** linear transfer ***/
    an = vecScale(vecDot(gameTable.balls[a].v,vecNeg(normVec)),vecNeg(normVec));
    at = vecDiff(gameTable.balls[a].v,an);
    bn = vecScale(vecDot(gameTable.balls[b].v,normVec),normVec);
    bt = vecDiff(gameTable.balls[b].v,bn);
  
    gameTable.balls[a].v = vecAdd(at,bn);
    gameTable.balls[b].v = vecAdd(bt,an);

    /*** angular transfer ***/
    /*vp1 = vecCross(vecScale(radius,vecNeg(normVec)),gameTable.balls[a].w);
    vp2 = vecCross(vecScale(radius,normVec),gameTable.balls[b].w);
    
    vpr1 = vecDiff(vp1,vp2);
    vpr2 = vecDiff(vp2,vp1);
    
    ff1 = vecScale(-MU_BALL*BALL_MASS*vecMag(vecDiff(an,bn)),
          vecUnit(vecAdd(vpr1,at)));
    ff2 = vecScale(-MU_BALL*BALL_MASS*vecMag(vecDiff(an,bn)),
          vecUnit(vecAdd(vpr2,bt)));
    
    dw1 = vecScale(5*impulse_time/(2*BALL_MASS*radius*radius),
          vecCross(vecScale(radius,vecNeg(normVec)),ff1));
    dw2 = vecScale(5*impulse_time/(2*BALL_MASS*radius*radius),
          vecCross(vecScale(radius,normVec),ff2));*/
    
    /*gameTable.balls[a].w = vecAdd(gameTable.balls[a].w,dw1);
    gameTable.balls[b].w = vecAdd(gameTable.balls[b].w,dw2);*/
    gameTable.balls[a].w = gameTable.balls[b].w = makeVector(0.0,0.0,0.0);
  
    gameTable.balls[a].movement = gameTable.balls[b].movement = SLIDE;
  }
}

#define CUSHION_LOSS 0.2     /* linear (in speed) loss of energy by cushion */
#define MU_WALL 0.1          /* friction const between cushion an ball */
void bankBall(int a, int axis)
{
  struct Vector rv,ff,dw;
  struct Vector vt, vn; /* tangential and normal components of velocity */
  struct Vector vp;     /* perimeter velocity of ball at contact with cushion */
  float radius = gameTable.balls[a].radius;
  float impulse_time = .05; /* time ball is in contact with cushion */
  
  if(demo_stage == 3)
    gameTable.balls[a].movement = STATIONARY;
  else
  {
    if(axis)  /* y direction */
      vn = makeVector(0.0,gameTable.balls[a].v.y,0.0);
    else      /* x direction */
      vn = makeVector(gameTable.balls[a].v.x,0.0,0.0);
    vt = vecDiff(gameTable.balls[a].v, vn);
  
    rv = vecScale(radius,vecUnit(makeVector(vn.x,vn.y,.26*radius)));
    vp = vecAdd(vt,vecCross(gameTable.balls[a].w,rv));

    ff = vecScale(-vecMag(vn)*MU_WALL,vecUnit(vp));
  
    dw = vecScale(5*impulse_time/(2*BALL_MASS*radius*radius),ff);

    /* parallel component */
    /*gameTable.balls[a].w = vecAdd(gameTable.balls[a].w,dw);*/
    gameTable.balls[a].w = makeVector(0.0,0.0,0.0);

    /* normal component */
    gameTable.balls[a].v = vecAdd(gameTable.balls[a].v,vecAdd(
                           vecScale(1.0+sqrt(1.0-CUSHION_LOSS),vecNeg(vn)),ff));
    gameTable.balls[a].v.z = 0;  /* to greatly simplify things */
    gameTable.balls[a].movement = SLIDE;
  }
}

/******************************************************************/


/******************* collision detection - stage 3 ****************/

float calc_collision_time(int ball1, int ball2, double dt)
{
  float time1,time2; /* two possible answers */
  float a,b,c;
  struct Vector dv, dr;
  float radius = gameTable.balls[ball1].radius;
   
  dv = vecDiff(gameTable.balls[ball1].v,gameTable.balls[ball2].v);
  dr = vecDiff(gameTable.balls[ball1].r,gameTable.balls[ball2].r);
  a = vecDot(dv,dv);
  b = vecDot(dr,dv)/a;
  c = (vecDot(dr,dr)-4*radius*radius)/a;

  /* t^2 + 2b*t + c = 0 */
  c  = (b*b>c)? sqrt(b*b-c):1000;
  time1 = -b + c;
  time2 = -b - c;
   
  return MIN(time1,time2);
}

float calc_bank_time(int ball, int axis, double dt)
{
  float rail_pos;
  float radius = gameTable.balls[ball].radius;
  /* parameters for vector equation of a line */
  float r,v;
  if(axis == 0) /* in x direction */
  {
    r = gameTable.balls[ball].r.x;
    v = gameTable.balls[ball].v.x;
    rail_pos = gameTable.playing_length/2;
  } else   /* in y direction */
  {
    r = gameTable.balls[ball].r.y;
    v = gameTable.balls[ball].v.y;
    rail_pos = gameTable.playing_width/2;
  }

  /* position of ball is given by r + v*t */
  if(v != 0) /* can't be moving parallel to the rail */
  {
    return ((v/ABS(v))*(rail_pos-radius)-r)/v;
  }
  return 1000;
}

/******************************************************************/


/*************************** ball movement ************************/

void updatePos(float dt)
{    
  int i;
  float radius = gameTable.balls[0].radius;
  float pl = gameTable.playing_length/2,
        pw = gameTable.playing_width/2;

  for(i=0;i<NUM_BALLS;i++)
    if(gameTable.balls[i].movement!=STATIONARY && gameTable.balls[i].inGame)
    {
      /* translate balls */
      gameTable.balls[i].r = vecAdd(gameTable.balls[i].r,
                             vecScale(dt,gameTable.balls[i].v));

      /* check for pocketed balls */
      if(vecMag(vecDiff(makeVector(pl,pw,0.0),
                        vecAbs(gameTable.balls[i].r)))<=2*radius ||
         vecMag(vecDiff(makeVector(0.0,pw,0.0),
                        vecAbs(gameTable.balls[i].r)))<=2*radius)
        gameTable.balls[i].inGame = 0;
    }
  
}

void moveBalls(float dt)
{
  int i,j,k;
  int ball1,ball2;
  float collision_time,bank_time;
  double timestep=dt;
  enum event {NONE,COLLISION,BANK};
  enum event myEvent=NONE;

  /* determine if any collisions or banks will occur within time dt */
  for(i=0;i<NUM_BALLS;i++)
    if(gameTable.balls[i].inGame && (gameTable.balls[i].movement!=STATIONARY))
    {
      /* check for collision */
      for(j=0;j<NUM_BALLS;j++)
        if(i!=j)
        {
          collision_time = calc_collision_time(i,j,dt);
          /* if a collision is about to occur */
          if(0<=collision_time && collision_time<timestep) 
          { 
            ball1=i; ball2=j;
            myEvent=COLLISION;
            timestep=collision_time;
          }
        }
      
      /* check for bank */
      for(k=0;k<2;k++)
      {
        bank_time = calc_bank_time(i,k,dt);
        if(0<=bank_time && bank_time<timestep)
        {
          ball1=i; ball2=k;
          myEvent=BANK;
          timestep=bank_time;
        }
      }
    }

  /* update position of ball */
  if(demo_stage == 2)
    updatePos(dt);
  else
    updatePos(timestep);
  
  if(demo_stage == 0 || demo_stage > 2)
  {
    /* update velocity vectors if necessary */
    if(myEvent==COLLISION)
      collideBalls(ball1,ball2);
    else if(myEvent==BANK)
      bankBall(ball1,ball2);
  }

  if(demo_stage != 2)
    /* recurse */
    if(timestep < dt)
      moveBalls(dt-timestep);
}

#define VEL_MIN .05
#define OMEGA_MIN 0.5
float MU_SLIDE = 0.1,
      MU_ROLL = 0.02;
void updateTable(float dt)
{
  int i;
  int balls_moving = 0;
  struct Vector vp,vp2,vaccel,waccel,ff;
  float vpPar, vp2Par;
  float radius = gameTable.balls[0].radius;

  moveBalls(dt);

  /* calc new accelerations and speeds - stage 2 */
  for(i=0;i<NUM_BALLS;i++)
    if(gameTable.balls[i].movement!=STATIONARY && gameTable.balls[i].inGame)
    {
      balls_moving = 1;

      if(gameTable.balls[i].movement == SLIDE) /* if sliding */
      {
        /* relative perimeter velocity at point of contact with the felt */
        vp = vecAdd(gameTable.balls[i].v,
             vecCross(makeVector(0.0,0.0,-radius),gameTable.balls[i].w));        

        /* force of friction */
        ff = vecScale(-MU_SLIDE*BALL_MASS*GRAVITY,vecUnit(vp));
          
        vaccel = vecScale(1/BALL_MASS,ff);
        waccel = vecScale(5/(2*BALL_MASS*radius*radius),
                 vecCross(makeVector(0.0,0.0,-radius),ff));

        /* perform accelerations */
        gameTable.balls[i].w = vecAdd(gameTable.balls[i].w,vecScale(dt,waccel));
        gameTable.balls[i].v = vecAdd(gameTable.balls[i].v,vecScale(dt,vaccel));

        /* recalculate perimeter speed */
        vp2 = vecAdd(gameTable.balls[i].v,
              vecCross(gameTable.balls[i].w,makeVector(0.0,0.0,-radius)));

        vpPar  = vecDot(vp,vecDiff(vp,vp2));
        vp2Par = vecDot(vp2,vecDiff(vp,vp2));

        /* check to see if it should start to roll */
        if((vpPar > 0.0 && vp2Par < 0.0) || (vp2Par > 0.0 && vpPar < 0.0))
        {
           /* align linear velocity with angular velocity */
           gameTable.balls[i].v = vecCross(gameTable.balls[i].w,
                                           makeVector(0.0,0.0,radius));
           gameTable.balls[i].movement = ROLL;
        }
      } else             /* if rolling */
      {
        /* relative perimeter velocity at point of contact with the felt */
        vp = vecCross(makeVector(0.0,0.0,-radius),gameTable.balls[i].w);        

        /* force of friction */
        ff = vecScale(MU_ROLL*BALL_MASS*GRAVITY,vecUnit(vp));
          
        waccel = vecScale(5/(2*BALL_MASS*radius*radius),
                 vecCross(makeVector(0.0,0.0,-radius),ff));

        gameTable.balls[i].w = vecAdd(gameTable.balls[i].w,vecScale(dt,waccel));
        /* align v with w to assure rolling */
        gameTable.balls[i].v = vecCross(gameTable.balls[i].w,
                               makeVector(0.0,0.0,radius));
       }

     /* check to see if balls are about to stop */
     if(vecMag(gameTable.balls[i].w) < OMEGA_MIN &&
        vecMag(gameTable.balls[i].v) < VEL_MIN)
     {
       gameTable.balls[i].v = gameTable.balls[i].w = makeVector(0.0,0.0,0.0);
       gameTable.balls[i].movement = STATIONARY;
     }
     
  }

  if(!balls_moving)
    SHOT_IN_PROGRESS=0;
}

/******************************************************************/


/********************** shot control - stage 1 ********************/

#define SPRING_CONSTANT 50.0     /* to calculate force of shot */
#define IMPULSE_TIME .005        /* time of contact in seconds */

/* give cue ball initial velocities */
void shootBall(struct Vector x, struct Vector r)
{
  float radius = gameTable.balls[0].radius;
  
  /* linear component */
  gameTable.balls[0].v = vecScale(-SPRING_CONSTANT*IMPULSE_TIME/
                                  BALL_MASS/SCALE_RATIO,x);

  /* angular component */
  gameTable.balls[0].w = vecScale(5*IMPULSE_TIME/(2*BALL_MASS*radius*radius),
                         vecCross(r,vecScale(-SPRING_CONSTANT,x)));

  gameTable.balls[0].movement = SLIDE;

  if(demo_stage != 1)
    SHOT_IN_PROGRESS = 1;
}

/******************************************************************/


/*************************** cue control **************************/

void hitCue()
{
  float radius = gameTable.balls[0].radius;
  struct Vector xv = makeVector(-C(cueAngle)*cuePower,-S(cueAngle)*cuePower,0.0);
  struct Vector rv = vecScale(-sqrt(1-radius*radius),xv);
  rv.z = cueHeight*radius/AIM_BALL_RADIUS;
  shootBall(xv,rv);
  SHOW_CUE_AIM = 0;
}

/******************************************************************/


/************************** end my illiPool code **************************/
/**************************************************************************/


/************************** global variables **************************/
int win=1;                 /* used once to choose window size         */
float gap, gap0=1.;        /* deFault() uses gap0 set by arguments()  */
float lux[3]={1.,2.,3.};   /* world light non unit  vector */
float luxx[3];             /* object space  direction vector          */
float amb, pwr;        /*ambient fraction, pseudo-specular power      */
float mysiz,speed, torq, focal, wfar; /* navigation control variables */
unsigned int PAW,XX,YY,SHIF;  /* used in chaptrack gluttery           */ 
int xwide,yhigh;                /* viewportery width and height       */
int mode,morph,msg,binoc;       /* viewing globals */
int th0, th1, dth, ta0, ta1, dta;  /* torus parameters                */
#define FLYMODE  (0)         /* yellow: turns around head as center   */ 
#define TURNMODE (1)         /* purple: turns around object center    */ 
int ii, jj, kk;  float tmp, temp;          /* saves gray hairs later  */
float aff[16], starmat[16], mat[16];   /* OpenGL placement matrices   */ 
int binoc;                        /* flag for binocular stereo        */
float nose;                       /* to eye distance in console       */
char clefs[128];                  /* which keys were pressed last     */
/*********************** steering *************************************/
void autotymer(int reset){                         /* cheap animator  */
#define  TYME(cnt,max,act) {static cnt; if(first)cnt=max; else\
                            if(cnt?cnt--:0){ act ; goto Break;}}
  static first = 1;              /* the first time autymer is called  */
  if(reset)first=1;              /* or if it is reset to start over   */
  TYME( shrink , 150 , th0++;th1--;ta0++;ta1--)  
  TYME( pause  , 20, 0  )
  TYME( grow   , 150,th0--;th1++;ta0--;ta1++)
  TYME( dwell  , 30, 0  )
  TYME(finish  , 1 , first = 1 )  /* this TYME must be the last one   */
  first = 0;
  Break:   ;                    /* yes Virginia, C has gotos          */
}
/**********************************************************************/
void deFault(void){         /* (Z)ap also restores these assignments  */ 
  th0=5; th1=355;  ta0=5; ta1=355; gap = gap0;    /* torus parameters */ 
  msg=1; binoc=0; nose=.06; mode=TURNMODE;       /* gadget parameters */   
  speed=.02; torq=.02; focal = 2.; wfar=13; mysiz=.01; morph=0; 
  FOR(ii,0,16) starmat[ii]=aff[ii] = (ii/4==ii%4); /* identity matrix */ 
  amb = .3; pwr = 10;                            /* lighting params   */
  tmp=NRM(lux); FOR(ii,0,3)lux[ii] /= tmp;  /* normalize light vector */ 
  aff[12]=0; aff[13]= 0; aff[14]= -4.2; /* place where we can see it  */
  autotymer(1);          /* reset autotymer to start at the beginning */
  
  /************************* added code ***************************/
  createTable();
  /****************************************************************/
  
}

/**************************** modified ********************************/
void drawall(void)
{
  if(SHOT_IN_PROGRESS)
    updateTable(TIME_STEP);
  drawTable();
}
/**********************************************************************/



/**********************************************************************/
void drawstars(void){  /* replace with SLevy's much prettier stars    */ 
  static float star[MANYSTARS][3]; static int virgin=1;
  if(virgin){             /* first time through set up the stars      */
     FOR(ii,0,MANYSTARS){ /* in a unit cube then  on unit sphere      */
       FOR(jj,0,3)star[ii][jj]  =(float)random()/RAND_MAX - 0.5;
       tmp=NRM(star[ii]); FOR(jj,0,3)star[ii][jj]/=tmp;        
     }
   virgin=0; /* never again */
  }
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();           /* optional insurance or superstition    */ 
    glMultMatrixf(starmat);
    glColor3f(0.8,0.9,1.0);        
    glBegin(GL_POINTS); 
      FOR(ii,0,MANYSTARS)glVertex3fv(star[ii]); 
    glEnd();
  /* glutWireTeapot(1);  if you prefer one on the firmament instead  */ 
  glPopMatrix();            /* optional insurance or superstition    */
  glClear(GL_DEPTH_BUFFER_BIT); /* put the stars at infinity         */ 
}
/************************ steering ***********************************/
void arguments(int argc,char **argv){           /* Pat Hanrahan 1989 */
      while(--argc){++argv; if(argv[0][0]=='-')switch(argv[0][1]){
      case 'w': win =atoi(argv[1]); argv++; argc--; break; 
      case 'g': gap0 =atof(argv[1]); argv++; argc--; break;
      case 'L': lux[0]=atof(argv[1]);
                lux[1]=atof(argv[2]);
                lux[2]=atof(argv[3]); argv +=3; argc -=3; break;
   }}}
/**********************************************************************/
int number, hasnumber, decimal, sign;  /* globals for SLevy's gadgets */
   /* these are assigned in keyboard() but used by these factor fcns  */  
float getnumber(float dflt){    /*  from keyboard, factor of bump()   */ 
     float v = (sign ? -number : number);  /* positive or negative nr */
     if(!hasnumber) return dflt;       /* if no new nr use old on     */ 
     return decimal>0 ? v/(float)decimal : v;
}
void bump(float *val, float incr){          /* SLevy 98 */
  float by = fabs(incr);   /* wizard speak ... best not mess with it  */ 
  char fmt[8], code[32];
  int digits = 1;
  if(hasnumber) {
    *val = getnumber(0);
    return;
  }
  if(by <= .003) digits = 3;
  else if(by <= .03) digits = 2;
  sprintf(fmt, "%%.%de", digits);
  sprintf(code, fmt, *val * (1 + incr));
  sscanf(code, "%f", val);
}
/********************from SLevy 2jan02 ********************************/
int getbutton(char key) { 
    int uu = clefs[key & 127]; clefs[key & 127]=0; return uu;
}
/**********************************************************************/
void keyboard(unsigned char key, int x, int y){

struct Vector xv;
xv = makeVector(-0.5,0.0,0.0);

   clefs[key&127]=1;  /* globalize the keys that were pressed         */ 
#define  IF(K)            if(key==K)  
#define  PRESS(K,A,b)     IF(K){b;} IF(K-32){A;}  /* catch upper case */
#define  TOGGLE(K,flg)    IF(K){(flg) = 1-(flg); }
#define  CYCLE(K,f,m)   PRESS((K),(f)=(((f)+(m)-1)%(m)),(f)=(++(f)%(m)))
#define  SLIDI(K,f,m,M)   PRESS(K,(--f<m?m:f), (++f>M?M:f)) 
#define  SLIDF(K,f,m,M,d) PRESS(K,((f -= d)<m?m:f), ((f += d)>M?M:f))

/* Only 127 ASCII chars are processed in this GLUT callback function  */ 
/* Use the specialkeybo function for the special keys                 */ 
   IF(27) { exit(0); }                           /* ESC exit          */
   TOGGLE('v',binoc);                            /* cross-eyed STEREO */
   TOGGLE(' ',mode);                             /* space key         */
   TOGGLE('h',morph);                            /* autotymer on/off  */
   CYCLE('w',msg,3);           /* writing on/off/speedometer+bullseye */
   PRESS('n', nose -= .001 , nose += .001 );     /* for binoculars    */
   PRESS('s', bump(&speed,.02), bump(&speed,-.02));/* flying speed    */ 
   PRESS('q', bump(&torq, .02), bump(&torq, -.02)); /* turning speed  */
   PRESS('o', focal *= 1.1 , focal /= 1.1)       /* telephoto         */
   PRESS('i', mysiz /= 1.1, mysiz *= 1.1)        /* rescale the world */
   PRESS('p', wfar *= 1.01 , wfar   /= 1.01)   /* rear clipping plane */
   PRESS('z', deFault(), deFault());             /* zap changes       */

/************************* added key commands *************************/
   /* misc. key commands */
   PRESS('a',SHOW_CUE_AIM=1,SHOW_CUE_AIM=1);
   PRESS('h',hitCue(),hitCue());
   PRESS('d',demo_stage++,demo_stage--);
   PRESS('b',NUM_BALLS++,NUM_BALLS--);
   PRESS('t',TIME_STEP+=.01,TIME_STEP-=.01);
   PRESS('s',MU_SLIDE+=.01,MU_SLIDE-=.01);
   PRESS('r',MU_ROLL+=.001,MU_ROLL-=.001);
   /* aiming cue and controlling power */
   PRESS('8',cuePower /= 1.1, cuePower /= 1.1);
   PRESS('2',cuePower *= 1.1, cuePower *= 1.1);
   PRESS('4',cueAngle += 2, cueAngle += 2);
   PRESS('6',cueAngle -= 2, cueAngle -= 2);
   PRESS('5',cueAngle += 90, cueAngle += 90);
   /* where the cue ball is hit with respect to its center of mass */
   PRESS('1',cueHeight-=.01, cueHeight-=.01);
   PRESS('7',cueHeight+=.01, cueHeight+=.01);
/**********************************************************************/
   
/********** SLevy's parser creates the input decimal ******************/
   if(key >= '0' && key <= '9'){         /* if key is a digit numeral */
          hasnumber = 1; number = number*10+key-'0'; decimal *= 10; } 
   else if(key == '.') { decimal = 1; }  /* it's a decimal !          */
   else if(key == '-') { sign = -1; }    /* it's negative  !          */
   else { hasnumber = number = decimal = sign = 0;} /* erase mess     */
   glutPostRedisplay();                 /* in case window was resized */
}
/**********************************************************************/
void specialkeybo(int key, int x, int y){
  clefs[0]= key ;
  switch(key){    /*  HOME END PAGE_DOWN RIGHT F1 etc  see glut.h    */
  case GLUT_KEY_F1:  th0++; th1--; break;
  case GLUT_KEY_F2:  th0--; th1++; break;
  
/*********************** allow for finer tuning ***********************/
  case GLUT_KEY_UP: cuePower /= 1.01;
  case GLUT_KEY_DOWN: cuePower *= 1.01;
  case GLUT_KEY_RIGHT: cueAngle += .2;
  case GLUT_KEY_LEFT: cueAngle -= .2;
/**********************************************************************/  
  
  /* default: fprintf(stderr,"non-ASCII char [%d] pressed.\n", key); */
  }
  hasnumber=number=decimal=0; glutPostRedisplay();
}
/**********************************************************************/
#if (!UNIX)
float speedometer(void){                      /* this one is for win32*/ 
  double dbl; static double rate; static int ii=0;
  static struct _timeb lnow, lthen;
    if(++ii % 8 == 0){                 /* 8 times around measure time */
	   _ftime(&lnow);
		dbl =  (double)(lnow.time - lthen.time)
			 +(double)(lnow.millitm - lthen.millitm)/1000;
		lthen = lnow;  rate = 8/dbl;
      }
    return((float)rate);
}
#else
float speedometer(void){                    /* this one is for unix */
double dbl; static double rate; static int ii=0;
static struct timezone notused; static struct timeval now, then;
   if(++ii % 8 == 0){  /* 8 times around measure time */
      gettimeofday(&now, &notused); /* elapsed time */
      dbl =  (double)(now.tv_sec - then.tv_sec)
         +(double)(now.tv_usec - then.tv_usec)/1000000;
      then = now;  rate = 8/dbl;
      }
   return((float)rate);
}
#endif
/**********************************************************************/
void char2wall(float x,float y,float z, char buf[]){
     char *p; glRasterPos3f(x,y,z);
     for(p = buf;*p;p++) glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*p);
}
/**********************************************************************/
void messages(void){char buf[256]; 
  /* console messages are done differently from cave */
#define  LABEL(x,y,W,u) {sprintf(buf,(W),(u));char2wall(x,y,0.,buf);}
  glMatrixMode(GL_PROJECTION); glPushMatrix();  /* new projection matrix */
  glLoadIdentity(); gluOrtho2D(0,3000,0,3000);  /* new 2D coordinates */
  glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
      if(mode==TURNMODE) glColor3f(1.,0.,1.); else glColor3f(1.,1.,0.);
      LABEL(1500,1500,"%s","o"); /* place a bullseye dead center */
      if(msg!=2){              /* bypass the graffiti */
      LABEL(80,2840,"illiPool","");
      LABEL(10,10,"written by: Brian Townsend","");
      LABEL(10,80,"Time step %0.2f",TIME_STEP);
      /************ for presentation purposes ************/
      LABEL(10,150,"Demo Stage %i",demo_stage);
      /***************************************************/
      LABEL(80,2770,"  Cue Position     %0.4f",gameTable.balls[0].r.x/SCALE_RATIO);
      LABEL(80,2700,"                   %0.4f",gameTable.balls[0].r.y/SCALE_RATIO);
      LABEL(80,2630,"  Cue Velocity     %0.4f",gameTable.balls[0].v.x/SCALE_RATIO);
      LABEL(80,2560,"                   %0.4f",gameTable.balls[0].v.y/SCALE_RATIO);
      LABEL(80,2490,"  Cue Rotation     %0.4f",gameTable.balls[0].w.x);
      LABEL(80,2420,"                   %0.4f",gameTable.balls[0].w.y);
      LABEL(80,2350,"                   %0.4f",gameTable.balls[0].w.z);
      LABEL(80,2280,"  Cue movement     %s",(gameTable.balls[0].movement==ROLL)? 
                                 "ROLL" : ((gameTable.balls[0].movement==SLIDE)? 
                                 "SLIDE" : 
                                 "STATIONARY"));
      LABEL(80,2210,"MU_SLIDE %0.2f",MU_SLIDE);
      LABEL(80,2140,"MU_ROLL  %0.3f",MU_ROLL);
    } /* end bypass*/ 
    glPopMatrix();
    glMatrixMode(GL_PROJECTION); glPopMatrix();
} 
/************************ navigation **********************************/
void chaptrack(int paw,int xx,int yy,int shif){/* Glenn Chappell 1992 */
   long dx,dy; 
   dx = xx -.5*xwide; dx = abs(dx)>5?dx:0;        /* 5 pixel latency  */
   dy = yy -.5*yhigh; dy = abs(dy)>5?dy:0; 
   glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
   if(mode==TURNMODE) glTranslatef(aff[12],aff[13],aff[14]);
   glRotatef(dx*torq,0.,1.,0.); glRotatef(dy*torq,1.,0.,0.);
   if(paw&(1<<GLUT_RIGHT_BUTTON ))glRotatef(shif?-10:-1,0.,0.,1.);
   if(paw&(1<<GLUT_LEFT_BUTTON  ))glRotatef(shif?10:1,0.,0.,1.);
   if(mode==FLYMODE){
      glPushMatrix();
      glMultMatrixf(starmat);
      glGetFloatv(GL_MODELVIEW_MATRIX,starmat);
      glPopMatrix(); }
   if(paw&(1<<GLUT_MIDDLE_BUTTON))glTranslatef(0.,0.,shif?-speed:speed);
   if(clefs[0]==GLUT_KEY_PAGE_UP) glTranslatef(0., speed,0.);
   if(clefs[0]==GLUT_KEY_PAGE_DOWN) glTranslatef(0.,-speed,0.);
   if(mode==TURNMODE) glTranslatef(-aff[12],-aff[13],-aff[14]);
   glMultMatrixf(aff); 
   glGetFloatv(GL_MODELVIEW_MATRIX,aff);
   FOR(ii,0,3){luxx[ii]=0; FOR(jj,0,3)luxx[ii] +=aff[ii*4+jj]*lux[jj];}
   glPopMatrix();
}
/************************* scenery ************************************/
void reshaped(int xx, int yy){xwide=xx ; yhigh=yy;} /*win width,height*/
/**********************************************************************/
void drawcons(void){ float asp =(float)xwide/yhigh; /* aspect ratio   */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  glClearColor(0,0,0,0);   /* base color, try (.1,.2,.3,0.)           */  
  if(binoc) glViewport(0,yhigh/4,xwide/2,yhigh/2);
  glMatrixMode(GL_PROJECTION); glLoadIdentity();
  glFrustum(-mysiz*asp,mysiz*asp,-mysiz,mysiz,mysiz*focal,wfar); 
  glMatrixMode(GL_MODELVIEW); glLoadIdentity();
  drawstars();
  glTranslatef(-binoc*nose,0.0,0.0);
  glMultMatrixf(aff);
  drawall();
  if(binoc){
      glViewport(xwide/2,yhigh/4,xwide/2,yhigh/2); 
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      drawstars();
      glTranslatef(binoc*nose,0.0,0.0);
      glMultMatrixf(aff);
      drawall();
    }
  glViewport(0,0,xwide,yhigh);
  if(msg) messages(); 
  glutSwapBuffers();
}
/************************** steering **********************************/
void idle(void){            /* do this when nothing else is happening */
   if(morph) autotymer(0);                       /* advance autotymer */ 
   glutPostRedisplay();                          /* redraw the window */
   IFCLICK('=',chaptrack(PAW,XX,YY,SHIF);)       /* bypass navigation */
   glDisable(GL_DEPTH_TEST);                   /* bypass depth buffer */ 
   IFCLICK('-',glEnable(GL_DEPTH_TEST); )      /* bypass depth buffer */
}
/**********************************************************************/
void mousepushed(int but,int stat,int x,int y){
  if(stat==GLUT_DOWN) PAW |= (1<<but); /*key came down and called back*/
  else PAW &= (-1 ^ (1<<but));              /* on the wayup erase flag*/ 
  XX=x; YY=y;        /* position in window coordinates (pos integers) */ 
  SHIF=(glutGetModifiers()==GLUT_ACTIVE_SHIFT)?1:0;  /* shift down too*/
}
/**********************************************************************/
void mousemoved(int x,int y){ XX=x; YY=y; }
/***************** one ring to rule the all ***************************/
int main(int argc, char **argv){  
   arguments(argc,argv);                      /* from the commandline */
   deFault();                         /* values of control parameters */
       glutInit(&argc, argv);  
       glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
       switch(win){ 
           case 0: break;                   /* manage your own window */
           case 1: glutInitWindowSize(640, 480);
                   glutInitWindowPosition(100,100); break;
           case 2: glutInitWindowPosition(0,0); break;
         }
       glutCreateWindow("<* illiSkel 2002 in C/OpenGL/GLUT *>");
       if(win==2) glutFullScreen();
       glEnable(GL_DEPTH_TEST);                    /* enable z-buffer */
       glutDisplayFunc(drawcons); 
               /* the following are optional for interactive control  */ 
       glutKeyboardFunc(keyboard);
       glutSpecialFunc(specialkeybo);
       glutMouseFunc(mousepushed);
       glutMotionFunc(mousemoved);       
       glutPassiveMotionFunc(mousemoved); 
                                      /*  beyond here all are needed  */
       glutReshapeFunc(reshaped);
       glutIdleFunc(idle);             
       glutMainLoop();
}
/**********************************************************************/
 
