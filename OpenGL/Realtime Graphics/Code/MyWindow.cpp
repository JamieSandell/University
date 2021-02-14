#include <vector>
#include <cmath>
#include "MyWindow.h"
#include "Cube.h"
#include "Vector4f.h"
#include "Vector3f.h"

using namespace std;

MyWindow::MyWindow(float cam) {
	SetSize(512,512);
	SetDepthBits(24);
	_cameraAngle = cam;

	_lights = new MyCylinder[8];
	_lightSource = new Lights[1];

	// set the shading mode
	_gouraudShading = true;
	_wireframe = false;
	_flatShading = false;
	//for shadows
	SetStencilBits(1);
}

MyWindow::~MyWindow() {
	delete [] _lights;
	delete [] _images;
	delete [] _lightSource;
	if (_myScriptReader.GetNumberOfTextures()>0)
		delete [] _textures;
	else
		delete _textures;

	for (vector<Shape *>::iterator p = _allShapes.begin(); p != _allShapes.end(); ++p){
		delete *p;
	}
}

void MyWindow::PositionLights(void){	
	Vector4f position = _allShapes[0]->GetPosition();
	Vector3f heightWidthDepth = _allShapes[0]->GetHeightWidthDepth();
	Vector3f destination;
	destination.Assign(_allShapes[3]->GetPosition().x(), _allShapes[3]->GetPosition().y(), _allShapes[3]->GetPosition().z());

	// front top left light
	Vector4f newLightPosition(position.x()-(heightWidthDepth.y()/2), position.y()+(heightWidthDepth.x())/2,
		position.z()+(heightWidthDepth.z()/2), 1.0f); //physical light postion
	Vector3f newLightPosition2(position.x()-(heightWidthDepth.y()/2), position.y()+(heightWidthDepth.x())/2,
		position.z()+(heightWidthDepth.z()/2)); // used for DirectionVectorBetweenTwoPoints method

	_lights[0].SetPosition(newLightPosition); // new physical light position
	_lightSource[0].setPosition(newLightPosition); // new light source position
	_lightSource[0].setDirection(newLightPosition2.DirectionVectorBetweenTwoPoints(newLightPosition2, destination));
	Vector4f dest(destination.x(),destination.y(),destination.z(),1.0f);
	glPushMatrix();
	_lights[0].Update(dest);
	glPopMatrix();

	// front top right light
	newLightPosition.Assign(position.x()+(heightWidthDepth.y()/2), position.y()+(heightWidthDepth.x())/2,
		position.z()+(heightWidthDepth.z()/2), 1.0f);
	newLightPosition2.Assign(position.x()+(heightWidthDepth.y()/2), position.y()+(heightWidthDepth.x())/2,
		position.z()+(heightWidthDepth.z()/2));
	_lights[1].SetPosition(newLightPosition);
	_lightSource[1].setPosition(newLightPosition);
	_lightSource[1].setDirection(newLightPosition2.DirectionVectorBetweenTwoPoints(newLightPosition2, destination));
	glPushMatrix();
	_lights[1].Update(dest);
	glPopMatrix();

	// front bottom right light
	newLightPosition.Assign(position.x()+(heightWidthDepth.y()/2), position.y()-(heightWidthDepth.x())/2,
		position.z()+(heightWidthDepth.z()/2), 1.0f);
	newLightPosition2.Assign(position.x()+(heightWidthDepth.y()/2), position.y()-(heightWidthDepth.x())/2,
		position.z()+(heightWidthDepth.z()/2));
	_lights[2].SetPosition(newLightPosition);
	_lightSource[2].setPosition(newLightPosition);
	_lightSource[2].setDirection(newLightPosition2.DirectionVectorBetweenTwoPoints(newLightPosition2, destination));
	glPushMatrix();
	_lights[2].Update(dest);
	glPopMatrix();

	// front bottom left light
	newLightPosition.Assign(position.x()-(heightWidthDepth.y()/2), position.y()-(heightWidthDepth.x())/2,
		position.z()+(heightWidthDepth.z()/2), 1.0f);
	newLightPosition2.Assign(position.x()-(heightWidthDepth.y()/2), position.y()-(heightWidthDepth.x())/2,
		position.z()+(heightWidthDepth.z()/2));
	_lights[3].SetPosition(newLightPosition);
	_lightSource[3].setPosition(newLightPosition);
	_lightSource[3].setDirection(newLightPosition2.DirectionVectorBetweenTwoPoints(newLightPosition2, destination));
	glPushMatrix();
	_lights[3].Update(dest);
	glPopMatrix();

	// back top left light
	newLightPosition.Assign(position.x()-(heightWidthDepth.y()/2), position.y()+(heightWidthDepth.x())/2,
		position.z()-(heightWidthDepth.z()/2), 1.0f);
	newLightPosition2.Assign(position.x()-(heightWidthDepth.y()/2), position.y()+(heightWidthDepth.x())/2,
		position.z()-(heightWidthDepth.z()/2));
	_lights[4].SetPosition(newLightPosition);
	_lightSource[4].setPosition(newLightPosition);
	_lightSource[4].setDirection(newLightPosition2.DirectionVectorBetweenTwoPoints(newLightPosition2, destination));
	glPushMatrix();
	_lights[4].Update(dest);
	glPopMatrix();

	// back top right light
	newLightPosition.Assign(position.x()+(heightWidthDepth.y()/2), position.y()+(heightWidthDepth.x())/2,
		position.z()-(heightWidthDepth.z()/2), 1.0f);
	newLightPosition2.Assign(position.x()+(heightWidthDepth.y()/2), position.y()+(heightWidthDepth.x())/2,
		position.z()-(heightWidthDepth.z()/2));
	_lights[5].SetPosition(newLightPosition);
	_lightSource[5].setPosition(newLightPosition);
	_lightSource[5].setDirection(newLightPosition2.DirectionVectorBetweenTwoPoints(newLightPosition2, destination));
	glPushMatrix();
	_lights[5].Update(dest);
	glPopMatrix();

	// back bottom right light
	newLightPosition.Assign(position.x()+(heightWidthDepth.y()/2), position.y()-(heightWidthDepth.x())/2,
		position.z()-(heightWidthDepth.z()/2), 1.0f);
	newLightPosition2.Assign(position.x()+(heightWidthDepth.y()/2), position.y()-(heightWidthDepth.x())/2,
		position.z()-(heightWidthDepth.z()/2));
	_lights[6].SetPosition(newLightPosition);
	_lightSource[6].setPosition(newLightPosition);
	_lightSource[6].setDirection(newLightPosition2.DirectionVectorBetweenTwoPoints(newLightPosition2, destination));
	glPushMatrix();
	_lights[6].Update(dest);
	glPopMatrix();

	// back bottom left light
	newLightPosition.Assign(position.x()-(heightWidthDepth.y()/2), position.y()-(heightWidthDepth.x())/2,
		position.z()-(heightWidthDepth.z()/2), 1.0f);
	newLightPosition2.Assign(position.x()-(heightWidthDepth.y()/2), position.y()-(heightWidthDepth.x())/2,
		position.z()-(heightWidthDepth.z()/2));
	_lights[7].SetPosition(newLightPosition);
	_lightSource[7].setPosition(newLightPosition);
	_lightSource[7].setDirection(newLightPosition2.DirectionVectorBetweenTwoPoints(newLightPosition2, destination));
	glPushMatrix();
	_lights[7].Update(dest);
	glPopMatrix();
}


