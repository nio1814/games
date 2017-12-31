#include "level.h"

#include "object.h"

#include <map>
#include <qnamespace.h>

Level::Level()
{
	m_objects.push_back(std::make_shared<Object>(30,70,0,0));

	m_player = m_objects[0];
}

Level::~Level()
{

}

void Level::setKeys(std::shared_ptr<std::map<int,bool> > keys)
{

}

void Level::updateKeys()
{
	if (Qt::Key_Left) {
		m_player->setVelocity(1.0f, 0.0f);
	}
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
		(*i)->update(timeElapsed);
	}
}
