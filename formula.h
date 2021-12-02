//add, view, select formula
#ifndef FORMULA_H
#define FORMULA_H

#include <string>
#include <list>

struct TheFormula {
	int a, b;
	std::string f;
};

class Formula {
public:
	Formula();
	Formula(std::string fname, TheFormula formula);

	void set_fname(std::string _fname);
	void edit_formula(TheFormula _formula);

	std::string get_fname();
	std::string get_f();

private:
	std::string _fname;
	TheFormula _formula;
	std::string _f;
};
#endif