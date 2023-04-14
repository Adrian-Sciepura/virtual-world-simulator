#ifndef SIMULATION_MANAGER_H
#define SIMULATION_MANAGER_H

#include <iostream>
#include <queue>
#include <vector>
#include <functional>

#include "../Graphics/GraphicsEngine.h"
#include "../Graphics/AssetManager.h"

#include "World.h"
#include "../Entity/EntityCompare.h"
#include "../Entity/Entity.h"

#include "../Entity/Animals/Animal.h"
#include "../Entity/Animals/Wolf.h"
#include "../Entity/Animals/Sheep.h"
#include "../Entity/Animals/Fox.h"
#include "../Entity/Animals/Turtle.h"
#include "../Entity/Animals/Antelope.h"
#include "../Entity/Animals/Human.h"

#include "../Entity/Plants/Plant.h"
#include "../Entity/Plants/Grass.h"
#include "../Entity/Plants/Dandelion.h"
#include "../Entity/Plants/Guarana.h"
#include "../Entity/Plants/Nightshade.h"

class SimulationManager
{
private:
	std::priority_queue < Entity*, std::vector<Entity*>, EntityCompare> entities;
	
	GraphicsEngine graphicsEngine;
	WORD* colorBuffer;

	AssetManager* assetManager;
	const int singleEntitySize;

	World world;
	Entity*** worldMap;
	int worldWidth, worldHeight;

	int round;
	
	void draw();
	void drawBoard();
	void drawText(std::string text, const Point& position);
	void drawInfo();
	void updateInfo();

	void update();
public:
	SimulationManager();
	~SimulationManager();

	void start();
	
	
};

#endif