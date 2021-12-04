#ifndef COMPONENTMATCH_H
#define COMPONENTMATCH_H

#include <vector>

namespace npv
{
	class ComponentMatch
	{
	public:
		ComponentMatch(std::vector<float> values, float deviationNumerical, float target);
		
		void printMatch();
	private:
		std::vector<float> _values;
		float _deviationNumerical;
		float _deviationPercent;
	};
}



#endif