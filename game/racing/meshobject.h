#ifndef MESHOBJECT_H
#define MESHOBJECT_H

class Mass;
class MeshModel;

class MeshObject
{
public:
	MeshObject();
	~MeshObject();

		Mass* mass;
		MeshModel* mesh;
		bool isDynamicMesh;
};

#endif // MESHOBJECT_H
