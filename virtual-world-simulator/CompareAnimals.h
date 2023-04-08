#ifndef COMPARE_ANIMALS_H
#define COMPARE_ANIMALS_H

#include "Animal.h"

class CompareAnimals
{
public:
	bool operator()(Animal* lhs, Animal* rhs)
	{
		if (lhs->getPriority() == rhs->getPriority())
			return lhs->getLifespan() < rhs->getLifespan();
		else
			return lhs->getPriority() < rhs->getPriority();
	}
};

#endif