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
	void ChangeOptionAvailability(char identifier, bool availability);
	void ChangeOptionDescription(char identifier, std::string newDescription);

	void ChangeItemValue(char identifier, std::string newValue);
	void ChangeItemValue(char identifier, double newValue);
	void ChangeItemDescription(char identifier, std::string newDescription);

private:
	//Menu name
	std::string _name;

	//Vector storing all menu options
	std::map<char, MenuOption> _options;
	//Vector storing all menu items
	std::map<char, MenuItem> _items;

	//Chose to use std::unordered_set instead of std::set, as the operation time complexity is O(1) instead of O(log(n))
	//Set containing all available user choices
	std::unordered_set<char> _availableOptions;
};

#endif