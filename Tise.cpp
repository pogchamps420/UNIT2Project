#include "Tise.h"

namespace T
{
    Tise::Tise() {}
 
    void Tise::TiseMenu()
    {
        System::Clear();

        //Define user-selectable options
        std::vector<MenuOption> TMenuOptions
        {
            MenuOption('a', "Power Dissipation Calculator"),
            MenuOption('x', "Option Delilah"),
            MenuOption('x', "Exit")
        };
        //Define items to be displayed, value can be either a string or an int. In this case nothing since its just a normal menu.
        std::vector<MenuItem> TMenuItems {};

        //Initialise menu    
        Menu TMenu("Main menu", TMenuOptions, TMenuItems);
        TMenu.PrintMenu();

        // initialise Menu for Power Dissipation
        T::PD PDiss({ 0 });
        PDiss.Add('k', 1);
        std::vector<MenuOption> PDMenuOptions
        {
            MenuOption('a', "Average Power Dissipation"),
            MenuOption('b', "Switching Power Loss"),
            MenuOption('c', "Conduction Power Loss"),
            MenuOption('d', "Change Values"),
            MenuOption('e', "Clear Values"),
            MenuOption('f', "Import Data"),
            MenuOption('g', "Export Data"),
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
            MenuItem('k', "fs", 1),
            MenuItem('l', "Ts", 1),
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
        System::Sleep(1);
        switch (Option)
        {
        case 'a':
            PowerDissipation(PDiss, PDMenu);
            break;
        case 'b':
            // Insert D code
            break;
        case 'x':
            return;
            break;
        default:
            TiseMenu();
            break;
        }
    }
    void Tise::PowerDissipation(PD PDiss, Menu PDMenu)
    {
        System::Clear();
        PDMenu = UpdatePDValues(PDiss, PDMenu);
        PDMenu.PrintMenu();

        char Option = PDMenu.ChooseOption();
        System::Sleep(1);
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
        case 'f':
            PDiss = ImportData(PDiss);
            PowerDissipation(PDiss, PDMenu);
            break;
        case 'g':
            ExportData(PDiss, false);
            PowerDissipation(PDiss, PDMenu);
            break;
        case 'x':
            TiseMenu();
            break;
        default:
            PowerDissipation(PDiss, PDMenu);
            break;
        }
    }
    Menu Tise::ChangeValues(T::PD Pdiss, Menu PDMenu)
    {
        bool ValidOption = 0, ValidValue = 0;
        std::cout << "\nEnter the letter of the value you want to add/change: ";
        char option;
        try { std::cin >> option; }
        catch (const std::exception&) 
        {
            System::Sleep(1);
            std::cout << "\n\tInvalid input";
            System::Sleep(1);
            ChangeValues(Pdiss, PDMenu);
        }
        char AvailableLetters[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r' };
        for (int i = 0; i < 18; i++)
        {
            if (AvailableLetters[i] == option) { ValidOption = 1; }
        }
        if (ValidOption)
        {
            bool loop = 1;
            while (loop)
            {
                std::cout << "\nEnter the value you want to use: ";
                double value;
                try 
                { 
                    std::cin >> value; 
                    if (std::is_floating_point<double>::value)
                    {
                        Pdiss.Add(option, value);
                        PDMenu.ChangeItemValue(option, value);

                        std::cout << "\nItem changed.\n";
                        System::Sleep(1);
                        PowerDissipation(Pdiss, PDMenu);
                        return PDMenu;
                    }
                    else 
                    { 
                        std::cout << "\n\tInvalid value";
                        System::Sleep(1);
                    }
                }
                catch (const std::exception&) 
                { 
                    char exit;
                    std::cin >> exit;
                    if (exit == 'x') { loop = 0; }
                    std::cout << "\n\tInvalid value";
                    System::Sleep(1);
                }
            }
        }
        else
        {
            std::cout << "\n\tInvalid input";
            System::Sleep(1);
            ChangeValues(Pdiss, PDMenu);
        }
    }
    Menu Tise::UpdatePDValues(T::PD Pdiss, Menu PDMenu)
    {
        PDMenu.ChangeItemValue('a', Pdiss.Get('a'));
        PDMenu.ChangeItemValue('b', Pdiss.Get('b'));
        PDMenu.ChangeItemValue('d', Pdiss.Get('d'));
        PDMenu.ChangeItemValue('e', Pdiss.Get('e'));
        PDMenu.ChangeItemValue('i', Pdiss.Get('i'));
        PDMenu.ChangeItemValue('j', Pdiss.Get('j'));
        PDMenu.ChangeItemValue('k', Pdiss.Get('k'));
        PDMenu.ChangeItemValue('l', Pdiss.Get('l'));
        PDMenu.ChangeItemValue('m', Pdiss.Get('m'));
        PDMenu.ChangeItemValue('o', Pdiss.Get('o'));
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
        Pdiss.Add('r',Pdiss.CalcPdis());
        PDMenu.ChangeItemValue('r', Pdiss.CalcPdis());
        return PDMenu;
    }

    void Tise::PDISS(T::PD PDiss, Menu& PDMenu)
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
            System::Sleep(1);
            switch (Option)
            {
            case 'a':
                double pdiss;
                //pdiss = Menu.GetItemValue('a') + Menu.GetItemValue('b');
                pdiss = PDiss.CalcPdis();
                Menu.ChangeItemValue('c', pdiss);
                PDMenu.ChangeItemValue('r', pdiss);
                std::cout << "\nAverage Power Dissipation: " << Menu.GetItemValue('c') << "\n";
                System::Sleep(2);
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
            default:
                break;
            }
        }
        PowerDissipation(PDiss, PDMenu);
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
            MenuItem('b', "fs", 1),
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
            System::Sleep(1);
            switch (Option)
            {
            case 'a':
                double pon;
                pon = PDiss.CalcPon();
                Menu.ChangeItemValue('c', pon);
                PDMenu.ChangeItemValue('q', pon);
                std::cout << "\nConduction Power Loss: " << Menu.GetItemValue('c') << "\n";
                System::Sleep(2);
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
            default:
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
            System::Sleep(1);
            switch (Option)
            {
            case 'a':
                double Won;
                Won = PDiss.CalcWon();
                Menu.ChangeItemValue('d', Won);
                PDMenu.ChangeItemValue('n', Won);
                std::cout << "\nEnergy dissipated during ON state time: " << Menu.GetItemValue('d') << "\n";
                System::Sleep(2);
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
            default:
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
            MenuItem('a', "Ts", 1),
            MenuItem('b', "fs", 1)
        };

        Menu Menu("Switching Period / Frequency", MenuOptions, MenuItems);
        Menu.ChangeItemValue('a', PDMenu.GetItemValue('l'));
        Menu.ChangeItemValue('b', PDMenu.GetItemValue('k'));
        bool loop = 1;
        while (loop)
        {
            Menu.PrintMenu();
            char Option = Menu.ChooseOption();
            System::Sleep(1);
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
            default:
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
            MenuItem('c', "fs", 1),
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
            System::Sleep(1);
            switch (Option)
            {
            case 'a':
                double ps;
                ps = PDiss.CalcPs();
                Menu.ChangeItemValue('d', ps);
                PDMenu.ChangeItemValue('p', ps);
                std::cout << "\nSwitching Power Loss: " << Menu.GetItemValue('d') << "\n";
                System::Sleep(2);
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
            default:
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
            System::Sleep(1);
            switch (Option)
            {
            case 'a':
                double Wcon;
                Wcon = PDiss.CalcWcon();
                Menu.ChangeItemValue('d', Wcon);
                PDMenu.ChangeItemValue('g', Wcon);
                std::cout << "\nEnergy dissipated during ON state time: \n\n\t\t" << Menu.GetItemValue('d') << "\n";
                System::Sleep(2);
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
            default:
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
            System::Sleep(1);
            switch (Option)
            {
            case 'a':
                double Wcoff;
                Wcoff = PDiss.CalcWcoff();
                Menu.ChangeItemValue('d', Wcoff);
                PDMenu.ChangeItemValue('h', Wcoff);
                std::cout << "\nEnergy dissipated during OFF state time: \n\n\t\t\t" << Menu.GetItemValue('d') << "\n";
                System::Sleep(2);
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
            default:
                break;
            }
        }
        PS(PDiss, PDMenu, parent);
    }
    // Outside data
    void Tise::ExportData(PD PDiss, bool newfile)
    {
        if (!newfile)
        {
            // Save to file
            std::cout << "\n\tExporting.";
            std::ofstream SaveFile;
            SaveFile.open("PowerDissipationData.csv");
            SaveFile << "tri," << PDiss.Get('a');
            SaveFile << "\ntfv," << PDiss.Get('b');
            SaveFile << "\ntcon," << PDiss.CalcTcon();
            SaveFile << "\ntrv," << PDiss.Get('d');
            SaveFile << "\ntfi," << PDiss.Get('e');
            SaveFile << "\ntcoff," << PDiss.CalcTcoff();
            SaveFile << "\nWcon," << PDiss.CalcWcon();
            SaveFile << "\nWcoff," << PDiss.CalcWcoff();
            SaveFile << "\nVDC," << PDiss.Get('i');
            SaveFile << "\nIo," << PDiss.Get('j');
            SaveFile << "\nfs," << PDiss.Get('k');
            SaveFile << "\nTs," << PDiss.Get('l');
            SaveFile << "\nVon," << PDiss.Get('m');
            SaveFile << "\nWon," << PDiss.CalcWon();
            SaveFile << "\nTon," << PDiss.Get('o');
            SaveFile << "\nPs," << PDiss.CalcPs();
            SaveFile << "\nPon," << PDiss.CalcPon();
            SaveFile << "\nPdis," << PDiss.CalcPdis();
            SaveFile.close();
            System::Buffer();
            std::cout << "\n\tSaved as 'PowerDissipationData'\n\n";
            System::Sleep(1);
        }
        else
        {
            // Create new file
            std::cout << "\n\tCreating new Data file: 'PowerDissipationData'.";
            std::ofstream SaveFile;
            SaveFile.open("PowerDissipationData.csv");
            SaveFile << "tri,0";
            SaveFile << "\ntfv,0";
            SaveFile << "\ntcon,0";
            SaveFile << "\ntrv,0";
            SaveFile << "\ntfi,0";
            SaveFile << "\ntcoff,0";
            SaveFile << "\nWcon,0";
            SaveFile << "\nWcoff,0";
            SaveFile << "\nVDC,0";
            SaveFile << "\nIo,0";
            SaveFile << "\nfs,1";
            SaveFile << "\nTs,1";
            SaveFile << "\nVon,0";
            SaveFile << "\nWon,0";
            SaveFile << "\nTon,0";
            SaveFile << "\nPs,0";
            SaveFile << "\nPon,0";
            SaveFile << "\nPdis,0";
            SaveFile.close();
            System::Buffer();
            std::cout << "\n\tNew Data file created: 'PowerDissipationData'\n\n";
            System::Sleep(1);
        }
    }
    PD Tise::ImportData(PD PDiss)
    {
        std::ifstream ReadFile;
        std::cout << "\n\nNote: Make sure data is added to this file before importing.\nImporting data from 'PowerDissipationData'.";
        System::Buffer();
        ReadFile.open("PowerDissipationData.csv");
        std::string empty = "";
        std::getline(ReadFile, empty);
        if (empty == "")
        {
            std::cout << "\nError: No file found.\nCreating new blank file.\nImporting blank data.\n";
            System::Sleep(1);
            ExportData(PDiss, true);
        }
        std::string temp;
        T::Data *Values = new T::Data[18]{"",0};
        ReadFile.close();
        ReadFile.open("PowerDissipationData.csv");
        for (int i = 0; i < 18; i++)
        {
            std::getline(ReadFile, temp, ',');
            Values[i].Name = temp;
            std::getline(ReadFile, temp);
            if (temp == "inf") { temp = "0"; }
            Values[i].Values = std::stoi(temp);
        }
        // add to menu
        PDiss.Add('a', Values[0].Values);
        PDiss.Add('b', Values[1].Values);
        PDiss.Add('c', Values[2].Values);
        PDiss.Add('d', Values[3].Values);
        PDiss.Add('e', Values[4].Values);
        PDiss.Add('f', Values[5].Values);
        PDiss.Add('g', Values[6].Values);
        PDiss.Add('h', Values[7].Values);
        PDiss.Add('i', Values[8].Values);
        PDiss.Add('j', Values[9].Values);
        PDiss.Add('k', Values[10].Values);
        PDiss.Add('m', Values[12].Values);
        PDiss.Add('n', Values[13].Values);
        PDiss.Add('o', Values[14].Values);
        PDiss.Add('p', Values[15].Values);
        PDiss.Add('q', Values[16].Values);
        PDiss.Add('r', Values[17].Values);
        ReadFile.close();

        std::cout << "Data Imported\n";
        System::Sleep(1);
        return PDiss;
    }
}