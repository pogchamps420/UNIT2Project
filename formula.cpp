//  add a database to hold all formulas, formulas are retrieved by name
#include "formula.h"

Formula::Formula()
	: _fname("Test"), _formula() {}
Formula::Formula(std::string fname, TheFormula formula)
	: _fname(fname), _formula() {}

void Formula::set_fname(std::string fname) { _fname = fname; }
void Formula::edit_formula(TheFormula formula) { _formula = formula; }

std::string Formula::get_fname() { return _fname; }
std::string Formula::get_f() { return _f; }eturn _f; }