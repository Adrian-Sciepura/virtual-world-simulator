#include "Animal.h"

Animal::Animal(World* world, Point position, char symbol, int strength, int priority) :
	Entity{ world, position, symbol, strength, priority }
{

}

Animal::~Animal()
{

}

void Animal::move(const Point& newPosition)
{
    Entity*** map = world->getMap();
    Entity* entity = map[newPosition.x][newPosition.y];
    if (entity != nullptr)
    {
        //std::clog << "Collision detected at: " << newPosition.y << ", " << newPosition.x << '\n';
        //std::clog << "1. Entity type: " << this->symbol << " with priority: " << this->priority << " and lifespan: " << this->lifespan << '\n';
        //std::clog << "2. Entity type: " << entity->getSymbol() << " with priority: " << entity->getPriority() << " and lifespan: " << entity->getLifespan() << '\n';
        if (!entity->collision(*this))
        {
            if(this->isAlive == false)
                map[position.x][position.y] = nullptr;
            
            return;
        }
        else
        {
            map[newPosition.x][newPosition.y] = nullptr;
        }
    }

    map[position.x][position.y] = nullptr;
    this->position = newPosition;
    map[position.x][position.y] = this;
}

void Animal::update()
{
    int currentX = this->position.x;
    int currentY = this->position.y;
    int newX = currentX;
    int newY = currentY;
    
    while (newX == currentX && newY == currentY)
    {
        newX = currentX + Utility::random(-1, 1);
        newY = currentY + Utility::random(-1, 1);

        if (newX < 0)
            newX = 0;
        else if (newX > world->getWidth() - 1)
            newX -= 1;

        if (newY < 0)
            newY = 0;
        else if (newY > world->getHeight() - 1)
            newY -= 1;
    }

    this->move({ newX, newY });
	Entity::update();
}

bool Animal::collision(Entity& entity)
{
    int entityStrength = entity.getStrength();

    if (entityStrength > this->strength ||
        (entityStrength == this->strength && entity.getLifespan() > this->lifespan))
    {
        this->isAlive = false;
        return true;
    }

    entity.kill();
    return false;
}