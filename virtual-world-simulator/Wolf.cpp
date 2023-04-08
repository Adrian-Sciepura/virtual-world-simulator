#include "Wolf.h"

Wolf::Wolf(Point position) : 
	Animal{ position, 'W', 9, 5 }
{
}

Wolf::~Wolf()
{
}

void Wolf::update()
{
	Animal::update();
}
