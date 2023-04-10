#ifndef HUMAN_H
#define HUMAN_H

#include <conio.h>
#include "Animal.h"

class Human : public Animal
{
protected:
	enum keyCodes
	{
		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77
	};

public:
	Human(World* world, Point position);
	
	virtual void update();
};

#endif