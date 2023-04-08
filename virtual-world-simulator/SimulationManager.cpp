#include "SimulationManager.h"

SimulationManager::SimulationManager() : map{nullptr}
{

}

SimulationManager::~SimulationManager()
{

}

void SimulationManager::start()
{
	map[1][1] = new Wolf({ 1, 1 });
	char c = NULL;
	while (c != 'q')
	{
		std::cin >> c;
		system("cls");
		update();
	}
}

void SimulationManager::update()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (map[i][j] == nullptr)
				continue;

			Animal* temp = dynamic_cast<Animal*>(map[i][j]);
			if (temp != nullptr)
				animals.push(temp);
		}
	}

	while (!animals.empty())
	{
		animals.top()->update();
		animals.pop();
	}
}

void SimulationManager::stop()
{

}