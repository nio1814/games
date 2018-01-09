#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <memory>
#include <map>

#include "characters.h"

class Object;
class TextureLoader;
class Sprite;
class Keys;

class Level
{
public:
	Level();
	~Level();

	void setKeys(std::shared_ptr<Keys> keys);

	void updateKeys();
	void draw();
	void update(float timeElapsed);
	void updateEnemy(std::shared_ptr<Object> enemy);
	void load();
private:
	void setPlayer(std::shared_ptr<Object> player);
	void addEnemy(std::shared_ptr<Object> enemy);

	std::vector<std::shared_ptr<Object> > m_objects;
	std::shared_ptr<Object> m_player;
	std::vector<std::shared_ptr<Object> > m_enemies;
	std::shared_ptr<Keys> m_keys;
	std::shared_ptr<TextureLoader> m_textureLoader;
	std::map<Character,std::unique_ptr<Sprite> > m_sprites;
};

#endif // LEVEL_H
