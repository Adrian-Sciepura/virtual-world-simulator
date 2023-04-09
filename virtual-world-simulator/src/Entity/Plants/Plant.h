#ifndef PLANT_H
#define PLANT_H

#include "../Entity.h"

class Plant : public Entity
{
protected:
	int spreadChance;
	enum SpreadChance
	{
		LOW = 2,
		MEDIUM = 3,
		HIGH = 4
	};

public:
	Plant(World* world, Point position, char symbol, int strength, SpreadChance spreadChance);
	~Plant();


	template <class T>
	void spread()
	{
		static_assert(std::is_base_of<Plant, T>::value, "T must be derived from Plant");
		int currentX = this->position.x;
		int currentY = this->position.y;
		Entity*** map = world->getMap();
		std::vector<Point> freeFields;
		for (int i = currentY - 1; i < currentY + 1; i++)
		{
			for (int j = currentX - 1; j < currentX + 1; j++)
			{
				if (i < 0 || i > world->getHeight() - 1 || j < 0 || j > world->getWidth() - 1)
					continue;
				if (map[i][j] == nullptr)
					freeFields.push_back(Point(i, j));
			}
		}
		if (freeFields.size() > 0)
		{
			Point newPosition = freeFields[Utility::random(0, freeFields.size() - 1)];
			map[newPosition.x][newPosition.y] = new T(world, newPosition);
			//std::clog << "New " << newPlant->getSymbol() << " born at: " << newPosition.y << ", " << newPosition.x << '\n';
		}
	}

	virtual void update() = 0;
	virtual bool collision(Entity& entity) = 0;
};

#endif