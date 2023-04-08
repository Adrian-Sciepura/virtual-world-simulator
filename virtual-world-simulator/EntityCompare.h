#ifndef ENTITY_COMPARE_H
#define ENTITY_COMPARE_H

#include "Entity.h"

class EntityCompare
{
public:
	bool operator()(Entity* lhs, Entity* rhs)
	{
		if (lhs->getPriority() == rhs->getPriority())
			return lhs->getLifespan() < rhs->getLifespan();
		else
			return lhs->getPriority() < rhs->getPriority();
	}
};

#endif