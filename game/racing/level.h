#ifndef LEVEL_H
#define LEVEL_H

class MeshObject;

class Level
{
public:
	Level();
	~Level();
		void addPlayer(const char* modelfile);
		void initObject(MeshObject* obj);
		MeshObject* player;
};

#endif // LEVEL_H
