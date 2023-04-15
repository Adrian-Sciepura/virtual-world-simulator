#include "Human.h"

Human::Human(World* world, Point position) :
    Animal{ AssetManager::getAssetManager()->getAsset("human"), world, position, 'H', 5, 4 }, newPosition{ position }
{
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
    bool temp = Animal::collision(logFile, entity);
    if (!this->isAlive)
        world->endGame();

    return temp;
}
