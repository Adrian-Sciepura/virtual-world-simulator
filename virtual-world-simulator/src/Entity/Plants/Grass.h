#ifndef GRASS_H
#define GRASS_H

#include "Plant.h"

class Grass : public Plant
{
public:
	Grass(World* world, Point position);

	void update();
	bool collision(Entity& entity);
};

#endif