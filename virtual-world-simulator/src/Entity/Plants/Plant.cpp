#include "Plant.h"

int Plant::numberOfPlants = 0;

Plant::Plant(BMPFile* texture, World* world, Point position, char symbol, int strength, SpreadChance spreadChance) :
	Entity{ texture, world, position, symbol, strength, 0 }, spreadChance{ spreadChance }
{
	numberOfPlants++;
}

Plant::Plant(BMPFile* texture, World* world, Point position, char symbol, int strength, int lifeSpan, SpreadChance spreadChance) :
	Entity{ texture, world, position, symbol, strength, 0, lifeSpan }, spreadChance{ spreadChance }
{
	numberOfPlants++;
}

Plant::~Plant()
{
	numberOfPlants--;
}

bool Plant::collision(std::fstream& logFile, Entity& entity)
{
	logFile << this->position << " The " << this->symbol << " has been eaten by " << entity.getSymbol() << "\n";
	this->isAlive = false;
	return true;
}

int Plant::getNumberOfPlants()
{
	return numberOfPlants;
}
