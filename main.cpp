#include <iostream>
#include <vector>
#include "menu.h"
#include "menuelement.h"
#include "formula.h"
#include "module.h"
#include "user.h"
#include "initiate.h"
#include "PD.h"
namespace T
{
    void TiseTestingGround();
    void PowerDissipation(T::PD PDiss, Menu PDMenu);
    Menu ChangeValues(PD Pdiss, Menu PDMenu);
    Menu PDISS(PD Pdiss, Menu Menu);
    Menu PS(PD PDiss, Menu PDMenu);
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

    std::vector<MenuOption> TMenuOptions
    {
        MenuOption("1", "Power Dissipation Calculator", 'p'),
        MenuOption("2", "Option B", 'b'),
        MenuOption("3", "Option C", 'c'),
        MenuOption("x", "Main Menu", 'x')
    };
    std::vector<MenuItem> TMenuItems
    {
        //MenuItem("i1", "Item one", "string value"),
        //MenuItem("i2", "Item two", 420)
    };

    Menu TMenu("Main menu", TMenuOptions, TMenuItems);
    TMenu.PrintMenu();

    // initialise stuff
    PD PDiss({ 0 }); 
    std::vector<MenuOption> PDMenuOptions
    {
        MenuOption("0", "Add Values", 'a'),
        MenuOption("1", "Clear Values", 'c'),
        MenuOption("1", "Switching Power Loss", 's'),
        MenuOption("2", "Conduction Power Loss", 'o'),
        MenuOption("3", "Average Power Dissipation", 'd'),
        MenuOption("x", "Back", 'x')
    };
    std::vector<MenuItem> PDMenuItems
    {
        MenuItem("1", "1: tri", 0),
        MenuItem("2", "2: tfv", 0),
        MenuItem("3", "3: tcon", 0),
        MenuItem("4", "4: trv", 0),
        MenuItem("5", "5: tfi", 0),
        MenuItem("6", "6: tcoff", 0),
        MenuItem("7", "7: Wcon", 0),
        MenuItem("8", "8: Wcoff", 0),
        MenuItem("9", "9: VDC", 0),
        MenuItem("10", "10: Io", 0),
        MenuItem("11", "11: fs", 0),
        MenuItem("12", "12: Ts", 0),
        MenuItem("13", "13: Von", 0),
        MenuItem("14", "14: Won", 0),
        MenuItem("15", "15: Ton", 0),
        MenuItem("16", "16: Ps", 0),
        MenuItem("17", "17: Pon", 0),
        MenuItem("18", "18: Pdis", 0),
    };
    Menu PDMenu("Power Dissipation menu", PDMenuOptions, PDMenuItems);

    char Option = TMenu.ChooseOption();
    switch (Option)
    {
    case 'p':
        T::PowerDissipation(PDiss, PDMenu);
        break;
    case 'x':
        T::TiseTestingGround();
        break;
    default:
        T::TiseTestingGround();
        break;
    }

