#ifndef ANIMAL_H
#define ANIMAL_H

#include "Entity.h"

class Animal : public Entity
{
public:
	Animal(World* world, Point position, char symbol, int strength, int priority);
	~Animal();

	void move(const Point& newPosition);
	virtual void update() = 0;
	virtual void collision() = 0;
};

#endif