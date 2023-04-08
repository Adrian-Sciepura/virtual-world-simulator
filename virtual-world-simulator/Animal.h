#ifndef ANIMAL_H
#define ANIMAL_H

#include "Entity.h"

class Animal : public Entity
{
public:
	Animal(Point position, char symbol, int strength, int priority);
	~Animal();

	virtual void update() = 0;
};

#endif