#include "Human.h"

Human::Human(World* world, Point position) :
    Animal{ AssetManager::getAssetManager()->getAsset("human"), world, position, 'H', 5, 4 }, newPosition{ position }, abilityTurnedOn{ false }
{
}

Human::Human(World* world, Point position, int lifeSpan, int strength) :
    Animal{ AssetManager::getAssetManager()->getAsset("human"), world, position, 'H', strength, 4, lifeSpan }, newPosition{ position }, abilityTurnedOn{ false }
{
}

Point Human::getNewPosition() const
{
    return this->newPosition;
}

bool Human::checkIfAbilityTurnedOn() const
{
    return this->abilityTurnedOn;
}

void Human::switchAbility(bool value)
{
    this->abilityTurnedOn = value;
}

bool Human::setNewPosition(int keyCode)
{
    int mapWidth = this->world->getWidth();
    int mapHeight = this->world->getHeight();

    switch (keyCode)
    {
        case KeyCodes::UP:
        {
            if (this->position.x == 0)
                break;

            newPosition.x = (this->position.x - 1);
            return true;
        }
        case KeyCodes::DOWN:
        {
            if (this->position.x == mapHeight - 1)
                break;

            newPosition.x = (this->position.x + 1);
            return true;
        }
        case KeyCodes::LEFT:
        {
            if (this->position.y == 0)
                break;

            newPosition.y = (this->position.y - 1);
            return true;
        }
        case KeyCodes::RIGHT:
        {
            if (this->position.y == mapWidth - 1)
                break;

            newPosition.y = (this->position.y + 1);
            return true;
        }
    }

    return false;
}

void Human::update(std::fstream& logFile)
{
    this->move(logFile, newPosition);

    if (!this->isAlive)
        world->endGame();
}

bool Human::collision(std::fstream& logFile, Entity& entity)
{
    if (abilityTurnedOn)
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

    bool temp = Animal::collision(logFile, entity);
    if (!this->isAlive)
        world->endGame();

    return temp;
}
