#include "variables.h"


bbc::CONVERTERS::CONVERTERS()
	: _values() {}
bbc::CONVERTERS::CONVERTERS(Values values)
	: _values(values) {}

//bbc::BUCK::BUCK(Values values)
//	:  {_values = values; }

//bbc::BOOST::BOOST(Values values)
//	: {_values = values; }

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

double bbc::CONVERTERS::CalcVlON()
{
	if (_values.Vl == 0) {
		_values.Vl = (_values.L) * ((_values.delta_i) / (_values.K * _values.Ts));
	}
	return _values.Vl;
}

double bbc::CONVERTERS::CalcVlOFF()
{
	if (_values.Vl == 0) {
		_values.Vl = (_values.L) * ((_values.delta_i) / ((1 - _values.K) * _values.Ts));
	}
	return _values.Vl;
}

double bbc::CONVERTERS::CalcFs()
{
	if (_values.Fs == 0) {
		_values.Fs = ( 1 / _values.Ts );
	}
	return _values.Fs;
}

bool is_number(const std::string& word) {
		return !word.empty() && std::all_of(word.begin(), word.end(), ::isdigit);
	}

std::string bbc::CONVERTERS::Calculus()
{

	//bool is_number(const std::string & word) {
	//	return !word.empty() && std::all_of(word.begin(), word.end(), ::isdigit);
	//}

	std::string expression;
	std::cin >> expression;
	std::string exponent("^");

	//we need to account for calculus with a constant and of variables with exponents..
	//first we should check if it is a constant using isdigit lmao

	char CalcOption;
	std::cout << "Please enter 1 for Differentiation or 2 for Integration: ";
	std::cin >> CalcOption;

	switch (CalcOption) {
		// Differentiation
	case '1': {
		if (is_number(expression)) {
			//std::cout << "It's a constant.\n";
			std::cout << "0";
			return "";
		}
		else {
			// it'll be a variable or exponent lol
			std::size_t found = exponent.find(expression);
			found = expression.find("^");

			if (found != std::string::npos) {
				// do the differentiation
				std::cout << "It's a power term\n";
				std::string coeff = expression.substr(0, found);
				std::cout << coeff << "\n";
				std::string power = expression.substr(found + 1);
				std::cout << power << "\n";
				//std::string new_coeff = coeff * power;
				//std::cout << new_coeff;

				double new_coeff = std::stod(coeff);
				std::cout << typeid(new_coeff).name() << "\n";

				double new_power = std::stod(power);
				std::cout << typeid(new_power).name() << "\n";

				double result = new_coeff * new_power;
				std::cout << result << "\n";

				new_power -= 1;
				std::cout << new_power << "\n";

				std::cout << result << "x^" << new_power;

				//return value
				std::string first = std::to_string(result);
				std::string last = std::to_string(new_power);
				std::string new_expression = first + "x^" + last;
				std::cout << new_expression;
				return new_expression;

				
			}
			else {
				std::cout << "It's a term with a linear coefficient\n";

				//just remove the variable from the term hehe
				int index = 0;
				for (int x = 0; x < expression.length(); x++) {
					if (isdigit(expression[x])) {
						expression[index] = expression[x];
						index++;
					}
				}

				std::string lin_result = expression.substr(0, index);
				return lin_result;
				//std::cout << expression.substr(0, index);

			}
		}
		break;
	}
			// Integration
	case '2': {

		if (is_number(expression)) {
			std::cout << "It's a constant.\n";
			//return the constant plus the variable
			std::string const_expression = expression + "x\n";
			std::cout << expression << "x\n";
			return const_expression;
		}
		else {
			// it'll be a linear coefficient variable or exponent lol
			std::size_t found = exponent.find(expression);
			found = expression.find("^");

			std::string coeff = expression.substr(0, found);
			std::cout << coeff << "\n";

			double new_coeff = std::stod(coeff);
			std::cout << typeid(new_coeff).name() << "\n";

			if (found != std::string::npos) {
				std::cout << "It's a power term";
				// do the integration..
				std::string power = expression.substr(found + 1);
				std::cout << power << "\n";
				//std::string new_coeff = coeff * power;
				//std::cout << new_coeff;

				double new_power = std::stod(power);
				std::cout << typeid(new_power).name() << "\n";

				new_power += 1;
				std::cout << new_power << "\n";

				double result = new_coeff / new_power;
				std::cout << result << "\n";
				std::cout << result << "x^" << new_power << "\n";

				//return value
				std::string first = std::to_string(result);
				std::string last = std::to_string(new_power);
				std::string new_expression = first + "x^" + last;
				std::cout << new_expression;
				return new_expression;
			}
			else {

				double half_coeff = new_coeff / 2;
				std::string prefix = std::to_string(half_coeff);
				std::cout << "It's a term with a linear coefficient\n";
				//std::cout << new_coeff / 2 << "x^2";
				std::string linear_result = prefix + "x^2";
				return linear_result;
			}
		}
	}
	default:
		std::cout << "oops";
		return "";
	} 
	//return "";
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