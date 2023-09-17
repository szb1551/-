#pragma once
#include "tank.h"
#include "map.h"


class Enemy : public TANK
{
private:
	int ID = 0;
public:
	bool show = false;
	Enemy(int x, int y, Direction dir) :TANK(x, y, dir) {};
	Enemy() {};
	void Update();
	void UpdatePosition();
	void DRAWONE();
	bool Can_Fire();
	void SetID(int id) { ID = id; };//设置坦克的ID
	int GetID() { return ID; };
	void CanRun(bool& can_run);
	Direction EnemyDirection(Point_Image target); //敌方坦克寻路算法
	Direction EnemyDirection(int x, int y);
	Direction EnemyDirection(Point target);
};