#include <iostream>
#include <vector>
#include "menu.h"
#include "menuelement.h"
#include "PD.h"
#include "Tise.h"
#include "eseries.h"
#include "componentmatch.h"
#include "potentialdivider.h"

int main()
{
    //intro title
    System::Clear();
    std::cout << "Welcome to our sandbox\n\Project by Tise Olayinka, Delilah Hague, Rafal Kalisz\nGroup 35\tELEC2645\n" << std::endl;
    System::Sleep(1);
    std::cout << "Press enter to start: ";
    while (std::cin.get() != '\n');

    //Display menu
    T::Tise TMenu;
    TMenu.TiseMenu();

    //outro sequence
    std::cout << "\n\nThank you for using our Sandbox\n\Project by Tise Olayinka, Delilah Hague, Rafal Kalisz\nGroup 35\tELEC2645" << std::endl;
    System::Sleep(1);
    std::cout << "\n\tBye <3";
    while (std::cin.get() != '\n');
}
