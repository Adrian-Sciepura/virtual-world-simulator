#ifndef ANTELOPE_H
#define ANTELOPE_H

#include "Animal.h"

class Antelope : public Animal
{
protected:
	bool runAway();

public:
	Antelope(World* world, Point position);
	
	virtual void update();
	virtual bool collision(Entity& entity);
};

#endif