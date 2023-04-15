#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include <fstream>

#include "../Common/Utility.h"
#include "../Common/Point.h"
#include "../App/World.h"
#include "../Graphics/AssetManager.h"

class World;

class Entity
{
protected:
	BMPFile* texture;
	World* world;
	Point position;
	bool isAlive;
	char symbol;
	int strength;
	int priority;
	int lifespan;

public:
	Entity(BMPFile* texture, World* world, Point position, char symbol, int strength, int priority);
	Entity(BMPFile* texture, World* world, Point position, char symbol, int strength, int priority, int lifeSpan);
	virtual ~Entity();

	BMPFile* getTexture() const;
	Point getPosition() const;
	char getSymbol() const;
	int getStrength() const;
	int getPriority() const;
	int getLifespan() const;

	void setStrength(int strength);

	void kill();
	bool checkIfAlive() const;
	virtual void update(std::fstream& logFile);
	
	//returns true if occupied field becomes free
	virtual bool collision(std::fstream& logFile, Entity& entity) = 0;
};

#endif