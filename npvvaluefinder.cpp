#include "npvvaluefinderh.h"

void npvfinder::RunNpvFinder()
{
	std::vector<MenuItem> npvItems
	{
		MenuItem('e', "Selected E series number",0),
		MenuItem('v', "Value to match", 0)
	};

	std::vector<MenuOption> npvOptions
	{
		MenuOption('a', "Change variable value"),
		MenuOption('b', "Show the values in the E series"),
		MenuOption('c', "Get nearest NPV value"),
		MenuOption('x', "Exit")
	};

	Menu npvMenu("NPV value finder", npvOptions, npvItems);

	bool npvwhile = true;

	while (npvwhile)
	{
		npvMenu.PrintMenu();
		char npvSelect = npvMenu.ChooseOption();
		char caseSelect;
		double caseDouble;

		switch (npvSelect)
		{

		case 'a':
		{
			std::cout << "Choose variable to change: ";
			std::cin >> caseSelect;
			if (caseSelect == 'e' || caseSelect == 'v')
			{
				std::cout << "Enter new value: ";
				std::cin >> caseDouble;
				npvMenu.ChangeItemValue(caseSelect, caseDouble);
			}
			else
			{
				std::cout << "ERROR: invalid variable identifier, press enter to continue...\n";
				while (std::cin.get() != '\n');
			}
			break;
		}

		case 'b':
		{
			if (npv::CheckENumber(npvMenu.GetItemValue('v')))
			{
				npv::Eseries printSeries(npvMenu.GetItemValue('v'));
				printSeries.PrintSeries();
			}
			else
			{
				std::cout << "ERROR: invalid E series number, press enter to continue...\n";
				while (std::cin.get() != '\n');
			}
			break;
		}

		case 'c':
		{
			if (npv::CheckENumber(npvMenu.GetItemValue('v')))
			{
				npv::Eseries changeSeries(npvMenu.GetItemValue('v'));
				std::pair<double, double> foundValue = changeSeries.FindNearest(npvMenu.GetItemValue('v'));
				if (foundValue.first == foundValue.second)
				{
					npvMenu.ChangeItemValue('v', foundValue.first);
				}
				else
				{
					std::cout << "Option 1: " << foundValue.first << '\n';
					std::cout << "Option 2: " << foundValue.second << '\n';
					std::cout << "Choose the option: ";
					std::cin >> caseSelect;
					if (caseSelect == '1')
						npvMenu.ChangeItemValue('v', foundValue.first);
					else if (caseSelect == '2')
						npvMenu.ChangeItemValue('v', foundValue.second);
					else
					{
						std::cout << "ERROR: incorrect option selected, press enter to continue...";
						while (std::cin.get() != '\n');
					}
				}
			}
			else
			{
				std::cout << "ERROR: invalid E series number, press enter to continue...\n";
				while (std::cin.get() != '\n');
			}
			break;
		}
		}
	}

}
