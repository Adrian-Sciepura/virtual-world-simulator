#ifndef PLANT_H
#define PLANT_H

#include "Entity.h"

class Plant : public Entity
{
public:
	Plant(World* world, Point position, char symbol, int strength);
	~Plant();

	virtual void update() = 0;
	virtual bool collision(Entity& entity) = 0;
};

#endif