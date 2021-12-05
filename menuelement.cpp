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
	this->value = "";
}
MenuItem::MenuItem(char identifier, std::string description) : MenuElement(identifier, description)
{
	this->value = "";
}
MenuItem::MenuItem(char identifier, std::string description, std::string value) : MenuElement(identifier, description)
{
	this->value = value;
}
MenuItem::MenuItem(char identifier, std::string description, double value) : MenuItem(identifier, description)
{
	this->value = std::to_string(value);
}
void MenuItem::ChangeValue(std::string newValue)
{
	this->value = newValue;
}
void MenuItem::ChangeValue(double newValue)
{
	this->value = std::to_string(newValue);
}

//Definitions for the MenuOption class

MenuOption::MenuOption() : MenuElement() //Default constructor
{
	this->visibility = true;
	this->identifier = '\0';
}
MenuOption::MenuOption(char identifier, std::string description) : MenuElement(identifier, description)
{
	this->visibility = true;
	this->identifier = identifier;
}
MenuOption::MenuOption(char identifier, std::string description, bool visibility) : MenuElement(identifier, description)
{
	this->visibility = visibility;
	this->identifier = identifier;
}
void MenuOption::ChangeVisibility(bool visibility)
{
	this->visibility = visibility;
}