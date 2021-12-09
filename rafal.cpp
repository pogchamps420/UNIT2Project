#include "rafal.h"

namespace rafal
{
	void Rafal()
	{
		System::Clear();

		std::vector<MenuOption> rafalOptions
		{
			MenuOption('a', "Run NPV value finder"),
			MenuOption('b', "Run resistor potential divider calculator"),
			MenuOption('x', "Return to main menu")
		};

		Menu rafalMenu("Rafal's Menu", rafalOptions, std::vector<MenuItem> {});
		rafalMenu.PrintMenu();

		char rafalc = rafalMenu.ChooseOption();

		switch (rafalc)
		{
		case 'a':
			break;
		
		case 'b':
			potdiv::RunDividerCalculator();
			break;
		
		case 'x':
			break;

		}
	}
}