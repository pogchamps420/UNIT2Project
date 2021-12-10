#ifndef BUCKBOOST_H
#define BUCKBOOST_H 

#include <iostream>
#include <string>
#include "variables.h"
#include "menu.h"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <string>
#include <stdlib.h>  



//class here pls, tie it all up
namespace bbc
{
	class BUCKBOOST
	{
		public:
			BUCKBOOST();

			void InitMenu();
			void BuckBoostConverters(CONVERTERS BBCStuff, BUCK BuckStuff, BOOST BoostStuff, Menu BBCMenu);
			void ChangeValues(Menu *menu);
			Menu UpdateBBCValues(CONVERTERS BBCStuff, BUCK Buck, BOOST Boost, Menu BBCMenu);
			Menu UpdateBBCValues(BOOST Boost, Menu BBCMenu);
			Menu UpdateBBCValues(BUCK Buck, Menu BBCMenu);
			void VOLT_INDUCT(CONVERTERS BBCStuff, BUCK BuckStuff, BOOST BoostStuff, Menu& BBCMenu);
			void SEL_INDUCT(CONVERTERS BBCStuff, BUCK BuckStuff, BOOST BoostStuff, Menu& BBCMenu);
			void SEL_CAP(CONVERTERS BBCStuff, BUCK BuckStuff, BOOST BoostStuff, Menu& BBCMenu);
			
		private:
	};
}
#endif

