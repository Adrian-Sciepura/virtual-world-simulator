#include "Entity.h"

Entity::Entity(Point position, char symbol, int strength, int priority) :
    position{ position }, symbol{ symbol }, strength{ strength }, priority{ priority }, lifespan{ 0 }
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

void Entity::update()
{
	std::cout << "Updating entity type: " << this->symbol << " with priority: " << this->priority << " and lifespan: " << this->lifespan << '\n';
	this->lifespan++;
}