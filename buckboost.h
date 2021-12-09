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
			void BuckBoostConverters(CONVERTERS BBCStuff, Menu BBCMenu);
			Menu ChangeValues(CONVERTERS BBCStuff, Menu BBCMenu);
			Menu UpdateBBCValues(CONVERTERS BBCStuff, Menu BBCMenu);
			void VOLT_INDUCT(CONVERTERS BBCStuff, Menu& BBCMenu);
			void SEL_INDUCT(CONVERTERS BBCStuff, Menu& BBCMenu);
			void SEL_CAP(CONVERTERS BBCStuff, Menu& BBCMenu);
			
		private:
	};
}
#endif

