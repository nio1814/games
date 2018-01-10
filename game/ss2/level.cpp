#include "level.h"

#include "object.h"
#include "textureloader.h"
#include "sprite.h"
#include "keys.h"
#include "motion.h"
#include "camera.h"
#include "vector3d.h"

#include <map>
#include "qtgl.h"

#include <stdio.h>

Level::Level() :
	m_camera(std::make_unique<Camera>(Vector3D(0,0,5)))
{
	m_textureLoader = std::make_shared<TextureLoader>();

	m_keys = std::make_shared<Keys>();
}

Level::~Level()
{

}

void Level::setKeys(std::shared_ptr<Keys> keys)
{
	m_keys = keys;
	m_keys->setKeyIndex(Keys::Left, Qt::Key_Left);
	m_keys->setKeyIndex(Keys::Right, Qt::Key_Right);
	m_keys->setKeyIndex(Keys::Jump, Qt::Key_Control);
}

void Level::updateKeys()
{
//	if (m_keys->count(Qt::Key_Left) && m_keys->at(Qt::Key_Left))
	if (m_keys->keyPressed(Keys::Left))
		m_player->moveLeft();
	else  if (m_keys->keyPressed(Keys::Right))
		m_player->moveRight();
	else
		m_player->noLeftRightMove();

	if(m_keys->keyPressed(Keys::Jump))
		m_player->jump();
}

void Level::draw()
{
	glLookAt(m_camera->position().vector(), m_camera->look().vector(), m_camera->up().vector());

	for (auto i=m_objects.begin(); i!=m_objects.end(); i++)
	{
		(*i)->draw();
	}
}

void Level::update(float timeElapsed)
{
	updateKeys();
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
	for(std::shared_ptr<Object> enemy : m_enemies)
		updateEnemy(enemy);

	for (auto i=m_objects.begin(); i!=m_objects.end(); i++)
	{
		(*i)->update(timeElapsed);
	}
	//	fprintf(stderr, "%f %f %f", m_player->position()[0], m_player->position()[1], m_player->position()[2]);
	*m_lookPosition = m_player->position();
	m_lookPosition->setZ(5);
	m_camera->update(timeElapsed);
}

void Level::updateEnemy(std::shared_ptr<Object> enemy)
{
	if(enemy->position().x()<m_player->position().x())
		enemy->moveRight();
	else
		enemy->moveLeft();
}

void Level::load()
{
	for(Character character : {Goomba, MMX, Mario1Little})
		m_sprites[character] = std::make_unique<Sprite>(m_textureLoader, character);

	setPlayer(std::make_shared<Object>(1,1.5,0,0));
	m_player->setHasGravity(true);
//	m_player->setSprite(*m_sprites[Goomba]);
	m_player->setSprite(*m_sprites[Mario1Little]);

	std::shared_ptr<Object> object;
	object = std::make_shared<Object>(1,1, 3, 1);
	object->setHasGravity(true);
	object->setSprite(*m_sprites[Goomba]);
	addEnemy(object);
	m_objects.push_back(std::make_shared<Object>(10,1,0,-5));
	object = std::make_shared<Object>(5,1,10,-5);
	Motion motion;
	motion.addCycle(3, 2.5, Vector2D(1,0));
	object->setMotion(motion);
	m_objects.push_back(object);

	m_camera->setMode(Camera::Follow);
	m_lookPosition = std::make_shared<Vector3D>(m_player->position());
	m_camera->setFollowPosition(m_lookPosition);
	m_camera->setLookToPosition(Vector3D(0,0,5));
}

void Level::setPlayer(std::shared_ptr<Object> player)
{
	m_player = player;
	if(std::find(m_objects.begin(), m_objects.end(), m_player) == m_objects.end())
		m_objects.push_back(m_player);
}

void Level::addEnemy(std::shared_ptr<Object> enemy)
{
	m_enemies.push_back(enemy);
	m_objects.push_back(enemy);
}
