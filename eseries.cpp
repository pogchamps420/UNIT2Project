#include "eseries.h"

namespace npv
{
	Eseries::Eseries(int E)
	{
		_E = E;
		for (int i = 0; i < E24Values.size(); i += 24 / E)
			_values.push_back(E24Values[i]);
	}

	const std::vector<float> Eseries::E24Values = { 1.0,1.1,1.2,1.3,1.5,1.6,1.8,2.8,2.2,2.4,2.7,3.0,3.3,3.6,3.9,4.3,4.7,5.1,5.6,6.2,6.8,7.5,8.2,9.1 };
	
	bool CheckENumber(int E)
	{
		if ((E / 3) % 2 == 0 && E / 6 <= 32)
			return true;
		else if (E == 3)
			return true;
		return false;
	}

}