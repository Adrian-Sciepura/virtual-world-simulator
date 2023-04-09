#ifndef SHEEP_H
#define SHEEP_H

#include "Animal.h"

class Sheep : public Animal
{
public:
	Sheep(World* world, Point position);

	virtual bool collision(Entity& entity);
};

#endif