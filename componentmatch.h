#ifndef COMPONENTMATCH_H
#define COMPONENTMATCH_H

#include <vector>
#include <iostream>

namespace npv
{
	class ComponentMatch
	{
	public:
		ComponentMatch(std::pair<double, double> values, double calcValue, double target, std::string unit, std::string resultUnit);
		
		void printMatch();
	private:
		std::pair<double, double> _values;
		double _deviationNumerical;
		double _calculatedValue;
		float _deviationPercent;
		std::string _unit;
		std::string _resultUnit;
	};
}



#endif