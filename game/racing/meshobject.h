#ifndef MESHOBJECT_H
#define MESHOBJECT_H

class Mass;
class MeshModel;
class Vector3D;

class MeshObject
{
public:
	MeshObject();
	~MeshObject();
		virtual void init();							// this method will call the init() method of every mass
		virtual void simulate(float dt);				// Iterate the masses by the change in time
		void updateBoundingBox();

		Mass* mass;
		MeshModel* mesh;
		MeshModel* bbox;
		bool hasBBox;
		bool isDynamicMesh;
		bool isMoveable;
};

void doCollision(MeshObject* obj1, const MeshObject* obj2, const Vector3D& point, const Vector3D& norm);

#endif // MESHOBJECT_H
