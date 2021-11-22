#include "menuprinter.h"

#include <iostream>
#include <string>
#include <set>

MenuOption::MenuOption(char identifier, std::string text) { this->identifier = identifier; this->text = text; }

Menu::Menu() {};

Menu::Menu(std::string name, std::vector<MenuOption> items)
{
	_name = name;

	for (MenuOption currentItem : items)
	{
		_options.push_back(currentItem);
		_availableOptions.insert(currentItem.identifier);
	}
}

void Menu::PrintMenu()
{
	std::cout << "-----------------------\n";
	std::cout << _name << '\n';
	std::cout << "-----------------------\n";
	for (MenuOption displayItem : _options)
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
	if (_availableOptions.find(inputChar) == _availableOptions.end())
	{
		std::cout << "ERROR: option '"<< inputChar <<"' not available\n";
		return GetInput();
	}
	else
		return inputChar;
}
