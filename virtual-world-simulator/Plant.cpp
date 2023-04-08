#include "Plant.h"

Plant::Plant(World* world, Point position, char symbol, int strength) :
	Entity{ world, position, symbol, strength, 0 }
{

}

Plant::~Plant()
{
}

void Plant::update()
{
	Entity::update();
}