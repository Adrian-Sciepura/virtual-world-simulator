#ifndef NIGHTSHADE_H
#define NIGHTSHADE_H

#include "Plant.h"

class Nightshade : public Plant
{
public:
	Nightshade(World* world, Point position);

	virtual void update(std::fstream& logFile);
	virtual bool collision(std::fstream& logFile, Entity& entity);
};

#endif