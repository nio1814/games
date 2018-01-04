#ifndef SPRITE_H
#define SPRITE_H

#include "tga.h"
#include "characters.h"

#include <map>

struct Animation
{
	Animation(){};
	Animation(std::vector<std::string> filenames);

	std::vector<TGA> m_images;
};

class Sprite
{
	enum Action{Stand, Run};
public:
	Sprite(Character character);

	void load(Character character);
	unsigned int textureIndex();
private:
	std::map<Action, Animation> m_actions;
};

#endif // SPRITE_H
