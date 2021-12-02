#ifndef MENUPRINTER_H
#define MENUPRINTER_H

#include <unordered_set>
#include <map>
#include <vector>
#include <string>

//Parent class for menu items and options
class MenuElement
{
public:
	std::string name;
	std::string description;

	MenuElement();
	MenuElement(std::string name, std::string description);
};

//Class used to contain data displayable in a menu
class MenuItem : public MenuElement
{
public:
	//Value displayed next to the descripion
	std::string value;

	MenuItem();
	MenuItem(std::string name, std::string description);
	MenuItem(std::string name, std::string description, std::string value);
	MenuItem(std::string name, std::string description, int value);
};

//Class used to contain information for selectable options in a menu
class MenuOption : public MenuElement
{
public:
	//Determines whether the option is to be displayed and selectable 
	bool visibility;
	//Unique char identifier used to refer to the option
	char identifier;
	
	MenuOption();
	MenuOption(std::string name, std::string description, char identifier);
	MenuOption(std::string name, std::string description, char identifier,  bool visibility);

	void ChangeVisibility(bool visibility);
};

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