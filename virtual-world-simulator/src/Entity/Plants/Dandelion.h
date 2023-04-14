#ifndef DANDELION_H
#define DANDELION_H

#include "Plant.h"

class Dandelion : public Plant
{
public:
	Dandelion(World* world, Point position);

	virtual void update(std::fstream& logFile);
};

#endif