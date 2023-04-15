#ifndef FOX_H
#define FOX_H

#include "Animal.h"

class Fox : public Animal
{
public:
	Fox(World* world, Point position);
	Fox(World* world, Point position, int lifeSpan, int strength);

	virtual void update(std::fstream& logFile);
	virtual bool collision(std::fstream& logFile, Entity& entity);
};

#endif