#include "Grass.h"

Grass::Grass(World* world, Point position) :
	Plant { world, position, 'G', 0 }
{

}

Grass::~Grass()
{
}

void Grass::update()
{
	Plant::update();
}

bool Grass::collision(Entity& entity)
{
	this->isAlive = false;
	return true;
}
