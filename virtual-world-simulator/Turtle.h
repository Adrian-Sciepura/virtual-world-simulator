#ifndef TURTLE_H
#define TURTLE_H

#include "Animal.h"

class Turtle : public Animal
{
public:
	Turtle(World* world, Point position);
	
	virtual void update();
	virtual bool collision(Entity& entity);
};

#endif