#ifndef ESERIES_H
#define ESERIES_H

#include <vector>
#include <iostream>
#include <unordered_set>
#include "componentmatch.h"

namespace npv
{
	class Eseries
	{
	public:

		Eseries(int E);
		ComponentMatch MatchSingle(float target, float givenValue, float (*Calc)(float, float));
		ComponentMatch MatchPair(float target, float (*Calc)(float, float));

	private:
		bool CheckENumber(int E);
		int _E;
		std::vector<float> _values;
	
	protected:
		static const std::vector<float> E24Values;
	};

}

#endif
