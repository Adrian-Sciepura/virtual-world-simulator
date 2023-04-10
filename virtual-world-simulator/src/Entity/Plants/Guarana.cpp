#include "Guarana.h"

Guarana::Guarana(World* world, Point position) :
    Plant { world, position, 'U', 0, SpreadChance::MEDIUM }
{
}

void Guarana::update()
{
	this->spread<Guarana>();
	Entity::update();
}

bool Guarana::collision(Entity& entity)
{
	entity.setStrength(entity.getStrength() + 3);
    return Plant::collision(entity);
}
