#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <conio.h>

#include "GraphicsEngine.h"
#include "AssetManager.h"
#include "MenuItem.h"
#include "../Common/KeyCodes.h"

class Menu
{
private:
	GraphicsEngine* graphicsEngine;
	BMPFile* font;
	std::string title;
	int titleLength;
	int cursorPosition;
	std::vector<MenuItem> items;
	int itemsLength;

	void draw(int availableMenuOptions, std::vector<std::string>& values);
	void handleInput(std::string& current, int key);

public:
	Menu(GraphicsEngine* graphicsEngine, std::string title);
	~Menu();

	void addItem(const MenuItem& item);

	//returns vector of strings, first is the index of the selected option, others are the entries
	std::vector<std::string> open(int availableMenuOptions);
};

#endif