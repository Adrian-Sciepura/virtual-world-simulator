#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include "Point.h"
#include "World.h"

class World;

class Entity
{
protected:
	World* world;
	Point position;
	char symbol;
	int strength;
	int priority;
	int lifespan;

public:
	Entity(World* world, Point position, char symbol, int strength, int priority);
	virtual ~Entity();

	Point getPosition() const;
	char getSymbol() const;
	int getStrength() const;
	int getPriority() const;
	int getLifespan() const;

	virtual void update() = 0;
	virtual void collision() = 0;
};

#endif