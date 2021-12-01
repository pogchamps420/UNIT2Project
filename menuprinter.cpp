#include "menuprinter.h"

#include <iostream>
#include <string>
#include <set>

//Definitions for the MenuElement class

MenuElement::MenuElement() //Default constructor
{
	this->name = "";
	this->description = "";
}
MenuElement::MenuElement(std::string name, std::string description) 
{
	this->name = name;
	this->description = description;
}

//Definitions for the MenuItem class

MenuItem::MenuItem() : MenuElement() {} //Default constructor
//Constructor overloads

MenuItem::MenuItem(std::string name, std::string description) : MenuElement(name, description) { this->value = ""; }
MenuItem::MenuItem(std::string name, std::string description, std::string value) : MenuElement(name, description) { this->value = value; }
MenuItem::MenuItem(std::string name, std::string description, int value) : MenuItem(name, description) { this->value = std::to_string(value); }


//Definitions for the MenuOption class

MenuOption::MenuOption() : MenuElement() { this->visibility = true; this->identifier = '\0'; }
MenuOption::MenuOption(std::string name, std::string description, char identifier) : MenuElement(name, description) { this->visibility = true; this->identifier = identifier; }
MenuOption::MenuOption(std::string name, std::string description, char identifier, bool visibility) : MenuElement(name, description) { this->visibility = visibility; this->identifier = identifier; }
void MenuOption::ChangeVisibility(bool visibility) { this->visibility = visibility; }

//Definitions for the Menu class

Menu::Menu() {};
Menu::Menu(std::string name, std::vector<MenuOption> options, std::vector<MenuItem> items)
{
	_name = name;

	for (MenuOption currentOption : options)
	{
		_options[currentOption.name] = currentOption;
		_availableOptions.insert(currentOption.name);
	}
	for (MenuItem currentItem : items)
	{
		_items[currentItem.name] = currentItem;
	}
}

void Menu::PrintMenu()
{
	std::cout << "-----------------------\n";
	std::cout << _name << '\n';
	std::cout << "-----------------------\n";

	std::map<std::string, MenuItem>::iterator itemIterator = _items.begin();
	while(itemIterator != _items.end())
	{
		std::cout << itemIterator->second.description << ": " << itemIterator->second.value << '\n';
		itemIterator++;
	}
	std::cout << "-----------------------\n";

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
	if (_availableOptions.find(inputString) == _availableOptions.end())
	{
		std::cout << "ERROR: option '"<< inputString <<"' not available\n";
		return ChooseOption();
	}
	else
		return _options[inputString].identifier;
}

void Menu::ChangeOptionAvailability(std::string optionName, bool availability)
{
}
