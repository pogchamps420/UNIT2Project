#include <iostream>
#include <vector>
#include <algorithm>
#include "menu.h"
#include "menuelement.h"
#include "PD.h"
#include "Tise.h"
#include "buckboost.h"
#include "variables.h"
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
        MenuOption('1', "Option A"),
        MenuOption('2', "Option B"),
        MenuOption('3', "BBC"),
        MenuOption('0', "Tise")
    };

    //Define items to be displayed, value can be either a string or an int
    std::vector<MenuItem> mainMenuItems
    {
        MenuItem('a', "Item one", 69),
        MenuItem('b', "Item two", 420)
    };
                                                                                                                                                                                                                                                                                                
    //Initialise menu
    Menu mainMenu("Main menu", mainMenuOptions, mainMenuItems);
    
    //Display menu
    mainMenu.PrintMenu();

    char chosenOption = mainMenu.ChooseOption();
    T::Tise TMenu;
    bbc::BUCKBOOST BMenu;

    switch (chosenOption)
    {
        case '0':
            TMenu.TiseMenu();
            break;
        case '3':
            BMenu.InitMenu();
            break;
        default:
            break;
    }
    

    //Adhoc fix for debug window closing immediately after entering input
    char temp;
    std::cin >> temp;
}