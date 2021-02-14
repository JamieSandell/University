#include <algorithm>
#include <cmath>
#include "Shape.h"

using std::vector;
using std::find;

Shape::Shape(void)
{
	_animation.Create();
}

Shape::~Shape()
{
}

void Shape::Animate(float deltaTime, float timeElapsed){
	_animation.Animate(_position, deltaTime, timeElapsed);
}

void Shape::ApplyMaterial(void)const{
	_material.apply();
}
void Shape::CalculateFaceConnectivity(int faceConnectivityArray[], int sizeOfFaceConnectivityArray,
									  const Vector3f (*vertexArray)[3], int sizeOfVertexArray,
									  int numberOfFaces, const int faceTable[]) const{
	
}

void Shape::CalculateVertexNormals(int numberOfFaces, GLfloat(*normalArray)[3], GLfloat(*vertexArray)[3] , int sizeOfArrays,
								   int numberOfFaceConnectionsPerFace, int numberOfVerticesPerFace) const{
   Vector3f *faceNormals = new Vector3f[numberOfFaces];
   Vector3f v0, v1, v2;
   Vector3f normal;
   int vertexCounter = 0;
   for (int i = 0; i < numberOfFaces; i++){
	   v0.Assign(vertexArray[vertexCounter][0], vertexArray[vertexCounter][1], vertexArray[vertexCounter][2]);
	   vertexCounter++;
	   v1.Assign(vertexArray[vertexCounter][0], vertexArray[vertexCounter][1], vertexArray[vertexCounter][2]);
	   vertexCounter++;
	   v2.Assign(vertexArray[vertexCounter][0], vertexArray[vertexCounter][1], vertexArray[vertexCounter][2]);
	   vertexCounter++;
	   faceNormals[i] = normal.CalculateFaceNormals(v0, v1, v2); // TODO: needs changing to support v0...vn
   }

   vector<vector<vector<GLfloat> > > faces;
   int vertexArrayCounter = 0;
   // construct the faces
   for (int i = 0; i < numberOfFaces; i++){
	   vector<vector<GLfloat> > face(numberOfVerticesPerFace);
	   int j = 0;
	   for (vector<vector<GLfloat> >::iterator i = face.begin(); i != face.end(); ++i){
		   i->push_back(vertexArray[j+vertexArrayCounter][0]); //TODO: change code so it can deal any numberOfVerticesPerFace(e.g. more than 3)
		   i->push_back(vertexArray[j+vertexArrayCounter][1]);
		   i->push_back(vertexArray[j+vertexArrayCounter][2]);
		   j++;
	   }
	   faces.push_back(face);
	   vertexArrayCounter+=numberOfVerticesPerFace;
	   face.clear();
   }

	int faceConnectivitySize = numberOfFaceConnectionsPerFace*numberOfFaces*numberOfVerticesPerFace;
   int *faceConnectivityTable = new int[faceConnectivitySize];
   int tableCounter = 0;
   int faceCounter = 0;
   int faceVertexCounter = 0;
   int numberOfVerticesCounter = 0;
   int foundFacesThisTrip = 0;
   vertexArrayCounter = 0;
	// find out which vertices share the same face
   //if (fabs(faces[faceCounter][i][0]-vertexArray[faceVertexCounter][0]) < 0.00001)//faces[j][0][0] vertex 0 of facej, and x of vertex 0
   for (int i = 0; i < sizeOfArrays; i++){
	   for (int j = 0; j < numberOfFaces; j++){
		   for (int k = 0; k < numberOfVerticesPerFace; k++){
			   if (foundFacesThisTrip<numberOfFaceConnectionsPerFace){
					if (fabs(vertexArray[i][0]-faces[j][k][0])<0.001)
						if (fabs(vertexArray[i][1]-faces[j][k][1])<0.001)
							if (fabs(vertexArray[i][2]-faces[j][k][2])<0.001){ // x,y, and z match so must match the face
								faceConnectivityTable[tableCounter] = j; // equals the current face //TODO: tableCounter max reaches 12 should be 36
								// last change made was faceVertexCounter code below
								tableCounter++;
								foundFacesThisTrip++;
								faceVertexCounter = 0; // found a match on this face so reset the counter to 0 and break from this face
								break;
							}
				faceVertexCounter++;
				if (faceVertexCounter>numberOfVerticesPerFace-1) //x,y,z of faces[j]
				   faceVertexCounter = 0;
		   }

	   }
	   }
	   foundFacesThisTrip = 0;
   }

	Vector3f vecMeanFaceNormal; //The vertex normal is the mean of all the faces' (that connect to that vertex) normals
	for (int i = 0; i < sizeOfArrays; i++){
		for (int j = i*numberOfFaceConnectionsPerFace;
			j < (i*numberOfFaceConnectionsPerFace)+numberOfFaceConnectionsPerFace; j++){
			vecMeanFaceNormal = vecMeanFaceNormal + (faceNormals[faceConnectivityTable[j]]);
		}
		vecMeanFaceNormal = vecMeanFaceNormal/numberOfFaceConnectionsPerFace;
		vecMeanFaceNormal = vecMeanFaceNormal.Normalise();
		normalArray[i][0] = vecMeanFaceNormal.x();
		normalArray[i][1] = vecMeanFaceNormal.y();
		normalArray[i][2] = vecMeanFaceNormal.z();
		vecMeanFaceNormal.Assign(0.0f,0.0f,0.0f); // reset it for the next iteration
	}

	delete [] faceNormals;
	delete [] faceConnectivityTable;
}
void Shape::CopyBaseMembers(const Shape &source){
	this->_animation = source._animation;
	this->_directionVector = source._directionVector;
	this->_heightWidthDepth = source._heightWidthDepth;
	this->_image = source._image;
	this->_initialPosition = source._initialPosition;
	this->_position = source._position;
	this->_textureEnabled = source._textureEnabled;
	this->_material = source._material;
}
void Shape::DrawNormals(void)const{

}
Animation Shape::GetAnimation(void) const{
	return _animation;
}
Vector3f Shape::GetDirectionVector(void) const{
	return _animation.GetDirectionVector();
}

