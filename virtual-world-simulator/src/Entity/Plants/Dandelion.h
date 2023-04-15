#ifndef DANDELION_H
#define DANDELION_H

#include "Plant.h"

class Dandelion : public Plant
{
public:
	Dandelion(World* world, Point position);
	Dandelion(World* world, Point position, int lifeSpan, int strength);

	virtual void update(std::fstream& logFile);
};

#endif