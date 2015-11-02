#include "level.h"
#include "camera.h"
#include "keys.h"

Level::Level()
{
    started = false;
    numPlayers = 0;
    majAxis = Vector3D(0,0,1);
    bGravity = false;
    gravityM = 9.81;
    gravityV = majAxis*gravityM;
    //numTextures = 0;

    cameras = new CameraPoints;
    lights = NULL;
    //alltexture = new texture_s[MAXTEXTURES];
    //player1 = player2 = NULL;
}

Level::~Level()
{

}

Level::Level(int players)
{
    Level();
    numPlayers = players;
}


void Level::setMajAxis(Vector3D axis)
{
    majAxis = axis;
    allObj.majorAxis = axis;

    return;
}

bool Level::create(int index)
{
    bool status = false;
    int numExtraSpheres = rand()%15;

    switch(index)
    {
        case 0:
            allObj.addSpheres(2.0f, .55f,   Vector3D(-1.0f,1.5f,0.0f));
            allObj.addSpheres(1.0f, .35f,   Vector3D(1, 2, 1.5));

            for(int i=0; i<numExtraSpheres; i++)
            {
                allObj.addSpheres(fabs(.70f*cos((float)rand())), fabs(.50f*cos((float)rand()))+.1f,  Vector3D(3*cos((float)rand()), 4*fabs(cos((float)rand())), 3*cos((float)rand())));
                allObj.setColor(SPHERE, i, Vector3D(rand()%256, rand()%256, rand()%256) );
            }

            ball = &allObj.spheres->objs[1];
            //level1.player1 = ball;
            //ball->texture = balltxr;

            allObj.addPlanes(1,1,8,8,0,  Vector3D(0,0,0));
            allObj.setNormal(PLANE, 0, Vector3D(0,1,0));
//			allObj.setTexture(PLANE, 0, tile1txr);

            allObj.addPlanes(3,1,8,2,0,  Vector3D(-4,1,0));
            allObj.setNormal(PLANE, 1, Vector3D(1,0,0));

            cameras->addPoint(Vector3D(0, 4.6, 8), Vector3D(0, 0, 0), X, 10.0f);
            //level1.allObj.cameras->addPoint(Vector3D(xCam, 3.60f, -14.6f), Vector3D(-11.8f, -3.0f, -13.8f), 5.0f);
            cameras->addPoint(Vector3D(0, 3.60f, 0), Vector3D(0, 3.0f, -13.8f), Y, 10.0f);
            status = true;
            break;
        case 1:
            cameras->addPoint(Vector3D(5,5,2), Vector3D(-5,0,3), Z, DEFFOLLOWDIST);
            cameras->camview = FIRST;
            loadmap(":Data/model/myschool3.3ds", 1.5f);
            majAxis = Z;
            status = true;
            break;
        case 2:
            loadmap(":Data/model/map1.3ds", 1.0f);
            cameras->addPoint(Vector3D(5,5,2),Vector3D(-5,0,3), Z, DEFFOLLOWDIST);
            cameras->camview = FIRST;
            majAxis = Z;
            status = true;
            break;
    }

    return status;
}

/*Vector3D level::setCam(Object* obj, CameraView view)
{
    cameraPoint* cam = &cameras->cpoints[cameras->currentPoint];
    cameraPoint* nextcam;
    Vector3D cam2cam, cam2obj, cam2look;
    Vector3D pos, look, alongv, movepos;
    Vector3D objpos;
    GLfloat camdist, objvel, camRotate;

    camRotate = 0;

    if(cameras->currentPoint == cameras->numPoints-1)
    {
        nextcam = cam;
    }
    else
        nextcam = &cameras->cpoints[cameras->currentPoint+1];

    objpos = obj->mass->pos;
    objvel = obj->mass->vel.length();
    cam2obj = obj->mass->pos - cam->pos;

    /*cam2cam = nextcam->pos - cam->pos;
    camdist = cam2cam.length();
    alongv = cam2obj.proj(&cam2cam)*.1f;
    cam->movepos = cam->pos + alongv;*/
/*	if(view == FOLLOW)
    {
        if(obj->moveForce == Vector3D(0,0,0))
        {
            movepos = objpos - cam2obj.unit()*cam->followDist;
        }
        else
        {
            movepos = objpos - (obj->moveForce.unit()*cam->followDist + cam2obj.unit()*cam->followDist)/2;
        }
        cam->pos += (movepos - cam->pos)*.2f*delta*objvel;
        cam->look += (objpos - cam->look)*.7f*delta*objvel;

        //look = obj->mass->pos.proj(&nextcam->look, &cam->look);

        //gluLookAt(cam->movepos.x, cam->movepos.y, cam->movepos.z, look.x, look.y, look.z, cam->up.x, cam->up.y, cam->up.z);
    }
    else if(view == LOCKED)
    {
        cam->look += (objpos - cam->look)*.7f*delta*objvel;
    }
    else if(view == FIRST)
    {
        cam->look += (objpos.proj(&majAxis) - cam->look.proj(&majAxis))*.95f*delta;
        cam2look = cam->look - cam->pos;
        cam->pos = objpos;
        //cam->pos += (objpos - cam->pos)*1.95f*delta;
        if(isKeys(VK_LEFT))
            camRotate = 100*delta;
        else if(isKeys(VK_RIGHT))
            camRotate = -100*delta;
        cam2look = cam2look.rotate3D(&majAxis, camRotate);
        cam->look = cam2look + cam->pos;
    }

    gluLookAt(cam->pos.x, cam->pos.y, cam->pos.z, cam->look.x, cam->look.y, cam->look.z, cam->up.x, cam->up.y, cam->up.z);
    cam2look = cam->look - cam->pos;

    return cam2look;
}
*/

