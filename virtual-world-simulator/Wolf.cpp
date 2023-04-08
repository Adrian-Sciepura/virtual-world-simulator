#include "Wolf.h"

Wolf::Wolf(World* world, Point position) :
	Animal{ world, position, 'W', 9, 5 }
{
}

Wolf::~Wolf()
{
}

void Wolf::update()
{
	Animal::update();
}

bool Wolf::collision(Entity& entity)
{
	return Animal::collision(entity);
}
