#ifndef SIMULATION_MANAGER_H
#define SIMULATION_MANAGER_H

#include <iostream>
#include <queue>
#include <vector>
#include <functional>


#include "World.h"
#include "../Entity/EntityCompare.h"
#include "../Entity/Entity.h"

#include "../Entity/Animals/Animal.h"
#include "../Entity/Animals/Wolf.h"
#include "../Entity/Animals/Sheep.h"
#include "../Entity/Animals/Fox.h"
#include "../Entity/Animals/Turtle.h"
#include "../Entity/Animals/Antelope.h"

#include "../Entity/Plants/Plant.h"
#include "../Entity/Plants/Grass.h"

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