#include <math.h>

#include <constants.h>

#include "shape.h"

extern int BLACKub[3] = {0,0,0};
extern int REDub[3] = {255, 0, 0};
extern int ORANGEub[3] = {248, 101, 0};
extern int YELLOWub[3] = {255, 255, 0};
extern int GREENub[3] = {0, 255, 0};
extern int BLUEub[3] = {0,0, 255};
extern int WHITEub[3] = {255, 255, 255};

cube_c::cube_c()
{}

cube_c::cube_c(cubis type, color ctop, color cbot, color cleft, color cright, color cfront, color cback)
{
	sides[TOP] = ctop;
	sides[BOTTOM] = cbot;
	sides[LEFT] = cleft;
	sides[RIGHT] = cright;
	sides[FRONT] = cfront;
	sides[BACK] = cback;
}

void cube_c::drawCube()
{
	//regular xy graph, z out
	int *tempRGB;

	glBegin(GL_QUADS);									// Draw A Quad
		//draw top
		glColor3ub(0,0,0);
		glNormal3f(0.0f, 1.0f, 0.0f);						// Normal Pointing Up
		glVertex3f( 1.0f, 1.0f, 0.0f);					// Top Right Of The Quad (Top)
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Left Of The Quad (Top)
		glVertex3f( 0.0f, 1.0f, 1.0f);					// Bottom Left Of The Quad (Top)
		glVertex3f( 1.0f, 1.0f, 1.0f);					// Bottom Right Of The Quad (Top)
		tempRGB = getRGB(sides[TOP]);
		glColor3ub(tempRGB[0],tempRGB[1],tempRGB[2]);		// Set The Color To Green
		glNormal3f(0.0f, 1.0f, 0.0f);						// Normal Pointing Up
		glVertex3f( 0.95f, 1.01f, 0.05f);					// Top Right Of The Quad (Top)
		glVertex3f( 0.05f, 1.01f, 0.05f);					// Top Left Of The Quad (Top)
		glVertex3f( 0.05f, 1.01f, 0.95f);					// Bottom Left Of The Quad (Top)
		glVertex3f( 0.95f, 1.01f, 0.95f);					// Bottom Right Of The Quad (Top)

		//draw bottom
		glColor3ub(0,0,0);
		glNormal3f(0.0f, -1.0f, 0.0f);						// Normal Pointing Up
		glVertex3f( 1.0f,0.0f, 1.0f);					// Top Right Of The Quad (Bottom)
		glVertex3f( 0.0f,0.0f, 1.0f);					// Top Left Of The Quad (Bottom)
		glVertex3f( 0.0f,0.0f,0.0f);					// Bottom Left Of The Quad (Bottom)
		glVertex3f( 1.0f,0.0f,0.0f);					// Bottom Right Of The Quad (Bottom)
		tempRGB = getRGB(sides[BOTTOM]);
		glColor3ub(tempRGB[0],tempRGB[1],tempRGB[2]);
		glNormal3f(0.0f, -1.0f, 0.0f);						// Normal Pointing Up
		glVertex3f( .95f,-0.01f, .95f);					// Top Right Of The Quad (Bottom)
		glVertex3f( 0.05f,-0.01f, .95f);					// Top Left Of The Quad (Bottom)
		glVertex3f( 0.05f,-0.01f, 0.05f);					// Bottom Left Of The Quad (Bottom)
		glVertex3f( .95f,-0.01f, 0.05f);					// Bottom Right Of The Quad (Bottom)
		
		//draw front
		glColor3ub(0,0,0);
		glVertex3f( 1.0f, 1.0f, 1.0f);					// Top Right Of The Quad (Front)
		glVertex3f(0.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Front)
		glVertex3f(0.0f,0.0f, 1.0f);					// Bottom Left Of The Quad (Front)
		glVertex3f( 1.0f,0.0f, 1.0f);					// Bottom Right Of The Quad (Front)
		tempRGB = getRGB(sides[FRONT]);
		glColor3ub(tempRGB[0],tempRGB[1],tempRGB[2]);
		glNormal3f(0.0f, 0.0f, 1.0f);						// Normal Pointing Up
		glVertex3f( .95f, .95f, 1.01f);					// Top Right Of The Quad (Front)
		glVertex3f(0.05f, .95f, 1.01f);					// Top Left Of The Quad (Front)
		glVertex3f(0.05f,0.05f, 1.01f);					// Bottom Left Of The Quad (Front)
		glVertex3f( .95f,0.05f, 1.01f);					// Bottom Right Of The Quad (Front)
		
		//draw back
		glColor3ub(0,0,0);
		glVertex3f( 1.0f,0.0f,0.0f);					// Top Right Of The Quad (Back)
		glVertex3f(0.0f,0.0f,0.0f);					// Top Left Of The Quad (Back)
		glVertex3f(0.0f, 1.0f,0.0f);					// Bottom Left Of The Quad (Back)
		glVertex3f( 1.0f, 1.0f,0.0f);					// Bottom Right Of The Quad (Back)
		tempRGB = getRGB(sides[BACK]);
		glColor3ub(tempRGB[0],tempRGB[1],tempRGB[2]);
		glVertex3f( .95f,0.05f,-0.01f);					// Top Right Of The Quad (Back)
		glVertex3f(0.05f,0.05f,-0.01f);					// Top Left Of The Quad (Back)
		glVertex3f(0.05f, .95f,-0.01f);					// Bottom Left Of The Quad (Back)
		glVertex3f( .95f, .95f,-0.01f);					// Bottom Right Of The Quad (Back)
		
		//draw left
		glColor3ub(0,0,0);
		glVertex3f(0.0f, 1.0f, 1.0f);					// Top Right Of The Quad (Left)
		glVertex3f(0.0f, 1.0f,0.0f);					// Top Left Of The Quad (Left)
		glVertex3f(0.0f,0.0f,0.0f);					// Bottom Left Of The Quad (Left)
		glVertex3f(0.0f,0.0f, 1.0f);					// Bottom Right Of The Quad (Left)
		tempRGB = getRGB(sides[LEFT]);
		glColor3ub(tempRGB[0],tempRGB[1],tempRGB[2]);
		glVertex3f(-0.01f, .95f, .95f);					// Top Right Of The Quad (Left)
		glVertex3f(-0.01f, .95f,0.05f);					// Top Left Of The Quad (Left)
		glVertex3f(-0.01f,0.05f,0.05f);					// Bottom Left Of The Quad (Left)
		glVertex3f(-0.01f,0.05f, .95f);					// Bottom Right Of The Quad (Left)
		
		//draw rights
		glColor3ub(0,0,0);
		glVertex3f( 1.0f, 1.0f,0.0f);					// Top Right Of The Quad (Right)
		glVertex3f( 1.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Right)
		glVertex3f( 1.0f,0.0f, 1.0f);					// Bottom Left Of The Quad (Right)
		glVertex3f( 1.0f,0.0f,0.0f);					// Bottom Right Of The Quad (Right)
		tempRGB = getRGB(sides[RIGHT]);
		glColor3ub(tempRGB[0],tempRGB[1],tempRGB[2]);
		glVertex3f( 1.01f, .95f,0.05f);					// Top Right Of The Quad (Right)
		glVertex3f( 1.01f, .95f, .95f);					// Top Left Of The Quad (Right)
		glVertex3f( 1.01f,0.05f, .95f);					// Bottom Left Of The Quad (Right)
		glVertex3f( 1.01f,0.05f,0.05f);					// Bottom Right Of The Quad (Right)
	glEnd();											// Done Drawing The Quad

	return;
}

