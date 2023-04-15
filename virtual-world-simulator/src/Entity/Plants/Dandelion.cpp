#include "Dandelion.h"

Dandelion::Dandelion(World* world, Point position) :
	Plant { AssetManager::getAssetManager()->getAsset("dandelion"), world, position, 'D', 0, SpreadChance::LOW }
{
}

Dandelion::Dandelion(World* world, Point position, int lifeSpan, int strength) :
	Plant { AssetManager::getAssetManager()->getAsset("dandelion"), world, position, 'D', strength, lifeSpan, SpreadChance::LOW }
{
}

void Dandelion::update(std::fstream& logFile)
{
	for(int i = 0; i < 3; i++)
		this->spread<Dandelion>(logFile);

	Entity::update(logFile);
}