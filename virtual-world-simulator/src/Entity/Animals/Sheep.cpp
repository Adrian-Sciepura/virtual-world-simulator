#include "Sheep.h"

Sheep::Sheep(World* world, Point position) : 
    Animal{ AssetManager::getAssetManager()->getAsset("sheep"), world, position, 'S', 4, 4 }
{
}

bool Sheep::collision(std::fstream& logFile, Entity& entity)
{
	Sheep* sheep = dynamic_cast<Sheep*>(&entity);
	if (sheep != nullptr)
	{
		this->breed<Sheep>(logFile, *sheep);
		return false;
	}

	return Animal::collision(logFile, entity);
}
