#ifndef MENU_H
#define MENU_H

#include "menuelement.h"

#include <string>
#include <map>
#include <vector>
#include <unordered_set>

class Menu
{
public:
	Menu();
	Menu(std::string name, std::vector<MenuOption> options, std::vector<MenuItem> items);

	//Method printing the menu layout to the console
	void PrintMenu();
	//Method asking the user to choose a menu item and returning its identifier if it's among available options
	char ChooseOption();
	//Method changing the visibility of the option in the menu and its selectability
	void ChangeOptionAvailability(std::string optionName, bool availability);
	
	// Tise added stuff
	// Edit items in menu
	void EditItems(std::string itemname, double value, std::vector<MenuItem> &Items);

private:
	//Menu name
	std::string _name;

	//Vector storing all menu options
	std::map<std::string, MenuOption> _options;
	//Vector storing all menu items
	std::map<std::string, MenuItem> _items;

	//Chose to use std::unordered_set instead of std::set, as the operation time complexity is O(1) instead of O(log(n))
	//Set containing all available user choices
	std::unordered_set<std::string> _availableOptions;
};

#endif