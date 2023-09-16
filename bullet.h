#pragma once
#include "Structs.h"

extern enum Direction;

class Bullet
{
private:
	int speed = 15; //子弹速度
public:
	Point_Image point;
	Direction dir;
	int status = 0; //子弹状态
	int width = 10; //子弹的大小
	int height = 10;
	virtual void Move();
	virtual bool Collide(Rect& rect);
	void Update();
};