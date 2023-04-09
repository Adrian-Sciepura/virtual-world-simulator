#include "SimulationManager.h"

SimulationManager::SimulationManager() : 
	world{ 20, 20 }, worldMap{ world.getMap() }, worldWidth{ world.getWidth() }, worldHeight{ world.getHeight() }
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
	worldMap[1][1] = new Grass(&world, { 1, 1 });
	worldMap[3][3] = new Grass(&world, { 3, 3 });
	worldMap[1][2] = new Grass(&world, { 1, 2 });
	worldMap[1][0] = new Grass(&world, { 1, 0 });
	worldMap[0][1] = new Wolf(&world, { 0, 1 });
	worldMap[4][4] = new Wolf(&world, { 4, 4 });
	worldMap[3][1] = new Sheep(&world, { 3, 1 });
	worldMap[10][10] = new Fox(&world, { 10, 10 });
	worldMap[5][5] = new Turtle(&world, { 5, 5 });
	worldMap[7][14] = new Antelope(&world, { 7, 14 });
	worldMap[1][18] = new Antelope(&world, { 1, 18 });
	worldMap[1][19] = new Antelope(&world, { 1, 19 });

	char c = NULL;
	while (c != 'q')
	{
		system("cls");
		update();

		std::cout << "\nNacisnij q aby zakonczyc lub ENTER aby kontynuowac\n";
		c = getchar();
	}
}