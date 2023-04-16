#include "PineHogweed.h"

PineHogweed::PineHogweed(World* world, Point position) :
    Plant{ AssetManager::getAssetManager()->getAsset("pineHogweed"), world, position, 'P', 10, SpreadChance::LOW }
{

}

PineHogweed::PineHogweed(World* world, Point position, int lifeSpan, int strength) :
    Plant{ AssetManager::getAssetManager()->getAsset("pineHogweed"), world, position, 'P', strength, lifeSpan, SpreadChance::LOW, }
{
}

void PineHogweed::update(std::fstream& logFile)
{
    Entity*** map = world->getMap();
    int currentX = this->position.x;
    int currentY = this->position.y;

    for (int i = currentX - 1; i <= currentX + 1; i++)
    {
        if (i < 0 || i > world->getHeight() - 1)
            continue;

        for (int j = currentY - 1; j <= currentY + 1; j++)
        {
            if (j < 0 || j > world->getWidth() - 1)
                continue;

            if (map[i][j] != nullptr && map[i][j]->getPriority() != 0)
                map[i][j]->kill();
        }
    }
}

bool PineHogweed::collision(std::fstream& logFile, Entity& entity)
{
	logFile << this->position << " " << entity.getSymbol() << " was killed when eating " << this->symbol << '\n';
	entity.kill();
	this->kill();
	return true;
}
