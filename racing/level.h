#ifndef LEVEL_H
#define LEVEL_H

#include "light.h"
#include "camera.h"

struct Contact
{
	bool touch;
	Vector3D point;
	Vector3D norm;

	Contact()
	{
		touch = false;
	}
};

class MeshObject;

class Level
{
public:
	Level();
	~Level();
		void addPlayer(MeshObject* obj);
		void addPlayer(QString modelfile);
		void initObject(MeshObject* obj);
		MeshObject* addObject(const char* modelfile);
	void addLight(GLenum lnum, const Vector3D ptn, const Vector3D amb, const Vector3D dif, const Vector3D spec);
		void draw();
		void run(GLfloat dt);
		void updateObjects(GLfloat dt);
		void updateCamera(GLfloat dt);
		bool checkKeys();

		Vector3D up;
		MeshObject* player;
  std::vector<MeshObject*> objs;
		QList<Contact> contactPoints;
		CameraPoint cam;
		CameraView camview;
    std::vector<Light*> m_lights;
};

#endif // LEVEL_H
