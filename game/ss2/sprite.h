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
	Animation(std::vector<std::shared_ptr<Frame> > frames, float duration, int loopEnd=-1, int loopStart=-1);

	int index();
	unsigned int textureIndex();
	std::shared_ptr<Frame> currentFrame();
	std::shared_ptr<Frame> frame(int n);
	void update(float timeElapsed);
	void start();

private:
	float duration();

	std::vector<std::shared_ptr<Frame> > m_frames;
//	int m_index = -1;
	float m_time = -1;
	int m_loopIndexStart = -1;
	int m_loopIndexEnd = -1;
};

class Sprite
{
public:
	Sprite(std::shared_ptr<TextureLoader> textureLoader, Character character);
	Sprite(const Sprite& sprite);

	void load(Character character);
	unsigned int textureIndex();
	void update(float timeElapsed);
//	std::shared_ptr<Action> action();
	bool hasAction(Action action);
	void setAction(Action action);
	float heightWidthScale();
	std::vector<float> sizeScale();

//	Sprite& operator =(const Sprite& other);
private:
	void addAction(Action action, std::vector<std::string> filenames, float duration=0, int loopEnd=-1, int loopStart=-1);
	std::shared_ptr<const Frame> frame();
	std::shared_ptr<Animation> currentAnimation();

	std::map<Action, std::shared_ptr<Animation> > m_actions;
	std::shared_ptr<TextureLoader> m_textureLoader;
	Action m_action;
	std::shared_ptr<const Frame> m_referenceFrame;
};

#endif // SPRITE_H
