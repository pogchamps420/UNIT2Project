#include <iostream>
#include <vector>
#include "menuprinter.h"



int main()
{
    //Example usage of menuprinter

    //Define user-selectable options
    std::vector<MenuOption> mainMenuOptions
    {
        MenuOption("O1", "Option A", 'a'),
        MenuOption("O2", "Option B", 'b'),
        MenuOption("O3", "Option C", 'c')
    };

    //Define items to be displayed, value can be either a string or an int
    std::vector<MenuItem> mainMenuItems
    {
        MenuItem("i1", "Item one", "string value"),
        MenuItem("i2", "Item two", 420)
    };

    //Initialise menu
    Menu mainMenu("Main menu", mainMenuOptions, mainMenuItems);

    //Display menu
    mainMenu.PrintMenu();

    char chosenOption = mainMenu.ChooseOption();
    switch (chosenOption)
    {
    default:
        break;
    }

    //Adhoc fix for debug window closing immediately after entering input
    char temp;
    std::cin >> temp;
}