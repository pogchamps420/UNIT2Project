#ifndef INITIATE_H
#define INITIATE_H

#include <algorithm>
#include <iostream>
#include "formula.h"
#include "module.h"
//#include "user.h"

class Initiate {
public:
	Initiate();
	Initiate(int Profile);

	void set_profile(int _profile);
	void defaultprofile();
	void testprofile();

	//User get_user();

private:
	int _profile;
	//User _user;
};
#endif