#include <iostream>
#include <vector>
#include "menu.h"
#include "menuelement.h"
#include "eseries.h"
#include "componentmatch.h"



int main()
{
    
    npv::Eseries E6(6);
    std::cout << E6.FindNearest(0.5).first << ' ' << E6.FindNearest(0.5).second << '\n';
    std::cout << E6.FindNearest(3.3).first << ' ' << E6.FindNearest(3.3).second << '\n';
    std::cout << E6.FindNearest(4.0).first << ' ' << E6.FindNearest(4.0).second << '\n';
    std::cout << E6.FindNearest(9.5).first << ' ' << E6.FindNearest(9.5).second << '\n';
    std::cout << E6.FindNearest(10).first << ' ' << E6.FindNearest(10).second << '\n';
    std::cout << E6.FindNearest(950).first << ' ' << E6.FindNearest(950).second << '\n';

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

}