#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include "Point.h"

class Entity
{
protected:
	Point position;
	char symbol;
	int strength;

public:
	Entity(Point position, char symbol, int strength);
	virtual ~Entity();

	Point getPosition() const;
	char getSymbol() const;
	int getStrength() const;

	virtual void update() = 0;
};

#endif