#include "meshobject.h"

#include "mass.h"
#include "model3d.h"

MeshObject::MeshObject()
{
	mass = new Mass;
	mesh = NULL;
	hasBBox = false;
	isDynamicMesh = false;
	isMoveable = false;
	bbox = new MeshModel;
}

MeshObject::~MeshObject()
{
	delete mass;
	if(isDynamicMesh)
		delete mesh;
	delete bbox;
}

void MeshObject::init()								// this method will call the init() method of every mass
{
	mass->init();						// call init() method of the mass

	return;
}

void MeshObject::simulate(float dt)					// Iterate the masses by the change in time
{
	mass->simulate(dt);				// Iterate the mass and obtain new position and new velocity

	return;
}

void MeshObject::draw()
{
	//Draw object
	glPushMatrix();
	glTranslatef(mass->pos.x, mass->pos.y, mass->pos.z);
	glRotatef(mass->theta, mass->axis.x, mass->axis.y, mass->axis.z);
	mesh->draw();
	glPopMatrix();

	//Draw bounding box
	glPushMatrix();
	//glTranslatef(bbox.center.x, bbox.center.y, bbox.center.z);
	//glColor4f(1,1,1,0.2f);
	bbox->draw();
	glPopMatrix();
	return;
}

void MeshObject::updateBoundingBox()
{
	Vector3D toVert;

	bbox->translate(mass->dpos);

	for(int i=0; i<bbox->numVerts; i++)
	{
		toVert = bbox->verts[i].coord - mass->pos;
		toVert = toVert.rotate3D(mass->axis, mass->dtheta);
		bbox->verts[i].coord = mass->pos + toVert;
		bbox->verts[i].norm = bbox->verts[i].norm.rotate3D(mass->axis, mass->dtheta);
	}

	return;
}

void doCollision(MeshObject* obj1, const MeshObject* obj2, const Vector3D& point, const Vector3D& norm)
{
	GLfloat m1, m2;
	Vector3D v11, v12, v21, vrel;
	GLfloat w11, w12, w21;
	GLfloat I1;
	GLfloat j;
	Vector3D rCom2pt1, rCom2pt2;
	Vector3D temp;

	m1 = obj1->mass->m;
	I1 = obj1->mass->I;
	w11 = obj1->mass->avel;
	w21 = obj2->mass->avel;
	v11 = obj1->mass->vel;
	v21 = obj2->mass->vel;

	rCom2pt1 = point - obj1->mass->pos;
	rCom2pt2 = point - obj2->mass->pos;

	vrel = v11 + rCom2pt1*w11 - v21 - rCom2pt2*w21;
	j = (-(1+obj1->mass->elas)*(vrel.dot(norm))/(1/m1 + Cross(rCom2pt1,norm).dot(Cross(rCom2pt1,norm))/I1));

	v12 = v11 + norm*(j/m1);
	w12 = (obj1->mass->axis*w11 + obj1->mass->axis*Cross(rCom2pt1,norm*j).length()/I1).length();

	obj1->mass->vel = v12;
	obj1->mass->avel = w12/6.283185307;

	return;
}
