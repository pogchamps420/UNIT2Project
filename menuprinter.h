#ifndef MENUPRINTER_H
#define MENUPRINTER_H

#include <unordered_set>
#include <vector>
#include <string>

class MenuItem
{

//All variables are kept public for ease of access
public:
	
	/*
	Example menu item:

	a: option a

	identifier = 'a', text = "option a"
	*/

	MenuItem(char identifier, std::string text);

	//Character used to choose the item
	char identifier; 

	//Text displayed next to identifier
	std::string text;

};

class Menu
{
public:

	Menu();
	Menu(std::string name, std::vector<MenuItem> items);
	
	//Method printing the menu layout to the console
	void PrintMenu();
	
	//Method asking the user to choose a menu item and returning its identifier if it's among available options
	char GetInput();

private:

	//Menu name
	std::string _name;

	//Vector storing all menu items
	std::vector<MenuItem> _items;

	//Chose to use std::unordered_set instead of std::set, as the operation time complexity is O(1) instead of O(log(n))
	//Set containing all available user choices
	std::unordered_set<char> _availableItems;

};

#endif