#include "Dandelion.h"

Dandelion::Dandelion(World* world, Point position) :
	Plant { world, position, 'D', 0, SpreadChance::LOW }
{
}

void Dandelion::update()
{
	for(int i = 0; i < 3; i++)
		this->spread<Dandelion>();

	Entity::update();
}