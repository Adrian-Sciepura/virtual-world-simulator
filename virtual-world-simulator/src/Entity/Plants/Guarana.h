#ifndef GUARANA_H
#define GUARANA_H

#include "Plant.h"

class Guarana : public Plant
{
public:
	Guarana(World* world, Point position);
	
	virtual void update();
	virtual bool collision(Entity& entity);
};

#endif