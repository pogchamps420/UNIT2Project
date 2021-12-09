#include <iostream>
#include <vector>
#include "menu.h"
#include "menuelement.h"
#include "PD.h"
#include "Tise.h"
#include "eseries.h"
#include "componentmatch.h"
#include "potentialdivider.h"
#include "System.h"
#include "rafal.h"

int main()
{
    //intro title
    System::Clear();
    std::cout << "Welcome to our sandbox\n\Project by Tise Olayinka, Delilah Hague, Rafal Kalisz\nGroup 35\tELEC2645\n" << std::endl;
    System::Sleep(1);
    std::cout << "Press enter to start: ";
    while (std::cin.get() != '\n');

    //Display menu

    while (true)
    {
        System::Clear();

        std::vector<MenuItem> mainItems{};
        std::vector<MenuOption> mainOptions
        {
            MenuOption('T', "Tise's menu"),
            MenuOption('D', "Delilah's menu"),
            MenuOption('R', "Rafal's menu"),
            MenuOption('x', "Exit the application")
        };

        Menu mainMenu("Main Menu", mainOptions, mainItems);
        mainMenu.PrintMenu();
        char chosenOption = mainMenu.ChooseOption();

        T::Tise TMenu;

        switch (chosenOption)
        {
        
        case 'T':
            TMenu.TiseMenu();
            break;
        
        case 'R':
            rafal::Rafal();
            break;
        
        case 'x':
            goto break_main_while;
            break;
        }
    }
break_main_while:;


    

    
    

    //outro sequence
    std::cout << "\n\nThank you for using our Sandbox\n\Project by Tise Olayinka, Delilah Hague, Rafal Kalisz\nGroup 35\tELEC2645" << std::endl;
    System::Sleep(1);
    std::cout << "\n\tBye <3";
    while (std::cin.get() != '\n');
}