void MyWindow::OnCreate() {
	// todo: check the return bool
	bool createdSuccessfully = false;
	// create the lights (physical representation)
	createdSuccessfully = _lights[0].Create(&(Vector4f(0.0f, 0.5f, -2.0f, 1.0f)), 0.05f, false, "");
	createdSuccessfully = _lights[1].Create(&(Vector4f(0.0f, 0.5f, -2.0f, 1.0f)), 0.05f, false, "");
	createdSuccessfully = _lights[2].Create(&(Vector4f(0.0f, 0.5f, -2.0f, 1.0f)), 0.05f, false, "");
	createdSuccessfully = _lights[3].Create(&(Vector4f(0.0f, 0.5f, -2.0f, 1.0f)), 0.05f, false, "");
	createdSuccessfully = _lights[4].Create(&(Vector4f(0.0f, 0.5f, -2.0f, 1.0f)), 0.05f, false, "");
	createdSuccessfully = _lights[5].Create(&(Vector4f(0.0f, 0.5f, -2.0f, 1.0f)), 0.05f, false, "");
	createdSuccessfully = _lights[6].Create(&(Vector4f(0.0f, 0.5f, -2.0f, 1.0f)), 0.05f, false, "");
	createdSuccessfully = _lights[7].Create(&(Vector4f(0.0f, 0.5f, -2.0f, 1.0f)), 0.05f, false, "");
	createdSuccessfully = _myScriptReader.Create(".\\script.txt");
	_myScriptReader.ReadScriptFileAndParseIt(); // read the script file
	// Get the shapes
	_myScriptReader.GetAllShapes(_allShapes);
	// Get the rotation speed of the container
	angle_inc = _myScriptReader.GetRotationSpeed();
	// Get the light sources
	_lightSource = new Lights[8];
	_myScriptReader.GetLights(_lightSource, _numberOfLightsCreated);
	// turn the lights on
	for (int i = 0; i < _numberOfLightsCreated; i++)
		_lightSource[i].apply();
	// Create the textures
	int numberOfTextures = _myScriptReader.GetNumberOfTextures();
	if (numberOfTextures>0){
		_textures = new GLuint [numberOfTextures];
		_images = new Image [numberOfTextures];
	}
	LoadImages(_myScriptReader.GetNumberOfTextures(), _images, _myScriptReader.GetTextures());
	glGenTextures(_myScriptReader.GetNumberOfTextures(), &_textures[0]);
	Build2DMipMaps(_myScriptReader.GetNumberOfTextures(), _images, _textures);
	// Inverse the normals for the inner cube
	_allShapes[0]->InverseNormals(); // inverse the normals of the inner cube
	// set the projection required
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.1f, +0.1f, -0.1f, +0.1f, 0.1f, +30.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0,0, Width(), Height());
	glEnable(GL_DEPTH_TEST);
	// set the background clear colour to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// set the shade model to smooth (Gouraud shading)
	glShadeModel(GL_SMOOTH);
	// remove back faces
	glEnable(GL_CULL_FACE);
	// enable blending for transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	// turn the global ambient off by setting it to zero
	Color ambient(1.0,0.0,1.0,1.0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient.rgba());
	// set up engine variables
	angle = 0.0f;
	current_time = (float)App::GetTime();
	_startTime = (float)App::GetTime();
	_cameraPosition =-3.0;
	_cameraRotation = 0.0;
	_rotateBoxAutomatically = true;
	_direction = 1;
	_selectedMode = WIREFRAME;
	_shadowsToShow = NOSHADOWS;
	_maxSelectionModeValue = 3;
	_drawNormals = false;
	_animate = true;
	// turn the shader on
	//bool result = _myShader.Apply();
	//Create the fog
	_fogColor[0] = 0.5f;
	_fogColor[1] = 0.5f;
	_fogColor[2] = 0.5f;
	_fogColor[3] = 1;
	glFogfv(GL_FOG_COLOR, _fogColor);
	glFogf(GL_FOG_DENSITY, 0.35f);
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 0.0f);
	glFogf(GL_FOG_END, 10.0f);
	_fogEnabled = _myScriptReader.IsFogEnabled();
}
void buildShadowMatrix( float fMatrix[][16], const Vector4f &fLightPos, const Vector4f &fPlane, int fMatrixIndex )
{
	float dotp;

	// Calculate the dot-product between the plane and the light's position
	dotp = fPlane.x() * fLightPos.x() + 
		fPlane.y() * fLightPos.y() + 
		fPlane.z() * fLightPos.z() + 
		fPlane.w() * fLightPos.w();

	// First column
	fMatrix[fMatrixIndex][0]  = dotp - fLightPos.x() * fPlane.x();
	fMatrix[fMatrixIndex][4]  = 0.0f - fLightPos.x() * fPlane.y();
	fMatrix[fMatrixIndex][8]  = 0.0f - fLightPos.x() * fPlane.z();
	fMatrix[fMatrixIndex][12] = 0.0f - fLightPos.x() * fPlane.w();

	// Second column
	fMatrix[fMatrixIndex][1]  = 0.0f - fLightPos.y() * fPlane.x();
	fMatrix[fMatrixIndex][5]  = dotp - fLightPos.y() * fPlane.y();
	fMatrix[fMatrixIndex][9]  = 0.0f - fLightPos.y() * fPlane.z();
	fMatrix[fMatrixIndex][13] = 0.0f - fLightPos.y() * fPlane.w();

	// Third column
	fMatrix[fMatrixIndex][2]  = 0.0f - fLightPos.z() * fPlane.x();
	fMatrix[fMatrixIndex][6]  = 0.0f - fLightPos.z() * fPlane.y();
	fMatrix[fMatrixIndex][10] = dotp - fLightPos.z() * fPlane.z();
	fMatrix[fMatrixIndex][14] = 0.0f - fLightPos.z() * fPlane.w();

	// Fourth column
	fMatrix[fMatrixIndex][3]  = 0.0f - fLightPos.w() * fPlane.x();
	fMatrix[fMatrixIndex][7]  = 0.0f - fLightPos.w() * fPlane.y();
	fMatrix[fMatrixIndex][11] = 0.0f - fLightPos.w() * fPlane.z();
	fMatrix[fMatrixIndex][15] = dotp - fLightPos.w() * fPlane.w();
}

