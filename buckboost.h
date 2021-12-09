#ifndef BUCKBOOST_H
#define BUCKBOOST_H 

#include <iostream>
#include <string>
#include "variables.h"
#include "menu.h"


//class here pls, tie it all up
namespace bbc
{
	class BUCKBOOST
	{
		public:
			BUCKBOOST();

			void InitMenu();
			void BuckBoostConverters(CONVERTERS BBCStuff, BUCK BuckStuff, BOOST BoostStuff, Menu BBCMenu);
			Menu ChangeValues(CONVERTERS BBCStuff, Menu BBCMenu);
			Menu UpdateBBCValues(CONVERTERS BBCStuff, Menu BBCMenu);
			Menu UpdateBBCValues(BOOST Boost, Menu BBCMenu);
			Menu UpdateBBCValues(BUCK Buck, Menu BBCMenu);
			void VOLT_INDUCT(CONVERTERS BBCStuff, BUCK BuckStuff, BOOST BoostStuff, Menu& BBCMenu);
			void SEL_INDUCT(CONVERTERS BBCStuff, BUCK BuckStuff, BOOST BoostStuff, Menu& BBCMenu);
			void SEL_CAP(CONVERTERS BBCStuff, BUCK BuckStuff, BOOST BoostStuff, Menu& BBCMenu);
			
		private:
	};
}
#endif

