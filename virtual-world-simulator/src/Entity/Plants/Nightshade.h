#ifndef NIGHTSHADE_H
#define NIGHTSHADE_H

#include "Plant.h"

class Nightshade : public Plant
{
public:
	Nightshade(World* world, Point position);

	virtual void update();
	virtual bool collision(Entity& entity);
};

#endif