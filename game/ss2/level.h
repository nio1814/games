#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <memory>
#include <map>

#include "characters.h"

class Object;
class TextureLoader;
class Sprite;

class Level
{
public:
	Level();
	~Level();

	void setKeys(std::shared_ptr<std::map<int,bool> > keys);

	void updateKeys();
	void draw();
	void update(float timeElapsed);
	void load();
private:
	std::vector<std::shared_ptr<Object> > m_objects;
	std::shared_ptr<Object> m_player;
	std::shared_ptr<std::map<int,bool> > m_keys;
	std::shared_ptr<TextureLoader> m_textureLoader;
	std::map<Character,std::unique_ptr<Sprite> > m_sprites;
};

#endif // LEVEL_H
