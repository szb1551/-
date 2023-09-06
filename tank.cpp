#include "tank.h"

TANK::TANK(int x, int y, Direction dir)
{
	maprow = x;
	mapcol = y;
	direction = dir;
}

void TANK::Update(double xlength, double ylength)
{
	x = mapcol * xlength;
	y = maprow * ylength;
}