void findPlane( Vector4f &plane, const Vector3f &v0, const Vector3f &v1, const Vector3f &v2 )
{
	Vector3f vec0, vec1;

	// Need 2 vectors to find cross product
	vec0.AssignX(v1.x() - v0.x());
	vec0.AssignY(v1.y() - v0.y());
	vec0.AssignZ(v1.z() - v0.z());

	vec1.AssignX(v2.x() - v0.x());
	vec1.AssignY(v2.y() - v0.y());
	vec1.AssignZ(v2.z() - v0.z());

	// Find cross product to get A, B, and C of plane equation
	plane.AssignX(vec0.y() * vec1.z() - vec0.z() * vec1.y());
	plane.AssignY(-(vec0.x() * vec1.z() - vec0.z() * vec1.x()));
	plane.AssignZ(vec0.x() * vec1.y() - vec0.y() * vec1.x());

	plane.AssignW(-(plane.x() * v0.x() + plane.y() * v0.y() + plane.z() * v0.z()));
}

void MyWindow::DrawScene(float deltaTime){
	// Need to create 8 shadow matrices (because that is the number of lights)
		//per cube planes (6 planes, left,right,front,back,top,bottom)
	float g_shadowMatrix[8*6][16]; //numberOfLights*numberOfPlanes
	Vector4f g_lightPosition; // World position of light source, 8 of these, 1 for each lightSource
	Vector4f lightPos;
	vector<Vector4f> vecG_LightPosition;
	// populate the light position vector
	for (int i = 0; i < 8; i++){//number of lights
		lightPos = _lightSource[i].GetPosition();
		g_lightPosition[0] = lightPos.x(); //8 of these, 1 for each lightSource
		g_lightPosition[1] = lightPos.y(); //8 of these, 1 for each lightSource
		g_lightPosition[2] = lightPos.z(); //8 of these, 1 for each lightSource
		g_lightPosition[3] = lightPos.w(); //8 of these, 1 for each lightSource
		vecG_LightPosition.push_back(g_lightPosition);
	}
	Vector4f shadowPlane;
	vector<Vector3f> planeVector0, planeVector1, planeVector2; //6 lots of these, 1 for each of the planes of the box
	Vector3f v0, v1, v2;// these are pushed back onto planeVector0,1,2 respectively

	Vector4f boxCentre = _allShapes[0]->GetPosition();
	float boxSize = _allShapes[0]->GetHeightWidthDepth().x()/2;

	// Begin: Define Cube Planes
	// To define a plane that matches the floor, we need 3 vertices from it
	// left plane
	v0.AssignX(boxCentre.x()-(boxSize-0.1f)); //x
	v0.AssignY(boxCentre.y()+0.1f); //y
	v0.AssignZ(boxCentre.z()+0.4f);
	planeVector0.push_back(v0);

	v1.AssignX(boxCentre.x()-(boxSize-0.1f));
	v1.AssignY(boxCentre.y()+0.2f);
	v1.AssignZ(boxCentre.z()+0.3f);
	planeVector1.push_back(v1);

	v2.AssignX(boxCentre.x()-(boxSize-0.1f));
	v2.AssignY(boxCentre.y()+0.3f);
	v2.AssignZ(boxCentre.z()+0.2f);
	planeVector2.push_back(v2);
	// right plane
	v0.AssignX(boxCentre.x()+(boxSize-0.1f)); //x
	v0.AssignY(boxCentre.y()+0.1f); //y
	v0.AssignZ(boxCentre.z()+0.4f);
	planeVector0.push_back(v0);

	v1.AssignX(boxCentre.x()+(boxSize-0.1f));
	v1.AssignY(boxCentre.y()+0.2f);
	v1.AssignZ(boxCentre.z()+0.3f);
	planeVector1.push_back(v1);

	v2.AssignX(boxCentre.x()+(boxSize-0.1f));
	v2.AssignY(boxCentre.y()+0.3f);
	v2.AssignZ(boxCentre.z()+0.2f);
	planeVector2.push_back(v2);
	// front plane
	v0.AssignX(boxCentre.x()+0.1f); //x
	v0.AssignY(boxCentre.y()+(boxSize-0.1f)); //y
	v0.AssignZ(boxCentre.z()+0.4f);
	planeVector0.push_back(v0);

	v1.AssignX(boxCentre.x()+0.2f);
	v1.AssignY(boxCentre.y()+(boxSize-0.1f));
	v1.AssignZ(boxCentre.z()+0.3f);
	planeVector1.push_back(v1);

	v2.AssignX(boxCentre.x()+0.3f);
	v2.AssignY(boxCentre.y()+(boxSize-0.1f));
	v2.AssignZ(boxCentre.z()+0.2f);
	planeVector2.push_back(v2);
	// back plane
	v0.AssignX(boxCentre.x()+0.1f); //x
	v0.AssignY(boxCentre.y()-(boxSize-0.1f)); //y
	v0.AssignZ(boxCentre.z()+0.4f);
	planeVector0.push_back(v0);

	v1.AssignX(boxCentre.x()+0.2f);
	v1.AssignY(boxCentre.y()-(boxSize-0.1f));
	v1.AssignZ(boxCentre.z()+0.3f);
	planeVector1.push_back(v1);

	v2.AssignX(boxCentre.x()+0.3f);
	v2.AssignY(boxCentre.y()-(boxSize-0.1f));
	v2.AssignZ(boxCentre.z()+0.2f);
	planeVector2.push_back(v2);
	// bottom plane
	v0.AssignX(boxCentre.x()+0.1f); //x
	v0.AssignY(boxCentre.y()+0.4f); //y
	v0.AssignZ(boxCentre.z()-(boxSize-0.1f));
	planeVector0.push_back(v0);

	v1.AssignX(boxCentre.x()+0.2f);
	v1.AssignY(boxCentre.y()+0.3f);
	v1.AssignZ(boxCentre.z()-(boxSize-0.1f));
	planeVector1.push_back(v1);

	v2.AssignX(boxCentre.x()+0.3f);
	v2.AssignY(boxCentre.y()+0.2f);
	v2.AssignZ(boxCentre.z()-(boxSize-0.1f));
	planeVector2.push_back(v2);
	// top plane
	v0.AssignX(boxCentre.x()+0.1f); //x
	v0.AssignY(boxCentre.y()+0.4f); //y
	v0.AssignZ(boxCentre.z()+(boxSize-0.1f));
	planeVector0.push_back(v0);

	v1.AssignX(boxCentre.x()+0.2f);
	v1.AssignY(boxCentre.y()+0.3f);
	v1.AssignZ(boxCentre.z()+(boxSize-0.1f));
	planeVector1.push_back(v1);

	v2.AssignX(boxCentre.x()+0.3f);
	v2.AssignY(boxCentre.y()+0.2f);
	v2.AssignZ(boxCentre.z()+(boxSize-0.1f));
	planeVector2.push_back(v2);
	// End: Define Cube Planes

	vector<Vector4f> vecShadowPlanes;
	for (int i = 0; i < 8; i++){ // number of lights
		for (int j = 0; j < 6; j++){ //number of planes
			findPlane( shadowPlane, planeVector0[j], planeVector1[j], planeVector2[j] );
			vecShadowPlanes.push_back(shadowPlane);
		}
	}
	int counter = 0;
	int spCounter = 0;
	for (int i = 0; i < 8*6; i++){ //numberOfLights*numberOfPlanes
		if (counter>7)
			counter = 0;
		if (spCounter>5)
			spCounter = 0;
		buildShadowMatrix( g_shadowMatrix, vecG_LightPosition[counter], vecShadowPlanes[spCounter], i );
		counter++;
		spCounter++;
	}

	// place the box
	glPushMatrix();
		if (_fogEnabled)
			glEnable(GL_FOG);
		else
			glDisable(GL_FOG);
		glTranslatef(0.0f,0.0f,_cameraPosition);
		glRotatef(_cameraAngle, 1.0f,0.0f,0.0f);
		//glRotatef(_cameraRotation, 0.0f, 1.0f, 0.0f);

		glTranslatef(_allShapes[0]->GetPosition().x(), _allShapes[0]->GetPosition().y(), _allShapes[0]->GetPosition().z());

		// TODO: split this into a method
		// Begin Light Section
		glRotatef(angle, 0.0f, 0.0f, 1.0f); // rotates with the box but doesn't rotate the light
		//glRotatef(angle, 0.0f, 1.0f, 0.0f); // doesn't rotate with the box but does rotate the light
		glTranslatef(-(_allShapes[0]->GetPosition().x()), -(_allShapes[0]->GetPosition().y()),
			-(_allShapes[0]->GetPosition().z())); // reverse translation
		// from putting the box into place
		Update(deltaTime);// update the scene; // It matters where this command is because the
		// light position is offset from the above glTranslate
		glEnable(GL_LIGHTING);

		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilOp(GL_REPLACE,GL_REPLACE,GL_REPLACE); // set the inner containers stencil bits to 1
		// draw the boxes, inner container with inversed normals, this is the method to achieve the
		// transparency described in the spec, inside faces get lit whilst front facing faces
		// are transparent
		// The inner box is not drawn until after every other object has been drawn because of alpha-blending
		// to achieve the transparency effect
		glPushMatrix(); //inner container
			if (_selectedMode!=NONTEXTUREDFLATSHADING && _selectedMode!=SMOOTHSHADING && _selectedMode!=WIREFRAME){
				if (_allShapes[0]->GetTextureEnabledStatus()){
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, _allShapes[0]->GetTextureID());
				}
			}
			else
				glDisable(GL_TEXTURE_2D);
			glCullFace(GL_FRONT);//don't show the front face (for the transparency effect)
			_allShapes[0]->ApplyMaterial();
			glTranslatef(_allShapes[0]->GetPosition().x(), _allShapes[0]->GetPosition().y(), _allShapes[0]->GetPosition().z());
			_allShapes[0]->Draw();
			if (_drawNormals)
				_allShapes[0]->DrawNormals();
			glCullFace(GL_BACK); //don't cull the front faces of the other objects
		glPopMatrix();

		glStencilFunc(GL_EQUAL, 1, 1);
		glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
		/*stencil test will pass if and only if the stencil buffer bit for a pixel is set to the reference value 1.
		Whatever the outcome, the stencil buffer value is left as it is (1 or 0).*/
		// draw shadows
		if (_shadowsToShow==WALLSHADOWS){
			for (int i = 0; i < 8*6; i++){//numberOfLights*numberOfPlanes
				for (vector<Shape *>::const_iterator p = _allShapes.begin()+2; p != _allShapes.end(); ++p){ // skip the first 2, first 2 are containers
					// and have transparency, as such they must be drawn after opaque shapes
					glPushMatrix();
					glDisable(GL_LIGHTING);
					glDisable(GL_TEXTURE_2D);
					glColor3f(0.2f, 0.2f, 0.2f);
					glMultMatrixf((GLfloat *)g_shadowMatrix[i]);
					glTranslatef((*p)->GetPosition().x(), (*p)->GetPosition().y(), (*p)->GetPosition().z());
					(*p)->Draw();
					glEnable(GL_LIGHTING);
					glPopMatrix();
				}
			}
		}
		//turn off the stencil test
		glDisable(GL_STENCIL_TEST);
		// draw all shapes (excluding the outer and inner box)
		for (vector<Shape *>::const_iterator p = _allShapes.begin()+2; p != _allShapes.end(); ++p){ // skip the first 2, first 2 are the boxes
		// and the outer container has transparency, as such it must be drawn after the opaque shapes
		glPushMatrix();
			glTranslatef((*p)->GetPosition().x(), (*p)->GetPosition().y(), (*p)->GetPosition().z());
			if (_selectedMode!=NONTEXTUREDFLATSHADING && _selectedMode!=SMOOTHSHADING && _selectedMode!=WIREFRAME){
				if ((*p)->GetTextureEnabledStatus()){
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, (*p)->GetTextureID());
				}
			}
			(*p)->ApplyMaterial();
			(*p)->Draw();
			glDisable(GL_TEXTURE_2D);
			if (_drawNormals)
				(*p)->DrawNormals();
		glPopMatrix();
		}

		glDisable(GL_LIGHTING);
		glCullFace(GL_FRONT);//the physical light geometry (MyCylinder) is described in a CW way
		// so this call will actually cull the back faces of them
		// Draw the physical lights
		for (int i = 0; i < _numberOfLightsCreated; i++){
			glPushMatrix();
				glColor4fv(_lightSource[i].GetDiffuse().rgba());
				glTranslatef(_lights[i].GetPosition().x(), _lights[i].GetPosition().y(), _lights[i].GetPosition().z());
				_lights[i].Draw();
				glRotatef(90.0f, 1.0f,0.0f,0.0f);
			glPopMatrix();
		}
		glEnable(GL_LIGHTING);
		glCullFace(GL_BACK);

		// Draw outer-box with original normals
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glPushMatrix(); //outer container
			if (_selectedMode!=NONTEXTUREDFLATSHADING && _selectedMode!=SMOOTHSHADING && _selectedMode!=WIREFRAME){
				if (_allShapes[1]->GetTextureEnabledStatus()){
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, _allShapes[1]->GetTextureID());
				}
			}
			else
				glDisable(GL_TEXTURE_2D);
			glCullFace(GL_BACK);
			_allShapes[1]->ApplyMaterial();
			glTranslatef(_allShapes[1]->GetPosition().x(), _allShapes[1]->GetPosition().y(), _allShapes[1]->GetPosition().z());
			_allShapes[1]->Draw();
			if (_drawNormals)
				_allShapes[1]->DrawNormals();
		glPopMatrix();
	glPopMatrix();
}
void MyWindow::OnDisplay() {
	float delta_t, temp_time;
	temp_time = (float)App::GetTime();
	delta_t = temp_time-current_time;
	current_time = temp_time;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	if (_rotateBoxAutomatically)
		angle += angle_inc*delta_t*_direction;

	if(angle>360.0f) angle -=360.0f;

	// determine the shading to use
	switch (_selectedMode){
		case WIREFRAME:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glShadeModel(GL_SMOOTH);
			break;
		case SMOOTHSHADING:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glShadeModel(GL_SMOOTH);
			break;
		case NONTEXTUREDFLATSHADING:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glShadeModel(GL_FLAT);
			break;
		case SMOOTHSHADEDTEXTURED:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glShadeModel(GL_SMOOTH);
			break;
	}

	DrawScene(delta_t);
	SwapBuffers();
}

