#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>

struct MenuItem
{
	enum class ItemType
	{
		TEXT,
		ENTRY
	};

	ItemType type;
	std::string text;

	MenuItem(ItemType type, std::string text);
};

#endif