#include <fstream>
#include "model3d.h"

MeshModel::MeshModel()
{
	numVerts = 0;
	numTris = 0;

	verts = new MeshVert[MAX_VERTS];
	tris = new MeshTriangle[MAX_VERTS];
}

MeshModel::~MeshModel()
{
	delete verts;
	delete tris;
}

bool MeshModel::loadFile(string filename)
{
	bool status=false;
	ifstream fileIn(filename.c_str());
	const int maxLength = 256;
	char tempString[maxLength];
	GLfloat vert[3];
	GLfloat norm[3];
	GLint vertIdx[3];
	int i;
	GLint textureID = -1;
	GLfloat texCoord[3][2];

	if(fileIn.is_open())
	{
		status = true;
		fileIn.getline(tempString, maxLength);
		fileIn.getline(tempString, maxLength);
		//Get vertices
		do
		{
			//Get vertex coordinates
			fileIn.getline(tempString, maxLength, '[');
			fileIn >> vert[0];
			fileIn.get();
			fileIn >> vert[1];
			fileIn.get();
			fileIn >> vert[2];
			//Get vertex normal
			fileIn.getline(tempString, maxLength, '[');
			fileIn >> norm[0];
			fileIn.get();
			fileIn >> norm[1];
			fileIn.get();
			fileIn >> norm[2];
			fileIn.getline(tempString, maxLength);
			addVertex(vert[0], vert[1], vert[2], norm[0], norm[1], norm[2]);
		}while(fileIn.peek()=='\t');
		fileIn.getline(tempString, maxLength);
		//Get vertex indicies of faces
		do
		{
			fileIn.get();
			fileIn >> vertIdx[0];
			fileIn.get();
			fileIn >> vertIdx[1];
			fileIn.get();
			fileIn >> vertIdx[2];
			fileIn.get();
			//Get face normal
			fileIn.getline(tempString, maxLength, '[');
			fileIn >> norm[0];
			fileIn.get();
			fileIn >> norm[1];
			fileIn.get();
			fileIn >> norm[2];
			//Get texture
			fileIn.getline(tempString, maxLength, ']');
			fileIn >> textureID;
			if(textureID)
			{
				fileIn.getline(tempString, maxLength, '[');
				fileIn >> texCoord[0][0];
				fileIn.get();
				fileIn >> texCoord[0][1];
				fileIn.get(tempString,4);
				fileIn >> texCoord[1][0];
				fileIn.get();
				fileIn >> texCoord[1][1];
				fileIn.get(tempString,4);
				fileIn >> texCoord[2][0];
				fileIn.get();
				fileIn >> texCoord[2][1];
				addTriangle(vertIdx[0], vertIdx[1], vertIdx[2], norm[0], norm[1], norm[2], textureID, texCoord[0][0], texCoord[0][1], texCoord[1][0], texCoord[1][1], texCoord[2][0], texCoord[2][1]);
			}
			else
				addTriangle(vertIdx[0], vertIdx[1], vertIdx[2], norm[0], norm[1], norm[2]);
			fileIn.getline(tempString, maxLength);
			
		}
		while(fileIn.peek()=='\t');
		fileIn.close();
		//calcNormals();
	}
	else
	{
		MessageBox(NULL, (LPCWSTR)L"Error opening file", (LPCWSTR)L"Loading Mesh Model", MB_OK);
	}

	calcExtremes();

	return status;
}

void MeshModel::addVertex(GLfloat x, GLfloat y, GLfloat z)
{
	verts[numVerts].norm.z = 1;
	verts[numVerts++].coord = Vector3D(x,y,z);

	return;
}

void MeshModel::addVertex(GLfloat x, GLfloat y, GLfloat z, GLfloat nx, GLfloat ny, GLfloat nz)
{
	verts[numVerts].coord = Vector3D(x,y,z);
	verts[numVerts++].norm = Vector3D(nx,ny,nz);

	return;
}

void MeshModel::addTriangle(GLint v1, GLint v2, GLint v3)
{
	tris[numTris].vIndex[0] = v1;
	tris[numTris].vIndex[1] = v2;
	tris[numTris++].vIndex[2] = v3;

	return;
}

void MeshModel::addTriangle(GLint v1, GLint v2, GLint v3, GLfloat nx, GLfloat ny, GLfloat nz)
{
	addTriangle(v1,v2,v3);
	numTris--;
	tris[numTris++].norm = Vector3D(nx, ny, nz);

	return;
}

