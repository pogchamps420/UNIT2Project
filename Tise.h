#pragma once
#ifndef TISE_H
#define TISE_H

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <type_traits>
#include "PD.h"
#include "menu.h"
#include "System.h"

namespace T
{
	struct Data
	{
		std::string Name;
		int Values = 0;
	};
	class Tise
	{
		public:
			Tise();
			void TiseMenu(bool ExitMenu);
			void PowerDissipation(PD PDiss, Menu PDMenu);
			Menu ChangeValues(PD Pdiss, Menu PDMenu);
			Menu UpdatePDValues(PD Pdiss, Menu PDMenu);
			void PDISS(PD Pdiss, Menu& PDMenu);
			void PS(PD PDiss, Menu PDMenu, char parent);
			void PON(PD PDiss, Menu PDMenu, char parent);
			void WCON(PD PDiss, Menu PDMenu, char parent);
			void WCOFF(PD PDiss, Menu PDMenu, char parent);
			void TSFS(PD PDiss, Menu PDMenu, char parent);
			void WON(PD PDiss, Menu PDMenu, char parent);
			double GetDataInput();
			void ExportData(PD PDiss, bool newfile);
			PD ImportData(PD PDiss);

		private:
			bool ExitMenu;
	};
}
#endif