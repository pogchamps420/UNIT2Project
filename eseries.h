#ifndef ESERIES_H
#define ESERIES_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "componentmatch.h"

namespace npv
{
	class Eseries
	{
	public:

		Eseries(int E);
		std::pair<float,float> FindNearest(float target);
		std::vector<ComponentMatch> MatchPair(float target, float (*Calc)(float, float));

	private:
		bool CheckENumber(int E);
		int _E;
		std::vector<float> _values;
	
	protected:
		static const std::vector<float> E24Values;
	};

}

#endif
