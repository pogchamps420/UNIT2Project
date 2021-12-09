#pragma once
#ifndef VARIABLES_H
#define VARIABLES_H 
//variables buck and boost have in common: Pi, Po
//variables they differ on: Vout, Ii, Io, Vl, C, delta_vo, K, L
namespace bbc
{
	class CONVERTERS
	{
		struct Values
		{
			double Vin;
			double Vout;
			double Vl;
			double K;
			double Ii;
			double Io;
			double Il;
			double Fs;
			double L;
			double delta_vo;
			double delta_i;
			double Rl;
			double Ro;
			double C;
			double Pi;
			double Po;
			double Ts;


		};
	public:
		CONVERTERS();
		CONVERTERS(Values values);
		
		void AddValues(Values _values);
		Values ShowValues();
		double CalcPi();
		double CalcPo();
		double CalcRl();
		double CalcVlON();
		double CalcVlOFF();
		double CalcFs();
		//separate implementation for delta i and delta output voltage
		std::string Calculus();
		void ClearValues();

		void Add(char option, double value);
		double Get(char option);

		Values _values;

	private:
		
	};

	struct BUCK: public CONVERTERS
	{
	//public:
		BUCK();
		double CalcVout();
		double CalcK();
		double CalcIi();
		double CalcIo();
		double CalcL();
		double CalcC();
	};

	struct BOOST: public CONVERTERS
	{
	//public:
		BOOST();
		double CalcVout();
		double CalcK();
		double CalcIi();
		double CalcIo();
		double CalcL();
		double CalcC();
	};
}

#endif
