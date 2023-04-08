#include "Animal.h"

Animal::Animal(Point position, char symbol, int strength, int priority) :
	Entity{ position, symbol, strength }, priority{ priority }, lifespan{ 0 }
{

}

Animal::~Animal()
{

}

int Animal::getPriority() const
{
	return this->priority;
}

int Animal::getLifespan() const
{
	return this->lifespan;
}

void Animal::update()
{
	std::cout << "Updating animal type: " << this->symbol << " with priority: " << this->priority << " and lifespan: " << this->lifespan << '\n';
	this->lifespan++;
}