void MyWindow::OnIdle() {
	Redraw();
}

void MyWindow::OnResize(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-(float)w/h, (float)w/h, -1.0f, 1.0f, 1.0f, +10.0f);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,w,h);
}

void MyWindow::OnKeyboard(int key, bool down) {
	if (!down) return;
	switch( tolower(key) ) {
			case VK_RIGHT: 
				angle += 5.0;
				_direction = 1;
				break;
			case VK_LEFT:
				angle -= 5.0;
				_direction = -1;
				break;
			case 'a':
				if (_animate)
					_animate = false;
				else
					_animate = true;
				break;
			case 'm':
				_selectedMode++;
				if (_selectedMode>_maxSelectionModeValue)
					_selectedMode = 0;
				break;
			case 's':
				_shadowsToShow++;
				if (_shadowsToShow>1)
					_shadowsToShow = 0;
				break;
			case 'n':
				if (_drawNormals)
					_drawNormals = false;
				else
					_drawNormals = true;
				break;
			case 'p':
				if (_rotateBoxAutomatically)
					_rotateBoxAutomatically = false;
				else
					_rotateBoxAutomatically = true;
				break;
			case '1':
				if (_gouraudShading) {
					_gouraudShading = false;
					_flatShading = true;
				}
				else {
					_gouraudShading = true;
					_flatShading = false;
				}
				break;
			case '2':
				if (_wireframe)
					_wireframe = false;
				else
					_wireframe = true;
			default:
				break;
	}
}	