void cube_c::rotateSides(char axis, int direction)
{
	cubeSide newSide[6];
	cubeSide iSide;
	cube_c oldCube = *this;

	switch(axis)
	{
		case 'X':
			if(direction == 1)
			{
				newSide[TOP] = FRONT;
				newSide[RIGHT] = RIGHT;
				newSide[BOTTOM] = BACK;
				newSide[LEFT] = LEFT;
				newSide[FRONT] = BOTTOM;
				newSide[BACK] = TOP;
			}
			else if(direction == -1)
			{
				newSide[TOP] = BACK;
				newSide[RIGHT] = RIGHT;
				newSide[BOTTOM] = FRONT;
				newSide[LEFT] = LEFT;
				newSide[FRONT] = TOP;
				newSide[BACK] = BOTTOM;
			}
			break;
		case 'Y':
			if(direction == 1)
			{
				newSide[TOP] = TOP;
				newSide[RIGHT] = BACK;
				newSide[BOTTOM] = BOTTOM;
				newSide[LEFT] = FRONT;
				newSide[FRONT] = RIGHT;
				newSide[BACK] = LEFT;
			}
			else if(direction == -1)
			{
				newSide[TOP] = TOP;
				newSide[RIGHT] = FRONT;
				newSide[BOTTOM] = BOTTOM;
				newSide[LEFT] = BACK;
				newSide[FRONT] = LEFT;
				newSide[BACK] = RIGHT;
			}
			break;
		case 'Z':
			if(direction == -1)
			{
				newSide[TOP] = RIGHT;
				newSide[RIGHT] = BOTTOM;
				newSide[BOTTOM] = LEFT;
				newSide[LEFT] = TOP;
				newSide[FRONT] = FRONT;
				newSide[BACK] = BACK;
			}
			else if(direction == 1)
			{
				newSide[TOP] = LEFT;
				newSide[RIGHT] = TOP;
				newSide[BOTTOM] = RIGHT;
				newSide[LEFT] = BOTTOM;
				newSide[FRONT] = FRONT;
				newSide[BACK] = BACK;
			}
			break;
		default:
			break;
	}

	for(int i=0; i<6; i++)
	{
		iSide = (cubeSide)i;
		sides[newSide[iSide]] = oldCube.sides[iSide];
	}

	return;
}

