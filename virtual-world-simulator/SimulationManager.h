#ifndef SIMULATION_MANAGER_H
#define SIMULATION_MANAGER_H

#include <iostream>
#include <queue>
#include <vector>
#include <functional>

#include "World.h"
#include "EntityCompare.h"
#include "Entity.h"
#include "Animal.h"
#include "Wolf.h"
#include "Plant.h"
#include "Grass.h"

class SimulationManager
{
private:
	std::priority_queue < Entity*, std::vector<Entity*>, EntityCompare> entities;
	World world;
	int worldWidth, worldHeight;
	Entity*** worldMap;

public:
	SimulationManager();
	~SimulationManager();

	void start();
	void update();
};

#endif