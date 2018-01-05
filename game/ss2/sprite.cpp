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
						  });
//				textureIndices = m_textureLoader->load(filenames);
//				m_actions.insert(std::pair<Action,Animation>(Run, Animation(filenames)));
			}
			break;
		case MMX:
			addAction(Stand, {"img/characters/mmx/mmx.tga"});
			break;
	}
}

unsigned int Sprite::textureIndex()
{

	if(m_action && m_actions.count(*m_action))
		return m_actions.at(*m_action).textureIndex();
	else
		return -1;
}

void Sprite::setActionPointer(std::shared_ptr<Action> action)
{
	m_action = action;
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
//	*m_action = *other.m_action;

	return *this;
}

//std::shared_ptr<Sprite::Action> Sprite::action()
//{
//	return m_action;
//}

void Sprite::addAction(Action action, std::vector<std::string> filenames)
{
	std::vector<std::shared_ptr<Frame> > textures = m_textureLoader->load(filenames);

	m_actions.insert(std::pair<Action,Animation>(action, Animation(textures)));
}

std::shared_ptr<const Frame> Sprite::frame()
{
	std::shared_ptr<Frame> frame;

	if(m_action && m_actions.count(*m_action))
		frame = m_actions[*m_action].frame();

	return frame;
}


Animation::Animation(std::vector<std::shared_ptr<Frame> > frames) :
	m_frames(frames)
{
	if(m_index<0)
		m_index = 0;
}

unsigned int Animation::textureIndex()
{
	return m_frames[m_index]->textureIndex;
}

std::shared_ptr<Frame> Animation::frame()
{
	std::shared_ptr<Frame> currentFrame;

	if(m_index>=0)
		currentFrame = m_frames[m_index];

	return currentFrame;
}
