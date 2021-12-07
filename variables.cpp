#include "variables.h"
#include <math.h>

bbc::CONVERTERS::CONVERTERS()
	: _values() {}
bbc::CONVERTERS::CONVERTERS(Values values)
	: _values(values) {}

void bbc::CONVERTERS::AddValues(Values values) { _values = values; }
bbc::CONVERTERS::Values bbc::CONVERTERS::ShowValues() { return _values; }

double bbc::BUCK::CalcVout()
{
	if (_values.Vout == 0) {
		_values.Vout = _values.K * _values.Vin;
	}
	return _values.Vout;
}

double bbc::BOOST::CalcVout()
{
	if (_values.Vout == 0) {
		_values.Vout = _values.Vin * ((1)/(1-_values.K));
	}
	return _values.Vout;
}

double bbc::BUCK::CalcK()
{
	if (_values.K == 0) {
		_values.K = _values.Vout / _values.Vin;
	}
	return _values.K;
}

double bbc::BOOST::CalcK()
{
	if (_values.K == 0) {
		_values.K = (1 - (_values.Vin / _values.Vout));
	}
	return _values.K;
}

double bbc::BUCK::CalcIi()
{
	if (_values.Ii == 0) {
		_values.Ii = _values.K * _values.Io;
	}
	return _values.Ii;
}

double bbc::BOOST::CalcIi()
{
	if (_values.Ii == 0) {
		_values.Ii = _values.Io * ((1) / (1 - _values.K));
	}
	return _values.Ii;
}

double bbc::BUCK::CalcIo()
{
	if (_values.Io == 0) {
		_values.Io = _values.Ii / _values.K;
	}
	return _values.Io;
}

double bbc::BOOST::CalcIo()
{
	if (_values.Io == 0) {
		_values.Io = ((1-_values.K) / _values.Ii);
	}
	return _values.Io;
}

double bbc::BUCK::CalcL()
{
	if (_values.L == 0) {
		_values.L = ((_values.Vin - _values.Vout) * _values.K) / (_values.Fs * _values.delta_i);
	}
	return _values.L;
}

double bbc::BOOST::CalcL()
{
	if (_values.L == 0) {
		_values.L = ((_values.Vin  * _values.K) / (_values.Fs * _values.delta_i));
	}
	return _values.L;
}

double bbc::CONVERTERS::CalcRl()
{
	if (_values.Rl == 0) {
		_values.Rl = _values.Vl / _values.Il;
	}
	return _values.Rl;
}

double bbc::BUCK::CalcC()
{
	if (_values.C == 0) {
		_values.C = ((_values.Vin - _values.Vout) / (8*pow(_values.Fs, 2)*_values.delta_vo*_values.L) * _values.K);
	}
	return _values.C;
}

double bbc::BOOST::CalcC()
{
	if (_values.C == 0) {
		_values.C = ((_values.K * _values.Ts) / (_values.Ro * _values.C));
	}
	return _values.C;
}

double bbc::CONVERTERS::CalcPi()
{
	if (_values.Pi == 0) {
		_values.Pi = (_values.Vin * _values.Ii);
	}
	return _values.Pi;
}

double bbc::CONVERTERS::CalcPo()
{
	if (_values.Po == 0) {
		_values.Po = (_values.Vout * _values.Io);
	}
	return _values.Po;
}



void bbc::CONVERTERS::ClearValues()
{
	Values newValues = {};
	_values = newValues;
}

void bbc::CONVERTERS::Add(char option, double value)
{
	switch (option)
	{
	case 'a':
		_values.Vin = value;
		break;
	case 'b':
		_values.Vout = value;
		break;
	case 'c':
		_values.Vl = value;
		break;
	case 'd':
		_values.K = value;
		break;
	case 'e':
		_values.Ii = value;
		break;
	case 'f':
		_values.Io = value;
		break;
	case 'g':
		_values.Il = value;
		break;
	case 'h':
		_values.Po = value;
		break;
	case 'i':
		_values.L = value;
		break;
	case 'j':
		_values.delta_vo = value;
		break;
	case 'k':
		_values.Fs = value;
		_values.Ts = (float)1 / value;
		break;
	case 'l':
		_values.Ts = value;
		_values.Fs = (float)1 / value;
		break;
	case 'm':
		_values.delta_i = value;
		break;
	case 'n':
		_values.Rl = value;
		break;
	case 'o':
		_values.Ro = value;
		break;
	case 'p':
		_values.C = value;
		break;
	case 'q':
		_values.Pi = value;
		break;
	default:
		break;
	}
}
double bbc::CONVERTERS::Get(char option)
{
	switch (option)
	{
	case 'a':
		return _values.Vin;
		break;
	case 'b':
		return _values.Vout;
		break;
	case 'c':
		return _values.Vl;
		break;
	case 'd':
		return _values.K;
		break;
	case 'e':
		return _values.Ii;
		break;
	case 'f':
		return _values.Io;
		break;
	case 'g':
		return _values.Il;
		break;
	case 'h':
		return _values.Po;
		break;
	case 'i':
		return _values.L;
		break;
	case 'j':
		return _values.delta_vo;
		break;
	case 'k':
		return _values.Fs;
		break;
	case 'l':
		return _values.Ts;
		break;
	case 'm':
		return _values.delta_i;
		break;
	case 'n':
		return _values.Rl;
		break;
	case 'o':
		return _values.Ro;
		break;
	case 'p':
		return _values.C;
		break;
	case 'q':
		return _values.Pi;
		break;
	default:
		return 0;
	}
}