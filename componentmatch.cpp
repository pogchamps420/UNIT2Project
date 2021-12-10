#include "componentmatch.h"


namespace npv
{
	ComponentMatch::ComponentMatch(std::pair<double, double> values, double calcValue, double target, std::string unit, std::string resultUnit)
	{
		_values = values;
		_calculatedValue = calcValue;
		_deviationNumerical = calcValue - target;
		_deviationPercent = _deviationNumerical / target;
		_unit = unit;
		_resultUnit = resultUnit;
	}
	
	void ComponentMatch::printMatch()
	{
		std::cout << "Value one: " << _values.first << " " << _unit << '\n';
		std::cout << "Value two: " << _values.second << " " << _unit << '\n';
		std::cout << "Calculated result: " << _calculatedValue << " " << _resultUnit << '\n';
		std::cout << "Deviation from target result: " << _deviationNumerical << " " << _resultUnit << " (" << _deviationPercent * 100 << "%)\n";
	}
}
