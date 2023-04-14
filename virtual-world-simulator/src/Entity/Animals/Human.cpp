#include "Human.h"

Human::Human(World* world, Point position) :
    Animal{ AssetManager::getAssetManager()->getAsset("human"), world, position, 'H', 5, 4 }
{
}

void Human::update()
{
    int mapWidth = this->world->getWidth();
    int mapHeight = this->world->getHeight();
    bool correctKey = false;
    int key = NULL;

    while (!correctKey)
    {
        key = _getch();
        switch(key)
        {
            case keyCodes::UP:
            {
                if (this->position.x == 0)
                    continue;

                this->move({ this->position.x - 1, this->position.y });
                correctKey = true;
                break;
            }
            case keyCodes::DOWN:
            {
                if(this->position.x == mapHeight - 1)
					continue;

                this->move({ this->position.x + 1, this->position.y });
                correctKey = true;
                break;
            }
            case keyCodes::LEFT:
            {
                if (this->position.y == 0)
					continue;

                this->move({ this->position.x, this->position.y - 1 });
                correctKey = true;
                break;
            }
            case keyCodes::RIGHT:
            {
                if (this->position.y == mapWidth - 1)
                    continue;

                this->move({ this->position.x, this->position.y + 1 });
                correctKey = true;
                break;
            }
        }
    }
}