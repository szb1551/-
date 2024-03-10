#pragma once
#include "Structs.h"

extern enum Direction;

class Bullet
{
private:
	int speed = 10; //子弹速度
	int owner = 0; //默认为友方
	bool TARGET = false;//是否击中老鹰
public:
	Point_Image point;
	Direction dir;
	int status = 0; //子弹状态
	int width = 10; //子弹的大小
	int height = 10;
	virtual void Move(); //子弹移动
	virtual bool Collide(Rect& rect); //子弹的碰撞
	void Update(); //子弹更新
	void SetOwner(int owner) { this->owner = owner; }; //设置子弹类别，避免友伤
	void HitTarget() { TARGET = TRUE; }; //子弹击中目标
	bool GetTarget() { return TARGET; };//是否击中目标
};