#include <iostream>
#include <string.h>

#include "datastructs.h"
//#include "text.h"
#include "vector3d.h"
#include "object/object.h"

#include "menu.h"
using namespace std;

menuTree::menuTree() : NodeClass<void*>()
{
//	font = NULL;
//	font3d = NULL;
}

/*menuTree::~menuTree()
{
	delete font;
}*/


void menuTree::addLeaf(void* input, dataType tp, string name)
{
	Vector3D* vec3dPtr = NULL;
	Object* objectPtr = NULL;

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
			case tpFLOAT:
				ptr[numLeaf].val = input;
				ptr[numLeaf].ID = name.append(" (float)");
				break;
			case tpSHAPE:
				ptr[numLeaf].val = input;
				ptr[numLeaf].ID = name.append(" (shape)");
				break;
			case tpTEXTURE:
				ptr[numLeaf].val = input;
				break;
			case tpVECTOR3D:
				vec3dPtr = static_cast<Vector3D*>(input);
				ptr[numLeaf].val = input;
				ptr[numLeaf].ID = name.append(" (vector)");
				ptr[numLeaf].addLeaf(&vec3dPtr->x, tpFLOAT, " x");
				ptr[numLeaf].addLeaf(&vec3dPtr->y, tpFLOAT, " y");
				ptr[numLeaf].addLeaf(&vec3dPtr->z, tpFLOAT, " z");
				break;
			case tpOBJP:
				ptr[numLeaf].val = input;
				break;
			case tpOBJECT:
				objectPtr = static_cast<Object*>(input);
				ptr[numLeaf].val = input;
				ptr[numLeaf].ID = name.append(" (object)");
//				ptr[numLeaf].addLeaf(objectPtr->mass, tpMASS, " mass");
				ptr[numLeaf].addLeaf(&objectPtr->shape, tpSHAPE, " object type");
				ptr[numLeaf].addLeaf(&objectPtr->bMovable, tpBOOL, " movable");
				switch(objectPtr->shape)
				{
          case Object::SPHERE:
					case Object::PLANE:
					case Object::LINE:
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

void menuTree::display()
{
	//glPrintHead(150,60,tP->ptr[mod(tP->currentLeaf-1,tP->numLeaf)].ID.c_str(), 8);
//	glDraw3DText(ID.c_str(),font3d);

	return;
}

