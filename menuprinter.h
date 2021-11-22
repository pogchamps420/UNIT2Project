#ifndef MENUPRINTER_H
#define MENUPRINTER_H

#include <unordered_set>
#include <vector>
#include <string>

class MenuOption
{
//All variables are kept public for ease of access
public:
	
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

class Menu
{
public:

	Menu();
	Menu(std::string name, std::vector<MenuOption> options);
	
	//Method printing the menu layout to the console
	void PrintMenu();
	
	//Method asking the user to choose a menu item and returning its identifier if it's among available options
	char GetInput();

private:

	//Menu name
	std::string _name;

	//Vector storing all menu options
	std::vector<MenuOption> _options;

	//Chose to use std::unordered_set instead of std::set, as the operation time complexity is O(1) instead of O(log(n))
	//Set containing all available user choices
	std::unordered_set<char> _availableOptions;

};

#endif