#include "module.h"

Module::Module()
	: _mname("0200"), _year(0), _formulas() {}
Module::Module(std::string mname, int year, std::list<std::string> formulas)
	: _mname(mname), _year(year), _formulas(formulas) {}

void Module::set_modulename(std::string mname) { _mname = mname; }
void Module::set_yearofstudy(int year) { _year = year; }
void Module::set_formulas(std::list<std::string> formulas) { _formulas = formulas; }

std::string Module::get_modulename() { return _mname; }
int Module::get_yearofstudy() { return _year; }
std::list<std::string> Module::get_formulas() { return _formulas; }

//edit
void Module::edit_formulas(std::list<std::string> formulas, bool mode)
{
	//mode 0 = add a formula, 1 = remove a formula
}