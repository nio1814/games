//#include <fstream>
#include "model3d.h"

#include <QTextStream>
#include <QFile>

QChar peek(QTextStream& textStream)
{
	int initialPosition = textStream.pos();
	QChar nextChar = *textStream.read(1).data();
	textStream.seek(initialPosition);

	return nextChar;
}

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

bool MeshModel::loadFile(QString filename)
{
	bool status=false;

	const int maxLength = 256;
//	char tempString[maxLength];
	GLfloat vert[3];
	GLfloat norm[3];
	GLint vertIdx[3];
	GLint textureID = -1;
	GLfloat texCoord[3][2];

	QFile file(filename);
	if(file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream fileIn(&file);
		QString tempString;

		status = true;
//		fileIn.getline(tempString, maxLength);
		tempString = fileIn.readLine();
//		fileIn.getline(tempString, maxLength);
		tempString = fileIn.readLine();
		//Get vertices
		do
		{
			//Get vertex coordinates
//			fileIn.getline(tempString, maxLength, '[');
//			tempString = fileIn.readLine().split('[').last();
			fileIn.read(2);
			fileIn >> vert[0];
//			fileIn.get();
			fileIn.read(1);
			fileIn >> vert[1];
//			fileIn.get();
			fileIn.read(1);
			fileIn >> vert[2];

			//Get vertex normal
//			fileIn.getline(tempString, maxLength, '[');
//			tempString = fileIn.readLine().split(']').last();
			fileIn.read(3);
			fileIn >> norm[0];
//			fileIn.get();
			fileIn.read(1);
			fileIn >> norm[1];
//			fileIn.get();
			fileIn.read(1);
			fileIn >> norm[2];
//			fileIn.getline(tempString, maxLength);
			tempString = fileIn.readLine();
			addVertex(vert[0], vert[1], vert[2], norm[0], norm[1], norm[2]);
//		}while(fileIn.peek()=='\t');
		}while(peek(fileIn)=='\t');

//		fileIn.getline(tempString, maxLength);
		tempString = fileIn.readLine();
		//Get vertex indicies of faces
		do
		{
//			fileIn.get();
			fileIn.read(1);
			fileIn >> vertIdx[0];
//			fileIn.get();
			fileIn.read(1);
			fileIn >> vertIdx[1];
//			fileIn.get();
			fileIn.read(1);
			fileIn >> vertIdx[2];
//			fileIn.get();
			fileIn.read(1);

			//Get face normal
//			fileIn.getline(tempString, maxLength, '[');
//			tempString = fileIn.readLine().split('[').last();
			fileIn.read(3);
			fileIn >> norm[0];
//			fileIn.get();
			fileIn.read(1);
			fileIn >> norm[1];
//			fileIn.get();
			fileIn.read(1);
			fileIn >> norm[2];

			//Get texture
//			fileIn.getline(tempString, maxLength, ']');
//			tempString = fileIn.readLine().split(']').last();
			fileIn.read(2);
			fileIn >> textureID;
			if(textureID)
			{
//				fileIn.getline(tempString, maxLength, '[');
				tempString = fileIn.readLine().split('[').last();
				fileIn >> texCoord[0][0];
//				fileIn.get();
				fileIn.read(1);
				fileIn >> texCoord[0][1];
//				fileIn.get(tempString,4);
				tempString = fileIn.read(4);
				fileIn >> texCoord[1][0];
//				fileIn.get();
				fileIn.read(1);
				fileIn >> texCoord[1][1];
//				fileIn.get(tempString,4);
				tempString = fileIn.read(4);
				fileIn >> texCoord[2][0];
//				fileIn.get();
				fileIn.read(1);
				fileIn >> texCoord[2][1];
				addTriangle(vertIdx[0], vertIdx[1], vertIdx[2], norm[0], norm[1], norm[2], textureID, texCoord[0][0], texCoord[0][1], texCoord[1][0], texCoord[1][1], texCoord[2][0], texCoord[2][1]);
			}
			else
				addTriangle(vertIdx[0], vertIdx[1], vertIdx[2], norm[0], norm[1], norm[2]);
//			fileIn.getline(tempString, maxLength);
			tempString = fileIn.readLine();
//		}while(fileIn.peek()=='\t');
		}while(peek(fileIn)=='\t');
		file.close();
		//calcNormals();
	}
	else
	{
		//MessageBox(NULL, (LPCWSTR)L"Error opening file", (LPCWSTR)L"Loading Mesh Model", MB_OK);
    qErrnoWarning("Error opening mesh model file %s\n", filename.toStdString().c_str());
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

void MeshModel::translate(const Vector3D& shift)
{
	for(int i=0; i<numVerts; i++)
	{
		/*verts[i].coord.x += shift.x;
		verts[i].coord.y += shift.y;
		verts[i].coord.z += shift.z;*/
		verts[i].coord += shift;
	}

	//calcCenter();

	return;
}

void MeshModel::translateTo(const Vector3D* pos)
{
	Vector3D shift;

	shift = *pos - center;
	translate(shift);

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
	translate(-center);
	calcCenter();

	return;
}

bool detectCollision(const Vector3D& point, const Vector3D* triVerts, const Vector3D& norm)
{
	bool detect = false;
	Vector3D alongNorm;
	float height;
	Vector3D planeNormIn;
	Vector3D vec;
	Vector3D pointInPlane;
	Vector3D vec1, vec2;
	int v;

	alongNorm = point - triVerts[0];
	alongNorm = alongNorm.proj(norm);
	height = alongNorm.length();

	if(height<1)
	{
		pointInPlane = point - norm*height;
		v = 0;
		do
		{
			vec = triVerts[(v+1)%3] - triVerts[v];
			vec.unitize();
			planeNormIn = triVerts[(v+2)%3] - triVerts[v];
			planeNormIn = planeNormIn - planeNormIn.proj(vec);
			vec1 = triVerts[(v+2)%3] - triVerts[v];
			vec2 = pointInPlane - triVerts[v];
			float temp = (vec1.dot(planeNormIn)*vec2.dot(planeNormIn));
			if(temp>0)
				detect = true;
			else
				detect = false;
		}while(detect && (v++)<2);
	}

	return detect;
}

bool MeshModel::detectCollisionM(const MeshModel* mesh2, Vector3D* point, Vector3D* norm)
{
	bool detect = false;
	MeshVert* triVerts[3];
	//MeshVert** triVerts;
	Vector3D triVertsCoords[3];

	//triVerts = new MeshVert*[3];
	for(int v=0; v<numVerts; v++)
	{
		for(int t=0; t<mesh2->numTris; t++)
		{
			//triVerts = mesh2->getVerts(t);
			mesh2->getVerts(triVerts,t);
			for(int v2=0; v2<3; v2++)
				triVertsCoords[v2] = (triVerts[v2]->coord);
			if(mesh2->tris[t].norm.length()>0.5)
			{
				if(detectCollision(verts[v].coord, triVertsCoords, mesh2->tris[t].norm))
				{
					detect = true;
					*point = verts[v].coord;
					*norm = mesh2->tris[t].norm;
				}
			}
		}
	}

	//delete triVerts;

	return detect;
}
