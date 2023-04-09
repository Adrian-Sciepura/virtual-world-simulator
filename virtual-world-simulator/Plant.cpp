#include "Plant.h"

Plant::Plant(World* world, Point position, char symbol, int strength, SpreadChance spreadChance) :
	Entity{ world, position, symbol, strength, 0 }, spreadChance{ spreadChance }
{

}

Plant::~Plant()
{
}