#ifndef PLANT_H
#define PLANT_H

#include "../Entity.h"

class Plant : public Entity
{
protected:
	int spreadChance;
	enum SpreadChance
	{
		LOW = 1,
		MEDIUM = 2,
		HIGH = 3
	};

public:
	Plant(World* world, Point position, char symbol, int strength, SpreadChance spreadChance);
	~Plant();


	template <class T>
	void spread()
	{
		static_assert(std::is_base_of<Plant, T>::value, "T must be derived from Plant");

		int random = Utility::random(1, 25);
		if (random > this->spreadChance)
			return;

		int currentX = this->position.x;
		int currentY = this->position.y;
		Entity*** map = world->getMap();
		std::vector<Point> freeFields;
		for (int i = currentX - 1; i <= currentX + 1; i++)
		{
			if (i < 0 || i > world->getHeight() - 1)
				continue;

			for (int j = currentY - 1; j <= currentY + 1; j++)
			{
				if (j < 0 || j > world->getWidth() - 1)
					continue;

				if (map[i][j] == nullptr)
					freeFields.push_back(Point(i, j));
			}
		}

		if (freeFields.size() > 0)
		{
			Point newPosition = freeFields[Utility::random(0, freeFields.size() - 1)];
			map[newPosition.x][newPosition.y] = new T(world, newPosition);
		}
	}

	virtual void update() = 0;
	virtual bool collision(Entity& entity);
};

#endif