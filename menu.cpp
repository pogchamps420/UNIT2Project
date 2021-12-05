#include "menu.h"
#include <iostream>
#include <string>
#include <set>

//Definitions for the Menu class

Menu::Menu() //Default constructor
{
	_name = "";
}
Menu::Menu(std::string name, std::vector<MenuOption> options, std::vector<MenuItem> items)
{
	_name = name;

	for (MenuOption currentOption : options)
	{
		_options[currentOption.identifier] = currentOption;
		if (currentOption.GetVisibility())
			_availableOptions.insert(currentOption.identifier);
	}
	for (MenuItem currentItem : items)
	{
		_items[currentItem.identifier] = currentItem;
	}
}

void Menu::PrintMenu()
{
	//Displaying the menu's name

	std::cout << "-----------------------\n";
	std::cout << _name << '\n';
	std::cout << "-----------------------\n";

	//Displaying all items

	std::map<char, MenuItem>::iterator itemIterator = _items.begin();
	while (itemIterator != _items.end())
	{
		std::cout << itemIterator->second.identifier << " - " << itemIterator->second.description << ": " << itemIterator->second.GetValue() << '\n';
		itemIterator++;
	}
	std::cout << "-----------------------\n";

	//Displaying all visible options

	std::map<char, MenuOption>::iterator optionIterator = _options.begin();
	while (optionIterator != _options.end())
	{
		if (optionIterator->second.GetVisibility())
			std::cout << optionIterator->second.identifier << ": " << optionIterator->second.description << '\n';
		optionIterator++;
	}
	std::cout << "-----------------------\n";
}

char Menu::ChooseOption()
{
	char inputChar;
	std::cout << "Choose an option from above list: ";
	std::cin >> inputChar;

	//Checking if the option is selectable
	if (_availableOptions.find(inputChar) == _availableOptions.end())
	{
		std::cout << "ERROR: option '" << inputChar << "' not available\n";

		//Prompt the user to enter the option again
		return ChooseOption();
	}
	else
		return _options[inputChar].identifier;
}

void Menu::ChangeOptionAvailability(char identifier, bool availability)
{
	if (_options[identifier].GetVisibility() != availability)
	{
		_options[identifier].ChangeVisibility(availability);

		if (availability)
			_availableOptions.erase(identifier);
		else
			_availableOptions.insert(identifier);
	}
}

void Menu::ChangeItemDescription(char identifier, std::string newDescription)
{
	_items[identifier].ChangeDescription(newDescription);
}

void Menu::ChangeItemValue(char identifier, double newValue)
{
	_items[identifier].ChangeValue(newValue);
}

void Menu::ChangeOptionDescription(char identifier, std::string newDescription)
{
	_options[identifier].ChangeDescription(newDescription);
}

double Menu::GetItemValue(char identifier)
{
	return _items[identifier].GetValue();
}