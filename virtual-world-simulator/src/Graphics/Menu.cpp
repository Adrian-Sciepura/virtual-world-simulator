#include "Menu.h"

Menu::Menu(GraphicsEngine* graphicsEngine, std::string title) :
	graphicsEngine{ graphicsEngine }, font{ AssetManager::getAssetManager()->getAsset("font") }, 
	title{ title }, titleLength{ (int)title.size() * 8 }, cursorPosition{ 0 }, itemsLength{ 0 }
{
}

Menu::~Menu()
{

}

void Menu::addItem(const MenuItem& item)
{
	items.push_back(item);
	itemsLength = items.size() * 16;

	for (int i = 0; i < items.size(); i++)
		itemsLength += items[i].text.size() * 8;
}

void Menu::draw(int availableMenuOptions, std::vector<std::string>& values)
{
	graphicsEngine->clearBuffer();
	graphicsEngine->drawText(font, title, { (graphicsEngine->getScreenWidth() - titleLength) / 2, 80 }, Color::GREEN);

	int length = 0;
	int screenWidth = graphicsEngine->getScreenWidth();
	int currentEntry = 0;
	Color color;

	for (int i = 0; i < items.size(); i++)
	{
		if (i == cursorPosition)
			color = Color::RED;
		else
			if (i > availableMenuOptions)
				color = Color::GRAY;
			else
				color = Color::WHITE;

		graphicsEngine->drawText(font, items[i].text, { ( screenWidth - itemsLength) / 2 + length, 120 }, color);
		if (items[i].type == MenuItem::ItemType::ENTRY)
		{
			int pos = (values[currentEntry + 1].size() - items[i].text.size()) * 4;

			graphicsEngine->drawText(font, values[currentEntry + 1], { (screenWidth - itemsLength) / 2 + length - pos, 130 });
			currentEntry++;
		}


		length += items[i].text.size() * 8 + 16;
	}

	graphicsEngine->drawBuffer();
}

std::vector<std::string> Menu::open(int availableMenuOptions)
{
	cursorPosition = 0;
	std::vector<std::string> result;
	
	result.push_back("");
	for (int i = 0; i < items.size(); i++)
		if (items[i].type == MenuItem::ItemType::ENTRY)
			result.push_back("");
	
	bool quit = false;
	int currentEntry = 0;
	int key = NULL;
	draw(availableMenuOptions, result);

	while (!quit)
	{
		key = _getch();

		switch (key)
		{
			case KeyCodes::LEFT:
			{
				if (cursorPosition > 0)
				{
					if (items[cursorPosition].type == MenuItem::ItemType::ENTRY)
						currentEntry--;

					cursorPosition--;
				}

				break;
			}
			case KeyCodes::RIGHT:
			{
				if (cursorPosition < availableMenuOptions)
				{
					cursorPosition++;
					if (items[cursorPosition].type == MenuItem::ItemType::ENTRY)
						currentEntry++;
				}

				break;
			}
			case KeyCodes::ENTER:
			{
				if (items[cursorPosition].type == MenuItem::ItemType::ENTRY)
					break;
				
				quit = true;
				result[0] = std::to_string(cursorPosition);
				break;
			}
			default:
			{
				if (items[cursorPosition].type != MenuItem::ItemType::ENTRY)
					break;

				handleInput(result[currentEntry+1], key);
				break;
			}
		}

		draw(availableMenuOptions, result);
	}

	return result;
}

void Menu::handleInput(std::string& current, int key)
{
	if (key == KeyCodes::BACKSPACE)
	{
		if(current.size() > 0)
			current.pop_back();
	}
	else if (key >= KeyCodes::SPACE && key <= KeyCodes::GRAVE)
	{
		current.push_back((char)key);
	}
}