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
	bool TARGET = false; //�Ƿ����Ŀ��
protected:
	double xlength; //̹�˱���Ŀ��
	double ylength; //̹�˱���ĳ���
	HDC hdc; //̹�˻��Ƶ�hdc
	HBITMAP hBlt; //̹�˵���ͼ
	int step = 5;//�߹�һ����ͼ��ԪҪ���ѵĲ���
public:
	Bullet bullet; //̹�˵��ӵ�
	bool button_fire = false; //�Ƿ��ѿ��������Կ��������ӵ�����ǰ���޷����䡣
	bool change_dir = true;
	double x; //ʵ�ʵ���ͼ����
	double y; //ʵ����ͼ����
	double maprow; //��ͼ����x
	double mapcol; //��ͼ����y
	Direction direction; //̹�˵ķ���
	int life = 5;
	TANK(int x1, int y1, Direction dir);
	TANK() {};
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
	virtual void SetBlt(HBITMAP hBit); //������ͼ
	void HitTarget() { TARGET = true; };
	bool GetTarget() { return TARGET; };
	void SetOwner(int owner) { this->owner = owner;  bullet.SetOwner(owner); };//���ö���
	int GetOwner() { return owner; };//�õ�̹�˵Ķ���
 	Rect Get_Rect() { return Rect(x, y, xlength, ylength); };
	Point_Image GetImagePoint() { return Point_Image(x, y); };
	Point GetPoint() { return Point(maprow, mapcol); };
	void Insert(TANK *tank); //����̹��
	void Delete(TANK* tank); //ɾ��̹��
	bool Get_Bullet_state() { return bullet.status; };
	void SetHDC(HDC& hdc) { this->hdc = hdc; };
};