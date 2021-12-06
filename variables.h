#pragma once
#ifndef VARIABLES_H
#define VARIABLES_H 
namespace bbc
{
	class CONVERTERS
	{
		struct Values
		{
			double Vin;
			double Vout;

		};
	public:
		CONVERTERS();
		CONVERTERS(Values values);
		CONVERTERS(double Wcon, double Wcoff, double fs, double Won);



		void AddValues(Values _values);
		Values ShowValues();
		double CalcTcon();
		double CalcTcoff();
		double CalcWcon();
		double CalcWcoff();
		double CalcPs();
		double CalcWon();
		double CalcPon();
		double CalcPdis();
		void ClearValues();

		void Add(char option, double value);
		double Get(char option);

	private:
		Values _values;
	};
}

#endif
