/*
********************************************************************************

Copyright 2006, 2007 Ben Ruyl                                                                              

This file is part of Sokoban 3D.

Sokoban 3D is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Sokoban 3D is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Sokoban 3D; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

********************************************************************************    
*/ 

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "sokomain.h"

float tex[] = {

	// front
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,

	//back
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 0.0f,
	0.0f, 1.0f,	

	// left
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,

	//right
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 0.0f,
	0.0f, 1.0f,
	//top:
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,

	// bottom
	1.0f, 1.0f,
	0.0f, 1.0f,	
	1.0f, 0.0f,
	0.0f, 0.0f,
};

float norm[] = {

	// Front Face
	0.0f, 0.0f, 1.0f,

	// Back Face
	0.0f, 0.0f,-1.0f,

	// Left Face
	-1.0f, 0.0f, 0.0f,

	// Right face
	1.0f, 0.0f, 0.0f,

	// Top Face
	0.0f, 1.0f, 0.0f,

	// Bottom Face
	0.0f,-1.0f, 0.0f,
};

void DrawSkybox(float x, float y, float z, float width, float height, float length)
{
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_TRIANGLE_STRIP);					
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x,y,z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y + height, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z); 
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_TRIANGLE_STRIP);			
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x,y,z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length); 	
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_TRIANGLE_STRIP);				
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x,y,z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,y,	z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y,z + length); 	
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_TRIANGLE_STRIP);					
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,y + height,z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length); 	
	glEnd();


	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_TRIANGLE_STRIP);				
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length); 
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_TRIANGLE_STRIP);				
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length); 
	glEnd();

	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

}



void DrawCrate(float x, float y, float z, float w, float h, float d, int texid)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glBindTexture(GL_TEXTURE_2D, texid);
	w *= 0.5f;
	h *= 0.5f;
	d *= 0.5f;

	/*GLfloat box[] = {
	// FRONT
	-w, -h,  d,
	w, -h,  d,
	-w,  h,  d,
	w,  h,  d,
	// BACK
	-w, -h, -d,
	-w,  h, -d,
	w, -h, -d,
	w,  h, -d,
	// LEFT
	-w, -h,  d,
	-w,  h,  d,
	-w, -h, -d,
	-w,  h, -d,
	// RIGHT
	w, -h, -d,
	w,  h, -d,
	w, -h,  d,
	w,  h,  d,
	// TOP
	-w,  h,  d,
	w,  h,  d,
	-w, h, -d,
	w,  h, -d,
	// BOTTOM
	-w, -h,  d,
	-w, -h, -d,
	w, -h,  d,
	w, -h, -d,
	};




	glVertexPointer(3, GL_FLOAT, 0, box); 
	glTexCoordPointer(2, GL_FLOAT, 0, tex);
	glNormalPointer(GL_FLOAT, sizeof( float )*3, norm);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY); 
	//glEnableClientState(GL_NORMAL_ARRAY);

	glNormal3f( 0.0f, 1.0f, 0.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); 
	glNormal3f( 0.0f,-1.0f, 0.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 4, 4); 
	glNormal3f( 0.0f, 0.0f, 1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
	glNormal3f( 0.0f, 0.0f,-1.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);

	glNormal3f( 1.0f, 0.0f, 0.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 16, 4);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glDrawArrays(GL_TRIANGLE_STRIP, 20, 4);
	glDisableClientState(GL_VERTEX_ARRAY); 
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);*/


	if (texid == -1)
		glDisable(GL_TEXTURE_2D);


	glBegin(GL_QUADS);
	// Top Face
	glNormal3f( 0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-w,  h, -d);	// Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-w,  h,  d);	// Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f( w,  h,  d);	// Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f( w,  h, -d);	// Top Right Of The Texture and Quad
	glEnd();

	if (texid == texture[10]) // only the top should have a star in it
		glBindTexture(GL_TEXTURE_2D, texture[6]);

	glBegin(GL_QUADS);
	// Bottom Face
	glNormal3f( 0.0f,-1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-w, -h, -d);	// Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f( w, -h, -d);	// Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f( w, -h,  d);	// Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-w, -h,  d);	// Bottom Right Of The Texture and Quad
	// Front Face
	glNormal3f( 0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-w, -h,  d);	// Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f( w, -h,  d);	// Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f( w,  h,  d);	// Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-w,  h,  d);	// Top Left Of The Texture and Quad
	// Back Face
	glNormal3f( 0.0f, 0.0f,-1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-w, -h, -d);	// Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-w,  h, -d);	// Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f( w,  h, -d);	// Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f( w, -h, -d);	// Bottom Left Of The Texture and Quad

	// Right face
	glNormal3f( 1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( w, -h, -d);	// Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f( w,  h, -d);	// Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f( w,  h,  d);	// Top Left Of The Texture and Quad
	glTexCoord2f(0.0f, 0.0f); glVertex3f( w, -h,  d);	// Bottom Left Of The Texture and Quad
	// Left Face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-w, -h, -d);	// Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-w, -h,  d);	// Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-w,  h,  d);	// Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-w,  h, -d);	// Top Left Of The Texture and Quad
	glEnd();

	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
}

