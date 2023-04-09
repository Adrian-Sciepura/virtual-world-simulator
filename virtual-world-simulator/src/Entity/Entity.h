#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>

#include "../Common/Utility.h"
#include "../Common/Point.h"
#include "../App/World.h"

class World;

class Entity
{
protected:
	World* world;
	Point position;
	bool isAlive;
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

	void kill();
	bool checkIfAlive() const;
	virtual void update();
	virtual bool collision(Entity& entity) = 0; //returns true if entity dies
};

#endif