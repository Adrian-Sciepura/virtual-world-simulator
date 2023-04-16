#ifndef WORLD_H
#define WORLD_H

#include "../Entity/Entity.h"
#include <queue>

class Entity;

class World
{
private:
	std::queue<Entity*> garbage;
	Entity*** map;
	int width;
	int height;
	int gameOver;

public:
	World(int width, int height);
	~World();

	Entity***& getMap();
	int getWidth() const;
	int getHeight() const;
	bool checkIfGameOver() const;

	void addEntityToDelete(Entity* entity);

	void clearGarbage();
	void endGame();
};

#endif