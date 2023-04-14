#ifndef WOLF_H
#define WOLF_H

#include "Animal.h"

class Wolf : public Animal
{
public:
	Wolf(World* world, Point position);

	virtual bool collision(std::fstream& logFile, Entity& entity);
};

#endif