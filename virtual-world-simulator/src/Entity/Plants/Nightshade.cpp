#include "Nightshade.h"

Nightshade::Nightshade(World* world, Point position) :
    Plant{ AssetManager::getAssetManager()->getAsset("nightShade"), world, position, 'N', 99, SpreadChance::LOW }
{
}

void Nightshade::update()
{
	this->spread<Nightshade>();
	Entity::update();
}

bool Nightshade::collision(Entity& entity)
{
	entity.kill();
	world->getMap()[position.x][position.y] = nullptr;
    return Plant::collision(entity);
}
