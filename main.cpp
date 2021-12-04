#include <iostream>
#include <vector>
#include "menu.h"
#include "menuelement.h"
#include "formula.h"
#include "module.h"
#include "user.h"
#include "initiate.h"
namespace T
{
    void TiseTestingGround();
}

int main()
{
    //Example usage of menuprinter

    //Define user-selectable options
    std::vector<MenuOption> mainMenuOptions
    {
        MenuOption("O1", "Option A", 'a'),
        MenuOption("O2", "Option B", 'b'),
        MenuOption("O3", "Option C", 'c'),
        MenuOption("0", "Tise", 'T')
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
        case 'T':
            T::TiseTestingGround();
            break;
    default:
        break;
    }

    //Adhoc fix for debug window closing immediately after entering input
    char temp;
    std::cin >> temp;
}

void T::TiseTestingGround()
{
    std::cout << "\n\nwelcome\nok\nlets do this\n\n" << std::endl;


    /*          FOR LATER
    //ypyoyoyoyo
    std::cout << "welcome\nok\nlets do this\n\n" << std::endl;

    //set up test proflie
    Initiate setup;
    setup.set_profile(0);
     //get all the stuff from the profile into main
    User tester = setup.get_user();

    //tests
    std::cout << tester.get_surname() << std::endl;
    std::list<std::string> testmods = tester.get_modules();
    for (std::string mod : testmods)
    {
        std::cout << mod << std::endl;
        // trying to show formulas for specific modules ***********************************************
        /*
        Module mmm;
        std::list<std::string> Formulas = tester.get_formulas();
        for (std::string Formula : Formulas)
        {
            std::cout << mod << "\n :	" << Formula << std::endl;
        }
        //
    }


    //do stuff
    //actual calculator
    */
}