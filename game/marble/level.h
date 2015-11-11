#ifndef LEVEL_H
#define LEVEL_H

#include "qtgl.h"

#include "object.h"
#include "3dsGT/3dsLoader.h"

#include <qstring.h>

class light_c;

class Level
{
public:
    Level();
	Level(int players);
//    Level(QString filename);
    ~Level();

    bool create(int index);
    void loadmap(QString filename, GLfloat scale);
    void run(GLfloat dt);
    void run3ds();
    void draw();

    void setMajAxis(Vector3D axis);
    //Vector3D setCam(Object* obj, CameraView view);
    void addCamera(Vector3D campos, Vector3D lookpos, const Vector3D upin, GLfloat dist);
	Vector3D setCam(const Vector3D &pos, GLfloat delta, GLfloat objvel=1);
    void updateCam();
    void setView(CameraView view);
    //texture_s* addTexture(char *filename, char *ID);
    //texture_s* addTexture(char *filename1, char *filename2, char *ID);

    object_sphere* ball;
    CameraPoints* cameras;
    Vector3D majAxis;
private:
    int levelNum;
    bool started;
	GLfloat startTime, currentTime, timer;
    int numPlayers;
    Vector3D playerStart;		//player starting positions

    bool bGravity;
    GLfloat gravityM;
    Vector3D gravityV;
    //int numTextures;
    //messageList msgList;

    object_holder allObj;
    //Object *player1, *player2;
    //texture_s *alltexture;

    light_c* lights;

    C3dsLoader world3ds;
    QString mapFileName;
};

#endif // LEVEL_H
