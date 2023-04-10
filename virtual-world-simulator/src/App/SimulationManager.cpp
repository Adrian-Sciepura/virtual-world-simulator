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
}

void SimulationManager::draw()
{
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
	worldMap[1][1] = new Fox(&world, Point(1, 1));
	worldMap[1][8] = new Fox(&world, Point(1, 8));
	worldMap[1][10] = new Fox(&world, Point(1, 10));
	worldMap[10][10] = new Fox(&world, Point(10, 10));
	worldMap[2][2] = new Wolf(&world, Point(2, 2));
	worldMap[2][3] = new Wolf(&world, Point(2, 3));
	worldMap[7][18] = new Turtle(&world, Point(7, 18));
	worldMap[7][19] = new Turtle(&world, Point(7, 19));
	worldMap[19][19] = new Antelope(&world, Point(19, 19));
	worldMap[19][18] = new Antelope(&world, Point(19, 18));
	worldMap[18][18] = new Grass(&world, Point(18, 18));
	worldMap[17][16] = new Grass(&world, Point(17, 16));
	worldMap[15][15] = new Dandelion(&world, Point(15, 15));
	worldMap[13][13] = new Guarana(&world, Point(13, 13));
	worldMap[8][8] = new Nightshade(&world, Point(8, 8));
	worldMap[8][9] = new Nightshade(&world, Point(8, 9));
	worldMap[8][8] = new Human(&world, Point(8, 8));

	char c = NULL;
	while (c != 'q')
	{
		system("cls");
		draw();
		update();
		system("cls");
		draw();

		std::cout << "\Press q to quit game or ENTER to continue\n";
		c = getchar();
	}
}