#ifndef HUMAN_H
#define HUMAN_H

#include <conio.h>
#include "../../Common/KeyCodes.h"
#include "Animal.h"

class Human : public Animal
{
protected:
	Point newPosition;

public:
	Human(World* world, Point position);
	
	bool setNewPosition(int keyCode);
	virtual void update(std::fstream& logFile);
};

#endif