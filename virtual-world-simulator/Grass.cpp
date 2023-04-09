#include "Grass.h"

Grass::Grass(World* world, Point position) :
	Plant { world, position, 'G', 0, SpreadChance::HIGH }
{

}

void Grass::update()
{
	int random = Utility::random(0, 10);
	if (random <= this->spreadChance)
		this->spread<Grass>();

	Entity::update();
}

bool Grass::collision(Entity& entity)
{
	this->isAlive = false;
	return true;
}
