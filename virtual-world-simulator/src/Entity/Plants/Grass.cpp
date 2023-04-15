#include "Grass.h"

Grass::Grass(World* world, Point position) :
	Plant { AssetManager::getAssetManager()->getAsset("grass"), world, position, 'G', 0, SpreadChance::MEDIUM }
{

}

Grass::Grass(World* world, Point position, int lifeSpan, int strength) :
	Plant { AssetManager::getAssetManager()->getAsset("grass"), world, position, 'G', strength, lifeSpan, SpreadChance::MEDIUM, }
{
}

void Grass::update(std::fstream& logFile)
{
	this->spread<Grass>(logFile);
	Entity::update(logFile);
}