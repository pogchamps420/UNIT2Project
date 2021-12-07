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
			void PowerDissipation(CONVERTERS PDiss, Menu PDMenu);
			/* Menu ChangeValues(PD Pdiss, Menu PDMenu);
			Menu UpdatePDValues(PD Pdiss, Menu PDMenu);
			void PDISS(PD Pdiss, Menu& PDMenu);
			void PS(PD PDiss, Menu PDMenu, char parent);
			void PON(PD PDiss, Menu PDMenu, char parent);
			void WCON(PD PDiss, Menu PDMenu, char parent);
			void WCOFF(PD PDiss, Menu PDMenu, char parent);
			void TSFS(PD PDiss, Menu PDMenu, char parent);
			void WON(PD PDiss, Menu PDMenu, char parent);
			*/
		private:
	};
}
#endif

