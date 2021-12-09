#ifndef ESERIES_H
#define ESERIES_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include "componentmatch.h"

namespace npv
{

	bool CheckENumber(int E);

	class Eseries
	{
	public:

		Eseries(int E);
		std::pair<double,double> FindNearest(double target);
		/*std::vector<ComponentMatch> MatchPair(double target, double givenValue,
			double (*Calc)(double, double), double (*InverseCalc)(double, double), std::string unit, std::string resultUnit);*/

	private:
		int _E;
		std::vector<double> _values;
	protected:
		static const std::vector<double> E24Values;
	};

}

#endif
