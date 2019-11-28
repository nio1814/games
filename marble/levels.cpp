#include "level.h"

#include "object/plane.h"

std::shared_ptr<Level> createLevel1()
{
  std::shared_ptr<Level> level = std::make_shared<Level>();
  level->majAxis = Y;
  const Vector3D gravity = level->majAxis * -9.8f;

  std::shared_ptr<object_sphere> sphere = std::make_shared<object_sphere>(2.0f, .55f);
  sphere->mass->pos = Vector3D(-1.0f,1.5f,0.0f);
  sphere->setGravity(gravity);
  level->objects.addObject(sphere);
//            allObj.addSpheres(2.0f, .55f,   Vector3D(-1.0f,1.5f,0.0f));

  level->player = std::make_shared<object_sphere>(1.0f, .35f);
  level->player->mass->pos = Vector3D(1, 2, 1.5);
  level->player->mass->elas = .5;
  level->player->setGravity(gravity);
//            allObj.addSpheres(1.0f, .35f,   Vector3D(1, 2, 1.5));
  level->objects.addObject(level->player);

    for(int i=0; i<rand()%15; i++)
    {
        sphere = std::make_shared<object_sphere>(std::abs(.70f*cos((float)rand())), std::abs(.50f*cos((float)rand()))+.1f);
        sphere->mass->pos = Vector3D(3*cos((float)rand()), 4*fabs(cos((float)rand())), 3*cos((float)rand()));
        sphere->setGravity(gravity);
        sphere->texture.color = Vector3D(rand()%256, rand()%256, rand()%256);
        level->addObject(sphere);
//                allObj.addSpheres(fabs(.70f*cos((float)rand())), fabs(.50f*cos((float)rand()))+.1f,  Vector3D(3*cos((float)rand()), 4*fabs(cos((float)rand())), 3*cos((float)rand())));
//                allObj.setColor(SPHERE, i, Vector3D(rand()%256, rand()%256, rand()%256) );
    }

  //		  ball = allObj.spheres.objs[1];

  //            ball = &allObj.spheres[1];
      //level1.player1 = ball;
      //ball->texture = balltxr;

//  level->objects.majorAxis = majAxis;

  matrix2D3 basis;
  basis.A[0] = Z;
  basis.A[1] = X;
  basis.A[2] = Y;
  level->objects.m_basis = basis;

//  level.objects.addPlanes(1,1,8,8,0,0,  Vector3D(0,0,0));
  level->objects.addPlane(1,8,8,0,0,  Vector3D(0,0,0));
  //            allObj.setNormal(PLANE, 0, Vector3D(0,1,0));
  //			allObj.setTexture(PLANE, 0, tile1txr);
  //            allObj.addPlanes(3,1,8,2,0,0, Vector3D(-4,1,0));
  //            allObj.setNormal(PLANE, 1, Vector3D(1,0,0));
//  plane = object_plane(2,8,Vector3D(-4,1,0),X,basis);
//  allObj.addPlane(plane);
  std::shared_ptr<object_plane> plane = level->objects.addPlane(2, 8, Vector3D(-4,1,0), X, basis);
  std::shared_ptr<object_plane> nextPlane = copyPlane(plane);
  nextPlane->mass->pos = Vector3D(4,1,0);
  //            allObj.setPos(PLANE, 2,  Vector3D(4,1,0));
  //            allObj.setNormal(PLANE, 2, Vector3D(-1,0,0));
//  allObj.addPlane(plane);
  level->addObject(nextPlane);

  //            allObj.setPos(PLANE, 3,  Vector3D(0,1,4));
  nextPlane = copyPlane(plane);
  nextPlane->setPosition(Vector3D(0,1,4));
  //            allObj.setNormal(PLANE, 3, Vector3D(0,0,-1));
  nextPlane->rotate(Y,90);
  //            allObj.flipBase(PLANE, 3);
//  allObj.addPlane(plane);
  level->addObject(nextPlane);

  //			allObj.addPlanes(2,1,2,2,0,0,  Vector3D(0,0,0));
  //            allObj.setPos(PLANE, 4,  Vector3D(-3,1,-4));
  //            allObj.setNormal(PLANE, 4, Vector3D(0,0,1));
//  plane = object_plane(2,2,Vector3D(-3,1,-4), Z, basis);
//  allObj.addPlane(plane);
  level->objects.addPlane(2, 2, Vector3D(-3, 1, -4), Z, basis);

  //			allObj.setPos(PLANE, 5,  Vector3D(3,1,-4));
  //            allObj.setNormal(PLANE, 5, Vector3D(0,0,1));
  nextPlane = std::dynamic_pointer_cast<object_plane>(level->objects.last());
  nextPlane->setPosition(Vector3D(3,1,-4));
  nextPlane->orient(Z);
//  allObj.addPlane(plane);
  level->addObject(nextPlane);

  //			allObj.addPlanes(1,4,10,0,0,  Vector3D(0,-.98f,-8.9f));
  //            allObj.setNormal(PLANE, 6, Vector3D(0,1,-.2));
  //            allObj.flipBase(PLANE, 6);
  //        allObj.setTexture(PLANE, 6, wall1txr);
  //			plane = object_plane(1,4,10,0,0,Vector3D(0,1,-.2));
  //			plane.setPosition(Vector3D(0,-.98f,-8.9f));
//  plane = object_plane(10,4,Vector3D(0,-.98f,-8.9f),Vector3D(0,1,-.2), basis);
//  allObj.addPlane(plane);
  level->objects.addPlane(10,4,Vector3D(0,-.98f,-8.9f),Vector3D(0,1,-.2), basis);

  //			allObj.addPlanes(1,4,4,0,0,  Vector3D(0,-1.96f,-15.8f));
  //        allObj.setTexture(PLANE, 7, wall1txr);
//  plane = object_plane(4,4,Vector3D(0,-1.96f,-15.8f),majAxis,basis);
  //			plane.setPosition(Vector3D(0,-1.96f,-15.8f));
//  allObj.addPlane(plane);
  level->objects.addPlane(4,4,Vector3D(0,-1.96f,-15.8f), level->majAxis, basis);

  /*allObj.addPlanes(2,1,4,2,0,0,  Vector3D(0,-.96f,-17.8f));
      allObj.setNormal(PLANE, 8, Vector3D(0,0,1));
  allObj.flipBase(PLANE, 8);*/
//  plane = object_plane(2,4,Vector3D(0,-.96f,-17.8f),Z,basis);
//  allObj.addPlane(plane);

//  /*allObj.setPos(PLANE, 9,  Vector3D(2,-.96f,-15.8f));
//  allObj.setNormal(PLANE, 9, Vector3D(-1,0,0));*/
//  plane.setPosition(Vector3D(2,-.96f,-15.8f));
//  plane.orient(-X);
//  plane.rotateAroundNormal(90);
//  allObj.addPlane(plane);

//  /*allObj.addPlanes(1,4,20,0,0,  Vector3D(-11.8f,-3.92f,-15.8f));
//  allObj.setNormal(PLANE, 10, Vector3D(-.2f,1.0f,0.0f));*/
//      //level1.allObj.flipBase(PLANE, 10);
//  //        allObj.setTexture(PLANE, 10, wall1txr);
//  plane = object_plane(20,4, Vector3D(-11.8f,-3.92f,-15.8f), Vector3D(-.2f,1.0f,0.0f), basis);
//  allObj.addPlane(plane);

//  /*allObj.addPlanes(1,4,4,0,0,  Vector3D(-23.6f,-5.88f,-15.8f));
//  allObj.setNormal(PLANE, 11, Vector3D(0.0f, 1.0f, 0.0f));*/
//  //        allObj.setTexture(PLANE, 11, wall1txr);*/
//  plane = object_plane(4,4, Vector3D(-23.6f,-5.88f,-15.8f), Y, basis);
//  allObj.addPlane(plane);

//  /*allObj.addPlanes(10,1,4,1,0,0, Vector3D( -25.6f-sqr3/4, -5.63f, -15.8f));
//  allObj.setNormal(PLANE, 12, Vector3D(1.0f, sqrt(3), 0.0f));*/
//  plane = object_plane(4,1,Vector3D( -25.6f-sqr3/4, -5.63f, -15.8f), Vector3D(1.0f, sqrt(3), 0.0f), basis);
//  plane.flipBase();
//  allObj.addPlane(plane);

//  /*allObj.setPos(PLANE,13,  Vector3D(-23.6f, -5.63f, -17.8f-sqr3/4));
//      allObj.setNormal(PLANE, 13, Vector3D(0.0f, sqr3, 1.0f));
//  allObj.flipBase(PLANE, 13);*/
//  plane.setPosition(Vector3D(-23.6f, -5.63f, -17.8f-sqr3/4));
//  plane.orient(Vector3D(0.0f, sqr3, 1.0f));
//  allObj.addPlane(plane);

//  /*allObj.setPos(PLANE,14,  Vector3D(-25.6f-sqr3/2-.25f, -5.38f+sqr3/4, -15.8f));
//  allObj.setNormal(PLANE, 14, Vector3D(sqrt(3), 1.0f, 0.0f));*/
//  plane.setPosition(Vector3D(-25.6f-sqr3/2-.25f, -5.38f+sqr3/4, -15.8f));
//  plane.orient(Vector3D(sqrt(3), 1.0f, 0.0f));
//  allObj.addPlane(plane);

//  /*allObj.setPos(PLANE,15,  Vector3D(-23.6f, -5.38f+sqr3/4, -17.8f-sqr3/2-.25f));
//      allObj.setNormal(PLANE, 15, Vector3D(0.0f, 1.0f, sqr3));
//  allObj.flipBase(PLANE, 15);*/
//  plane.setPosition(Vector3D(-23.6f, -5.38f+sqr3/4, -17.8f-sqr3/2-.25f));
//  plane.orient(Vector3D(0.0f, 1.0f, sqr3));
//  allObj.addPlane(plane);

//  /*allObj.setPos(PLANE,16,  Vector3D(-25.6f-sqr3/2-.5f,-5.38f+sqr3/2+.5f,-15.8f));
//  allObj.setNormal(PLANE, 16, Vector3D(1.0f, 0.0f, 0.0f));*/
//  plane.setPosition(Vector3D(-25.6f-sqr3/2-.5f,-5.38f+sqr3/2+.5f,-15.8f));
//  plane.orient(X);
//  allObj.addPlane(plane);

//  /*allObj.setPos(PLANE,17,  Vector3D(-23.6f,-5.38f+sqr3/2+.5f,-17.8f-sqr3/2-.5f));
//      allObj.setNormal(PLANE, 17, Vector3D(0.0f, 0.0f, 1.0f));
//  allObj.flipBase(PLANE, 17);*/
//  plane.setPosition(Vector3D(-23.6f,-5.38f+sqr3/2+.5f,-17.8f-sqr3/2-.5f));
//  plane.orient(Z);
//  allObj.addPlane(plane);

//  /*allObj.setPos(PLANE,18,  Vector3D(-25.6f-sqr3/2-.25f, -4.38f+3*sqr3/4, -15.8f));
//  allObj.setNormal(PLANE, 18, Vector3D(-sqr3, 1.0f, 0.0f));*/
//  plane.setPosition(Vector3D(-25.6f-sqr3/2-.25f, -4.38f+3*sqr3/4, -15.8f));
//  plane.orient(Vector3D(-sqr3, 1.0f, 0.0f));
//  allObj.addPlane(plane);

//  /*allObj.setPos(PLANE,19,  Vector3D(-23.6f, -4.38f+3*sqr3/4, -17.8f-sqr3/2-.25f));
//      allObj.setNormal(PLANE, 19, Vector3D(0.0f, -1.0f, sqr3));
//  allObj.flipBase(PLANE, 19);*/
//  plane.setPosition(Vector3D(-23.6f, -4.38f+3*sqr3/4, -17.8f-sqr3/2-.25f));
//  plane.orient(Vector3D(0.0f, -1.0f, sqr3));
//  plane.flipBase();
//  allObj.addPlane(plane);

//  /*allObj.setPos(PLANE,20,  Vector3D(-25.6f-sqr3/4, -4.38f+sqr3+.25f, -15.8f));
//  allObj.setNormal(PLANE, 20, Vector3D(1.0f, -sqr3, 0.0f));*/
//  plane.setPosition(Vector3D(-25.6f-sqr3/4, -4.38f+sqr3+.25f, -15.8f));
//  plane.orient(Vector3D(1.0f, -sqr3, 0.0f));
//  plane.flipBase();
//  allObj.addPlane(plane);

//  /*allObj.setPos(PLANE,21,  Vector3D(-23.6f, -4.38f+sqr3+.25f, -17.8f-sqr3/4));
//      allObj.setNormal(PLANE, 21, Vector3D(0.0f, -sqr3, 1.0f));
//  allObj.flipBase(PLANE, 21);*/
//  plane.setPosition(Vector3D(-23.6f, -4.38f+sqr3+.25f, -17.8f-sqr3/4));
//  plane.orient(Vector3D(0.0f, -sqr3, 1.0f));
//  plane.flipBase();
//  allObj.addPlane(plane);

//  /*allObj.addPlanes(1,4,10,0,0,  Vector3D(-23.6f,-6.86f,-8.9f));
//      allObj.setNormal(PLANE, 22, Vector3D(0,1,.2));
//  allObj.flipBase(PLANE, 22);*/
//  //        allObj.setTexture(PLANE, 22, wall1txr);
//  plane = object_plane(10,4, Vector3D(-23.6f,-6.86f,-8.9f), Vector3D(0,1,.2), basis);
//  allObj.addPlane(plane);

//  //			allObj.addPlanes(1,8,8,0,0,  Vector3D(-23.6f,-7.84f, 0.0f));
//  //        allObj.setTexture(PLANE, 23, tile1txr);
//  plane = object_plane(8,8,Vector3D(-23.6f,-7.84f, 0.0f), majAxis, basis);
//  allObj.addPlane(plane);

//  /*allObj.addPlanes(3,1,8,2,0,0,  Vector3D(-27.6f,-6.84f,0.0f));
//  allObj.setNormal(PLANE, 24, Vector3D(1,0,0));*/
//  plane = object_plane(8,2,Vector3D(-27.6f,-6.84f,0.0f), X, basis);
//  plane.flipBase();
//  allObj.addPlane(plane);

//  /*allObj.setPos(PLANE, 25,  Vector3D(-19.6f,-6.84f,0.0f));
//  allObj.setNormal(PLANE, 25, Vector3D(-1,0,0));*/
//  plane.setPosition(Vector3D(-19.6f,-6.84f,0.0f));
//  plane.orient(-X);
//  allObj.addPlane(plane);

//  /*allObj.setPos(PLANE, 26,  Vector3D(-23.6f,-6.84f,4.0f));
//      allObj.setNormal(PLANE, 26, Vector3D(0,0,-1));
//  allObj.flipBase(PLANE, 26);*/
//  plane.setPosition(Vector3D(-23.6f,-6.84f,4.0f));
//  plane.orient(-Z);
//  allObj.addPlane(plane);

//  /*allObj.addPlanes(2,1,2,2,0,0,  Vector3D(0,0,0));
//      allObj.setPos(PLANE, 27,  Vector3D(-20.6f,-6.84f,-4));
//  allObj.setNormal(PLANE, 27, Vector3D(0,0,1));*/
//  plane = object_plane(2,2,Vector3D(-20.6f,-6.84f,-4), Z, basis);
//  allObj.addPlane(plane);

//  /*allObj.setPos(PLANE, 28,  Vector3D(-26.6f,-6.84f,-4));
//      allObj.setNormal(PLANE, 28, Vector3D(0,0,1));
//  allObj.flipBase(PLANE, 28);*/
//  plane.setPosition(Vector3D(-26.6f,-6.84f,-4));
//  plane.orient(Z);
//  allObj.addPlane(plane);

//  //        floors = &allObj.planes->objs[0];

  level->cameras.addPoint(Vector3D(0, 8.6, 8), Vector3D(0, 0, 0), level->majAxis, 5.0f);
      //level1.allObj.cameras->addPoint(Vector3D(xCam, 3.60f, -14.6f), Vector3D(-11.8f, -3.0f, -13.8f), 5.0f);
  level->cameras.addPoint(Vector3D(0, 3.60f, 0), Vector3D(0, 3.0f, -13.8f), level->majAxis, 10.0f);
  level->cameras.camview = FOLLOW;
//  majAxis = Y;

//    status = true;
  return level;
}
