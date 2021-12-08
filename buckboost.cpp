#include "buckboost.h"
#include "variables.h"
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cctype>
#include <string>
#include <stdlib.h>  

/* Non - linear variables relating to buck / boost converters are the inductor voltage,
*  inductor selection, capacitor selection, peak to peak output voltage ripple and change in charge
*/

bool is_number(const std::string& word) {
    return !word.empty() && std::all_of(word.begin(), word.end(), ::isdigit);
}

namespace bbc {
    BUCKBOOST::BUCKBOOST() {}

    void BUCKBOOST::InitMenu()
    {
        std::cout << "poggers" << std::endl;

        std::vector<MenuOption> BMenuOptions
        {
            MenuOption('a', "Power Dissipation Calculator"),
            MenuOption('b', "Buck/Boost Converter Calculator"),
            MenuOption('x', "Main Menu")
        };
        std::vector<MenuItem> BMenuItems{};

        Menu BMenu("Main menu", BMenuOptions, BMenuItems);
        BMenu.PrintMenu();

        // initialise general stuff for buck/boost converters
        bbc::CONVERTERS BBCStuff({ 0 });

        //initialise stuff for buck converters
        bbc::BUCK BuckStuff({ 0 });

        //initialise stuff for buck converters
        bbc::BOOST BoostStuff({ 0 });


        std::vector<MenuOption> BBCMenuOptions
        {
            MenuOption('a', "Inductor Voltage"),
            MenuOption('b', "Selection of Inductor"),
            MenuOption('c', "Selection of Capacitor"),
            MenuOption('d', "Duty Ratio/Cycle"),
            MenuOption('e', "Change Values"),
            MenuOption('f', "Clear Values"),
            MenuOption('x', "Back")
        };

        std::vector<MenuItem> BBCMenuItems
        {
            MenuItem('a', "Vin", 0),
            MenuItem('b', "Vout", 0),
            MenuItem('c', "Vl", 0),
            MenuItem('d', "K", 0),
            MenuItem('e', "Ii", 0),
            MenuItem('f', "Io", 0),
            MenuItem('g', "Il", 0),
            MenuItem('h', "Po", 0),
            MenuItem('i', "L", 0),
            MenuItem('j', "delta_vo", 0),
            MenuItem('k', "Fs", 0),
            MenuItem('l', "Ts", 0),
            MenuItem('m', "delta_i", 0),
            MenuItem('n', "Rl", 0),
            MenuItem('o', "Ro", 0),
            MenuItem('p', "C", 0),
            MenuItem('q', "Pi", 0),
        };
        Menu BBCMenu("Buck/Boost Converter menu", BMenuOptions, BMenuItems);

        
        // Main Menu
        char Option = BMenu.ChooseOption();
        switch (Option)
        {
        case 'a':
            PowerDissipation(PDiss, PDMenu);
            break;
        case 'b':
            BuckBoostConverters(BBCStuff, BBCMenu);
        case 'x':
            return;
            break;
        default:
            TiseMenu();
            break;
        }

    }
    void BUCKBOOST::BuckBoostConverters(bbc::CONVERTERS BuckBoostConverters, Menu BBCMenu)
    {
        BBCMenu = UpdateBBCValues(BuckBoostConverters, BBCMenu);
        BBCMenu.PrintMenu();

        char Option = BBCMenu.ChooseOption();
        switch (Option)
        {
        case 'a':
            VOLT_INDUCT(BBCStuff, BBCMenu);
            BuckBoostConverters(BBCStuff, BBCMenu);
            break;
        case 'b':
            //PS(PDiss, PDMenu, 'a');
            BuckBoostConverters(BBCStuff, BBCMenu);
            break;
        case 'c':
            //PON(PDiss, PDMenu, 'a');
            BuckBoostConverters(BBCStuff, BBCMenu);
            break;
        case 'd':
            BBCMenu = ChangeValues(BBCStuff, BBCMenu);
            break;
        case 'e':
            BBCStuff.ClearValues();
            BuckBoostConverters(BBCStuff, BBCMenu);
            break;
        case 'x':
            TiseMenu();
            break;
        default:
            BuckBoostConverters(BBCStuff, BBCMenu);
            break;
        }
    }

        

    }
    
    Menu CONVERTERS::ChangeValues(bbc::CONVERTERS BuckBoost, Menu BBCMenu)
    {
        std::cout << "\nEnter the number of the value you want to add/change: ";
        char option;
        std::cin >> option;
        std::cout << "\nEnter the value you want to use: ";
        double value;
        std::cin >> value;
        BuckBoost.Add(option, value);
        BBCMenu.ChangeItemValue(option, value);

        std::cout << "\nItem changed.\n";
        BuckBoostConverters(BBCStuff, BBCMenu);
        return BBCMenu;
    }

    Menu CONVERTERS::UpdateBBCValues(bbc::CONVERTERS BuckBoost, Menu BBCMenu)
    {
        BuckBoost.CalcPi();
        BBCMenu.ChangeItemValue('q', BuckBoost.CalcPi());
        BuckBoost.CalcPo();
        BBCMenu.ChangeItemValue('h', BuckBoost.CalcPo());
        BuckBoost.CalcRl();
        BBCMenu.ChangeItemValue('n', BuckBoost.CalcRl());
        BuckBoost.CalcVlON();
        BBCMenu.ChangeItemValue('c', BuckBoost.CalcVlON());
        BuckBoost.CalcVlOFF();
        BBCMenu.ChangeItemValue('c', BuckBoost.CalcVlOFF());
        BuckBoost.CalcVout();
        return BBCMenu;
    }

    Menu BUCK::UpdateBBCValues(bbc::BUCK Buck, Menu BBCMenu)
    {
        Buck.CalcK();
        BBCMenu.ChangeItemValue('d', Buck.CalcK());
        Buck.CalcIi();
        BBCMenu.ChangeItemValue('e', Buck.CalcIi());
        Buck.CalcIo();
        BBCMenu.ChangeItemValue('f', Buck.CalcIo());
        Buck.CalcL();
        BBCMenu.ChangeItemValue('i', Buck.CalcL());
        Buck.CalcC();
        BBCMenu.ChangeItemValue('p', Buck.CalcC());
        return BBCMenu;
    }

    Menu BOOST::UpdateBBCValues(bbc::BOOST Boost, Menu BBCMenu)
    {
        Boost.CalcK();
        BBCMenu.ChangeItemValue('d', Boost.CalcK());
        Boost.CalcIi();
        BBCMenu.ChangeItemValue('e', Boost.CalcIi());
        Boost.CalcIo();
        BBCMenu.ChangeItemValue('f', Boost.CalcIo());
        Boost.CalcL();
        BBCMenu.ChangeItemValue('i', Boost.CalcL());
        Boost.CalcC();
        BBCMenu.ChangeItemValue('p', Boost.CalcC());
        return BBCMenu;
    }

    void BUCKBOOST::VOLT_INDUCT(bbc::CONVERTERS BBCStuff, Menu& BBCMenu)
    {
        BBCMenu = UpdateBBCValues(BBCStuff, BBCMenu);
        std::vector<MenuOption> MenuOptions
        {
            MenuOption('a', "Calculate Inductor Voltage - Switch ON"),
            MenuOption('b', "Calculate Inductor Voltage - Switch OFF"),
            MenuOption('c', "Enter L"),
            MenuOption('d', "Enter delta_i"),
            MenuOption('e', "Calculate L"),
            MenuOption('f', "Calculate delta_i"),
            MenuOption('x', "Back")
        };
        std::vector<MenuItem> MenuItems
        {
            MenuItem('a', "Vl", 0),
            MenuItem('b', "Vl", 0),
            MenuItem('c', "L", 0),
            MenuItem('d', "delta_i", 0)
        };
        Menu Menu("Inductor Voltage", MenuOptions, MenuItems);

        //set up values
        Menu.ChangeItemValue('a', BBCMenu.GetItemValue('c'));
        Menu.ChangeItemValue('b', BBCMenu.GetItemValue('c'));
        Menu.ChangeItemValue('c', BBCMenu.GetItemValue('i'));
        Menu.ChangeItemValue('d', BBCMenu.GetItemValue('m'));

        bool loop = 1;
        while (loop)
        {
            Menu.PrintMenu();
            char Option = Menu.ChooseOption();
            switch (Option)
            {
            case 'a':
                double volt_induct;
                vl_switch_on = BBCStuff.CalcVlON();
                Menu.ChangeItemValue('a', vl_switch_on);
                BBCMenu.ChangeItemValue('c', vl_switch_on);
                std::cout << "\nInductor Voltage: " << Menu.GetItemValue('a') << "\n";
                break;
            case 'b':
                double volt_induct;
                vl_switch_off = BBCStuff.CalcVlOFF();
                Menu.ChangeItemValue('b', vl_switch_off);
                BBCMenu.ChangeItemValue('c', vl_switch_off);
                std::cout << "\nInductor Voltage: " << Menu.GetItemValue('b') << "\n";
                break;
            case 'c':
                std::cout << "L: ";
                double L;
                std::cin >> L;
                Menu.ChangeItemValue('c', L);
                BBCMenu.ChangeItemValue('i', L);
                BBCStuff.Add('i', L);
                break;
            case 'd':
                std::cout << "Change in Current: ";
                double delta_i;
                std::cin >> delta_i;
                Menu.ChangeItemValue('d', delta_i);
                BBCMenu.ChangeItemValue('m', delta_i);
                BBCStuff.Add('m', delta_i);
                break;
            case 'e':
                double l;
                l = BBCStuff.CalcL();
                Menu.ChangeItemValue('c', l);
                BBCMenu.ChangeItemValue('i', l);
                break;
            case 'f':
                double Delta_i;
                Delta_i = BBCStuff.Calculus();
                Delta_i = BBCMenu.GetItemValue('m');
                Menu.ChangeItemValue('b', l);
                BBCMenu.ChangeItemValue('m', l);
                break;
            case 'x':
                loop = 0;
                break;
            }
        }
        BuckBoostConverters(BBCStuff, BBCMenu);
    }
    }
}
}
    */





