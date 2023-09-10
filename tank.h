#pragma once
#include"include.h"


enum Direction{up, down,right,left};


struct Rect
{
	int x;
	int y;
	double width;
	double height;
	Rect(int x, int y, double width, double height) :x(x), y(y), width(width), height(height) {};
	Rect() {};
	friend ostream& operator<<(ostream&os, const Rect& rect)
	{
		os << rect.x << ' ' << rect.y << ' ' << rect.width << ' ' << rect.height;
		return os;
	}
};
//class ALL_TANK
//{
//private:
//	TANK* al_tank[10];
//public:
//	
//	int tank_num=0;
//	void Insert_tank(TANK* tank)
//	{
//		al_tank[tank_num] = tank;
//		tank_num++;
//	}
//};

class TANK {
private:
	//int count4;
	double xlength;
	double ylength;
	HBITMAP hBlt;
	int step = 4;//走过一个地图单元要花费的步数
public:
	bool change_dir = true;
	double x;
	double y;
	float maprow;
	float mapcol;
	Direction direction;
	int life;
	TANK(int x1, int y1, Direction dir);
	virtual void Update(double xlength, double ylength); //更新窗口坐标
	virtual void Update();// 更新内部参数
	virtual void DRAWONE(HDC& hdc);
	virtual void MOVE();
	virtual bool Collide(Rect& rect);
};