//-----------------------------------------------
rcube_c::rcube_c()
{
	rotationAngle = 0.0f;
	rotationAxis = '\0';
	rotationIndex = 0;
	rotationDirection = 1;
	isRotating = false;
}

void rcube_c::drawCube()
{
	//right handed cartesian
	int rotVec[3] = {0,1,0};

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			for(int k=0; k<3; k++)
			{
				glPushMatrix();
				switch(rotationAxis)
				{
					case 'X':
						if(j==rotationIndex)
						{
							rotVec[0] = 1;
							rotVec[1] = 0;
							rotVec[2] = 0;
							rotationAngle += ROTATESPEED*rotationDirection;
						}
						break;
					case 'Y':
						if(i==rotationIndex)
						{
							rotVec[0] = 0;
							rotVec[1] = 1;
							rotVec[2] = 0;
							rotationAngle += ROTATESPEED*rotationDirection;
						}
						break;
					case 'Z':
						if(k==rotationIndex)
						{
							rotVec[0] = 0;
							rotVec[1] = 0;
							rotVec[2] = 1;
							rotationAngle += ROTATESPEED*rotationDirection;
						}
						break;
					default:
						rotationAngle = 0;
						rotationDirection = 0;
						break;
				}
				if(rotationAxis=='X' && i==rotationIndex||rotationAxis=='Y' && j==rotationIndex||rotationAxis=='Z' && k==rotationIndex)
				{
					glRotatef(rotationAngle, rotVec[0],rotVec[1],rotVec[2]);			
				}
				glTranslatef(-1.5f + i, -1.5f + j, -1.5f + k); 
				cubes[i][j][k].drawCube();
				glPopMatrix();
			}
		}
	}

	return;
}

void rcube_c::rotateCube(char axis, int index, int direction)
{
	if(!isRotating)
	{
		rotationAxis = axis;
		rotationIndex = index;
		rotationDirection = direction;
		isRotating = true;
	}

	return;
}

void rcube_c::updateCube()
{
	if((fabs(rotationAngle) <(90.0f+5*ROTATESPEED)) && (fabs(rotationAngle) > (90.0f-5*ROTATESPEED)))
	{
		moveCubes();
		isRotating = false;
		rotationAngle = 0.0f;
		rotationIndex = 0;
		rotationDirection = 0;
	}

	return;
}

