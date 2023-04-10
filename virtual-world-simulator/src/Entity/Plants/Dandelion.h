#ifndef DANDELION_H
#define DANDELION_H

#include "Plant.h"

class Dandelion : public Plant
{
public:
	Dandelion(World* world, Point position);

	virtual void update();
	virtual bool collision(Entity& entity);
};

#endif