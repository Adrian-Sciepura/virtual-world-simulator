#include "Guarana.h"

Guarana::Guarana(World* world, Point position) :
    Plant { world, position, 'G', 0, SpreadChance::MEDIUM }
{
}

void Guarana::update()
{
    int random = Utility::random(1, 25);
	if (random <= this->spreadChance)
		this->spread<Guarana>();

	Entity::update();
}

bool Guarana::collision(Entity& entity)
{
	this->isAlive = false;
	entity.setStrength(entity.getStrength() + 3);
    return true;
}
