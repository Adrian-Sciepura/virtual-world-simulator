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
	Human(World* world, Point position, int lifeSpan, int strength);
	
	Point getNewPosition() const;
	bool setNewPosition(int keyCode);
	virtual void update(std::fstream& logFile);
	virtual bool collision(std::fstream& logFile, Entity& entity);
};

#endif