Vector3f Shape::GetHeightWidthDepth() const {
	return _heightWidthDepth;
}

const Vector4f &Shape::GetPosition() const {
	return _position;
}

std::string Shape::GetTexture(void) const{
	return _image;
}

bool Shape::GetTextureEnabledStatus() const {
	return _textureEnabled;
}

GLuint Shape::GetTextureID(void) const {
	return 0;
}

void Shape::InverseNormals(){

}
void Shape::InverseNormals(GLfloat (*normalArray)[3], GLuint normalArraySize){
	for (GLuint i = 0; i < normalArraySize; i++){
		normalArray[i][0] = normalArray[i][0]*-1;
		normalArray[i][1] = normalArray[i][1]*-1;
		normalArray[i][2] = normalArray[i][2]*-1;
	}
}

void Shape::SetAnimation(const Animation &animation){
	_animation = animation;
}
void Shape::SetAnimationCoefficients(const vector<Vector3f> &animation){
	_animation.Assign(animation);
}
void Shape::SetCollisionObject(const Shape *shape){

}
void Shape::SetDirectionVector(const Vector3f &directionVector){
	_animation.SetDirectionVector(directionVector);
}

void Shape::SetHeightWidthDepth(const Vector3f *hWD) {
	_heightWidthDepth = *hWD;
}

void Shape::SetInitialPosition(const Vector4f &initialPosition){
	_initialPosition = initialPosition;
}

void Shape::SetMaterial(const Materials &material){
	_material = material;
}
void Shape::SetPosition(const Vector4f &position) {
	_position = position;
}

void Shape::SetTexture(std::string image) {
	_image = image;
}

void Shape::SetTextureEnabledStatus(bool status) {
	_textureEnabled = status;
}

void Shape::SetTextureID(GLuint textureID){
}