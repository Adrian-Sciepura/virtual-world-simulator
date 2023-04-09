#include "Fox.h"

Fox::Fox(World* world, Point position) :
    Animal{ world, position, 'F', 3, 7 }
{
}

void Fox::update()
{
    int currentX = this->position.x;
    int currentY = this->position.y;
    int newX = currentX;
    int newY = currentY;

    std::vector<Point> possibleMoves;
    Entity*** map = world->getMap();

    for (int i = currentY - 1; i < currentY + 1; i++)
    {
        for (int j = currentX - 1; j < currentX + 1; j++)
        {
			if(i < 0 || i > world->getHeight() - 1 || j < 0 || j > world->getWidth() - 1)
				continue;

            if (i == currentY && j == currentX)
                continue;

            if (map[i][j] == nullptr || map[i][j]->getStrength() <= this->strength)
                possibleMoves.push_back(Point(i, j));
		}
    }
    if(possibleMoves.size() > 0)
    {
        Point newPosition = possibleMoves[Utility::random(0, possibleMoves.size() - 1)];
        this->move(newPosition);
    }
    Entity::update();
}

bool Fox::collision(Entity& entity)
{
    Fox* fox = dynamic_cast<Fox*>(&entity);
    if (fox != nullptr)
    {
        this->breed<Fox>(*fox);
        return false;
    }

    return Animal::collision(entity);
}
