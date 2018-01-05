#ifndef SPRITE_H
#define SPRITE_H

#include "characters.h"
#include "frame.h"

#include <map>
#include <memory>
#include <vector>

class TextureLoader;

class Animation
{
public:
	Animation(){};
	Animation(std::vector<std::shared_ptr<Frame> > frames);

	unsigned int textureIndex();
	std::shared_ptr<Frame> frame();

private:
	std::vector<std::shared_ptr<Frame> > m_frames;
	int m_index=-1;
};

class Sprite
{
public:
	Sprite(std::shared_ptr<TextureLoader> textureLoader, Character character);
	Sprite(const Sprite& sprite);

	void load(Character character);
	unsigned int textureIndex();
//	std::shared_ptr<Action> action();
	void setActionPointer(std::shared_ptr<Action> action);
	float heightWidthScale();

	Sprite& operator =(const Sprite& other);
private:
	void addAction(Action action, std::vector<std::string> filenames);
	std::shared_ptr<const Frame> frame();

	std::map<Action, Animation> m_actions;
	std::shared_ptr<TextureLoader> m_textureLoader;
	std::shared_ptr<Action> m_action;
};

#endif // SPRITE_H
