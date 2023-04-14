#include "Grass.h"

Grass::Grass(World* world, Point position) :
	Plant { AssetManager::getAssetManager()->getAsset("grass"), world, position, 'G', 0, SpreadChance::MEDIUM }
{

}

void Grass::update(std::fstream& logFile)
{
	this->spread<Grass>(logFile);
	Entity::update(logFile);
}