void MeshModel::addTriangle(GLint v1, GLint v2, GLint v3, GLfloat nx, GLfloat ny, GLfloat nz, GLuint texID, GLfloat tcx1, GLfloat tcy1, GLfloat tcx2, GLfloat tcy2, GLfloat tcx3, GLfloat tcy3)
{
	addTriangle(v1,v2,v3,nx,ny,nz);
	numTris--;
	tris[numTris].textureID = texID;
	tris[numTris].vTexCoord[0] = Vector2D(tcx1,tcy1);
	tris[numTris].vTexCoord[1] = Vector2D(tcx2,tcy2);
	tris[numTris++].vTexCoord[2] = Vector2D(tcx3,tcy3);

	return;
}

void MeshModel::draw()
{
	int t,v;
	float length;

	for(t=0; t<numTris; t++)
	{
		glBegin(GL_TRIANGLES);
		//glNormal3fv(tris[t].fNormal.toArray());
		//glNormal3f(tris[t].fNormal.x,tris[t].fNormal.y,tris[t].fNormal.z);
		//glNormal3f( 0.0f, 0.0f, 1.0f);
		for(v=0; v<3; v++)
		{
			//glVertex3fv(verts[tris[t].vIndex[v]].toArray());
			glBindTexture(GL_TEXTURE_2D, tris[t].textureID);
			glColor4f(verts[tris[t].vIndex[v]].color[0], verts[tris[t].vIndex[v]].color[1], verts[tris[t].vIndex[v]].color[2], verts[tris[t].vIndex[v]].color[3]);
			glNormal3f(verts[tris[t].vIndex[v]].norm.x, verts[tris[t].vIndex[v]].norm.y, verts[tris[t].vIndex[v]].norm.z);
			glTexCoord2f(tris[t].vTexCoord->x, tris[t].vTexCoord->y);
			glVertex3f(verts[tris[t].vIndex[v]].coord.x, verts[tris[t].vIndex[v]].coord.y, verts[tris[t].vIndex[v]].coord.z);
		}
		glEnd();
	}

	return;
}

void MeshModel::getVerts(Vector3D vs[], int tIdx)
{
	vs[0] = verts[tris[tIdx].vIndex[0]].coord;
	vs[1] = verts[tris[tIdx].vIndex[1]].coord;
	vs[2] = verts[tris[tIdx].vIndex[2]].coord;

	return;
}

void MeshModel::calcNormals()
{
	int t;
	Vector3D v[3];
	Vector3D vec1, vec2;

	for(t=0; t<numTris; t++)
	{
		getVerts(v, t);
		vec1 = v[2]-v[1];
		vec2 = v[0]-v[1];
		tris[t].norm = Cross(vec1, vec2);
		tris[t].norm.unitize();
	}

	return;
}

void MeshModel::scale(GLfloat scaleFactor)
{
	for(int v=0; v<numVerts; v++)
		verts[v].coord = verts[v].coord*scaleFactor;

	return;
}

void MeshModel::calcExtremes()
{
	mins.x = verts[0].coord.x;
	mins.y = verts[0].coord.y;
	mins.z = verts[0].coord.z;
	maxs.x = verts[0].coord.x;
	maxs.y = verts[0].coord.y;
	maxs.z = verts[0].coord.z;

	for(int i=0; i<numVerts; i++)
	{
		if(verts[i].coord.x < mins.x)
			mins.x = verts[i].coord.x;
		if(verts[i].coord.y < mins.y)
				mins.y = verts[i].coord.y;
		if(verts[i].coord.z < mins.z)
				mins.z = verts[i].coord.z;
		if(verts[i].coord.x > maxs.x)
			maxs.x = verts[i].coord.x;
		if(verts[i].coord.y > maxs.y)
				maxs.y = verts[i].coord.y;
		if(verts[i].coord.z > maxs.z)
				maxs.z = verts[i].coord.z;
	}

	return;
}

void MeshModel::translate(const Vector3D* shift)
{
	for(int i=0; i<numVerts; i++)
	{
		verts[i].coord.x += shift->x;
		verts[i].coord.y += shift->y;
		verts[i].coord.z += shift->z;
	}

	//calcCenter();

	return;
}

void MeshModel::translateTo(const Vector3D* pos)
{
	Vector3D shift;

	shift = *pos - center;
	translate(&shift);

	return;
}

MeshVert* MeshModel::getVert(int t, int v) const
{
	MeshVert* vertOut;

	vertOut = &verts[tris->vIndex[v]];

	return vertOut;
}

void MeshModel::getVerts(MeshVert** mv, int t) const
{
	//MeshVert* vertsOut[3];

	for(int v=0; v<3; v++)
		//vertsOut[v] = getVert(t,v);
		mv[v] = getVert(t,v);

	return;
}

Vector3D MeshModel::calcCenter()
{
	calcExtremes();
	center = Vector3D((maxs.x+mins.x)/2, (maxs.y+mins.y)/2, (maxs.z+mins.z)/2);
	return center;
}

void MeshModel::centerMesh()
{
	calcCenter();
	translate(&(-center));
	calcCenter();

	return;
}
