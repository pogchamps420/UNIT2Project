#include "menuprinter.h"

#include <iostream>
#include <string>
#include <set>

MenuItem::MenuItem(char identifier, std::string text) { this->identifier = identifier; this->text = text; }

Menu::Menu() {};

Menu::Menu(std::string name, std::vector<MenuItem> items)
{
	_name = name;

	for (MenuItem currentItem : items)
	{
		_items.push_back(currentItem);
		_availableItems.insert(currentItem.identifier);
	}
}

void Menu::PrintMenu()
{
	std::cout << "-----------------------\n";
	std::cout << _name << '\n';
	std::cout << "-----------------------\n";
	for (MenuItem displayItem : _items)
	{
		std::cout << displayItem.identifier << ": " << displayItem.text << '\n';
	}
	std::cout << "-----------------------\n";
}

char Menu::GetInput()
{
	char inputChar;
	std::cout << "Choose an option from above list: ";
	std::cin >> inputChar;
	if (_availableItems.find(inputChar) == _availableItems.end())
	{
		std::cout << "ERROR: option '"<< inputChar <<"' not available\n";
		return GetInput();
	}
	else
		return inputChar;
}
