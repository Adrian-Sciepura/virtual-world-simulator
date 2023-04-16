#include "World.h"

World::World(int width, int height) : width{ width }, height{ height }, gameOver{ false }
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

int World::getWidth() const
{
	return this->width;
}

int World::getHeight() const
{
	return this->height;
}

bool World::checkIfGameOver() const
{
	return this->gameOver;
}

void World::addEntityToDelete(Entity* entity)
{
	garbage.push(entity);
}

void World::clearGarbage()
{
	while (!garbage.empty())
	{
		delete garbage.front();
		garbage.pop();
	}
}

void World::endGame()
{
	this->gameOver = true;
}
