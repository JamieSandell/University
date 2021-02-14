#pragma once

#include "Vector3f.h"

class Node
{
public:
	Node(void);
	~Node(void);
	void Create(unsigned int gridWidth, unsigned int gridHeight);

private:
	unsigned int CalculateNumberOfNodes(unsigned int max, unsigned int min);
	void CreateGrid(unsigned int width,unsigned int height);
	void CreateNode(unsigned int boundingCoordinates[4], unsigned int parentID, unsigned int nodeID);

private:
	int _bType;
	Vector3f _vBoundingCoordinates[4];
	unsigned int _branches[4];
	unsigned int _vertexStrip1[8];
	unsigned int _vertexStrip2[8];
	unsigned int _vertexStrip3[8];
	unsigned int _vertexStrip4[8];
	unsigned int _id;
	unsigned int _parentID;
	unsigned int *p_fVerts;
	unsigned int *p_list;
	Node *p_nodeList;
};
