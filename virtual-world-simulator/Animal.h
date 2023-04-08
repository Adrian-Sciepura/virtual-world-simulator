#ifndef ANIMAL_H
#define ANIMAL_H

#include "Entity.h"

class Animal : public Entity
{
public:
	Animal(World* world, Point position, char symbol, int strength, int priority);
	~Animal();

	template <class T>
	void breed(T& animal)
	{
		static_assert(std::is_base_of<Animal, T>::value, "T must be derived from Animal");

		int currentX = this->position.getX();
		int currentY = this->position.getY();
		Entity*** map = world->getMap();
		std::vector<Point> freeFields;

		for (int i = currentY - 1; i < currentY + 1; i++)
		{
			for (int j = currentX - 1; j < currentX + 1; j++)
			{
				if (i < 0 || i > world->getHeight() - 1 || j < 0 || j > world->getWidth() - 1)
					continue;

				if (map[i][j] == nullptr || dynamic_cast<T*>(map[i][j]) == nullptr)
					freeFields.push_back(Point(j, i));
			}
		}

		if (freeFields.size() > 0)
		{
			Point newPosition = freeFields[Utility::random(0, freeFields.size() - 1)];
			T* newAnimal = new T(world, newPosition);
			Entity* entity = map[newPosition.getX()][newPosition.getY()];
			if (entity != nullptr && !entity->collision(*newAnimal))
			{
				delete newAnimal;
				return;
			}

			map[newPosition.getX()][newPosition.getY()] = newAnimal;
			std::clog << "New " << newAnimal->getSymbol() << " born at: " << newPosition.getY() << ", " << newPosition.getX() << '\n';
		}
	}

	void move(const Point& newPosition);
	virtual void update() = 0;
	virtual bool collision(Entity& entity) = 0;
};

#endif