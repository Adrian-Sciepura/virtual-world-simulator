#include "Plant.h"

int Plant::numberOfPlants = 0;

Plant::Plant(BMPFile* texture, World* world, Point position, char symbol, int strength, SpreadChance spreadChance) :
	Entity{ texture, world, position, symbol, strength, 0 }, spreadChance{ spreadChance }
{
	numberOfPlants++;
}

Plant::~Plant()
{
	numberOfPlants--;
}

bool Plant::collision(Entity& entity)
{
	this->isAlive = false;
	return true;
}

int Plant::getNumberOfPlants()
{
	return numberOfPlants;
}
