#include "menuelement.h"

//Definitions for the MenuElement class

MenuElement::MenuElement() //Default constructor
{
	this->identifier = ' ';
	this->description = "";
}
MenuElement::MenuElement(char identifier, std::string description)
{
	this->identifier = identifier;
	this->description = description;
}
void MenuElement::ChangeDescription(std::string newDescription)
{
	description = newDescription;
}

//Definitions for the MenuItem class

MenuItem::MenuItem() : MenuElement() //Default constructor
{
	this->_value = 0.0;
}
MenuItem::MenuItem(char identifier, std::string description) : MenuElement(identifier, description)
{
	this->_value = 0.0;
}
MenuItem::MenuItem(char identifier, std::string description, double value) : MenuItem(identifier, description)
{
	this->_value = value;
}
void MenuItem::ChangeValue(double newValue)
{
	this->_value = newValue;
}
void MenuItem::ChangeValueVec(std::vector <int> newVec)
{
	this->_vecvalue = newVec;
}
float MenuItem::GetValue()
{
	return _value;
}

//Definitions for the MenuOption class

MenuOption::MenuOption() : MenuElement() //Default constructor
{
	this->_visibility = true;
	this->identifier = '\0';
}
MenuOption::MenuOption(char identifier, std::string description) : MenuElement(identifier, description)
{
	this->_visibility = true;
	this->identifier = identifier;
}
MenuOption::MenuOption(char identifier, std::string description, bool visibility) : MenuElement(identifier, description)
{
	this->_visibility = visibility;
	this->identifier = identifier;
}
void MenuOption::ChangeVisibility(bool visibility)
{
	this->_visibility = visibility;
}
bool MenuOption::GetVisibility()
{
	return _visibility;
}