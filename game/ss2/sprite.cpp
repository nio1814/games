#include "sprite.h"

#include "textureloader.h"

Sprite::Sprite(std::shared_ptr<TextureLoader> textureLoader, Character character) :
	m_textureLoader(textureLoader)
{
	load(character);
}

Sprite::Sprite(const Sprite& sprite)
{
	*this = sprite;
}

void Sprite::load(Character character)
{
	m_actions.clear();
	std::vector<std::string> filenames;

	switch(character)
	{
		case Goomba:
			{
//				filenames = {"img/characters/goomba/gommba1.tga"};
//				std::vector<unsigned int> textureIndices = m_textureLoader->load(filenames);
//				m_actions.insert(std::pair<Action,Animation>(Stand, Animation(textureIndices)));
				addAction(Stand, {"img/characters/goomba/goomba1.tga"});

				addAction(Run, {
							  "img/characters/goomba/goomba1.tga",
							  "img/characters/goomba/goomba2.tga"
						  }, .3);
//				textureIndices = m_textureLoader->load(filenames);
//				m_actions.insert(std::pair<Action,Animation>(Run, Animation(filenames)));
			}
			break;
		case MMX:
			addAction(Stand, {"img/characters/mmx/mmx.tga"});
			addAction(Jump, {
						  "img/characters/mmx/mmxJump1.tga",
						  "img/characters/mmx/mmxJump2.tga",
						  "img/characters/mmx/mmxJump3.tga",
						  "img/characters/mmx/mmxJump4.tga",
						  "img/characters/mmx/mmxJump5.tga"
					  }, .8);
			break;
	}
}

unsigned int Sprite::textureIndex()
{
	std::shared_ptr<Animation> animation = currentAnimation();
	if(animation)
		return animation->textureIndex();
	else
		return -1;
}

void Sprite::update(float timeElapsed)
{
	std::shared_ptr<Animation> animation = currentAnimation();
	if(animation)
		animation->update(timeElapsed);
}

bool Sprite::hasAction(Action action)
{
	return m_actions.count(action);
}

void Sprite::setAction(Action action)
{
	if(hasAction(action))
	{
		if(m_action!=action)
			m_actions[action]->start();
		m_action = action;
	}
}

float Sprite::heightWidthScale()
{
	std::shared_ptr<const Frame> currentFrame = frame();

	return currentFrame->height*1.0/currentFrame->width;
}

Sprite &Sprite::operator =(const Sprite &other)
{
	m_actions = other.m_actions;
	m_textureLoader = other.m_textureLoader;
	m_action = other.m_action;

	return *this;
}

//std::shared_ptr<Sprite::Action> Sprite::action()
//{
//	return m_action;
//}

void Sprite::addAction(Action action, std::vector<std::string> filenames, float duration)
{
	std::vector<std::shared_ptr<Frame> > textures = m_textureLoader->load(filenames);

	if(m_actions.empty())
		m_action = action;
	std::shared_ptr<Animation> animation = std::make_shared<Animation>(textures, duration);
	m_actions.insert(std::pair<Action,std::shared_ptr<Animation>>(action, animation));
}

std::shared_ptr<const Frame> Sprite::frame()
{
	std::shared_ptr<Frame> frame;
	std::shared_ptr<Animation> animation = currentAnimation();

	if(animation)
		frame = animation->frame();

	return frame;
}

std::shared_ptr<Animation> Sprite::currentAnimation()
{
	std::shared_ptr<Animation> animation;
	if(hasAction(m_action))
		animation = m_actions[m_action];

	return animation;
}


Animation::Animation(std::vector<std::shared_ptr<Frame> > frames, float duration, int loopEnd, int loopStart) :
	m_frames(frames),
	m_loopIndexStart(loopStart),
	m_loopIndexEnd(loopEnd)
{
	float frameDuration = duration/frames.size();
	for(std::shared_ptr<Frame> frame : m_frames)
		frame->duration = frameDuration;

//	if(m_index<0)
	//		m_index = 0;
}

int Animation::index()
{
	float frameEndTimePrevious = 0;

	float loopTimeStart = 0;
	float loopTimeEnd = 0;

	for(size_t n=0; n<m_frames.size(); n++)
	{
		std::shared_ptr<Frame> frame = m_frames[n];
		float frameEndTimeNext = frameEndTimePrevious + frame->duration;
		if(n==(size_t)m_loopIndexStart)
			loopTimeStart = frameEndTimePrevious;
		else if(n==(size_t)m_loopIndexEnd)
			loopTimeEnd = frameEndTimeNext;

		if(m_time>loopTimeEnd)
			m_time -= loopTimeStart;
		if(m_time<frameEndTimeNext)
			return n;
	}

	return m_frames.size()-1;
}

unsigned int Animation::textureIndex()
{
	int i = index();

	if(i>=0)
		i = m_frames[i]->textureIndex;

	return i;
}

std::shared_ptr<Frame> Animation::frame()
{
	std::shared_ptr<Frame> currentFrame;

	int i = index();
	if(i>=0)
		currentFrame = m_frames[i];

	return currentFrame;
}

void Animation::update(float timeElapsed)
{
	m_time += timeElapsed;
}

void Animation::start()
{
	m_time = 0;
}
