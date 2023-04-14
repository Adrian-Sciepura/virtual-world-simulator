#include "Animal.h"

int Animal::numberOfAnimals = 0;

Animal::Animal(BMPFile* texture, World* world, Point position, char symbol, int strength, int priority) :
	Entity{ texture, world, position, symbol, strength, priority }
{
    numberOfAnimals++;
}

Animal::~Animal()
{
    numberOfAnimals--;
}

void Animal::move(const Point& newPosition)
{
    Entity*** map = world->getMap();
    Entity* entity = map[newPosition.x][newPosition.y];
    if (entity != nullptr)
    {

        bool result = entity->collision(*this);

        if (this->isAlive == false)
        {
            map[position.x][position.y] = nullptr;
            return;
        }

        if (result)
        {
            if (entity->checkIfAlive() == false && entity->getPriority() > this->priority)
                delete entity;
        }
        else
        {
            return;
        }

        /*if (!entity->collision(*this))
        {
            if(this->isAlive == false)
                map[position.x][position.y] = nullptr;
            
            return;
        }
        else
        {
            if (entity->checkIfAlive() == false && entity->getPriority() > this->priority)
                delete entity;

            if (this->isAlive == false)
            {
                map[position.x][position.y] = nullptr;
                return;
            }
        }*/
    }

    map[position.x][position.y] = nullptr;
    this->position = newPosition;
    map[newPosition.x][newPosition.y] = this;
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
        else if (newX > world->getHeight() - 1)
            newX -= 1;

        if (newY < 0)
            newY = 0;
        else if (newY > world->getWidth() - 1)
            newY -= 1;
    }

    this->move({ newX, newY });
	Entity::update();
}

bool Animal::collision(Entity& entity)
{
    //New animals are immortal in the first round
    if(this->lifespan == 0)
		return false;

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

int Animal::getNumberOfAnimals()
{
    return numberOfAnimals;
}
