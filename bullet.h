#pragma once
#include "Structs.h"

extern enum Direction;

class Bullet
{
private:
	int speed = 15; //�ӵ��ٶ�
public:
	Point_Image point;
	Direction dir;
	int status = 0; //�ӵ�״̬
	int width = 10; //�ӵ��Ĵ�С
	int height = 10;
	virtual void Move();
	virtual bool Collide(Rect& rect);
	void Update();
};