#ifndef SIMULATION_H
#define SIMULATION_H

#include "object/objects.h"
#include "camera.h"

class Simulation
{
public:
    Simulation();
//	Simulation(int num);
    ~Simulation();
	
    void run(GLfloat dt);
    void draw();
  Vector3D setCam();
	void setView(CameraView view);
	
  Objects allObj;
    CameraPoints* cameras;

	int simNum;
	bool started, paused;
	GLfloat startTime, currentTime, timer;
  Object::Pointer cameraFollowObject;
private:

};

#endif // SIMULATION_H
