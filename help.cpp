#include "bin/help.h"
#include "math.h";

int ConvertDoubleToInt(double a)
{
	return round(a);
}

int CanConvertDoubleToInt(double a)
{
	int biga = ceil(a);
	int smalla = (int)a;
	if (biga - a < 0.1) return biga;
	if (a - smalla < 0.1) return smalla;
	return -1;
}