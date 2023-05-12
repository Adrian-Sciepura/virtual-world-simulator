#ifndef NIGHTSHADE_H
#define NIGHTSHADE_H

#include "Plant.h"

class Nightshade : public Plant
{
public:
	Nightshade(World* world, Point position);
	Nightshade(World* world, Point position, int lifeSpan, int strength);

	virtual void update(std::fstream& logFile);
	virtual bool collision(std::fstream& logFile, Entity& entity);
};

#endif