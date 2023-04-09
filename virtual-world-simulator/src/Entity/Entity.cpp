#include "Entity.h"

Entity::Entity(World* world, Point position, char symbol, int strength, int priority) :
    world{ world }, position{ position }, symbol{ symbol }, strength{ strength }, priority{ priority }, lifespan{ 0 }, isAlive{ true }
{
}

Entity::~Entity()
{
}

Point Entity::getPosition() const
{
    return this->position;
}

char Entity::getSymbol() const
{
    return this->symbol;
}

int Entity::getStrength() const
{
    return this->strength;
}

int Entity::getPriority() const
{
    return this->priority;
}

int Entity::getLifespan() const
{
    return this->lifespan;
}

void Entity::kill()
{
    this->isAlive = false;
}

bool Entity::checkIfAlive() const
{
    return this->isAlive;
}

void Entity::update()
{
    this->lifespan++;
}