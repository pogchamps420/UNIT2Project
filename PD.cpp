#include "PD.h"

T::PD::PD()
	: _values() {}
T::PD::PD(Values values)
	: _values(values) {}

void T::PD::AddValues(Values values) { _values = values; }
T::PD::Values T::PD::ShowValues() { return _values; }

double T::PD::CalcTcon()
{
	if (_values.tcon == 0) {
		_values.tcon = _values.tri + _values.tfv;
	}
	return _values.tcon;
}
double T::PD::CalcTcoff()
{
	if (_values.tcoff == 0) {
		_values.tcoff = _values.trv + _values.tfi;
	}
	return _values.tcoff;
}
double T::PD::CalcWcon()
{
	if (_values.Wcon == 0) {
		_values.Wcon = 0.5 * _values.VDC * _values.Io * CalcTcon();
	}
	return _values.Wcon;
}
double T::PD::CalcWcoff()
{
	if (_values.Wcoff == 0) {
		_values.Wcoff = 0.5 * _values.VDC * _values.Io * CalcTcoff();
	}
	return _values.Wcoff;
}
double T::PD::CalcPs()
{
	if (_values.Ps == 0) {
		_values.Ps = (CalcWcon() + CalcWcoff()) * _values.fs;
	}
	return _values.Ps;
}
double T::PD::CalcWon()
{
	if (_values.Won == 0) { _values.Won = _values.Von * _values.Io * CalcTcon(); }
	return _values.Won;
}
double T::PD::CalcPon()
{
	if (_values.Pon == 0) {
		_values.Pon = CalcWon() * _values.fs;
	}
	return _values.Pon;
}
double T::PD::CalcPdis()
{
	_values.Pdis = CalcPs() + CalcPon();
	return _values.Pdis;
}
void T::PD::ClearValues()
{
	Values newValues = {};
	_values = newValues;
}

void T::PD::Add(char option, double value)
{
	switch (option)
	{
		case 'a':
			_values.tri = value;
			break;
		case 'b':
			_values.tfv = value;
			break;
		case 'c':
			_values.tcon = value;
			break;
		case 'd':
			_values.trv = value;
			break;
		case 'e':
			_values.tfi = value;
			break;
		case 'f':
			_values.tcoff = value;
			break;
		case 'g':
			_values.Wcon = value;
			break;
		case 'h':
			_values.Wcoff = value;
			break;
		case 'i':
			_values.VDC = value;
			break;
		case 'j':
			_values.Io = value;
			break;
		case 'k':
			_values.fs = value;
			_values.Ts = (float)1 / value;
			break;
		case 'l':
			_values.Ts = value;
			_values.fs = (float)1 / value;
			break;
		case 'm':
			_values.Von = value;
			break;
		case 'n':
			_values.Won = value;
			break;
		case 'o':
			_values.Ton = value;
			break;
		case 'p':
			_values.Ps = value;
			break;
		case 'q':
			_values.Pon = value;
			break;
		case 'r':
			_values.Pdis = value;
			break;
		default:
			break;
	}
}
double T::PD::Get(char option)
{
	switch (option)
	{
	case 'a':
		return _values.tri;
	case 'b':
		return _values.tfv;
	case 'c':
		return _values.tcon;
	case 'd':
		return _values.trv;
	case 'e':
		return _values.tfi;
	case 'f':
		return _values.tcoff;
	case 'g':
		return _values.Wcon;
	case 'h':
		return _values.Wcoff;
	case 'i':
		return _values.VDC;
	case 'j':
		return _values.Io;
	case 'k':
		return _values.fs;
	case 'l':
		return _values.Ts;
	case 'm':
		return _values.Von;
	case 'n':
		return _values.Won;
	case 'o':
		return _values.Ton;
	case 'p':
		return _values.Ps;
	case 'q':
		return _values.Pon;
	case 'r':
		return _values.Pdis;
	default:
		return 0;
	}
}