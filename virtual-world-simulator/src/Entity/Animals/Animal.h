#ifndef ANIMAL_H
#define ANIMAL_H

#include "../Entity.h"

class Animal : public Entity
{
public:
	Animal(World* world, Point position, char symbol, int strength, int priority);
	~Animal();

	template <class T>
	void breed(T& animal)
	{
		static_assert(std::is_base_of<Animal, T>::value, "T must be derived from Animal");

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

				if (map[i][j] == nullptr || dynamic_cast<T*>(map[i][j]) == nullptr)
					freeFields.push_back(Point(i, j));
			}
		}

		if (freeFields.size() > 0)
		{
			Point newPosition = freeFields[Utility::random(0, freeFields.size() - 1)];
			T* newAnimal = new T(world, newPosition);
			Entity* entity = map[newPosition.x][newPosition.y];
			if (entity != nullptr && !entity->collision(*newAnimal))
			{
				delete newAnimal;
				return;
			}

			map[newPosition.x][newPosition.y] = newAnimal;
			//std::clog << "New " << newAnimal->getSymbol() << " born at: " << newPosition.y << ", " << newPosition.x << '\n';
		}
	}

	void move(const Point& newPosition);
	virtual void update();
	virtual bool collision(Entity& entity);
};

#endif