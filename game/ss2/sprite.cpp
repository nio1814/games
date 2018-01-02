#include "sprite.h"

Sprite::Sprite(Character character)
{
	load(character);
}

void Sprite::load(Character character)
{
	m_actions.clear();
	std::vector<std::string> filenames;

	switch(character)
	{
		case Goomba:
			{
				filenames = {"img/characters/goomba/gommba1.tga"};
				m_actions.insert(std::pair<Action,Animation>(Stand, Animation(filenames)));

				filenames = {
					"img/characters/goomba/gommba1.tga",
					"img/characters/goomba/gommba2.tga"
				};
				m_actions.insert(std::pair<Action,Animation>(Run, Animation(filenames)));

			}
			break;
	}
}


Animation::Animation(std::vector<std::string> filenames)
{
	for (std::string filename : filenames)
		m_images.push_back(TGA(filename));
}
