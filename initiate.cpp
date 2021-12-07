#include "initiate.h"

Initiate::Initiate()
	: _profile(0) {}
Initiate::Initiate(int Profile)
	: _profile(Profile) {}

void Initiate::set_profile(int _profile)
{
	switch (_profile)
	{
	case 0:
		Initiate::testprofile();
		break;
	default:
		Initiate::defaultprofile();
		break;
	}
}
/*User Initiate::get_user()
{
	return _user;
}
*/
void Initiate::defaultprofile()
{
	std::cout << "hi" << std::endl;
}
void Initiate::testprofile()
{
	std::cout << "Profile: Test\n\n" << std::endl;

	//create user
	//User testUser;

	//create modules
	Module M0200;

	//create formulas
	Formula formula1("formula1name", { 1,2,"a+b" }); //placeholders till formula is defined
	Formula m0f0("formula2name", { 6,3,"a/b" });
	Formula m1f0("formula4name", { 1,5,"a*b" });
	Formula m2f0("formula6name", { 7,2,"a-b" });

	//create/add modules
	//std::list<std::string> Mods = testUser.get_modules();

	//add formulas to modules
	std::list<std::string> Formulas = M0200.get_formulas();
	Formulas.push_back(formula1.get_fname());
	Formulas.push_back(m0f0.get_fname());
	Formulas.push_back(m1f0.get_fname());
	Formulas.push_back(m2f0.get_fname());
	M0200.set_formulas(Formulas);

	//commit modules
	//Mods.push_back(M0200.get_modulename());
	//testUser.set_modules(Mods);

	//set info to user
	//_user = testUser;
}