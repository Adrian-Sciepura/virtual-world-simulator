#include "Antelope.h"

bool Antelope::runAway()
{
    Entity*** map = world->getMap();
    int currentX = this->position.x;
    int currentY = this->position.y;
    
    for (int i = currentY - 1; i < currentY + 1; i++)
    {
        for (int j = currentX - 1; j < currentX + 1; j++)
        {
            if (i < 0 || i > world->getHeight() - 1 || j < 0 || j > world->getWidth() - 1)
                continue;

            if (map[i][j] == nullptr)
            {
                map[i][j] = this;
                map[currentY][currentX] = nullptr;
                this->position = { i, j };
                return true;
            }
        }
    }

    return false;
}

Antelope::Antelope(World* world, Point position) :
    Animal{ world, position, 'A', 4, 4 }
{
}

void Antelope::update()
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
        else if (newX > world->getWidth() - 1)
            newX -= range;

        if (newY < 0)
            newY = 0;
        else if (newY > world->getHeight() - 1)
            newY -= range;
    }

    this->move({ newX, newY });
    Entity::update();
}

bool Antelope::collision(Entity& entity)
{
    Antelope* antelope = dynamic_cast<Antelope*>(&entity);
    if (antelope != nullptr)
    {
        this->breed<Antelope>(*antelope);
        return false;
    }

    int runAwayChance = Utility::random(1, 2);
    if(runAwayChance == 2 && this->runAway())
		return true;

    return Animal::collision(entity);
}
