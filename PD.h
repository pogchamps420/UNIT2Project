#pragma once
#ifndef PD_H
#define PD_H

namespace T
{
	class PD
	{
		struct Values
		{
			int tri;
			int tfv;
			int tcon;
			int trv;
			int tfi;
			int tcoff;
			int Wcon;
			int Wcoff;
			int VDC;
			int Io;
			int fs;
			int Ts;
			int Von;
			int Won;
			int Ton;
			int Ps;
			int Pon;
			int Pdis;
		};
		public:
			PD();
			PD(Values values);
			PD(int Wcon, int Wcoff, int fs, int Won);

			void AddValues(Values _values);
			Values ShowValues();
			int CalcTcon();
			int CalcTcoff();
			int CalcWcon();
			int CalcWcoff();
			int CalcPs();
			int CalcWon();
			int CalcPon();
			int CalcPdis();
			void ClearValues();

			void Add(int option, int value);

		private:
			/*
			int tri = _tri;
			int tfv = _tfv;
			int tcon = _tcon;
			int trv = _trv;
			int tfi = _tfi;
			int tcoff = _tcoff;
			int Wcon = _Wcon;
			int Wcoff = _Wcoff;
			int VDC = _VDC;
			int Io = _Io;
			int fs = _fs;
			int Ts = _Ts;
			int Von = _Von;
			int Won = _Won;
			int Ton = _Ton;
			int Ps = _Ps;
			int Pon = _Pon;
			int Pdis = _Pdis;
			*/
			Values _values;
	};
}

#endif