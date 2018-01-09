#include "sprite.h"

#include "textureloader.h"

//#include <limits>
#include <iostream>

Sprite::Sprite(std::shared_ptr<TextureLoader> textureLoader, Character character) :
	m_textureLoader(textureLoader),
	m_character(character)
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
						  }, .3, 1, 0);
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
	case Mario1Little:
		addAction(Stand, {"img/characters/mario1little/mario.tga"});
		addAction(Run, {
					  "img/characters/mario1little/marioRun1.tga",
					  "img/characters/mario1little/marioRun2.tga"
				  }, .2, 1);
		addAction(Jump, {"img/characters/mario1little/marioJump.tga"});
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

std::vector<float> Sprite::sizeScale()
{
	std::shared_ptr<const Frame> currentFrame = frame();

	std::vector<float> scale(2);
	scale[0] = currentFrame->width*1.0f/m_referenceFrame->width;
	scale[1] = currentFrame->height*1.0f/m_referenceFrame->height;

	return scale;
}

Character Sprite::character()
{
	return m_character;
}

//Sprite &Sprite::operator =(const Sprite &other)
//{
//	m_actions = other.m_actions;
//	m_textureLoader = other.m_textureLoader;
//	m_action = other.m_action;

//	return *this;
//}

//std::shared_ptr<Sprite::Action> Sprite::action()
//{
//	return m_action;
//}

void Sprite::addAction(Action action, std::vector<std::string> filenames, float duration, int loopEnd, int loopStart)
{
	std::vector<std::shared_ptr<Frame> > textures = m_textureLoader->load(filenames);

	std::shared_ptr<Animation> animation = std::make_shared<Animation>(textures, duration, loopEnd, loopStart);
	if(m_actions.empty())
	{
		m_action = action;
		m_referenceFrame = animation->frame(0);
	}
	m_actions.insert(std::pair<Action,std::shared_ptr<Animation>>(action, animation));
}

std::shared_ptr<const Frame> Sprite::frame()
{
	std::shared_ptr<Frame> frame;
	std::shared_ptr<Animation> animation = currentAnimation();

	if(animation)
		frame = animation->currentFrame();

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

	float t=0;
	for(size_t n=0; n<m_frames.size(); n++)
	{
		if(n==(size_t)m_loopIndexStart)
			loopTimeStart = t;
		t += m_frames[n]->duration;
		if(n==(size_t)m_loopIndexEnd)
			loopTimeEnd = t;
	}
	if(m_time>loopTimeEnd)
		m_time = loopTimeStart + m_time-loopTimeEnd;
//	std::cout << m_time << std::endl;

	for(size_t n=0; n<m_frames.size(); n++)
	{
		std::shared_ptr<Frame> frame = m_frames[n];
		float frameEndTimeNext = frameEndTimePrevious + frame->duration;

		if(m_time<frameEndTimeNext)
		{
//			std::cout << n << std::endl;
			return n;
		}

		frameEndTimePrevious = frameEndTimeNext;
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

std::shared_ptr<Frame> Animation::currentFrame()
{
	std::shared_ptr<Frame> currentFrame;

	int i = index();
	if(i>=0)
		currentFrame = m_frames[i];

	return currentFrame;
}

std::shared_ptr<Frame> Animation::frame(int n)
{
	return m_frames[n];
}

void Animation::update(float timeElapsed)
{
	m_time += timeElapsed;
}

void Animation::start()
{
	m_time = 0;
}
