#include "Guarana.h"

Guarana::Guarana(World* world, Point position) :
    Plant { AssetManager::getAssetManager()->getAsset("guarana"), world, position, 'U', 0, SpreadChance::MEDIUM }
{
}

void Guarana::update(std::fstream& logFile)
{
	this->spread<Guarana>(logFile);
	Entity::update(logFile);
}

bool Guarana::collision(std::fstream& logFile, Entity& entity)
{
	entity.setStrength(entity.getStrength() + 3);
    return Plant::collision(logFile, entity);
}
