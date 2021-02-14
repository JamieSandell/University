#include "Node.h"

#define LEAF_TYPE 0
#define NODE_TYPE 1

Node::Node(void)
{
}

Node::~Node(void)
{
}

void Node::Create(unsigned int gridWidth, unsigned int gridHeight){
	unsigned int result = gridWidth%4;
	while (result!=0)
	{
		gridWidth++;
		result = gridWidth%4;
	}
	result = gridHeight%4;
	while (result!=0)
	{
		gridHeight++;
		result = gridHeight%4;
	}

	CreateGrid(gridWidth+1,gridHeight+1);

	unsigned int Temp =(gridWidth/4)*(gridHeight/4);

	unsigned int Temp2 = CalculateNumberOfNodes(Temp,4);

	p_nodeList = (Node*)malloc(sizeof(Node)*Temp2);


	unsigned int uiBoundingCoordinates[] = {0,gridWidth,(gridHeight*(gridWidth+1)),((gridHeight)*(gridWidth+1))+gridWidth};

	CreateNode(uiBoundingCoordinates,0,0);
}
unsigned int Node::CalculateNumberOfNodes(unsigned int max, unsigned int min){
	int ctr = 0;
	int var = 0;

	while (var == 0)
	{
		ctr+=max;
		max=max/min;

		if (max==1)
			var = 1;
	}
	ctr++;

	return ctr;
}

void Node::CreateGrid(unsigned int width, unsigned int height){
	unsigned int total=0;

	p_fVerts = (unsigned int*)malloc((sizeof(unsigned int))*width*height*3);

	for(unsigned int ctr=0;ctr<height;ctr++)
	{
		for(unsigned int ctr2=0;ctr2<width;ctr2++)
		{				// Vertex number is total
			p_fVerts[total] =  ctr2;	// Vertex X component is ctr2
			p_fVerts[total+1] = 0;	// Vertex Y component is height field (0)
			p_fVerts[total+2] =  ctr;  // Vertex Z component is ctr
			total+=3;		// Increase total to be next vertex number
		}
	}	

	total=0;

	p_list = (unsigned int*)malloc((sizeof(unsigned int))*(width-1)*(height-1)
		*6);

	for(unsigned int ctr=0;ctr<(height-1);ctr++)
	{
		for(unsigned int ctr2=0;ctr2<(width-1);ctr2++)
		{				        //Triangles are built in twos, hence 
			//total+=6 to accomodate two sets of verts
			p_list[total] = (ctr*width)+ctr2;	  //Triangle A's 1st vertex
			p_list[total+1] = (ctr*width)+ctr2+width;
			p_list[total+2] = (ctr*width)+ctr2+1;

			p_list[total+3] = (ctr*width)+ctr2+width;   //Triangle B's first vertex
			p_list[total+4] = (ctr*width)+ctr2+width+1;
			p_list[total+5] = (ctr*width)+ctr2+1;

			total+=6;  //Increase total by six, because we're using two tri's a loop
		}
	}
}

void Node::CreateNode(unsigned int bounding[4], unsigned int parentID, unsigned int nodeID){
	static unsigned int TotalTreeID = 0;

	unsigned int uiNodeType;
	unsigned int uiWidth,uiHeight;

	uiWidth = p_fVerts[(bounding[1]*3)] - p_fVerts[(bounding[0]*3)]; 
	uiHeight = p_fVerts[(bounding[2]*3)+2] - p_fVerts[(bounding[0]*3)+2]; 

	if(0.5*uiWidth==2)
	{uiNodeType = LEAF_TYPE;}
	else
	{uiNodeType = NODE_TYPE;}

	Node *pNode = &p_nodeList[nodeID];

	pNode->_id = nodeID;
	pNode->_parentID = parentID;

	Vector3f tempVec(p_fVerts[(bounding[0]*3)], p_fVerts[(bounding[0]*3)+1], p_fVerts[(bounding[0]*3)+2]);
	pNode->_vBoundingCoordinates[0] = tempVec;

	tempVec.Assign(p_fVerts[(bounding[1]*3)], p_fVerts[(bounding[1]*3)+1], p_fVerts[(bounding[1]*3)+2]);
	pNode->_vBoundingCoordinates[1] = tempVec;

	tempVec.Assign(p_fVerts[(bounding[2]*3)], p_fVerts[(bounding[2]*3)+1], p_fVerts[(bounding[2]*3)+2]);
	pNode->_vBoundingCoordinates[2] = tempVec;

	tempVec.Assign(p_fVerts[(bounding[3]*3)], p_fVerts[(bounding[3]*3)+1], p_fVerts[(bounding[3]*3)+2]);
	pNode->_vBoundingCoordinates[3] = tempVec;

	pNode->_bType = uiNodeType;


	if(uiNodeType == LEAF_TYPE)
	{return;}
	else
	{	


		unsigned int BoundingBox[4];
		TotalTreeID++;	
		pNode->_branches[0] = TotalTreeID;

		BoundingBox[0] = bounding[0]; //Top-Left i.e. b[0]
		BoundingBox[1] = bounding[0]+((bounding[1]-bounding[0])/2); //Between b[0] and b[1]
		BoundingBox[2] = bounding[0]+((bounding[2]-bounding[0])/2); //[between b[0] and b[2]
		BoundingBox[3] = bounding[0]+((bounding[2]-bounding[0])/2)+((bounding[1]-bounding[0])/2); //middle of node


		CreateNode(BoundingBox,nodeID,TotalTreeID);

		//************************************************************************************************************

		TotalTreeID++;	
		pNode->_branches[1] = TotalTreeID;

		BoundingBox[0] = bounding[0]+((bounding[1]-bounding[0])/2); // Between b[0] and b[1]
		BoundingBox[1] = bounding[1]; //Top-Right i.e.  b[1]
		BoundingBox[2] = bounding[0]+((bounding[2]-bounding[0])/2)+((bounding[1]-bounding[0])/2); //middle of node
		BoundingBox[3] = bounding[0]+((bounding[2]-bounding[0])/2)+((bounding[1]-bounding[0])); //between b[1] & b[3]

		CreateNode(BoundingBox,nodeID,TotalTreeID);

		//************************************************************************************************************

		TotalTreeID++;	
		pNode->_branches[2] = TotalTreeID;

		BoundingBox[0] = bounding[0]+((bounding[2]-bounding[0])/2); //between b[0] and b[2]
		BoundingBox[1] = bounding[0]+((bounding[2]-bounding[0])/2)+((bounding[1]-bounding[0])/2); //middle of node
		BoundingBox[2] = bounding[2]; //Bottom-Left i.e. b[2]
		BoundingBox[3] = bounding[2]+((bounding[3]-bounding[2])/2); //between b[2] and b[3]

		CreateNode(BoundingBox,nodeID,TotalTreeID);

		//************************************************************************************************************

		TotalTreeID++;	
		pNode->_branches[3] = TotalTreeID;

		BoundingBox[0] = bounding[0]+((bounding[2]-bounding[0])/2)+((bounding[1]-bounding[0])/2); //middle of node
		BoundingBox[1] = bounding[0]+((bounding[2]-bounding[0])/2) + uiWidth; //between b[1] and b[3]
		BoundingBox[2] = bounding[2]+((bounding[3]-bounding[2])/2); //between b[2] and b[3]
		BoundingBox[3] = bounding[3]; //Bottom-Right i.e. b[3]

		CreateNode(BoundingBox,nodeID,TotalTreeID);
	}
	return;
}