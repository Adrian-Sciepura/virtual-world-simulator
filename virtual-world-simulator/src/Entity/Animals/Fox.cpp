#include "Fox.h"

Fox::Fox(World* world, Point position) :
    Animal{ AssetManager::getAssetManager()->getAsset("fox"), world, position, 'F', 3, 7 }
{
}

void Fox::update(std::fstream& logFile)
{
    int currentX = this->position.x;
    int currentY = this->position.y;

    std::vector<Point> possibleMoves;
    Entity*** map = world->getMap();

    for (int i = currentX - 1; i <= currentX + 1; i++)
    {
        if (i < 0 || i > world->getHeight() - 1)
            continue;

        for (int j = currentY - 1; j <= currentY + 1; j++)
        {
            if (j < 0 || j > world->getWidth() - 1 ||
                (i == currentX && j == currentY))
                continue;

            if (map[i][j] == nullptr || map[i][j]->getStrength() <= this->strength)
                possibleMoves.push_back(Point(i, j));
		}
    }
    if(possibleMoves.size() > 0)
    {
        Point newPosition = possibleMoves[Utility::random(0, possibleMoves.size() - 1)];
        this->move(logFile, newPosition);
    }
    Entity::update(logFile);
}

bool Fox::collision(std::fstream& logFile, Entity& entity)
{
    Fox* fox = dynamic_cast<Fox*>(&entity);
    if (fox != nullptr)
    {
        this->breed<Fox>(logFile, *fox);
        return false;
    }

    return Animal::collision(logFile, entity);
}
