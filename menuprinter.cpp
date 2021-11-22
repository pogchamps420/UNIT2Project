#include "menuprinter.h"

#include <iostream>
#include <string>
#include <set>

MenuOption::MenuOption(char identifier, std::string text)
{
	this->identifier = identifier;
	this->text = text;
}

MenuItem::MenuItem() {};
MenuItem::MenuItem(std::string name, std::string description, std::string value)
{
	this->name = name;
	this->description = description;
	this->value = value;
}
MenuItem::MenuItem(std::string name, std::string description, int value)
{
	this->name = name;
	this->description = description;
	this->value = std::to_string(value);
}

Menu::Menu() {};
Menu::Menu(std::string name, std::vector<MenuOption> options, std::vector<MenuItem> items)
{
	_name = name;

	for (MenuOption currentOption : options)
	{
		_options.push_back(currentOption);
		_availableOptions.insert(currentOption.identifier);
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

	//My dumb ass does not know how to iterate over map values, help
	std::map<std::string, MenuItem>::iterator itemIterator = _items.begin(); //Dumb iterator
	while(itemIterator != _items.end())
	{
		std::cout << itemIterator->second.description << ": " << itemIterator->second.value << '\n';
		itemIterator++;
	}
	std::cout << "-----------------------\n";
	for (MenuOption displayOption: _options)
	{
		std::cout << displayOption.identifier << ": " << displayOption.text << '\n';
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

void Menu::AddOverwriteItem(MenuItem item) { _items[item.name] = item; }
MenuItem Menu::GetItem(std::string name) { return _items[name]; }
void Menu::ChangeItemValue(std::string name, int newValue) { _items[name] = MenuItem(name, _items[name].description, newValue); }
void Menu::ChangeItemValue(std::string name, std::string newValue) { _items[name] = MenuItem(name, _items[name].description, newValue); }