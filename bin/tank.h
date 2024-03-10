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
	int owner = 0;
	bool TARGET = false; //是否击中目标
protected:
	double xlength; //坦克本身的宽度
	double ylength; //坦克本身的长度
	HDC hdc; //坦克绘制的hdc
	HBITMAP hBlt; //坦克的贴图
	int step = 5;//走过一个地图单元要花费的步数
public:
	Bullet bullet; //坦克的子弹
	bool button_fire = false; //是否已开过火，若以开火，则在子弹集中前，无法发射。
	bool change_dir = true;
	double x; //实际的贴图坐标
	double y; //实际贴图坐标
	double maprow; //地图坐标x
	double mapcol; //地图坐标y
	Direction direction; //坦克的方向
	int life = 5;
	TANK(int x1, int y1, Direction dir);
	TANK() {};
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
	virtual void SetBlt(HBITMAP hBit); //设置贴图
	void HitTarget() { TARGET = true; };
	bool GetTarget() { return TARGET; };
	void SetOwner(int owner) { this->owner = owner;  bullet.SetOwner(owner); };//设置队伍
	int GetOwner() { return owner; };//得到坦克的队伍
 	Rect Get_Rect() { return Rect(x, y, xlength, ylength); };
	Point_Image GetImagePoint() { return Point_Image(x, y); };
	Point GetPoint() { return Point(maprow, mapcol); };
	void Insert(TANK *tank); //加入坦克
	void Delete(TANK* tank); //删除坦克
	bool Get_Bullet_state() { return bullet.status; };
	void SetHDC(HDC& hdc) { this->hdc = hdc; };
};