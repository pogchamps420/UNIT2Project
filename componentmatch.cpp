#include "componentmatch.h"


namespace npv
{
	ComponentMatch::ComponentMatch(std::vector<float> values, float deviationNumerical, float target)
	{
		for (auto value : values)
			_values.push_back(value);
		_deviationNumerical = deviationNumerical;
		_deviationPercent = deviationNumerical / target;
	}
	
	void ComponentMatch::printMatch()
	{

	}
}
