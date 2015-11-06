#ifndef SIMULATION_H
#define SIMULATION_H

#include "object.h"

class Simulation
{
public:
    Simulation();
	Simulation(int num);
    ~Simulation();
	
    void run(GLfloat dt);
    void draw();
	Vector3D setCam(Object* obj);
	void setView(CameraView view);
	
	object_holder allObj;
    CameraPoints* cameras;

	int simNum;
	bool started, paused;
	GLfloat startTime, currentTime, timer;
};

#endif // SIMULATION_H
