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

        // initialise stuff for buck/boost converters
        bbc::CONVERTERS BBCStuff({ 0 });

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
            PS(PDiss, PDMenu, 'a');
            BuckBoostConverters(BBCStuff, BBCMenu);
            break;
        case 'c':
            PON(PDiss, PDMenu, 'a');
            BuckBoostConverters(BBCStuff, BBCMenu);
            break;
        case 'd':
            BBCMenu = ChangeValues(PDiss, BBCMenu);
            break;
        case 'e':
            PDiss.ClearValues();
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
        BBCMenu.ChangeItemValue('c', BuckBoost.CalcPi());
        Pdiss.CalcTcoff();
        PDMenu.ChangeItemValue('f', Pdiss.CalcTcoff());
        Pdiss.CalcWcon();
        PDMenu.ChangeItemValue('g', Pdiss.CalcWcon());
        Pdiss.CalcWcoff();
        PDMenu.ChangeItemValue('h', Pdiss.CalcWcoff());
        Pdiss.CalcPs();
        PDMenu.ChangeItemValue('p', Pdiss.CalcPs());
        Pdiss.CalcWon();
        PDMenu.ChangeItemValue('n', Pdiss.CalcWon());
        Pdiss.CalcPon();
        PDMenu.ChangeItemValue('q', Pdiss.CalcPon());
        Pdiss.CalcPdis();
        PDMenu.ChangeItemValue('r', Pdiss.CalcPdis());
        return PDMenu;
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

    //Pon + sub calcs
    void Tise::PON(T::PD PDiss, Menu PDMenu, char parent)
    {
        PDMenu = UpdatePDValues(PDiss, PDMenu);
        std::vector<MenuOption> MenuOptions
        {
            MenuOption('a', "Calculate Pon"),
            MenuOption('b', "Enter Won"),
            MenuOption('c', "Enter fs"),
            MenuOption('d', "Calculate Won"),
            MenuOption('e', "Calculate fs"),
            MenuOption('x', "Back")
        };
        std::vector<MenuItem> MenuItems
        {
            MenuItem('a', "Won", 0),
            MenuItem('b', "fs", 0),
            MenuItem('c', "Pon", 0)
        };

        Menu Menu("Conduction Power Loss", MenuOptions, MenuItems);
        Menu.ChangeItemValue('a', PDMenu.GetItemValue('n'));
        Menu.ChangeItemValue('b', PDMenu.GetItemValue('k'));
        Menu.ChangeItemValue('c', PDMenu.GetItemValue('q'));
        bool loop = 1;
        while (loop)
        {
            Menu.PrintMenu();
            char Option = Menu.ChooseOption();
            switch (Option)
            {
            case 'a':
                double pon;
                pon = PDiss.CalcPon();
                Menu.ChangeItemValue('c', pon);
                PDMenu.ChangeItemValue('q', pon);
                std::cout << "\nConduction Power Loss: " << Menu.GetItemValue('c') << "\n";
                break;
            case 'b':
                std::cout << "Won: ";
                double Won;
                std::cin >> Won;
                Menu.ChangeItemValue('a', Won);
                PDMenu.ChangeItemValue('n', Won);
                PDiss.Add('n', Won);
                break;
            case 'c':
                std::cout << "fs: ";
                double fs;
                std::cin >> fs;
                Menu.ChangeItemValue('b', fs);
                PDMenu.ChangeItemValue('k', fs);
                PDiss.Add('k', fs);
                break;
            case 'd':
                double won;
                WON(PDiss, PDMenu, parent);
                won = PDMenu.GetItemValue('n');
                Menu.ChangeItemValue('a', won);
                PDMenu.ChangeItemValue('n', won);
                break;
            case 'e':
                double Fs;
                TSFS(PDiss, PDMenu, 'a');
                Fs = PDMenu.GetItemValue('k');
                Menu.ChangeItemValue('b', Fs);
                PDMenu.ChangeItemValue('k', Fs);
                break;
            case 'x':
                loop = 0;
                break;
            }
        }
        switch (parent)
        {
        case 'a':
            PowerDissipation(PDiss, PDMenu);
            break;
        case 'b':
            PDISS(PDiss, PDMenu);
            break;
        default:
            break;
        }
        PDISS(PDiss, PDMenu);
    }
    void Tise::WON(T::PD PDiss, Menu PDMenu, char parent)
    {
        PDMenu = UpdatePDValues(PDiss, PDMenu);
        std::vector<MenuOption> MenuOptions
        {
            MenuOption('a', "Calculate Won"),
            MenuOption('b', "Enter Von"),
            MenuOption('c', "Enter Io"),
            MenuOption('d', "Enter Ton"),
            MenuOption('x', "Back")
        };
        std::vector<MenuItem> MenuItems
        {
            MenuItem('a', "Von", 0),
            MenuItem('b', "Io", 0),
            MenuItem('c', "Ton", 0),
            MenuItem('d', "Won", 0)
        };

        Menu Menu("Energy dissipated during ON state time", MenuOptions, MenuItems);
        Menu.ChangeItemValue('a', PDMenu.GetItemValue('m'));
        Menu.ChangeItemValue('b', PDMenu.GetItemValue('j'));
        Menu.ChangeItemValue('c', PDMenu.GetItemValue('o'));
        Menu.ChangeItemValue('d', PDMenu.GetItemValue('n'));
        bool loop = 1;
        while (loop)
        {
            Menu.PrintMenu();
            char Option = Menu.ChooseOption();
            switch (Option)
            {
            case 'a':
                double Won;
                Won = PDiss.CalcWon();
                Menu.ChangeItemValue('d', Won);
                PDMenu.ChangeItemValue('n', Won);
                std::cout << "\nEnergy dissipated during ON state time: " << Menu.GetItemValue('d') << "\n";
                break;
            case 'b':
                std::cout << "Von: ";
                double Von;
                std::cin >> Von;
                Menu.ChangeItemValue('a', Von);
                PDMenu.ChangeItemValue('m', Von);
                PDiss.Add('m', Von);
                break;
            case 'c':
                std::cout << "Io: ";
                double Io;
                std::cin >> Io;
                Menu.ChangeItemValue('b', Io);
                PDMenu.ChangeItemValue('j', Io);
                PDiss.Add('j', Io);
                break;
            case 'd':
                std::cout << "Ton: ";
                double Ton;
                std::cin >> Ton;
                Menu.ChangeItemValue('c', Ton);
                PDMenu.ChangeItemValue('o', Ton);
                PDiss.Add('o', Ton);
                break;
            case 'x':
                loop = 0;
                break;
            }
        }
        PON(PDiss, PDMenu, parent);
    }
    void Tise::TSFS(T::PD PDiss, Menu PDMenu, char parent)
    {
        PDMenu = UpdatePDValues(PDiss, PDMenu);
        std::vector<MenuOption> MenuOptions
        {
            MenuOption('a', "Enter Ts"),
            MenuOption('b', "Enter fs"),
            MenuOption('x', "Back")
        };
        std::vector<MenuItem> MenuItems
        {
            MenuItem('a', "Ts", 0),
            MenuItem('b', "fs", 0)
        };

        Menu Menu("Switching Period / Frequency", MenuOptions, MenuItems);
        Menu.ChangeItemValue('a', PDMenu.GetItemValue('l'));
        Menu.ChangeItemValue('b', PDMenu.GetItemValue('k'));
        bool loop = 1;
        while (loop)
        {
            Menu.PrintMenu();
            char Option = Menu.ChooseOption();
            switch (Option)
            {
            case 'a':
                std::cout << "Ts: ";
                double Ts, fs;
                std::cin >> Ts;
                Menu.ChangeItemValue('a', Ts);
                PDMenu.ChangeItemValue('l', Ts);
                PDiss.Add('l', Ts);
                fs = PDiss.Get('k');
                Menu.ChangeItemValue('b', fs);
                PDMenu.ChangeItemValue('k', fs);
                break;
            case 'b':
                std::cout << "fs: ";
                double _fs, ts;
                std::cin >> _fs;
                Menu.ChangeItemValue('b', _fs);
                PDMenu.ChangeItemValue('k', _fs);
                PDiss.Add('k', _fs);
                ts = PDiss.Get('l');
                Menu.ChangeItemValue('a', ts);
                PDMenu.ChangeItemValue('l', ts);
                break;
            case 'x':
                loop = 0;
                break;
            }
        }
        switch (parent)
        {
        case 'a':
            PON(PDiss, PDMenu, parent);
            break;
        case 'b':
            PS(PDiss, PDMenu, parent);
            break;
        default:
            break;
        }
        PDISS(PDiss, PDMenu);
    }

    // Ps + sub calcs
    void Tise::PS(T::PD PDiss, Menu PDMenu, char parent)
    {
        PDMenu = UpdatePDValues(PDiss, PDMenu);
        std::vector<MenuOption> MenuOptions
        {
            MenuOption('a', "Calculate Ps"),
            MenuOption('b', "Enter Wcon"),
            MenuOption('c', "Enter Wcoff"),
            MenuOption('d', "Enter fs"),
            MenuOption('e', "Calculate Wcon"),
            MenuOption('f', "Calculate Wcoff"),
            MenuOption('g', "Calculate fs"),
            MenuOption('x', "Back")
        };
        std::vector<MenuItem> MenuItems
        {
            MenuItem('a', "Wcon", 0),
            MenuItem('b', "Wcoff", 0),
            MenuItem('c', "fs", 0),
            MenuItem('d', "Ps", 0)
        };

        Menu Menu("Switching Power Loss", MenuOptions, MenuItems);
        Menu.ChangeItemValue('a', PDMenu.GetItemValue('g'));
        Menu.ChangeItemValue('b', PDMenu.GetItemValue('h'));
        Menu.ChangeItemValue('c', PDMenu.GetItemValue('k'));
        Menu.ChangeItemValue('d', PDMenu.GetItemValue('p'));
        bool loop = 1;
        while (loop)
        {
            Menu.PrintMenu();
            char Option = Menu.ChooseOption();
            switch (Option)
            {
            case 'a':
                double ps;
                ps = PDiss.CalcPs();
                Menu.ChangeItemValue('d', ps);
                PDMenu.ChangeItemValue('p', ps);
                std::cout << "\nSwitching Power Loss: " << Menu.GetItemValue('d') << "\n";
                break;
            case 'b':
                std::cout << "Wcon: ";
                double Wcon;
                std::cin >> Wcon;
                Menu.ChangeItemValue('a', Wcon);
                PDMenu.ChangeItemValue('g', Wcon);
                PDiss.Add('g', Wcon);
                break;
            case 'c':
                std::cout << "Wcoff: ";
                double Wcoff;
                std::cin >> Wcoff;
                Menu.ChangeItemValue('b', Wcoff);
                PDMenu.ChangeItemValue('h', Wcoff);
                PDiss.Add('h', Wcoff);
                break;
            case 'd':
                std::cout << "fs: ";
                double fs;
                std::cin >> fs;
                Menu.ChangeItemValue('c', fs);
                PDMenu.ChangeItemValue('k', fs);
                PDiss.Add('k', fs);
                break;
            case 'e':
                double wcon;
                WCON(PDiss, PDMenu, parent);
                wcon = PDMenu.GetItemValue('g');
                Menu.ChangeItemValue('a', wcon);
                PDMenu.ChangeItemValue('g', wcon);
                break;
            case 'f':
                double wcoff;
                WCOFF(PDiss, PDMenu, parent);
                wcoff = PDMenu.GetItemValue('h');
                Menu.ChangeItemValue('b', wcoff);
                PDMenu.ChangeItemValue('h', wcoff);
                break;
            case 'g':
                double Fs;
                TSFS(PDiss, PDMenu, 'b');
                Fs = PDMenu.GetItemValue('k');
                Menu.ChangeItemValue('c', Fs);
                PDMenu.ChangeItemValue('k', Fs);
                break;
            case 'x':
                loop = 0;
                break;
            }
        }
        switch (parent)
        {
        case 'a':
            PowerDissipation(PDiss, PDMenu);
            break;
        case 'b':
            PDISS(PDiss, PDMenu);
            break;
        default:
            break;
        }
        PDISS(PDiss, PDMenu);
    }
    void Tise::WCON(T::PD PDiss, Menu PDMenu, char parent)
    {
        PDMenu = UpdatePDValues(PDiss, PDMenu);
        std::vector<MenuOption> MenuOptions
        {
            MenuOption('a', "Calculate Wcon"),
            MenuOption('b', "Enter VDC"),
            MenuOption('c', "Enter Io"),
            MenuOption('d', "Enter tcon"),
            MenuOption('x', "Back")
        };
        std::vector<MenuItem> MenuItems
        {
            MenuItem('a', "VDC", 0),
            MenuItem('b', "Io", 0),
            MenuItem('c', "tcon", 0),
            MenuItem('d', "Wcon", 0)
        };

        Menu Menu("Energy dissipated during switching ON state time", MenuOptions, MenuItems);
        Menu.ChangeItemValue('a', PDMenu.GetItemValue('i'));
        Menu.ChangeItemValue('b', PDMenu.GetItemValue('j'));
        Menu.ChangeItemValue('c', PDMenu.GetItemValue('c'));
        Menu.ChangeItemValue('d', PDMenu.GetItemValue('g'));
        bool loop = 1;
        while (loop)
        {
            Menu.PrintMenu();
            char Option = Menu.ChooseOption();
            switch (Option)
            {
            case 'a':
                double Wcon;
                Wcon = PDiss.CalcWcon();
                Menu.ChangeItemValue('d', Wcon);
                PDMenu.ChangeItemValue('g', Wcon);
                std::cout << "\nEnergy dissipated during ON state time: \n\n\t\t" << Menu.GetItemValue('d') << "\n";
                break;
            case 'b':
                std::cout << "VDC: ";
                double VDC;
                std::cin >> VDC;
                Menu.ChangeItemValue('a', VDC);
                PDMenu.ChangeItemValue('i', VDC);
                PDiss.Add('i', VDC);
                break;
            case 'c':
                std::cout << "Io: ";
                double Io;
                std::cin >> Io;
                Menu.ChangeItemValue('b', Io);
                PDMenu.ChangeItemValue('j', Io);
                PDiss.Add('j', Io);
                break;
            case 'd':
                std::cout << "tcon: ";
                double tcon;
                std::cin >> tcon;
                Menu.ChangeItemValue('c', tcon);
                PDMenu.ChangeItemValue('c', tcon);
                PDiss.Add('c', tcon);
                break;
            case 'x':
                loop = 0;
                break;
            }
        }
        PS(PDiss, PDMenu, parent);
    }
    void Tise::WCOFF(T::PD PDiss, Menu PDMenu, char parent)
    {
        PDMenu = UpdatePDValues(PDiss, PDMenu);
        std::vector<MenuOption> MenuOptions
        {
            MenuOption('a', "Calculate Wcoff"),
            MenuOption('b', "Enter VDC"),
            MenuOption('c', "Enter Io"),
            MenuOption('d', "Enter tcoff"),
            MenuOption('x', "Back")
        };
        std::vector<MenuItem> MenuItems
        {
            MenuItem('a', "VDC", 0),
            MenuItem('b', "Io", 0),
            MenuItem('c', "tcoff", 0),
            MenuItem('d', "Wcoff", 0)
        };

        Menu Menu("Energy dissipated during switching OFF state time", MenuOptions, MenuItems);
        Menu.ChangeItemValue('a', PDMenu.GetItemValue('i'));
        Menu.ChangeItemValue('b', PDMenu.GetItemValue('j'));
        Menu.ChangeItemValue('c', PDMenu.GetItemValue('f'));
        Menu.ChangeItemValue('d', PDMenu.GetItemValue('h'));
        bool loop = 1;
        while (loop)
        {
            Menu.PrintMenu();
            char Option = Menu.ChooseOption();
            switch (Option)
            {
            case 'a':
                double Wcoff;
                Wcoff = PDiss.CalcWcoff();
                Menu.ChangeItemValue('d', Wcoff);
                PDMenu.ChangeItemValue('h', Wcoff);
                std::cout << "\nEnergy dissipated during OFF state time: \n\n\t\t\t" << Menu.GetItemValue('d') << "\n";
                break;
            case 'b':
                std::cout << "VDC: ";
                double VDC;
                std::cin >> VDC;
                Menu.ChangeItemValue('a', VDC);
                PDMenu.ChangeItemValue('i', VDC);
                PDiss.Add('i', VDC);
                break;
            case 'c':
                std::cout << "Io: ";
                double Io;
                std::cin >> Io;
                Menu.ChangeItemValue('b', Io);
                PDMenu.ChangeItemValue('j', Io);
                PDiss.Add('j', Io);
                break;
            case 'd':
                std::cout << "tcon: ";
                double tcon;
                std::cin >> tcon;
                Menu.ChangeItemValue('c', tcon);
                PDMenu.ChangeItemValue('f', tcon);
                PDiss.Add('f', tcon);
                break;
            case 'x':
                loop = 0;
                break;
            }
        }
        PS(PDiss, PDMenu, parent);
    }
}
}
    */






