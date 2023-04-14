#ifndef TURTLE_H
#define TURTLE_H

#include "Animal.h"

class Turtle : public Animal
{
public:
	Turtle(World* world, Point position);
	
	virtual void update(std::fstream& logFile);
	virtual bool collision(std::fstream& logFile, Entity& entity);
};

#endif