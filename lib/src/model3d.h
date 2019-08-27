#ifndef MODEL3D
#define MODEL3D

#include "vector3d.h"

#include "qtgl.h"
//#include <string>

//using namespace std;

#define MAX_VERTS 2000

struct MeshTriangle
{
	GLint vIndex[3];
	Vector2D vTexCoord[3];
	Vector3D norm;
	GLuint textureID;
	MeshTriangle()
	{
		vIndex[0] = 0;
		vIndex[1] = 0;
		vIndex[2] = 0;
		textureID = 0;
	}
};

struct MeshVert
{
	Vector3D coord;
	Vector3D norm;
	GLfloat color[4];

	MeshVert()
	{
		color[0] = 1.0f;
		color[1] = 1.0f;
		color[2] = 1.0f;
		color[3] = 1.0f;
	}
};

class MeshModel
{
public:
	MeshModel();
	~MeshModel();
	bool loadFile(QString filename);
	void addVertex(GLfloat x, GLfloat y, GLfloat z);
	void addVertex(GLfloat x, GLfloat y, GLfloat z, GLfloat nx, GLfloat ny, GLfloat nz);
	void addTriangle(GLint v1, GLint v2, GLint v3);
	void addTriangle(GLint v1, GLint v2, GLint v3, GLfloat nx, GLfloat ny, GLfloat nz);
	void addTriangle(GLint v1, GLint v2, GLint v3, GLfloat nx, GLfloat ny, GLfloat nz, GLuint texID, GLfloat tcx1, GLfloat tcy1, GLfloat tcx2, GLfloat tcy2, GLfloat tcx3, GLfloat tcy3);
	void getVerts(Vector3D vs[], int tIdx);
	MeshVert* getVert(int tri, int vert) const;
	void getVerts(MeshVert** mv, int t) const;
	void calcNormals();
	void draw();
	void scale(GLfloat scaleFactor);
	void translate(const Vector3D& shift);
	void translateTo(const Vector3D* pos);
	void calcExtremes();
	bool detectCollisionM(const MeshModel* mesh2, Vector3D* point, Vector3D* norm);
	Vector3D calcCenter();
	void centerMesh();

	int numVerts;
	int numTris;

	MeshVert* verts;
	MeshTriangle* tris;
	Vector3D maxs;
	Vector3D mins;
	Vector3D center;

};

#endif

