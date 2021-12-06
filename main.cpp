#include <iostream>
#include <vector>
#include "menu.h"
#include "menuelement.h"
#include "formula.h"
#include "module.h"
#include "user.h"
#include "initiate.h"
#include "PD.h"
#include "eseries.h"
#include "componentmatch.h"

namespace T
{
    void TiseTestingGround();
    void PowerDissipation(T::PD PDiss, Menu PDMenu);
    Menu ChangeValues(PD Pdiss, Menu PDMenu);
    Menu UpdatePDValues(PD Pdiss, Menu PDMenu);
    void PDISS(PD Pdiss, Menu &PDMenu);
    void PS(PD PDiss, Menu PDMenu, char parent);
    void PON(PD PDiss, Menu PDMenu, char parent);
    void WCON(PD PDiss, Menu PDMenu, char parent);
    void WCOFF(PD PDiss, Menu PDMenu, char parent);
    void TSFS(PD PDiss, Menu PDMenu, char parent);
    void WON(PD PDiss, Menu PDMenu, char parent);
}

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
        MenuOption('3', "Option C"),
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
    switch (chosenOption)
    {
        case '0':
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
    std::cout << "\n\n\tWelcome to my sandbox\n\tAspect of Project by Tise Olayinka\n\tELEC2645\tGroup 35\n\n" << std::endl;

    std::vector<MenuOption> TMenuOptions
    {
        MenuOption('a', "Power Dissipation Calculator"),
        MenuOption('x', "Option B"),
        MenuOption('x', "Main Menu")
    };
    std::vector<MenuItem> TMenuItems {};

    Menu TMenu("Main menu", TMenuOptions, TMenuItems);
    TMenu.PrintMenu();

    // initialise stuff for Power Dissipation
    PD PDiss({ 0 }); 
    std::vector<MenuOption> PDMenuOptions
    {
        MenuOption('a', "Average Power Dissipation"),
        MenuOption('b', "Switching Power Loss"),
        MenuOption('c', "Conduction Power Loss"),
        MenuOption('d', "Change Values"),
        MenuOption('e', "Clear Values"),
        MenuOption('x', "Back")
    };
    std::vector<MenuItem> PDMenuItems
    {
        MenuItem('a', "tri", 0),
        MenuItem('b', "tfv", 0),
        MenuItem('c', "tcon", 0),
        MenuItem('d', "trv", 0),
        MenuItem('e', "tfi", 0),
        MenuItem('f', "tcoff", 0),
        MenuItem('g', "Wcon", 0),
        MenuItem('h', "Wcoff", 0),
        MenuItem('i', "VDC", 0),
        MenuItem('j', "Io", 0),
        MenuItem('k', "fs", 0),
        MenuItem('l', "Ts", 0),
        MenuItem('m', "Von", 0),
        MenuItem('n', "Won", 0),
        MenuItem('o', "Ton", 0),
        MenuItem('p', "Ps", 0),
        MenuItem('q', "Pon", 0),
        MenuItem('r', "Pdis", 0)
    };
    Menu PDMenu("Power Dissipation menu", PDMenuOptions, PDMenuItems);


    // Main Menu
    char Option = TMenu.ChooseOption();
    switch (Option)
    {
    case 'a':
        T::PowerDissipation(PDiss, PDMenu);
        break;
    case 'x':
        main();
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
    PDMenu = UpdatePDValues(PDiss, PDMenu);
    PDMenu.PrintMenu();

    char Option = PDMenu.ChooseOption();
    switch (Option)
    {
        case 'a':
            PDISS(PDiss, PDMenu);
            PowerDissipation(PDiss, PDMenu);
            break;
        case 'b':
            PS(PDiss, PDMenu, 'a');
            PowerDissipation(PDiss, PDMenu);
            break;
        case 'c':
            PON(PDiss, PDMenu, 'a');
            PowerDissipation(PDiss, PDMenu);
            break;
        case 'd':
            PDMenu = ChangeValues(PDiss, PDMenu);
            break;
        case 'e':
            PDiss.ClearValues();
            PowerDissipation(PDiss, PDMenu);
            break;
        case 'x':
            TiseTestingGround();
            break;
        default:
            PowerDissipation(PDiss, PDMenu);
            break;
    }
}
Menu T::ChangeValues(PD Pdiss, Menu PDMenu)
{
    std::cout << "\nEnter the number of the value you want to add/change: ";
    char option;
    std::cin >> option;
    std::cout << "\nEnter the value you want to use: ";
    double value;
    std::cin >> value;
    Pdiss.Add(option, value);
    PDMenu.ChangeItemValue(option, value);

    std::cout << "\nItem changed.\n";
    PowerDissipation(Pdiss, PDMenu);
    return PDMenu;
}
Menu T::UpdatePDValues(PD Pdiss, Menu PDMenu)
{
    Pdiss.CalcTcon();
    PDMenu.ChangeItemValue('c', Pdiss.CalcTcon());
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

void T::PDISS(PD PDiss, Menu &PDMenu)
{
    PDMenu = UpdatePDValues(PDiss, PDMenu);
    std::vector<MenuOption> MenuOptions
    {
        MenuOption('a', "Calculate Pdiss"),
        MenuOption('b', "Enter Ps"),
        MenuOption('c', "Enter Pon"),
        MenuOption('d', "Calculate Ps"),
        MenuOption('e', "Calculate Pon"),
        MenuOption('x', "Back")
    };
    std::vector<MenuItem> MenuItems
    {
        MenuItem('a', "Ps", 0),
        MenuItem('b', "Pon", 0),
        MenuItem('c', "Pdiss", 0)
    };
    Menu Menu("Average Power Dissipation", MenuOptions, MenuItems);
    //set up values
    Menu.ChangeItemValue('a', PDMenu.GetItemValue('p'));
    Menu.ChangeItemValue('b', PDMenu.GetItemValue('q'));
    Menu.ChangeItemValue('c', PDMenu.GetItemValue('r'));
    bool loop = 1;
    while (loop)
    {
        Menu.PrintMenu();
        char Option = Menu.ChooseOption();
        switch (Option)
        {
        case 'a':
            double pdiss;
            //pdiss = Menu.GetItemValue('a') + Menu.GetItemValue('b');
            pdiss = PDiss.CalcPdis();
            Menu.ChangeItemValue('c', pdiss);
            PDMenu.ChangeItemValue('r', pdiss);
            std::cout << "\nAverage Power Dissipation: " << Menu.GetItemValue('c') << "\n";
            break;
        case 'b':
            std::cout << "Ps: ";
            double Ps;
            std::cin >> Ps;
            Menu.ChangeItemValue('a', Ps);
            PDMenu.ChangeItemValue('p', Ps);
            PDiss.Add('p', Ps);
            break;
        case 'c':
            std::cout << "Pon: ";
            double Pon;
            std::cin >> Pon;
            Menu.ChangeItemValue('b', Pon);
            PDMenu.ChangeItemValue('q', Pon);
            PDiss.Add('q', Pon);
            break;
        case 'd':
            double ps;
            PS(PDiss, PDMenu, 'b');
            ps = PDMenu.GetItemValue('p');
            Menu.ChangeItemValue('a', ps);
            PDMenu.ChangeItemValue('p', ps);
            break;
        case 'e':
            double pon;
            PON(PDiss, PDMenu, 'b');
            pon = PDMenu.GetItemValue('q');
            Menu.ChangeItemValue('b', pon);
            PDMenu.ChangeItemValue('q', pon);
            break;
        case 'x':
            loop = 0;
            break;
        }
    }
    PowerDissipation(PDiss, PDMenu);
}
//Pon + sub calcs
void T::PON(PD PDiss, Menu PDMenu, char parent)
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
void T::WON(PD PDiss, Menu PDMenu, char parent)
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
void T::TSFS(PD PDiss, Menu PDMenu, char parent) 
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
void T::PS(PD PDiss, Menu PDMenu, char parent)
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
            PDiss.Add('g', Wcon );
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
void T::WCON(PD PDiss, Menu PDMenu, char parent) 
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
void T::WCOFF(PD PDiss, Menu PDMenu, char parent) 
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
