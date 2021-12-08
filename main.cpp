#include <iostream>
#include <vector>
#include "menu.h"
#include "menuelement.h"
#include "PD.h"
#include "Tise.h"
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
        MenuOption('2', "Option A"),
        MenuOption('3', "Option B"),
        MenuOption('4', "Option C"),
        MenuOption('0', "Exit"),
        MenuOption('1', "Tise")
    };

    //Define items to be displayed, value can be either a string or an int
    std::vector<MenuItem> mainMenuItems
    {
        MenuItem('a', "Item one", 69),
        MenuItem('b', "Item two", 420)
    };

    //Initialise menu
    Menu mainMenu("Main menu", mainMenuOptions, mainMenuItems);


    // Loop system
    bool loop = true;
    while (loop)
    {
        //Display menu
        mainMenu.PrintMenu();

        char chosenOption = mainMenu.ChooseOption();
        T::Tise TMenu;
        switch (chosenOption)
        {
        case '0':
            loop = false;
            break;
        case '1':
            TMenu.TiseMenu();
            break;
        default:
            break;
        }
    }
}