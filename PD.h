#pragma once
#ifndef PD_H
#define PD_H
namespace T
{
	class PD
	{
		struct Values
		{
			double tri;
			double tfv;
			double tcon;
			double trv;
			double tfi;
			double tcoff;
			double Wcon;
			double Wcoff;
			double VDC;
			double Io;
			double fs;
			double Ts;
			double Von;
			double Won;
			double Ton;
			double Ps;
			double Pon;
			double Pdis;
		};
		public:
			PD();
			PD(Values values);
			PD(double Wcon, double Wcoff, double fs, double Won);



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

			void Add(int option, int value);

		private:
			Values _values;
	};
}

#endif