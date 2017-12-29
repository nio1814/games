#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <memory>
#include <map>

class Object;

class Level
{
public:
	Level();
	~Level();

	void setKeys(std::shared_ptr<std::map<int,bool> > keys);

	void updateKeys();
	void draw();
private:
	std::vector<std::shared_ptr<Object> > m_objects;
	std::shared_ptr<Object> m_player;
	std::shared_ptr<std::map<int,bool> > m_keys;
};

#endif // LEVEL_H