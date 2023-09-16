#pragma once
#include"include.h"
#include "bullet.h"



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
	double xlength; //坦克本身的宽度
	double ylength; //坦克本身的长度
	HBITMAP hBlt; //坦克的贴图
	int step = 5;//走过一个地图单元要花费的步数
	Bullet bullet; //坦克的子弹
	HDC hdc; //坦克绘制的hdc
public:
	bool button_fire = false;
	bool change_dir = true;
	double x; //实际的贴图坐标
	double y; //实际贴图坐标
	double maprow; //地图坐标x
	double mapcol; //地图坐标y
	Direction direction; //坦克的方向
	int life;
	TANK(int x1, int y1, Direction dir);
	virtual void Update(double xlength, double ylength); //更新窗口坐标
	virtual void Update();// 更新内部参数
	virtual void DRAWONE(); //画出坦克
	virtual void DRAWBULLET(); //画出子弹
	virtual void CanRun(bool& can_run, int xflag1, int xflag2, int yflag1, int yflag2);
	virtual void CanRun(bool& can_run);
	virtual void MOVE();
	virtual bool Collide(Rect& rect);
	virtual void show();
	virtual bool Can_Fire();
	virtual void Initial_Bullet();
	virtual void Fire(); //发射子弹
	bool Get_Bullet_state() { return bullet.status; };
	void SetHDC(HDC& hdc) { this->hdc = hdc; };
};