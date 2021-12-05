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
		std::pair<double,double> FindNearest(double target);
		std::vector<ComponentMatch> MatchPair(double target, double (*Calc)(double, double));

	private:
		bool CheckENumber(int E);
		int _E;
		std::vector<double> _values;
	
	protected:
		static const std::vector<double> E24Values;
	};

}

#endif
