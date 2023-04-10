#include "Nightshade.h"

Nightshade::Nightshade(World* world, Point position) :
    Plant{ world, position, 'N', 99, SpreadChance::LOW }
{
}

void Nightshade::update()
{
    int random = Utility::random(1, 25);
	if (random <= this->spreadChance)
		this->spread<Nightshade>();

	Entity::update();
}

bool Nightshade::collision(Entity& entity)
{
	this->isAlive = false;
	entity.kill();
    return true;
}
