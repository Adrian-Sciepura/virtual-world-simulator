#ifndef PINE_HOGWEED_H
#define PINE_HOGWEED_H

#include "Plant.h"

class PineHogweed : public Plant
{
public:
	PineHogweed(World* world, Point position);
	PineHogweed(World* world, Point position, int lifeSpan, int strength);

	virtual void update(std::fstream& logFile);
	virtual bool collision(std::fstream& logFile, Entity& entity);
};

#endif