#ifndef ANTELOPE_H
#define ANTELOPE_H

#include "Animal.h"

class Antelope : public Animal
{
protected:
	bool runAway();

public:
	Antelope(World* world, Point position);
	Antelope(World* world, Point position, int lifeSpan, int strength);
	
	virtual void update(std::fstream& logFile);
	virtual bool collision(std::fstream& logFile, Entity& entity);
};

#endif