void DrawScene()
{
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	float x = 0;
	float y = 0;
	float z = 0;
	float length = 400;
	float height = 400;
	float width = 400;

	x = 0;//x - width  / 2;
	y = 0;//y - height / 2;
	z = 0;//z - length / 2;


	if (mode == SELECT)
		glDisable(GL_LIGHTING);

	//  gluLookAt(-xpos, -ypos, -zpos, 0, 0, 0, 0, 1, 0);
	// glRotatef(360 - yrot,0,1.0f,0);


	glPushMatrix();
	// glTranslatef(xpos, ypos, zpos);

	glColor3f(1,1,1);

	if (mode == RENDER)
	{

		//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Draw Front side
		/*   glBindTexture(GL_TEXTURE_2D, texture[0]);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x-width,		  y-height,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x-width,		  y+height, z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z+length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y-height,		z+length);
		glEnd();

		// Draw Back side
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y-height,		z-length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z-length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x-width,		  y+height,	z-length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x-width,		  y-height,		z-length);
		glEnd();

		// Draw Left side
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x-width,		  y+height,	z-length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x-width,		  y+height,	z+length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x-width,		  y-height,		z+length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x-width,		  y-height,		z-length);
		glEnd();

		// Draw Right side
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y-height,		z-length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y-height,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height,	z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height,	z-length);
		glEnd();

		// Draw Up side
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z-length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x-width,		  y+height,	z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x-width,		  y+height,	z-length);
		glEnd();

		// Draw Down side
		glBindTexture(GL_TEXTURE_2D, texture[5]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x-width,		  y-height,		z-length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x-width,		  y-height,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y-height,		z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y-height,		z-length);
		glEnd();

		glEnable(GL_LIGHTING);
		glDepthMask(true); */
		if (RenderPass == 1)
			DrawSkybox(x, y, z, width, height, length);

	}

	glPopMatrix();



	if (FIsPlayingNewLevelAnimation)
	{
		glScalef(float(FNewLevelAnimFramesPos) / 180.0000f,
			float(FNewLevelAnimFramesPos) / 180.00000,
			float(FNewLevelAnimFramesPos) / 180.0000f);
	}
	//else
	//  glEnable(GL_LIGHTING);


	glColor4f(1, 1, 1, 1);

	int c = 0;
	for (int i = 0; i < FGameData[FThisLevel].FLevelWidth; i++)
		for (int j = 0; j < FGameData[FThisLevel].FLevelHeight; j++)
		{
			x = 0 - (5.0f * FGameData[FThisLevel].FLevelWidth / 2.0f) + 5*i;
			y = 0;
			z = 0 - (5.0f * FGameData[FThisLevel].FLevelHeight / 2.0f) + 5*j;

			glColor4f(1, 1, 1, 1);

			if ((FPuzzleFields[FThisLevel][i][j].FPartType != ptEmpty) &&
				(FPuzzleFields[FThisLevel][i][j].FPartType != ptWall))
			{


				if (EndPosOfPath.x == i && EndPosOfPath.y == j)
				{
					GLUquadricObj* QuadObj = gluNewQuadric();


					gluQuadricOrientation(QuadObj, GLU_OUTSIDE);
					gluQuadricDrawStyle(QuadObj, GLU_FILL);
					gluQuadricNormals(QuadObj, GLU_SMOOTH);
					gluQuadricTexture(QuadObj, GL_FALSE);


					glDisable(GL_TEXTURE_2D);

					glColor4f(0.3, 0.3, 0.8, 1);
					glPushMatrix();
					glTranslatef(x + 2.5f, y + 2.5f,
						z + 2.5f);
					//glBindTexture(GL_TEXTURE_2D, texture[8]);
					gluSphere(QuadObj, 0.5, 32, 32);
					glEnable(GL_TEXTURE_2D);
					glPopMatrix();

					gluDeleteQuadric(QuadObj);
					//        glColor3ub(100,100,47);
					// glColor3f(0.8, 0.8, 0);
				}

				// glColor3ub(47,79,47);
				glColor3ub(255,255,255);

				glPushName(c);


				if (ToggleShowCrates)
				{
					if (FPuzzleFields[FThisLevel][i][j].FIsCrateTarget)

						glBindTexture(GL_TEXTURE_2D, texture[10]);
					else
						glBindTexture(GL_TEXTURE_2D, texture[6]);



					glBegin(GL_QUADS);
					glNormal3f(0.0f, 1.0f, 0.0f);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(x,	  y,		z);
					glTexCoord2f(1.0f, 0.0f); glVertex3f(x,	  y,		z + 5);
					glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 5, y,		z + 5);
					glTexCoord2f(0.0f, 1.0f); glVertex3f(x + 5, y,		z);
					glEnd();
				}
				else
				{

					if (FPuzzleFields[FThisLevel][i][j].FIsCrateTarget)
						DrawCrate(x + 2.5f, y  - 0.625f, z + 2.5f, 5.0f, 1.25f, 5.0f, texture[10]);
					else
						DrawCrate(x + 2.5f, y  - 0.625f, z + 2.5f, 5.0f, 1.25f, 5.0f, texture[6]);
				}

				// DrawCrate(x + 2.5f, y  - 0.625f, z + 2.5f, 5.0f, 1.25f, 5.0f, texture[6]);
				/*   glBegin(GL_QUADS);
				glNormal3f(0.0f, 1.0f, 0.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(x,	  y,		z);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(x,	  y,		z + 5);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 5, y,		z + 5);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(x + 5, y,		z);
				glEnd();

				}*/

				glPopName();
			}


			if (ToggleShowCrates)
				if (FPuzzleFields[FThisLevel][i][j].FPartType == ptWall)
				{
					glColor4f(1, 1, 1, 1);
					//glColor4ub(70, 130, 180, 255);
					//glColor4ub(70, 60, 60, 255);
					// glColor4ub(28, 62, 69, 255);
					glColor4ub(41, 73, 72, 255);
					// glColor4ub(ir, ig, ib, 255);

					DrawCrate(x + 2.5f, y + 2.5f, z + 2.5f, 5.0f, 5.0f, 5.0f, texture[9]);
					glEnable(GL_TEXTURE_2D);
				}

				c++;
		}

		for (int i = 0; i < FGameData[FThisLevel].FCratesCount; i++)
		{
			glColor4f(1, 1, 1, 1);

			glPushMatrix();

			x = 0 - (5.0f * FGameData[FThisLevel].FLevelWidth / 2.0f) + 5*FCrateMoveX[i];
			y = 0;
			z = 0 - (5.0f * FGameData[FThisLevel].FLevelHeight / 2.0f) + 5*FCrateMoveZ[i];

			GLfloat em = 0;

			if (FPuzzleFields[FThisLevel][FGameData[FThisLevel].FCratesPosX[i]]
			[FGameData[FThisLevel].FCratesPosY[i]].FIsCrateTarget)
			{

				glColor3f(0.8, 0.8, 0);
			}

			//glTranslatef(x + 2.5f, y + 2.5f, z + 2.5f);

			//DrawGLObject(acrate);

			DrawCrate(x + 2.5f,y + 2.5f, z + 2.5f, 5.0f, 5.0f, 5.0f, texture[7]);


			glPopMatrix();
		}

		glColor4f(1, 1, 1, 1);

		x = 0 - (5.0f * FGameData[FThisLevel].FLevelWidth / 2.0f) + 5*FPlayerMoveX;
		y = 0;
		z = 0 - (5.0f * FGameData[FThisLevel].FLevelHeight / 2.0f) + 5*FPlayerMoveZ;
		//		{
		glPushMatrix();
		glTranslatef(x + 2.5f, y + 2.5f,
			z + 2.5f);
		glRotatef(playerrot, 0, 1, 0);

		GLUquadricObj* QuadObj = gluNewQuadric();


		gluQuadricOrientation(QuadObj, GLU_OUTSIDE);
		gluQuadricDrawStyle(QuadObj, GLU_FILL);
		gluQuadricNormals(QuadObj, GLU_SMOOTH);
		gluQuadricTexture(QuadObj, GL_FALSE);


		glEnable(GL_TEXTURE_2D);
		//  glBindTexture(GL_TEXTURE_2D, texture[8]);




		GLfloat specular [] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat shininess [] = { 25.0 };
		GLfloat noshininess [] = { 0.0 };
		GLfloat none [] = { 0.0, 0.0, 0.0, 0.0 };

		glColorMaterial(GL_FRONT, GL_AMBIENT);
		glColor3ub(75, 37, 37);
		glColorMaterial(GL_FRONT, GL_DIFFUSE);
		glColor3ub(100, 50, 50);
		glColorMaterial(GL_FRONT, GL_SPECULAR);
		glColor3f(0.6, 0.6, 0.6);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);


		/* glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);*/


		glDisable(GL_TEXTURE_2D);

		gluSphere(QuadObj, 2, 32, 32);

		glEnable(GL_TEXTURE_2D);


		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, noshininess);
		glColorMaterial(GL_FRONT, GL_SPECULAR);
		glColor3f(0, 0, 0);

		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);


		glColor3f(0, 0, 0);

		/* glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, none);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, none);*/



		glPopMatrix();

		glEnable(GL_TEXTURE_2D);

		gluDeleteQuadric(QuadObj);


		glPopMatrix();

		//	glPopMatrix();
}
