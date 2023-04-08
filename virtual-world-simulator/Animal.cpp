#include "Animal.h"

Animal::Animal(Point position, char symbol, int strength, int priority) :
	Entity{ position, symbol, strength, priority }
{

}

Animal::~Animal()
{

}

void Animal::update()
{
	Entity::update();
}