#include "SimulationManager.h"

SimulationManager::SimulationManager() : world{ 20, 20 }, worldMap{ world.getMap() }, worldWidth{ world.getWidth() }, worldHeight{ world.getHeight() }
{

}

SimulationManager::~SimulationManager()
{
	
}

void SimulationManager::update()
{
	for (int i = 0; i < worldHeight; i++)
	{
		for (int j = 0; j < worldWidth; j++)
		{
			if (worldMap[i][j] != nullptr)
				entities.push(worldMap[i][j]);
		}
	}

	while (!entities.empty())
	{
		Entity* entity = entities.top();
		if(entity->checkIfAlive())
		{
			entity->update();
			if(!entity->checkIfAlive())
			{
				delete entity;
			}
		}
		else
		{
			delete entity;
		}

		entities.pop();
	}

	std::cout << "-----------------------\n";
	for (int i = 0; i < worldHeight; i++)
	{
		for (int j = 0; j < worldWidth; j++)
		{
			std::cout << (worldMap[i][j] != nullptr ? worldMap[i][j]->getSymbol() : ' ');
		}
		std::cout << '\n';
	}
	std::cout << "-----------------------\n";
}

void SimulationManager::start()
{
	//std::vector<Point> p;
	//p.push_back({ 1, 1 });
	worldMap[1][1] = new Grass(&world, { 1, 1 });
	worldMap[3][3] = new Grass(&world, { 3, 3 });
	worldMap[1][2] = new Grass(&world, { 1, 2 });
	worldMap[1][0] = new Grass(&world, { 1, 0 });
	worldMap[0][1] = new Wolf(&world, { 0, 1 });
	worldMap[4][4] = new Wolf(&world, { 4, 4 });
	worldMap[3][1] = new Wolf(&world, { 3, 1 });
	//worldMap[3][1]->collision(*worldMap[4][4]);
	char c = NULL;
	while (c != 'q')
	{
		std::cin >> c;
		system("cls");
		update();
	}
}