#include "Entity.h"

Entity::Entity(BMPFile* texture, World* world, Point position, char symbol, int strength, int priority) :
    texture{ texture }, world { world }, position{ position }, symbol{ symbol }, strength{ strength }, priority{ priority }, lifespan{ 0 }, isAlive{ true }
{
}

Entity::~Entity()
{
}

BMPFile* Entity::getTexture() const
{
    return this->texture;
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

void Entity::setStrength(int strength)
{
    this->strength = strength;
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