void Level::addCamera(Vector3D campos, Vector3D lookpos, const Vector3D upin, GLfloat dist)
{
    cameras->addPoint(campos, lookpos, upin, dist);

    return;
}


Vector3D Level::setCam(Vector3D* pos)
{
    CameraPoint* cam = &cameras->cpoints[cameras->currentPoint];
    CameraPoint* nextcam;
    Vector3D cam2cam, cam2obj, cam2look;
    Vector3D look, alongv, movepos;
    GLfloat camdist, objvel, camRotate;

    camRotate = 0;

    if(cameras->currentPoint == cameras->numPoints()-1)
    {
        nextcam = cam;
    }
    else
        nextcam = &cameras->cpoints[cameras->currentPoint+1];

    cam2obj = *pos - cam->pos;

    if(cameras->camview == FOLLOW)
    {
        movepos = *pos - cam2obj.unit()*cam->followDist;
        cam->pos += (*pos - cam->pos)*.2f*delta*objvel;
        cam->look += (*pos - cam->look)*.7f*delta*objvel;
    }
    else if(cameras->camview == LOCKED)
    {
        cam->look += (*pos - cam->look)*.7f*delta*objvel;
    }
    else if(cameras->camview == FIRST)
    {
        cam->look += (pos->proj(&majAxis) - cam->look.proj(&majAxis))*.95f*delta;
        cam2look = cam->look - cam->pos;
        cam->pos = *pos;

        if(isKeys(Qt::Key_Left))
            camRotate = 100*delta;
        else if(isKeys(Qt::Key_Right))
            camRotate = -100*delta;
        cam2look = cam2look.rotate3D(&majAxis, camRotate);
        cam->look = cam2look + cam->pos;
    }

    glLookAt(cam->pos.toQVector3D(), cam->look.toQVector3D(), cam->up.toQVector3D());
    cam2look = cam->look - cam->pos;

    return cam2look;
}

void Level::updateCam()
{
    CameraPoint* cam = &cameras->cpoints[cameras->currentPoint];

    if(cam->look == cam->pos)
    {
        cam->pos += X;
    }

    switch(cameras->camview)
    {
        case FIRST:
            //cam->look += (cam->pos.proj(&majAxis) - cam->look.proj(&majAxis))*.95f*delta;
            break;
        case FOLLOW:
            break;
        default:
//			MessageBox(NULL,"Invalid Camera View.","ERROR",MB_OK | MB_ICONINFORMATION);
            qErrnoWarning("Invalid Camera View %d", cameras->camview);
            break;
    }

    glLookAt(cam->pos.toQVector3D(), cam->look.toQVector3D(), cam->up.toQVector3D());

    cam->oldPos = cam->pos;
    cam->oldLook = cam->look;
    return;
}

void Level::setView(CameraView view)
{
    cameras->camview = view;
    return;
}

/*texture_s* level::addTexture(char *filename, char *ID)
{
    bool success = false;
    texture_s* ptr = NULL;

    success = LoadGLTextures(&alltexture[numTextures++], filename);
    if(success)
        ptr = &alltexture[numTextures-1];

    return ptr;
}

texture_s* level::addTexture(char *filename1, char *filename2, char *ID)
{
    bool success = false;
    texture_s* ptr = NULL;

    success = LoadGLTextures(&alltexture[numTextures], filename1);
    if(success)
        success = LoadGLTextures(&alltexture[numTextures++], filename2);
    if(success)
        ptr = &alltexture[numTextures-1];

    return ptr;
}*/


/*Level::Level(char* filename): Level()
{
    mapFileName = filename;
    //world3ds.Init_3ds(filename);
}*/

void Level::loadmap(QString filename, GLfloat scale)
{
    mapFileName = filename;

    world3ds.Init_3ds(mapFileName.toLatin1().data());
    for(int i=0; i<world3ds.m3DModel.numOfObjects; i++)
    {
        for(int j=0; j<world3ds.m3DModel.pObject[i].numOfVerts; j++)
        {
            //world3ds.m3DModel.pObject[i].pVerts[j] = world3ds.m3DModel.pObject[i].pVerts[j]*scale;
            world3ds.m3DModel.pObject[i].pVerts[j].x = world3ds.m3DModel.pObject[i].pVerts[j].x*scale;
            world3ds.m3DModel.pObject[i].pVerts[j].y = world3ds.m3DModel.pObject[i].pVerts[j].y*scale;
            world3ds.m3DModel.pObject[i].pVerts[j].z = world3ds.m3DModel.pObject[i].pVerts[j].z*scale;
        }
    }

    return;
}

void Level::run(GLfloat dt)
{
    char timetext[100];
    QTime clock;

    if(!started)
    {
        started = true;
//		startTime = GetTickCount();
        startTime = clock.msec();
        currentTime = startTime;
    }
    else
    {
        currentTime = clock.msec();
        timer = (currentTime-startTime)/1000;
        sprintf(timetext, "%.2f", timer);
    }

    updateCam();
    run3ds();
    allObj.run(dt);

    //msgList.display(dt);

    return;
}

void Level::run3ds()
{
    /*for (int a = 0; a < allObj.spheres->numOfMasses; ++a)		// We will iterate every mass
    {
        allObj.spheres->objs[a].init();
    }

    detectCollision(&allObj, &world3ds.m3DModel);
    for(int sidx = 0; sidx < allObj.spheres->numOfMasses; sidx++)
    {
        if(allObj.spheres->objs[sidx].isTouching3ds)
            collide(&allObj.spheres->objs[sidx], &world3ds.m3DModel);
        //;
    }*/

    return;
}

void Level::draw()
{
//    world3ds.Render_3ds();
    allObj.draw();

    return;
}
