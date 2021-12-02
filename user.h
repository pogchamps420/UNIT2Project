#ifndef USER_H
#define USER_H

#include <string>
#include <list>

struct PersonalInfo {
	int userID;
	std::string forename;
	std::string surname;
	std::string username;
	std::string password;
};

class User {
public:
	User();
	User(PersonalInfo PInfo, std::list<std::string> Mods);
	User(int userID, std::string forename, std::string surname, std::string username, std::list<std::string> mods);

	void set_userID(int userID);
	void set_forename(std::string forename);
	void set_surname(std::string surname);
	void set_username(std::string username);
	void set_modules(std::list<std::string> mods);
	void set_formulas(std::list<std::string> Formulas);

	int get_userID();
	std::string get_forename();
	std::string get_surname();
	std::string get_username();
	std::list<std::string> get_modules();
	std::list<std::string> get_formulas();

private:
	void set_password(std::string password);
	std::string check_password();

	PersonalInfo _pinfo;
	int _userID;
	std::string _forename;
	std::string _surname;
	std::string _username;
	std::string _password;
	std::list<std::string> _mods;
	std::list<std::string> _formulas;
};
#endif