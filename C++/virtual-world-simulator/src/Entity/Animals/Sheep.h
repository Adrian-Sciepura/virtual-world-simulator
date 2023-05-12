#ifndef SHEEP_H
#define SHEEP_H

#include "Animal.h"

class Sheep : public Animal
{
public:
	Sheep(World* world, Point position);
	Sheep(World* world, Point position, int lifeSpan, int strength);

	virtual bool collision(std::fstream& logFile, Entity& entity);
};

#endif