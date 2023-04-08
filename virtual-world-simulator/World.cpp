#include "World.h"

World::World(int width, int height) : width{ width }, height{ height }
{
	this->map = new Entity**[this->height];
	for (int i = 0; i < this->height; i++)
	{
		this->map[i] = new Entity * [this->width];
		for (int j = 0; j < this->width; j++)
		{
			this->map[i][j] = nullptr;
		}
	}
}

World::~World()
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (this->map[i][j] != nullptr)
				delete this->map[i][j];
		}
		delete[] this->map[i];
	}
	delete[] this->map;
}

Entity***& World::getMap()
{
	return this->map;
}

int World::getWidth()
{
	return this->width;
}

int World::getHeight()
{
	return this->height;
}
