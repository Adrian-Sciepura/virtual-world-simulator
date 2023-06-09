#include "Wolf.h"

Wolf::Wolf(World* world, Point position) :
	Animal{ AssetManager::getAssetManager()->getAsset("wolf"), world, position, 'W', 9, 5 }
{
}

Wolf::Wolf(World* world, Point position, int lifeSpan, int strength) :
	Animal{ AssetManager::getAssetManager()->getAsset("wolf"), world, position, 'W', strength, 5, lifeSpan }
{
}

bool Wolf::collision(std::fstream& logFile, Entity& entity)
{
	Wolf* wolf = dynamic_cast<Wolf*>(&entity);
	if (wolf != nullptr)
	{
		this->breed<Wolf>(logFile, *wolf);
		return false;
	}

	return Animal::collision(logFile, entity);
}
