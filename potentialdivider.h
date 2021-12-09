#pragma once
#ifndef POTENTIALDIVIDER_H
#define POTENTIALDIVIDER_H

#include "menu.h"
#include "menuelement.h"
#include "eseries.h"
#include "componentmatch.h"
#include "System.h"
#include <vector>
#include <iostream>

namespace potdiv
{
	double OutVoltage(double vin, double ratio);
	double InVoltage(double vout, double ratio);
	double Ratio(double ra, double rb);
	double RaFromRatio(double rb, double ratio);
	double RbFromRatio(double ra, double ratio);

	void MakeResistorANpv(double rb, double vin, double vout);
	//double MakeResistorBNpv(double ra, double vin, double vout);

	void RunDividerCalculator();
}



#endif
