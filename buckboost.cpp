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
        //std::cout << "poggers" << std::endl;

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
        bbc::CONVERTERS BuckStuff({ 0 });

        //initialise stuff for buck converters
        bbc::CONVERTERS BoostStuff({ 0 });


        std::vector<MenuOption> BBCMenuOptions
        {
            MenuOption('a', "Inductor Voltage"),
            MenuOption('b', "Selection of Inductor"),
            MenuOption('c', "Selection of Capacitor"),
            //MenuOption('d', "Duty Ratio/Cycle"),
            MenuOption('d', "Change Values"),
            MenuOption('e', "Clear Values"),
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
            //PowerDissipation(PDiss, PDMenu);
            break;
        case 'b':
            BuckBoostConverters(BBCStuff, BuckStuff, BoostStuff, BBCMenu);
        case 'x':
            return;
            break;
        default:
            //TiseMenu();
            break;
        }

    }

    void BUCKBOOST::BuckBoostConverters(CONVERTERS BBCStuff, BUCK BuckStuff, BOOST BoostStuff, Menu BBCMenu)
    {
        BBCMenu = UpdateBBCValues(BBCStuff, BBCMenu);
        BBCMenu.PrintMenu();

        char Option = BBCMenu.ChooseOption();
        switch (Option)
        {
        case 'a':
            VOLT_INDUCT(BBCStuff, BuckStuff, BoostStuff, BBCMenu);
            BuckBoostConverters(BBCStuff, BuckStuff, BoostStuff, BBCMenu);
            break;
        case 'b':
            SEL_INDUCT(BBCStuff, BuckStuff, BoostStuff, BBCMenu);
            BuckBoostConverters(BBCStuff, BuckStuff, BoostStuff, BBCMenu);
            break;
        case 'c':
            SEL_CAP(BBCStuff, BuckStuff, BoostStuff, BBCMenu);
            BuckBoostConverters(BBCStuff, BuckStuff, BoostStuff, BBCMenu);
            break;
        case 'd':
            BBCMenu = ChangeValues(BBCStuff, BBCMenu);
            break;
        case 'e':
            BBCStuff.ClearValues();
            BuckBoostConverters(BBCStuff, BuckStuff, BoostStuff, BBCMenu);
            break;
        case 'x':
            //TiseMenu();
            break;
        default:
            BuckBoostConverters(BBCStuff, BuckStuff, BoostStuff, BBCMenu);
            break;
        }
        
    }
    
    Menu BUCKBOOST::ChangeValues(CONVERTERS BuckBoost, Menu BBCMenu)
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

    Menu BUCKBOOST::UpdateBBCValues(CONVERTERS BuckBoost, Menu BBCMenu)
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
        //BuckBoost.CalcVout();
        return BBCMenu;
    }

    Menu BUCKBOOST::UpdateBBCValues(BUCK Buck, Menu BBCMenu)
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

    Menu BUCKBOOST::UpdateBBCValues(BOOST Boost, Menu BBCMenu)
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

    void BUCKBOOST::VOLT_INDUCT(CONVERTERS BBCStuff, BUCK BuckStuff, BOOST BoostStuff, Menu& BBCMenu)
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
            //MenuItem('b', "Vl", 0),
            MenuItem('b', "L", 0),
            MenuItem('c', "delta_i", 0)
        };
        Menu Menu("Inductor Voltage", MenuOptions, MenuItems);

        //set up values
        Menu.ChangeItemValue('a', BBCMenu.GetItemValue('c'));
        Menu.ChangeItemValue('b', BBCMenu.GetItemValue('i'));
        Menu.ChangeItemValue('c', BBCMenu.GetItemValue('m'));

        bool loop = 1;
        while (loop)
        {
            Menu.PrintMenu();
            char Option = Menu.ChooseOption();
            switch (Option)
            {
            case 'a':
                double vl_switch_on;
                vl_switch_on = BBCStuff.CalcVlON();
                Menu.ChangeItemValue('a', vl_switch_on);
                BBCMenu.ChangeItemValue('c', vl_switch_on);
                std::cout << "\nInductor Voltage: " << Menu.GetItemValue('a') << "\n";
                break;
            case 'b':
                double vl_switch_off;
                vl_switch_off = BBCStuff.CalcVlOFF();
                Menu.ChangeItemValue('b', vl_switch_off);
                BBCMenu.ChangeItemValue('c', vl_switch_off);
                std::cout << "\nInductor Voltage: " << Menu.GetItemValue('a') << "\n";
                break;
            case 'c':
                std::cout << "L: ";
                double L;
                std::cin >> L;
                Menu.ChangeItemValue('b', L);
                BBCMenu.ChangeItemValue('i', L);
                BBCStuff.Add('i', L);
                break;
            case 'd':
                std::cout << "Change in Current: ";
                double delta_i;
                std::cin >> delta_i;
                Menu.ChangeItemValue('c', delta_i);
                BBCMenu.ChangeItemValue('m', delta_i);
                BBCStuff.Add('m', delta_i);
                break;
            case 'e':
                double l;
                l = BuckStuff.CalcL();
                Menu.ChangeItemValue('b', l);
                BBCMenu.ChangeItemValue('i', l);
                break;
            case 'f':
                double Delta_i;
                Delta_i = BBCStuff.Calculus();
                Delta_i = BBCMenu.GetItemValue('m');
                Menu.ChangeItemValue('c', l);
                BBCMenu.ChangeItemValue('m', l);
                break;
            case 'x':
                loop = 0;
                break;
            }
        }
        BuckBoostConverters(BBCStuff, BuckStuff, BoostStuff, BBCMenu);
    }

    void BUCKBOOST::SEL_INDUCT(CONVERTERS BBCStuff, BUCK BuckStuff, BOOST BoostStuff, Menu& BBCMenu)
    {
        BBCMenu = UpdateBBCValues(BBCStuff, BBCMenu);
        //BuckMenu = UpdateBBCValues(BuckStuff, BuckMenu);
        //BoostMenu = UpdateBBCValues(BoostStuff, BoostMenu);

        std::vector<MenuOption> MenuOptions
        {
            MenuOption('a', "Calculate Inductance - Buck Converter"),
            MenuOption('b', "Calculate Inductance - Boost Converter"),
            MenuOption('c', "Enter delta_i"),
            MenuOption('d', "Calculate delta_i"),
            MenuOption('e', "Enter switching frequency"),
            MenuOption('f', "Calculate switching frequency"),
            MenuOption('x', "Back")
        };
        std::vector<MenuItem> MenuItems
        {
            MenuItem('a', "L", 0),
            MenuItem('b', "delta_i", 0),
            MenuItem('c', "Fs", 0)
        };
        Menu Menu("Inductance", MenuOptions, MenuItems);

        //set up values
        Menu.ChangeItemValue('a', BBCMenu.GetItemValue('i'));
        Menu.ChangeItemValue('b', BBCMenu.GetItemValue('m'));
        Menu.ChangeItemValue('c', BBCMenu.GetItemValue('k'));

        bool loop = 1;
        while (loop)
        {
            Menu.PrintMenu();
            char Option = Menu.ChooseOption();
            switch (Option)
            {
            case 'a':
                double buck_inductance;
                buck_inductance = BuckStuff.CalcL();
                Menu.ChangeItemValue('a', buck_inductance);
                BBCMenu.ChangeItemValue('i', buck_inductance);
                std::cout << "\nInductance: " << Menu.GetItemValue('a') << "\n";
                break;
            case 'b':
                double boost_inductance;
                boost_inductance = BoostStuff.CalcL();
                Menu.ChangeItemValue('a', boost_inductance);
                BBCMenu.ChangeItemValue('i', boost_inductance);
                std::cout << "\nInductance: " << Menu.GetItemValue('a') << "\n";
                break;
            case 'c':
                std::cout << "Change in Current: ";
                double delta_i;
                std::cin >> delta_i;
                Menu.ChangeItemValue('c', delta_i);
                BBCMenu.ChangeItemValue('m', delta_i);
                BBCStuff.Add('m', delta_i);
                break;
            case 'd':
                double Delta_i;
                Delta_i = BBCStuff.Calculus();
                Delta_i = BBCMenu.GetItemValue('m');
                Menu.ChangeItemValue('c', l);
                BBCMenu.ChangeItemValue('m', l);
                break;
            case 'e':
                std::cout << "Switching Frequency: ";
                double f_switch;
                std::cin >> f_switch;
                Menu.ChangeItemValue('c', f_switch);
                BBCMenu.ChangeItemValue('k', f_switch);
                BBCStuff.Add('k', f_switch);
                break;
            case 'f':
                double F_switch;
                //add in input for Ts
                F_switch = BBCStuff.CalcFs();
                F_switch = BBCMenu.GetItemValue('k');
                Menu.ChangeItemValue('c', F_switch);
                BBCMenu.ChangeItemValue('k', F_switch);
                break;
            case 'x':
                loop = 0;
                break;
            }
        }
        BuckBoostConverters(BBCStuff, BuckStuff, BoostStuff, BBCMenu);
    }

    void BUCKBOOST::SEL_CAP(CONVERTERS BBCStuff, BUCK BuckStuff, BOOST BoostStuff, Menu& BBCMenu)
    {
        BBCMenu = UpdateBBCValues(BBCStuff, BBCMenu);
        //BuckMenu = UpdateBBCValues(BuckStuff, BuckMenu);
        //BoostMenu = UpdateBBCValues(BoostStuff, BoostMenu);

        std::vector<MenuOption> MenuOptions
        {
            MenuOption('a', "Calculate Capacitance - Buck Converter"),
            MenuOption('b', "Calculate Capacitance - Boost Converter"),
            MenuOption('c', "Enter output voltage ripple"),
            MenuOption('d', "Calculate output voltage ripple"),
            MenuOption('e', "Enter output voltage"),
            MenuOption('f', "Calculate output voltage - Buck Converter"),
            MenuOption('g', "Calculate output voltage - Boost Converter"),
            MenuOption('x', "Back")
        };
        std::vector<MenuItem> MenuItems
        {
            MenuItem('a', "L", 0),
            MenuItem('b', "delta_vo", 0),
            MenuItem('c', "Vout", 0)
        };
        Menu Menu("Inductance", MenuOptions, MenuItems);

        //set up values
        Menu.ChangeItemValue('a', BBCMenu.GetItemValue('i'));
        Menu.ChangeItemValue('b', BBCMenu.GetItemValue('j'));
        Menu.ChangeItemValue('c', BBCMenu.GetItemValue('b'));

        bool loop = 1;
        while (loop)
        {
            Menu.PrintMenu();
            char Option = Menu.ChooseOption();
            switch (Option)
            {
            case 'a':
                double buck_capacitance;
                buck_capacitance = BuckStuff.CalcC();
                Menu.ChangeItemValue('a', buck_capacitance);
                BBCMenu.ChangeItemValue('i', buck_capacitance);
                std::cout << "\nInductance: " << Menu.GetItemValue('a') << "\n";
                break;
            case 'b':
                double boost_capacitance;
                boost_capacitance = BoostStuff.CalcC();
                Menu.ChangeItemValue('a', boost_capacitance);
                BBCMenu.ChangeItemValue('i', boost_capacitance);
                std::cout << "\nInductance: " << Menu.GetItemValue('a') << "\n";
                break;
            case 'c':
                std::cout << "Output Voltage Ripple: ";
                double delta_vo;
                std::cin >> delta_vo;
                Menu.ChangeItemValue('b', delta_vo);
                BBCMenu.ChangeItemValue('j', delta_vo);
                BBCStuff.Add('j', delta_vo);
            case 'd':
                double Delta_vo;
                Delta_vo = BBCStuff.Calculus();
                Menu.ChangeItemValue('b', Delta_vo);
                BBCMenu.ChangeItemValue('j', Delta_vo);
                break;
            case 'e':
                std::cout << "Output Voltage: ";
                double Vout;
                std::cin >> Vout;
                Menu.ChangeItemValue('c', Vout);
                BBCMenu.ChangeItemValue('b', Vout);
                BBCStuff.Add('b', Vout);
            case 'f':
                double Buck_VOut;
                Buck_VOut = BuckStuff.CalcVout();
                Menu.ChangeItemValue('b', Buck_VOut);
                BBCMenu.ChangeItemValue('j', Buck_VOut);
                break;
            case 'g':
                double Boost_VOut;
                Boost_VOut = BoostStuff.CalcVout();
                Menu.ChangeItemValue('b', Boost_VOut);
                BBCMenu.ChangeItemValue('j', Boost_VOut);
                break;
            case 'x':
                loop = 0;
                break;
            }
        }
        BuckBoostConverters(BBCStuff, BuckStuff, BoostStuff, BBCMenu);
    }
}







