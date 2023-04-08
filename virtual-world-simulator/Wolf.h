#ifndef WOLF_H
#define WOLF_H

#include "Animal.h"

class Wolf : public Animal
{
public:
	Wolf(Point position);
	~Wolf();
	void update();
};

#endif