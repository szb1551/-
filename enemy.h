#pragma once
#include "tank.h"
#include "map.h"


class Enemy : public TANK
{
public:
	bool show = false;
	Enemy(int x, int y, Direction dir) :TANK(x, y, dir) {};
	Enemy() {};
	void Update();
	void UpdatePosition();
	void DRAWONE();
};