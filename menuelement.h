#pragma once
#ifndef MENUELEMENT_H
#define MENUELEMENT_H

#include <string>

//Parent class for menu items and options
class MenuElement
{
public:
	char identifier;
	std::string description;

	MenuElement();
	MenuElement(char identifier, std::string description);

	void ChangeDescription(std::string newDescription);
};

//Class used to contain data displayable in a menu
class MenuItem : public MenuElement
{
public:
	//Value displayed next to the descripion

	MenuItem();
	MenuItem(char identifier, std::string description);
	MenuItem(char identifier, std::string description, double value);

	void ChangeValue(std::string newValue);
	void ChangeValue(double newValue);
	float GetValue();

private:
	double _value;
};

//Class used to contain information for selectable options in a menu
class MenuOption : public MenuElement
{
public:
	//Determines whether the option is to be displayed and selectable 
		//Unique char identifier used to refer to the option

	MenuOption();
	MenuOption(char identifier, std::string description);
	MenuOption(char identifier, std::string description, bool visibility);
	void ChangeVisibility(bool visibility);
	bool GetVisibility();

private:
	bool _visibility;
};

#endif

