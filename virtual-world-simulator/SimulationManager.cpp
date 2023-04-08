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
		entities.top()->update();
		entities.pop();
	}

	for (int i = 0; i < worldHeight; i++)
	{
		for (int j = 0; j < worldWidth; j++)
		{
			std::cout << (worldMap[i][j] != nullptr ? worldMap[i][j]->getSymbol() : '#');
		}
		std::cout << '\n';
	}
}

void SimulationManager::start()
{
	worldMap[1][1] = new Grass( &world, { 1, 1 });
	worldMap[3][3] = new Wolf(&world, { 3, 3 });
	char c = NULL;
	while (c != 'q')
	{
		std::cin >> c;
		system("cls");
		update();
	}
}