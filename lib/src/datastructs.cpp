#include <iostream>
#include <string.h>

#include "datastructs.h"
#include "vector3d.h"
#include "mass.h"
#include "object/object.h"

using namespace std;

pointerTree::pointerTree() : NodeClass<void*>()
{}


void pointerTree::addLeaf(void* input, dataType tp, string name)
{
	Vector3D* vec3dPtr = NULL;
	Mass* massPtr = NULL;
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
			case tpMASS:
				massPtr = static_cast<Mass*>(input);
				ptr[numLeaf].val = input;
				ptr[numLeaf].ID = name.append(" (massobject)");
				ptr[numLeaf].addLeaf(&massPtr->m, tpFLOAT, "mass");
				ptr[numLeaf].addLeaf(&massPtr->elas, tpFLOAT, "elasticity");
				ptr[numLeaf].addLeaf(&massPtr->dir, tpVECTOR3D, "direction");
				ptr[numLeaf].addLeaf(&massPtr->pos, tpVECTOR3D, "position");
				ptr[numLeaf].addLeaf(&massPtr->vel, tpVECTOR3D, "velocity");
				ptr[numLeaf].addLeaf(&massPtr->force, tpVECTOR3D, "force");
				//ptr[numLeaf].addLeaf(input->m, tpVECTOR3D);
				//ptr[numLeaf].addLeaf(input->m, tpVECTOR3D);
				//ptr[numLeaf].addLeaf(input->m, tpVECTOR3D);
				ptr[numLeaf].addLeaf(&massPtr->I, tpFLOAT, "inertia");
				ptr[numLeaf].addLeaf(&massPtr->theta, tpFLOAT, "theta");
				ptr[numLeaf].addLeaf(&massPtr->avel, tpFLOAT, "angular velocity");
				ptr[numLeaf].addLeaf(&massPtr->torque, tpFLOAT, "torque");
				ptr[numLeaf].addLeaf(&massPtr->axis, tpVECTOR3D, "rotation axis");
				//ptr[numLeaf].addLeaf(input->m, tpVECTOR3D);
				//ptr[numLeaf].addLeaf(input->m, tpVECTOR3D);
				break;
			case tpOBJECT:
				objectPtr = static_cast<Object*>(input);
				ptr[numLeaf].val = input;
				ptr[numLeaf].ID = name.append(" (object)");
				ptr[numLeaf].addLeaf(objectPtr->mass, tpMASS, " mass");
				ptr[numLeaf].addLeaf(&objectPtr->objType, tpSHAPE, " object type");
				ptr[numLeaf].addLeaf(&objectPtr->bMovable, tpBOOL, " movable");
				switch(objectPtr->objType)
				{
					case SPHERE:
					case PLANE:
					case LINE:
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


