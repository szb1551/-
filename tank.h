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
	double xlength; //̹�˱���Ŀ��
	double ylength; //̹�˱���ĳ���
	HBITMAP hBlt; //̹�˵���ͼ
	int step = 5;//�߹�һ����ͼ��ԪҪ���ѵĲ���
	Bullet bullet; //̹�˵��ӵ�
	HDC hdc; //̹�˻��Ƶ�hdc
public:
	bool button_fire = false;
	bool change_dir = true;
	double x; //ʵ�ʵ���ͼ����
	double y; //ʵ����ͼ����
	double maprow; //��ͼ����x
	double mapcol; //��ͼ����y
	Direction direction; //̹�˵ķ���
	int life;
	TANK(int x1, int y1, Direction dir);
	virtual void Update(double xlength, double ylength); //���´�������
	virtual void Update();// �����ڲ�����
	virtual void DRAWONE(); //����̹��
	virtual void DRAWBULLET(); //�����ӵ�
	virtual void CanRun(bool& can_run, int xflag1, int xflag2, int yflag1, int yflag2);
	virtual void CanRun(bool& can_run);
	virtual void MOVE();
	virtual bool Collide(Rect& rect);
	virtual void show();
	virtual bool Can_Fire();
	virtual void Initial_Bullet();
	virtual void Fire(); //�����ӵ�
	bool Get_Bullet_state() { return bullet.status; };
	void SetHDC(HDC& hdc) { this->hdc = hdc; };
};