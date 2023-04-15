#ifndef WOLF_H
#define WOLF_H

#include "Animal.h"

class Wolf : public Animal
{
public:
	Wolf(World* world, Point position);
	Wolf(World* world, Point position, int lifeSpan, int strength);

	virtual bool collision(std::fstream& logFile, Entity& entity);
};

#endif