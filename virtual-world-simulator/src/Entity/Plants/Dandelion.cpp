#include "Dandelion.h"

Dandelion::Dandelion(World* world, Point position) :
	Plant { world, position, 'D', 0, SpreadChance::LOW }
{
}

void Dandelion::update()
{
	for(int i = 0; i < 3; i++)
	{
		int random = Utility::random(1, 25);
		if (random <= this->spreadChance)
			this->spread<Dandelion>();
	}

	Entity::update();
}

bool Dandelion::collision(Entity& entity)
{
	this->isAlive = false;
    return true;
}
