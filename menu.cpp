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
		_options[currentOption.name] = currentOption;
		if(currentOption.visibility)
			_availableOptions.insert(currentOption.name);
	}
	for (MenuItem currentItem : items)
	{
		_items[currentItem.name] = currentItem;
	}
}

void Menu::PrintMenu()
{
	//Displaying the menu's name

	std::cout << "-----------------------\n";
	std::cout << _name << '\n';
	std::cout << "-----------------------\n";
	
	//Displaying all items

	std::map<std::string, MenuItem>::iterator itemIterator = _items.begin();
	while(itemIterator != _items.end())
	{
		std::cout << itemIterator->second.name << " - " << itemIterator->second.description << ": " << itemIterator->second.value << '\n';
		itemIterator++;
	}
	std::cout << "-----------------------\n";

	//Displaying all visible options

	std::map<std::string, MenuOption>::iterator optionIterator = _options.begin();
	while(optionIterator != _options.end())
	{
		if(optionIterator->second.visibility)
			std::cout << optionIterator->second.name << ": " << optionIterator->second.description << '\n';
		optionIterator++;
	}
	std::cout << "-----------------------\n";
}

char Menu::ChooseOption()
{
	std::string inputString;
	std::cout << "Choose an option from above list: ";
	std::cin >> inputString;

	//Checking if the option is selectable
	if (_availableOptions.find(inputString) == _availableOptions.end())
	{
		std::cout << "ERROR: option '"<< inputString <<"' not available\n";

		//Prompt the user to enter the option again
		return ChooseOption();
	}
	else
		return _options[inputString].identifier;
}

void Menu::ChangeOptionAvailability(std::string optionName, bool availability)
{
	if (_options[optionName].visibility != availability)
	{
		_options[optionName].ChangeVisibility(availability);

		if (availability)
			_availableOptions.erase(optionName);
		else
			_availableOptions.insert(optionName);
	}
}

void Menu::ChangeItemDescription(std::string name, std::string newDescription)
{
	_items[name].ChangeDescription(newDescription);
}

void Menu::ChangeItemValue(std::string name, std::string newValue)
{
	_items[name].ChangeValue(newValue);
}

void Menu::ChangeItemValue(std::string name, int newValue)
{
	_items[name].ChangeValue(std::to_string(newValue));
}

void Menu::ChangeOptionDescription(std::string name, std::string newDescription)
{
	_options[name].ChangeDescription(newDescription);
}
