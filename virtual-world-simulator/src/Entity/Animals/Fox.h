#ifndef FOX_H
#define FOX_H

#include "Animal.h"

class Fox : public Animal
{
public:
	Fox(World* world, Point position);

	virtual void update();
	virtual bool collision(Entity& entity);
};

#endif