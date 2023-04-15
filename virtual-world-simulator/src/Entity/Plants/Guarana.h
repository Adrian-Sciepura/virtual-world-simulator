#ifndef GUARANA_H
#define GUARANA_H

#include "Plant.h"

class Guarana : public Plant
{
public:
	Guarana(World* world, Point position);
	Guarana(World* world, Point position, int lifeSpan, int strength);

	virtual void update(std::fstream& logFile);
	virtual bool collision(std::fstream& logFile, Entity& entity);
};

#endif