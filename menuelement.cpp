#include "menuelement.h"

//Definitions for the MenuElement class

MenuElement::MenuElement() //Default constructor
{
	this->name = "";
	this->description = "";
}
MenuElement::MenuElement(std::string name, std::string description)
{
	this->name = name;
	this->description = description;
}

//Definitions for the MenuItem class

MenuItem::MenuItem() : MenuElement() //Default constructor
{
	this->value = "";
}
MenuItem::MenuItem(std::string name, std::string description) : MenuElement(name, description)
{
	this->value = "";
}
MenuItem::MenuItem(std::string name, std::string description, std::string value) : MenuElement(name, description)
{
	this->value = value;
}
MenuItem::MenuItem(std::string name, std::string description, double value) : MenuItem(name, description)
{
	this->value = std::to_string(value);
}


//Definitions for the MenuOption class

MenuOption::MenuOption() : MenuElement() //Default constructor
{
	this->visibility = true;
	this->identifier = '\0';
}
MenuOption::MenuOption(std::string name, std::string description, char identifier) : MenuElement(name, description)
{
	this->visibility = true;
	this->identifier = identifier;
}
MenuOption::MenuOption(std::string name, std::string description, char identifier, bool visibility) : MenuElement(name, description)
{
	this->visibility = visibility;
	this->identifier = identifier;
}
void MenuOption::ChangeVisibility(bool visibility)
{
	this->visibility = visibility;
}