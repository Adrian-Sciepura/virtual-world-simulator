#ifndef WORLD_H
#define WORLD_H

#include "../Entity/Entity.h"

class Entity;

class World
{
private:
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

	void endGame();
};

#endif