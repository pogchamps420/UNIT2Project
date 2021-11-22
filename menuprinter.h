#ifndef MENUPRINTER_H
#define MENUPRINTER_H

#include <unordered_set>
#include <map>
#include <vector>
#include <string>

struct MenuOption
{	
	/*
	Example menu option:

	a: option a

	identifier = 'a', text = "option a"
	*/

	MenuOption(char identifier, std::string text);

	//Character used to choose the item
	char identifier; 

	//Text displayed next to identifier
	std::string text;
};

struct MenuItem
{
	/*
	Example menu item:

	item x: value

	name = "item x", value = "value"
	*/
	//Default constructor
	MenuItem();
	MenuItem(std::string name, std::string description, std::string value);
	//Constructor overload for handling integers as values
	MenuItem(std::string name, std::string description, int value);

	std::string name;
	std::string description;
	std::string value;
};

class Menu
{
public:
	Menu();
	Menu(std::string name, std::vector<MenuOption> options, std::vector<MenuItem> items);
	
	//Method printing the menu layout to the console
	void PrintMenu();
	//Method asking the user to choose a menu item and returning its identifier if it's among available options
	char GetInput();
	//Method adding or changing a menu item
	void AddOverwriteItem(MenuItem item);
	//Method getting a menu item
	MenuItem GetItem(std::string name);
	//Method changing a menu item's value to an int
	void ChangeItemValue(std::string name, int newValue);
	//Method changing a menu item's value to a string
	void ChangeItemValue(std::string name, std::string newValue);

private:
	//Menu name
	std::string _name;

	//Vector storing all menu options
	std::vector<MenuOption> _options;
	//Vector storing all menu items
	std::map<std::string, MenuItem> _items;

	//Chose to use std::unordered_set instead of std::set, as the operation time complexity is O(1) instead of O(log(n))
	//Set containing all available user choices
	std::unordered_set<char> _availableOptions;
};

#endif