void rcube_c::moveCubes()
{
	rcube_c oldCube = *this;

	switch(rotationAxis)
	{
		case 'X':
			if(rotationDirection == 1)
			{
				for(int j=0;j<3;j++)
				{
					for(int k=0;k<3;k++)
					{
						cubes[rotationIndex][2-k][j] = oldCube.cubes[rotationIndex][j][k];
						cubes[rotationIndex][2-k][j].rotateSides(rotationAxis,rotationDirection);
					}
				}
			}
			else if(rotationDirection == -1)
			{
				for(int j=0;j<3;j++)
				{
					for(int k=0;k<3;k++)
					{
						cubes[rotationIndex][k][2-j] = oldCube.cubes[rotationIndex][j][k];
						cubes[rotationIndex][k][2-j].rotateSides(rotationAxis,rotationDirection);
					}
				}
			}
			break;
		case 'Y':
			if(rotationDirection == -1)
			{
				for(int i=0;i<3;i++)
				{
					for(int k=0;k<3;k++)
					{
						cubes[2-k][rotationIndex][i] = oldCube.cubes[i][rotationIndex][k];
						cubes[2-k][rotationIndex][i].rotateSides(rotationAxis,rotationDirection);
					}
				}
			}
			else if(rotationDirection == 1)
			{
				for(int i=0;i<3;i++)
				{
					for(int k=0;k<3;k++)
					{
						cubes[k][rotationIndex][2-i] = oldCube.cubes[i][rotationIndex][k];
						cubes[k][rotationIndex][2-i].rotateSides(rotationAxis,rotationDirection);
					}
				}
			}
			break;
		case 'Z':
			if(rotationDirection == 1)
			{
				for(int i=0;i<3;i++)
				{
					for(int j=0;j<3;j++)
					{
						cubes[2-j][i][rotationIndex] = oldCube.cubes[i][j][rotationIndex];
						cubes[2-j][i][rotationIndex].rotateSides(rotationAxis,rotationDirection);
					}
				}
			}
			else if(rotationDirection == -1)
			{
				for(int i=0;i<3;i++)
				{
					for(int j=0;j<3;j++)
					{
						cubes[j][2-i][rotationIndex] = oldCube.cubes[i][j][rotationIndex];
						cubes[j][2-i][rotationIndex].rotateSides(rotationAxis,rotationDirection);
					}
				}
			}
			break;
		default:
			break;
	}

	return;
}

bool rcube_c::findCubeTouched(Vector3D campos, Vector3D moslook, int cubeLoc[], cubeSide &sideTouched)
{
	Vector3D mosLook2cam = campos - moslook;
	Vector3D points[3], *pointOnCube;
	float* pointp[3];
	cubeSide possibleSides[3];
	bool sideGood[3];
	
	bool foundCube = true;
		
	if(campos.x > 0.0f)
	{
		points[0] = findPointOnSide("+X",campos,moslook);
		possibleSides[0] = RIGHT;
	}
	else
	{
		points[0] = findPointOnSide("-X",campos,moslook);
		possibleSides[0] = LEFT;
	}
	if((fabs(points[0].y) < 1.5f*CUBELENGTH) && (fabs(points[0].z) < 1.5f*CUBELENGTH))
		sideGood[0] = true;
	else
		sideGood[0] = false;
		
	if(campos.y > 0.0f)
	{
		points[1] = findPointOnSide("+Y",campos,moslook);
		possibleSides[1] = TOP;
	}
	else
	{	
		points[1] = findPointOnSide("-Y",campos,moslook);
		possibleSides[1] = BOTTOM;
	}
	if((fabs(points[1].x) < 1.5f*CUBELENGTH) && (fabs(points[1].z) < 1.5f*CUBELENGTH))
		sideGood[1] = true;
	else
		sideGood[1] = false;
		
	if(campos.z > 0.0f)
	{
		points[2] = findPointOnSide("+Z",campos,moslook);
		possibleSides[2] = FRONT;
	}
	else
	{
		points[2] = findPointOnSide("-Z",campos,moslook);
		possibleSides[2] = BACK;
	}
	if((fabs(points[2].x) < 1.5f*CUBELENGTH) && (fabs(points[2].y) < 1.5f*CUBELENGTH))
		sideGood[2] = true;
	else
		sideGood[2] = false;
		
	pointOnCube = &points[0];
	sideTouched = possibleSides[0];

	if(((campos-points[1]).length() < (campos-points[0]).length()) && sideGood[1])
	{
		pointOnCube = &points[1];
		sideTouched = possibleSides[1];
	}
	if(((campos-points[2]).length() < (campos-*pointOnCube).length()) && sideGood[2])
	{
		pointOnCube = &points[2];
		sideTouched = possibleSides[2];
	}
	
	pointp[0] = &pointOnCube->x;
	pointp[1] = &pointOnCube->y;
	pointp[2] = &pointOnCube->z;
	
	for(int s=0;s<3;s++)
	{
		if((-1.5f*CUBELENGTH <= *pointp[s]) && (*pointp[s] < 0.0f))
			cubeLoc[s] = 0;
		else if(*pointp[s] < 0.5f*CUBELENGTH)
			cubeLoc[s] = 1;
		else if(*pointp[s] <= 1.5f*CUBELENGTH)
			cubeLoc[s] = 2;
		else
			foundCube = false;
		
		pointp[s] = NULL;
	}
	
	if((fabs(pointOnCube->x) > 1.5f*CUBELENGTH) && (fabs(pointOnCube->y) > 1.5f*CUBELENGTH) && (fabs(pointOnCube->z) > 1.5f*CUBELENGTH))
		foundCube = false;
		
	return foundCube;
}

