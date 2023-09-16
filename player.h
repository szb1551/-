#pragma once
#include "tank.h"
//#include "bullet.h"

class Player : public TANK
{
public:
	Player(int x, int y, Direction dir):TANK(x, y,dir) {};

};