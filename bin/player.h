#pragma once
#include "tank.h"
#include "map.h"
//#include "bullet.h"


class Player : public TANK
{
public:
	Player(int x, int y, Direction dir):TANK(x, y,dir) {};
	bool Collide(vector<TANK*>EM);
	void CanRun(bool& can_run);

};


