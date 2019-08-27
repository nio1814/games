#ifndef SHAPE
#define SHAPE

#include "qtgl.h"
#include <vector3d.h>

enum cubis{CORNER, EDGE, CENTER};
enum cubeSide{TOP, BOTTOM, LEFT, RIGHT, FRONT, BACK};
enum color{BLACK, RED, ORANGE, YELLOW, GREEN, BLUE, WHITE};

extern int BLACKub[3];
extern int REDub[3];
extern int ORANGEub[3];
extern int YELLOWub[3];
extern int GREENub[3];
extern int BLUEub[3];
extern int WHITEub[3];

#define CUBELENGTH 1.0f
#define ROTATESPEED .25f

class cube_c
{
public:
	cube_c();
	cube_c(cubis type, color ctop, color cbot, color cleft, color cright, color cfront, color cback);

	void drawCube();
	//rotate the sides of a cube
	void rotateSides(char axis, int direction);

	int newLocation[3];
	cubeSide newDirection[6];
	cubis cubeType;
	color sides[6];
};

class rcube_c
{
public:
	rcube_c();
	void drawCube();
	void rotateCube(char axis, int index, int direction);
	void rotateCube(Vector3D axis, int index, int direction);
	void updateCube();
	//move cubes to new positions following rotation
	void moveCubes();
	//find the cube touched and which side of the entire cube was touched
	bool findCubeTouched(Vector3D campos, Vector3D moslook, int cubeLoc[], cubeSide &touchedSide);
	//twist cube depending on which cube was touched and the direction of mouse movement
	void twistCube(Vector3D camPt, Vector3D lookPt, Vector3D mosMove);

	cube_c cubes[3][3][3];

	GLfloat rotationAngle;
	char rotationAxis;
	int rotationIndex;
	int rotationDirection;
	bool isRotating;
};

int* getRGB(color clr);
Vector3D findPointOnSide(char side[], Vector3D camPt, Vector3D lookPt);

#endif
