#ifndef SIMULATION_MANAGER_H
#define SIMULATION_MANAGER_H

#include <iostream>
#include <queue>
#include <vector>
#include <functional>

#include "EntityCompare.h"
#include "Entity.h"
#include "Animal.h"
#include "Wolf.h"

class SimulationManager
{
private:
	std::priority_queue < Entity*, std::vector<Entity*>, EntityCompare> entities;
	Entity* map[20][20];

public:
	SimulationManager();
	~SimulationManager();

	void start();
	void update();
	void stop();
};

#endif