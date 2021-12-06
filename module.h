//check formula for each module
#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <list>

class Module {
public:
	Module();
	Module(std::string MName, int Year, std::list<std::string> Formulas);

	void set_modulename(std::string _mname);
	void set_yearofstudy(int _year);
	void set_formulas(std::list<std::string> _formulas);
	void edit_formulas(std::list<std::string> _formulas, bool _mode);

	std::string get_modulename();
	int get_yearofstudy();
	std::list<std::string> get_formulas();

private:
	std::string _mname;
	int _year;
	std::list<std::string> _formulas;
};
#endif