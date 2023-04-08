#include "Entity.h"

Entity::Entity(Point position, char symbol, int strength) :
    position{ position }, symbol{ symbol }, strength{ strength }
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