    // to do later
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
void T::PowerDissipation(PD PDiss, Menu PDMenu)
{
    PDMenu.PrintMenu();

    char Option = PDMenu.ChooseOption();
    switch (Option)
    {
        case 'a':
            PDMenu = ChangeValues(PDiss, PDMenu);
            break;
        case 'c':
            PDiss.ClearValues();
            PowerDissipation(PDiss, PDMenu);
            break;
        case 's':
            PDMenu.ChangeItemValue(std::to_string(16), PDiss.CalcPs());
            std::cout << "\nSwitching Power Loss: " << PDiss.CalcPs() << "\n\n";
            PowerDissipation(PDiss, PDMenu);
            break;
        case 'o':
            PDMenu.ChangeItemValue(std::to_string(17), PDiss.CalcPon());
            std::cout << "\nConduction Power Loss: " << PDiss.CalcPon() << "\n";
            PowerDissipation(PDiss, PDMenu);
            break;
        case 'd':
            PDMenu.ChangeItemValue(std::to_string(18), PDiss.CalcPdis());
            std::cout << "\nDo you have Ps and Pon? y/n ";
            std::cout << "\nAverage Power Dissipation: " << PDiss.CalcPdis() << "\n";
            PowerDissipation(PDiss, PDMenu);
            break;
        case 'x':
            main();
            break;
        default:
            PowerDissipation(PDiss, PDMenu);
            break;
    }
}
Menu T::ChangeValues(PD Pdiss, Menu PDMenu)
{
    std::cout << "\nEnter the number of the value you want to add/change: ";
    int option;
    std::cin >> option;
    std::cout << "\nEnter the value you want to use: ";
    double value;
    std::cin >> value;
    Pdiss.Add(option, value);
    PDMenu.ChangeItemValue(std::to_string(option), value);

    std::cout << "\nItem changed.\n";
    PowerDissipation(Pdiss, PDMenu);
    return PDMenu;
}
Menu T::PDISS(PD PDiss, Menu PDMenu)
{
    std::vector<MenuOption> MenuOptions
    {
        MenuOption("a", "Enter Ps", 'a'),
        MenuOption("b", "Enter Pon", 'b'),
        MenuOption("c", "Calculate Ps", 'c'),
        MenuOption("d", "Calculate Pon", 'd'),
        MenuOption("e", "Calculate Pdiss", 'e'),
        MenuOption("x", "Back", 'x')
    };
    std::vector<MenuItem> MenuItems
    {
        MenuItem("a", "Ps", 0),
        MenuItem("b", "Pon", 0),
        MenuItem("c", "Pdiss", 0)
    };
    Menu Menu("Power Dissipation menu", MenuOptions, MenuItems);
    Menu.PrintMenu();
    char Option = Menu.ChooseOption();
    switch (Option)
    {
    case 'a':
        std::cout << "Ps: ";
        int Ps;
        std::cin >> Ps;
        MenuItems['a'].value = Ps;
        break;
    case 'b':
        std::cout << "Pon: ";
        int Pon;
        std::cin >> Pon;
        MenuItems['b'].value = Pon;
        break;
    case 'c':
        Menu = PS(PDiss, Menu);
        int Ps;
        std::cin >> Ps;
        MenuItems['c'].value = Ps;
        break;
    }

    PDMenu.ChangeItemValue(std::to_string(18), PDiss.CalcPdis());
    std::cout << "\nDo you have Ps and Pon? y/n ";
    std::cout << "\nAverage Power Dissipation: " << PDiss.CalcPdis() << "\n";
    PowerDissipation(PDiss, PDMenu);
    return;
}
Menu T::PS(PD PDiss, Menu PMenu)
{
    std::vector<MenuOption> MenuOptions
    {
        MenuOption("a", "Enter Wcon", 'a'),
        MenuOption("b", "Enter Wcoff", 'b'),
        MenuOption("c", "Enter fs", 'c'),
        MenuOption("d", "Calculate Wcon", 'd'),
        MenuOption("e", "Calculate Wcoff", 'e'),
        MenuOption("f", "Calculate fs", 'f'),
        MenuOption("g", "Calculate Ps", 'g'),
        MenuOption("x", "Back", 'x')
    };
    std::vector<MenuItem> MenuItems
    {
        MenuItem("a", "Wcon", 0),
        MenuItem("b", "Wcoff", 0),
        MenuItem("c", "fs", 0),
        MenuItem("d", "Ps", 0)
    };
    Menu Menu("Power Dissipation menu", MenuOptions, MenuItems);
    bool loop = true;
    while (loop) 
    {
        Menu.PrintMenu();
        char Option = Menu.ChooseOption();
        switch (Option)
        {
        case 'a':
            std::cout << "Wcon: ";
            int Wcon;
            std::cin >> Wcon;
            MenuItems['a'].value = Wcon;
            break;
        case 'b':
            std::cout << "Wcoff: ";
            int Wcoff;
            std::cin >> Wcoff;
            MenuItems['b'].value = Wcoff;
            break;
        case 'c':
            std::cout << "fs: ";
            int fs;
            std::cin >> fs;
            MenuItems['c'].value = fs;
            break;
        case 'g':
            int wcon, wcoff, fs, Ps;
            Ps = (wcon + wcoff) * fs;
            MenuItems['d'].value = Ps;
            break;
        }
    }
}