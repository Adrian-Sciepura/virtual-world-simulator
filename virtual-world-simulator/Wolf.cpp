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
	Wolf* wolf = dynamic_cast<Wolf*>(&entity);
	if (wolf != nullptr)
	{
		this->breed<Wolf>(*wolf);
		return false;
	}

	return Animal::collision(entity);
}