void rcube_c::twistCube(Vector3D camPt, Vector3D lookPt, Vector3D mosMove)
{
	int touchCube[3] = {-1,-1,-1};
	cubeSide touchCubeSide;	
	Vector3D relRotDir[2];	//0: about relative y, 1: about relative x
	char relRotAx[2];
	int axisIdx;
	int cubeIdx;
	int rotDir;				//direction of rotation(+1 or -1)
	
	if(!isRotating)
	{
		//touchCubeSide = rcube.findCubeTouched(cam.pos, moslook, touchCube);
		if(findCubeTouched(camPt, lookPt, touchCube,touchCubeSide))
		{
			//touchPoint = Vector3D(touchCube[0],touchCube[1],touchCube[2]) + char2vec3(touchCubeSide)
			switch(touchCubeSide)
			{
				case FRONT:
					relRotDir[0] = X;
					relRotAx[0] = 'Y';
					relRotDir[1] = -Y;
					relRotAx[1] = 'X';
					break;
				case BACK:
					relRotDir[0] = -X;
					relRotAx[0] = 'Y';
					relRotDir[1] = Y;
					relRotAx[1] = 'X';
					break;
				case LEFT:
					relRotDir[0] = Z;
					relRotAx[0] = 'Y';
					relRotDir[1] = -Y;
					relRotAx[1] = 'Z';
					break;
				case RIGHT:
					relRotDir[0] = -Z;
					relRotAx[0] = 'Y';
					relRotDir[1] = Y;
					relRotAx[1] = 'Z';
					break;
				case TOP:
					relRotDir[0] = -X;
					relRotAx[0] = 'Z';
					relRotDir[1] = Z;
					relRotAx[1] = 'X';
					break;
				case BOTTOM:
					relRotDir[0] = X;
					relRotAx[0] = 'Z';
					relRotDir[1] = -Z;
					relRotAx[1] = 'X';
					break;
				default:
					break;
			}
		
		
			if(fabs(mosMove.dot(relRotDir[1])) > fabs(mosMove.dot(relRotDir[0])))
				axisIdx = 1;
			else	
				axisIdx = 0;
				
			if(mosMove.dot(relRotDir[axisIdx]) > 0)
				rotDir = 1;
			else
				rotDir = -1;
				
			switch(relRotAx[axisIdx])
			{
				case 'X':
					cubeIdx = 0;
					break;
				case 'Y':
					cubeIdx = 1;
					break;
				case 'Z':
					cubeIdx = 2;
					break;
				default:
					break;
			}
			rotateCube(relRotAx[axisIdx], touchCube[cubeIdx], rotDir);
		}
	}		
		
	return;		
}
//------------------------------------------
int* getRGB(color clr)
{
	int *clrRGB;		//color to be output

	switch(clr)
	{
	case BLACK:
		clrRGB = BLACKub;
		break;
	case RED:
		clrRGB = REDub;
		break;
	case ORANGE:
		clrRGB = ORANGEub;
		break;
	case YELLOW:
		clrRGB = YELLOWub;
		break;
	case GREEN:
		clrRGB = GREENub;
		break;
	case BLUE:
		clrRGB = BLUEub;
		break;
	case WHITE:
		clrRGB = WHITEub;
		break;
	default:
		break;
	}

	return clrRGB;
}

Vector3D findPointOnSide(char side[], Vector3D camPt, Vector3D lookPt)
{
	Vector3D point;
	Vector3D center;
	Vector3D axis, look2cam;
	int sideSign;
	GLfloat distFrac;
	
	if(side[0] =='-')
	{
		sideSign = 1;
	}
	else
	{
		sideSign = 1;
	}
	
	axis = char2vec3(side[1])*sideSign;
	
	/*switch(side[1])
	{
		case 'X':
			axis = X*sideSign;
			break;
		case 'Y':
			axis = Y*sideSign;
			break;
		case 'Z':
			axis = Z*sideSign;
			break;
		default:
			break;
	}*/
	
	center = axis*CUBELENGTH*1.5f;	
	look2cam = camPt - lookPt;
	distFrac = (axis.dot(center-lookPt)/axis.dot(look2cam));
	point = lookPt + look2cam*distFrac;
	
	return point;
}
