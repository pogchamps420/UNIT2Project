#include "potentialdivider.h"

namespace potdiv
{
	double OutVoltage(double vin, double ratio)
	{
		return vin * ratio;
	}

	double Ratio(double ra, double rb)
	{
		return rb / (ra + rb);
	}

	double RaFromRatio(double rb, double ratio)
	{
		return rb / ratio - rb;
	}

	double RbFromRatio(double ra, double ratio)
	{
		return ra * ratio / (1 - ratio);
	}

	double InVoltage(double vout, double ratio)
	{
		return vout / ratio;
	}

	double MakeResistorANpv(int E, double rb, double vin, double targetVout)
	{
		double newRa = RaFromRatio(rb, targetVout / vin);
		npv::Eseries raSeries(E);
		std::pair<double, double> newRaPair = raSeries.FindNearest(newRa);
		double matchedVout1 = OutVoltage(vin, Ratio(newRaPair.first, rb));
		double matchedVout2 = OutVoltage(vin, Ratio(newRaPair.second, rb));
		npv::ComponentMatch match1(std::make_pair(newRaPair.first, rb), matchedVout1, targetVout, "Ohms", "V");
		npv::ComponentMatch match2(std::make_pair(newRaPair.second, rb), matchedVout2, targetVout, "Ohms", "V");
		std::cout << "------------------------------------\n";
		std::cout << "MATCH: 1\n";
		match1.printMatch();
		std::cout << "------------------------------------\n";
		std::cout << "MATCH: 2\n";
		match2.printMatch();
		std::cout << "------------------------------------\n";
		char chosenMatch;
	choose_match_err:;
		std::cout << "Choose one of the given matches: ";
		std::cin >> chosenMatch;
		if (chosenMatch == '1')
			return newRaPair.first;
		else if (chosenMatch == '2')
			return newRaPair.second;
		else
			goto choose_match_err;
	}

	double MakeResistorBNpv(int E, double ra, double vin, double targetVout)
	{
		double newRa = RbFromRatio(ra, targetVout / vin);
		npv::Eseries rbSeries(E);
		std::pair<double, double> newRbPair = rbSeries.FindNearest(newRa);
		double matchedVout1 = OutVoltage(vin, Ratio(ra, newRbPair.first));
		double matchedVout2 = OutVoltage(vin, Ratio(ra, newRbPair.second));
		npv::ComponentMatch match1(std::make_pair(ra, newRbPair.first), matchedVout1, targetVout, "Ohms", "V");
		npv::ComponentMatch match2(std::make_pair(ra, newRbPair.second), matchedVout2, targetVout, "Ohms", "V");
		std::cout << "------------------------------------\n";
		std::cout << "MATCH: 1\n";
		match1.printMatch();
		std::cout << "------------------------------------\n";
		std::cout << "MATCH: 2\n";
		match2.printMatch();
		std::cout << "------------------------------------\n";
		char chosenMatch;
	choose_match_err:;
		std::cout << "Choose one of the given matches: ";
		std::cin >> chosenMatch;
		if (chosenMatch == '1')
			return newRbPair.first;
		else if (chosenMatch == '2')
			return newRbPair.second;
		else
			goto choose_match_err;
	}

	void RunDividerCalculator()
	{
		std::vector<MenuItem> dividerItems
		{
			MenuItem('a',"Ra - first resistor value [Ohms]", 0),
			MenuItem('b',"Rb - second resistor value [Ohms]", 0),
			MenuItem('i',"Vin - input voltage [V]", 0),
			MenuItem('o',"Vout - output voltage [V]", 0)
		};

		std::vector<MenuOption> dividerOptions
		{
			MenuOption('a',"Change variable"),
			MenuOption('b',"Calculate one of the values"),
			MenuOption('c',"Get an NPV value of one of the resistors"),
			MenuOption('o',"Clear variables"),
			MenuOption('x',"Exit")
		};

		Menu dividerMenu("Resistor potential divider calculator", dividerOptions, dividerItems);
		while(true)
		{
			dividerMenu.PrintMenu();
			char ident = dividerMenu.ChooseOption();
			int E;
			char chIdent; 
			double chValue, ratio, otherRes;

			switch (ident)
			{
			case 'a':
			a_err:;
				std::cout << "Choose the variable you wish to change: ";
				std::cin >> chIdent;
				if (chIdent != 'a' && chIdent != 'b' && chIdent != 'o' && chIdent != 'i')
					goto a_err;
				std::cout << "Enter new value: ";
				std::cin >> chValue;
				dividerMenu.ChangeItemValue(chIdent, chValue);
				break;
				
			case 'b':
			b_err:;
				std::cout << "Choose the value you wish to calculate: ";
				std::cin >> chIdent;
				switch (chIdent)
				{
				case 'a':
					ratio = dividerMenu.GetItemValue('o') / dividerMenu.GetItemValue('i');
					dividerMenu.ChangeItemValue('a', RaFromRatio(dividerMenu.GetItemValue('b'), ratio));
					break;
				case 'b':
					ratio = dividerMenu.GetItemValue('o') / dividerMenu.GetItemValue('i');
					dividerMenu.ChangeItemValue('b', RbFromRatio(dividerMenu.GetItemValue('a'), ratio));
					break;
				case 'o':
					ratio = Ratio(dividerMenu.GetItemValue('a'), dividerMenu.GetItemValue('b'));
					dividerMenu.ChangeItemValue('o', OutVoltage(dividerMenu.GetItemValue('i'), ratio));
					break;
				case 'i':
					ratio = Ratio(dividerMenu.GetItemValue('a'), dividerMenu.GetItemValue('b'));
					dividerMenu.ChangeItemValue('i', InVoltage(dividerMenu.GetItemValue('o'), ratio));
					break;
				default:
					std::cout << "ERROR: invalid input\n";
					goto b_err;
					break;
				}
				break;

			case 'c':
			ce_err:;
				std::cout << "Enter the E value of the preferred value series: ";
				std::cin >> E;
				if (!npv::CheckENumber(E))
				{
					std::cout << "ERROR: incvalid E number\n";
					goto ce_err;
				}
			cr_err:;
				std::cout << "Choose the resistor to change: ";
				std::cin >> chIdent;
				if (chIdent == 'a')
				{
					chValue = MakeResistorANpv(E, dividerMenu.GetItemValue('b'), dividerMenu.GetItemValue('i'), dividerMenu.GetItemValue('o'));
					dividerMenu.ChangeItemValue('a', chValue);
				}
				else if (chIdent == 'b')
				{
					chValue = MakeResistorBNpv(E, dividerMenu.GetItemValue('a'), dividerMenu.GetItemValue('i'), dividerMenu.GetItemValue('o'));
					dividerMenu.ChangeItemValue('b', chValue);	
				}
				else
				{
					std::cout << "ERROR: not a valid resistor identifier\n";
					goto cr_err;
				}

				ratio = Ratio(dividerMenu.GetItemValue('a'), dividerMenu.GetItemValue('b'));
				dividerMenu.ChangeItemValue('o', OutVoltage(dividerMenu.GetItemValue('i'), ratio));
				
				break;

			case 'x':
				goto exit_pot_div;
				break;
			}
			std::system("cls");
		}
	exit_pot_div:;
	}
}