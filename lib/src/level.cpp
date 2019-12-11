#include "level.h"
#include "camera.h"
#include "keys.h"
#include "object/plane.h"
#include "object/sphere.h"

#include <qdatetime.h>

Level::Level()
{
    started = false;
    numPlayers = 0;
    majorAxis = Vector3D(0,0,1);
    bGravity = false;
    gravityM = 9.81f;
    gravityV = majorAxis*gravityM;
    //numTextures = 0;

    lights = NULL;
    //alltexture = new texture_s[MAXTEXTURES];
    //player1 = player2 = NULL;
}

Level::~Level()
{

}

void Level::addObject(std::shared_ptr<Object> object)
{
  this->objects.addObject(object);
}

Level::Level(int players)
{
    Level();
    numPlayers = players;
}


void Level::setMajAxis(Vector3D axis)
{
    majorAxis = axis;
    objects.majorAxis = axis;

    return;
}

bool Level::create(int index)
{
    bool status = false;
	srand(QDateTime::currentDateTime().time().msec());

//	numExtraSpheres = 0;

//    GLfloat sqr3 = sqrtf(3.0f);
	matrix2D3 basis;

    switch(index)
    {
        case 0:

            break;
        case 2:
            cameras.addPoint(Vector3D(5,5,2), Vector3D(-5,0,3), Z, DEFFOLLOWDIST);
            cameras.camview = FIRST;
            loadmap(":Data/model/myschool3.3ds", 1.5f);
            majorAxis = Z;
            status = true;
            break;
        case 3:
            loadmap(":Data/model/map1.3ds", 1.0f);
            cameras.addPoint(Vector3D(5,5,2),Vector3D(-5,0,3), Z, DEFFOLLOWDIST);
            cameras.camview = FIRST;
            majorAxis = Z;
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

    cam2cam = nextcam->pos - cam->pos;
    camdist = cam2cam.length();
    alongv = cam2obj.proj(&cam2cam)*.1f;
    cam->movepos = cam->pos + alongv;
    if(view == FOLLOW)
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
    cameras.addPoint(campos, lookpos, upin, dist);

    return;
}


Vector3D Level::setCam(const Vector3D& pos, GLfloat delta, GLfloat objvel)
{
    std::shared_ptr<CameraPoint> nextcam;
    Vector3D cam2cam, cam2obj, cam2look;
    Vector3D look, alongv, movepos;

  std::shared_ptr<CameraPoint> camera = this->cameras.current();
    if(this->cameras.currentIndex == this->cameras.numPoints()-1)
    {
        nextcam = camera;
    }
    else
        nextcam = this->cameras.points[cameras.currentIndex+1];

  cam2obj = pos - camera->pos;

    if(cameras.camview == FOLLOW)
    {
    movepos = pos - cam2obj.unit()*camera->followDist;
    camera->pos += (movepos - camera->pos)*.2f*delta*objvel;
    camera->look += (pos - camera->look)*.7f*delta*objvel;
    }
    else if(cameras.camview == LOCKED)
    {
    camera->look += (pos - camera->look)*.7f*delta*objvel;
    }
    else if(cameras.camview == FIRST)
    {
    camera->look += (pos.proj(majorAxis) - camera->look.proj(majorAxis))*.95f*delta;
        cam2look = camera->look - camera->pos;
    camera->pos = pos;

		  float camRotate = 0;
        if(isKeys(Qt::Key_Left))
            camRotate = 100*delta;
        else if(isKeys(Qt::Key_Right))
            camRotate = -100*delta;
        cam2look = cam2look.rotate3D(majorAxis, camRotate);
        camera->look = cam2look + camera->pos;
    }

    glLookAt(camera->pos.toQVector3D(), camera->look.toQVector3D(), camera->up.toQVector3D());
    cam2look = camera->look - camera->pos;

    return cam2look;
}

void Level::updateCam()
{
    if(this->camera()->look == this->camera()->pos)
    {
        this->camera()->pos += X;
    }

  Vector3D camToLook = this->camera()->look - this->camera()->pos;

    switch(cameras.camview)
    {
        case FIRST:
            //cam->look += (cam->pos.proj(&majAxis) - cam->look.proj(&majAxis))*.95f*delta;
            break;
        case FOLLOW:
      this->camera()->pos += camToLook*(camToLook.length() - this->camera()->followDist)*.01f;
            break;
        default:
//			MessageBox(NULL,"Invalid Camera View.","ERROR",MB_OK | MB_ICONINFORMATION);
            qErrnoWarning("Invalid Camera View %d", cameras.camview);
            break;
    }

    glLookAt(this->camera()->pos.toQVector3D(), this->camera()->look.toQVector3D(), this->camera()->up.toQVector3D());

    this->camera()->oldPos = this->camera()->pos;
    this->camera()->oldLook = this->camera()->look;
}

void Level::setView(CameraView view)
{
    cameras.camview = view;
    return;
}

std::shared_ptr<CameraPoint> Level::camera()
{
  return this->cameras.current();
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

    gravityVec = majorAxis*-1;
//    gravityVec = majAxis*0;
//    updateCam();
  setCam(player->pos, dt, player->vel.length());
    run3ds();
    objects.run(dt);

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
  glLookAt(this->camera()->pos.toQVector3D(), player->pos.toQVector3D(), majorAxis.toQVector3D());
//    world3ds.Render_3ds();
    objects.draw();

    return;
}
