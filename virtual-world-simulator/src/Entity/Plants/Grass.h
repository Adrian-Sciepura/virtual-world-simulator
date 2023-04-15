#ifndef GRASS_H
#define GRASS_H

#include "Plant.h"

class Grass : public Plant
{
public:
	Grass(World* world, Point position);
	Grass(World* world, Point position, int lifeSpan, int strength);

	virtual void update(std::fstream& logFile);
};

#endif