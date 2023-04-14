#ifndef ANIMAL_H
#define ANIMAL_H

#include "../Entity.h"

class Animal : public Entity
{
public:
	Animal(BMPFile* texture, World* world, Point position, char symbol, int strength, int priority);
	~Animal();

	template <class T>
	void breed(T& animal)
	{
		static_assert(std::is_base_of<Animal, T>::value, "T must be derived from Animal");

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
				if (j < 0 || j > world->getWidth() - 1 ||
					(i == currentX && j == currentY))
					continue;
				
				if (map[i][j] == nullptr || map[i][j]->getPriority() == 0)
					freeFields.push_back(Point(i, j));
			}
		}

		if (freeFields.size() > 0)
		{
			Point newPosition = freeFields[Utility::random(0, freeFields.size() - 1)];
			T* newAnimal = new T(world, newPosition);
			Entity* entity = map[newPosition.x][newPosition.y];
			if (entity != nullptr)
				entity->kill();
			
			map[newPosition.x][newPosition.y] = newAnimal;
		}
	}

	void move(const Point& newPosition);
	virtual void update();
	virtual bool collision(Entity& entity);
};

#endif