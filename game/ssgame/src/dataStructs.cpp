#include <iostream>
#include <string.h>
#include "dataStructs.h"
#include "vector3d.h"
#include "mass.h"
#include "objects.h"
using namespace std;

pointerTree::pointerTree() : NodeClass<void*>()
{
	ID = "head";
}

void pointerTree::addLeaf(void* input, dataType tp, string name)
{
	Vector2D* vec2dPtr = NULL;
	object_c* objectPtr = NULL;

	if(ptr == NULL)
		ptr = new pointerTree[MAXLEAF];
	if(numLeaf<MAXLEAF)
	{
		ptr[numLeaf].type = tp;
		ptr[numLeaf].parent = this;
		if(parent != NULL)
			ptr[numLeaf].level = parent->level+1;

		switch(tp)
		{
			case tpBOOL:
				ptr[numLeaf].val = input;
				ptr[numLeaf].ID = name.append(" (bool)");
				break;
			case tpINT:
				ptr[numLeaf].val = input;
				ptr[numLeaf].ID = name.append(" (int)");
				break;
			case tpFLOAT:
				ptr[numLeaf].val = input;
				ptr[numLeaf].ID = name.append(" (float)");
				break;
			case tpVECTOR2D:
				vec2dPtr = static_cast<Vector2D*>(input);
				ptr[numLeaf].val = input;
				ptr[numLeaf].ID = name.append(" (vector)");
				ptr[numLeaf].addLeaf(&vec2dPtr->x, tpFLOAT, " x");
				ptr[numLeaf].addLeaf(&vec2dPtr->y, tpFLOAT, " y");
				break;
			case tpOBJECT:
				objectPtr = static_cast<object_c*>(input);
				ptr[numLeaf].val = input;
				ptr[numLeaf].ID = name.append(" (object)");
				ptr[numLeaf].addLeaf(&objectPtr->pos, tpVECTOR2D, " Position");
				ptr[numLeaf].addLeaf(&objectPtr->posOld, tpVECTOR2D, " Old Position");
				ptr[numLeaf].addLeaf(&objectPtr->posz, tpFLOAT, " Z Position");
				ptr[numLeaf].addLeaf(&objectPtr->posMin, tpVECTOR2D, " Min Positions");
				ptr[numLeaf].addLeaf(&objectPtr->posMax, tpVECTOR2D, " Max Positions");
				ptr[numLeaf].addLeaf(&objectPtr->active, tpBOOL, " active");
				switch(objectPtr->objType)
				{
					default:
						break;
				}
				break;
			default:
				numLeaf--;
				break;
		}
	}
	else
		numLeaf--;

	numLeaf++;

	return;
}


