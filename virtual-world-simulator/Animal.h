#ifndef ANIMAL_H
#define ANIMAL_H

#include "Entity.h"

class Animal : public Entity
{
protected:
	int priority;
	int lifespan;

public:
	Animal(Point position, char symbol, int strength, int priority);
	~Animal();

	int getPriority() const;
	int getLifespan() const;

	virtual void update() = 0;
};

#endif