#ifndef GRASS_H
#define GRASS_H

#include "Plant.h"

class Grass : public Plant
{
public:
	Grass(World* world, Point position);
	~Grass();

	void update();
	void collision();
};

#endif