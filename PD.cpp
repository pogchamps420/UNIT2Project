#include "PD.h"

T::PD::PD()
	: _values() {}
T::PD::PD(Values values)
	: _values(values) {}

void T::PD::AddValues(Values values) { _values = values; }
T::PD::Values T::PD::ShowValues() { return _values; }

int T::PD::CalcTcon()
{
	if (_values.tcon == 0) {
		_values.tcon = _values.tri + _values.tfv;
	}
	return _values.tcon;
}
int T::PD::CalcTcoff()
{
	if (_values.tcoff == 0) {
		_values.tcoff = _values.trv + _values.tfi;
	}
	return _values.tcoff;
}
int T::PD::CalcWcon()
{
	if (_values.Wcon == 0) {
		_values.Wcon = 0.5 * _values.VDC * _values.Io * CalcTcon();
	}
	return _values.Wcon;
}
int T::PD::CalcWcoff()
{
	if (_values.Wcoff == 0) {
		_values.Wcoff = 0.5 * _values.VDC * _values.Io * CalcTcoff();
	}
	return _values.Wcoff;
}
int T::PD::CalcPs()
{
	if (_values.Ps == 0) {
		_values.Ps = (CalcWcon() + CalcWcoff()) * _values.fs;
	}
	return _values.Ps;
}
int T::PD::CalcWon()
{
	if (_values.Won == 0) { _values.Won = _values.Von * _values.Io * CalcTcon(); }
	return _values.Won;
}
int T::PD::CalcPon()
{
	if (_values.Pon == 0) {
		_values.Pon = CalcWon() * _values.fs;
	}
	return _values.Pon;
}
int T::PD::CalcPdis()
{
	_values.Pdis = CalcPs() + CalcPon();
	return _values.Pdis;
}
void T::PD::ClearValues()
{
	Values newValues = {};
	_values = newValues;
}

void T::PD::Add(int option, int value)
{
	switch (option)
	{
		case 1:
			_values.tri = value;
			break;
		case 2:
			_values.tfv = value;
			break;
		case 3:
			_values.tcon = value;
			break;
		case 4:
			_values.trv = value;
			break;
		case 5:
			_values.tfi = value;
			break;
		case 6:
			_values.tcoff = value;
			break;
		case 7:
			_values.Wcon = value;
			break;
		case 8:
			_values.Wcoff = value;
			break;
		case 9:
			_values.VDC = value;
			break;
		case 10:
			_values.Io = value;
			break;
		case 11:
			_values.fs = value;
			break;
		case 12:
			_values.Ts = value;
			break;
		case 13:
			_values.Von = value;
			break;
		case 14:
			_values.Won = value;
			break;
		case 15:
			_values.Ton = value;
			break;
		case 16:
			_values.Ps = value;
			break;
		case 17:
			_values.Pon = value;
			break;
		case 18:
			_values.Pdis = value;
			break;
		default:
			break;
	}
}