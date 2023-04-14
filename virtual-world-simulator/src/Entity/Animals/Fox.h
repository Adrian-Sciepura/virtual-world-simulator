#ifndef FOX_H
#define FOX_H

#include "Animal.h"

class Fox : public Animal
{
public:
	Fox(World* world, Point position);

	virtual void update(std::fstream& logFile);
	virtual bool collision(std::fstream& logFile, Entity& entity);
};

#endif