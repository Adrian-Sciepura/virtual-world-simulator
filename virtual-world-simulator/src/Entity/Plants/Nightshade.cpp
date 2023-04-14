#include "Nightshade.h"

Nightshade::Nightshade(World* world, Point position) :
    Plant{ AssetManager::getAssetManager()->getAsset("nightShade"), world, position, 'N', 99, SpreadChance::LOW }
{
}

void Nightshade::update(std::fstream& logFile)
{
	this->spread<Nightshade>(logFile);
	Entity::update(logFile);
}

bool Nightshade::collision(std::fstream& logFile, Entity& entity)
{
	logFile << this->position << " " << entity.getSymbol() << " was killed when eating " << this->symbol << '\n';
	entity.kill();
	world->getMap()[position.x][position.y] = nullptr;
	this->isAlive = false;
    return true;
}
