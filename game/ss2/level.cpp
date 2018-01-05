#include "level.h"

#include "object.h"
#include "textureloader.h"
#include "sprite.h"

#include <map>
#include <qnamespace.h>

#include <stdio.h>

Level::Level()
{
	m_textureLoader = std::make_shared<TextureLoader>();
}

Level::~Level()
{

}

void Level::setKeys(std::shared_ptr<std::map<int,bool> > keys)
{
	m_keys = keys;
}

void Level::updateKeys()
{
//	if (m_keys->count(Qt::Key_Left) && m_keys->at(Qt::Key_Left))
	if ((*m_keys)[Qt::Key_Left])
	{
		m_player->setVelocity(-1.0f, 0.0f);
//		m_player->setDirection(DirectionLeft);
	}
	else  if ((*m_keys)[Qt::Key_Right])
	{
		m_player->setVelocity(1.0f, 0.0f);
//		m_player->setDirection(DirectionRight);
	}
	else
		m_player->setVelocity(0.0f, 0.0f);

	if ((*m_keys)[Qt::Key_Control] && m_player->touching(Object::BottomSide))
		m_player->setVelocity(0.0f, 10.0f);

}

void Level::draw()
{
	for (auto i=m_objects.begin(); i!=m_objects.end(); i++)
	{
		(*i)->draw();
	}
}

void Level::update(float timeElapsed)
{
	for (auto i=m_objects.begin(); i!=m_objects.end(); i++)
	{
		(*i)->reset();
	}
	for(size_t m=0; m<m_objects.size(); m++)
	{
		for(size_t n=m+1; n<m_objects.size(); n++)
		{
			m_objects[m]->checkTouch(m_objects[n]);
		}
	}
	for (auto i=m_objects.begin(); i!=m_objects.end(); i++)
	{
		(*i)->update(timeElapsed);
	}
	//	fprintf(stderr, "%f %f %f", m_player->position()[0], m_player->position()[1], m_player->position()[2]);
}

void Level::load()
{
	for(Character character : {Goomba, MMX})
		m_sprites[character] = std::make_unique<Sprite>(m_textureLoader, character);

	m_player = std::make_shared<Object>(1,1.5,0,0);
	m_player->setHasGravity(true);
	m_player->setSprite(*m_sprites[MMX]);

	m_objects.push_back(m_player);
	m_objects.push_back(std::make_shared<Object>(10,1,0,-5));
}
