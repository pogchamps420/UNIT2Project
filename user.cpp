#include "user.h"

User::User()
	: _userID(201446249), _forename("Bob"), _surname("Marley"), _username("Yo"), _password("Yo"), _mods({ "0000","0100" }) {}
User::User(PersonalInfo pinfo, std::list<std::string> mods)
	: _pinfo({ pinfo }), _mods(mods) {}
User::User(int userID, std::string forename, std::string surname, std::string username, std::list<std::string> mods)
	: _userID(userID), _forename(forename), _surname(surname), _username(username), _mods(mods) {}

void User::set_userID(int userID) { _userID = userID; }
void User::set_forename(std::string forename) { _forename = forename; }
void User::set_surname(std::string surname) { _surname = surname; }
void User::set_username(std::string username) { _username = username; }
void User::set_modules(std::list<std::string> mods) { _mods = mods; }
void User::set_formulas(std::list<std::string> formulas) { _formulas = formulas; }

int User::get_userID() { return _userID; }
std::string User::get_forename() { return _forename; }
std::string User::get_surname() { return _surname; }
std::string User::get_username() { return _username; }
std::list<std::string> User::get_modules() { return _mods; }
std::list<std::string> User::get_formulas() { return _formulas; }

//log in
void User::set_password(std::string password) { _password = password; }
std::string User::check_password() { return _password; }
//other stuff