void MyWindow::OnMouseButton(MouseButton button, bool down) {
	if (down) {
		switch(button) {
				case MBLeft: 
					_leftDown = true;
					break;
				case MBRight:
					_rightDown = true;
					break;
				default:
					break;
		}
	} else {
		switch(button) {
				case MBLeft: 
					_leftDown = false;
					break;
				case MBRight:
					_rightDown = false;
					break;
				default:
					break;
		}
	}
}

void MyWindow::OnMouseMove(int x, int y) {
	static int temp_x, temp_y;
	if(_leftDown) {
		_cameraPosition += (y-temp_y)*0.05f;
	}
	if(_rightDown) {
		_cameraRotation += (x-temp_x)*0.5f;
	}
	temp_x = x;
	temp_y = y;
}
void MyWindow::Build2DMipMaps(int numberOfTextures, Image *images, const GLuint *textureID) const{
	// build 2D mip-maps from image
	for (int i = 0; i<numberOfTextures;i++) {
		glBindTexture(GL_TEXTURE_2D, textureID[i]);
		images[i].gluBuild2DMipmaps();
		images[i].Free();
	};
}
void MyWindow::LoadImages(int numberOfTextures, gxbase::Image *images, const std::vector<std::string> &textures) const{
	for (int i = 0; i < numberOfTextures; i++){
		images[i].Load(textures[i].c_str());
	}
}
void MyWindow::Update(float deltaTime){
	PositionLights();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_timeElapsed = (float)App::GetTime();
	_timeElapsed = _timeElapsed - _startTime;
	for (vector<Shape *>::iterator p = _allShapes.begin(); p != _allShapes.end(); ++p){
		(*p)->Update(deltaTime, _timeElapsed);
		if (_animate)
			(*p)->Animate(deltaTime, _timeElapsed);
	}
}