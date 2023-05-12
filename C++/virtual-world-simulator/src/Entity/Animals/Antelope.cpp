#include "Antelope.h"

bool Antelope::runAway()
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

            if (map[i][j] == nullptr)
            {
                map[i][j] = this;
                map[currentX][currentY] = nullptr;
                this->position = { i, j };
                return true;
            }
        }
    }

    return false;
}

Antelope::Antelope(World* world, Point position) :
    Animal{ AssetManager::getAssetManager()->getAsset("antelope"), world, position, 'A', 4, 4}
{
}

Antelope::Antelope(World* world, Point position, int lifeSpan, int strength) :
    Animal{ AssetManager::getAssetManager()->getAsset("antelope"), world, position, 'A', strength, 4, lifeSpan }
{
}

void Antelope::update(std::fstream& logFile)
{
    int range = Utility::random(1, 2);
    int currentX = this->position.x;
    int currentY = this->position.y;
    int newX = currentX;
    int newY = currentY;

    while (newX == currentX && newY == currentY)
    {
        newX = currentX + Utility::random(-range, range);
        newY = currentY + Utility::random(-range, range);

        if (newX < 0)
            newX = 0;
        else if (newX > world->getHeight() - 1)
            newX -= range;

        if (newY < 0)
            newY = 0;
        else if (newY > world->getWidth() - 1)
            newY -= range;
    }

    this->move(logFile, { newX, newY });
    Entity::update(logFile);
}

bool Antelope::collision(std::fstream& logFile, Entity& entity)
{
    Antelope* antelope = dynamic_cast<Antelope*>(&entity);
    if (antelope != nullptr)
    {
        this->breed<Antelope>(logFile, *antelope);
        return false;
    }

    int runAwayChance = Utility::random(1, 2);
    if(runAwayChance == 2 && this->runAway())
		return true;

    return Animal::collision(logFile, entity);
}
