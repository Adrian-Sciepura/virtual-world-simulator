#include "Turtle.h"

Turtle::Turtle(World* world, Point position) :
	Animal{ AssetManager::getAssetManager()->getAsset("turtle"), world, position, 'T', 2, 1 }
{
}

void Turtle::update(std::fstream& logFile)
{
    int chance = Utility::random(1, 4);
	if (chance == 4)
		Animal::update(logFile);
	else
		Entity::update(logFile);
}

bool Turtle::collision(std::fstream& logFile, Entity& entity)
{
	Turtle* turtle = dynamic_cast<Turtle*>(&entity);
	if (turtle != nullptr)
	{
		this->breed<Turtle>(logFile, *turtle);
		return false;
	}

	if(entity.getStrength() < 5)
		return false;

	return Animal::collision(logFile, entity);
}
