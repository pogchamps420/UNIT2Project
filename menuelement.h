#pragma once
#ifndef MENUELEMENT_H
#define MENUELEMENT_H

#include <string>

//Parent class for menu items and options
class MenuElement
{
public:
	std::string name;
	std::string description;

	MenuElement();
	MenuElement(std::string name, std::string description);

	void ChangeDescription(std::string newDescription);
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
	MenuItem(std::string name, std::string description, double value);

	void ChangeValue(std::string newValue);
	void ChangeValue(double newValue);
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
	MenuOption(std::string name, std::string description, char identifier, bool visibility);

	void ChangeVisibility(bool visibility);
};

#endif
