#pragma once
#include "Structs.h"

extern enum Direction;

class Bullet
{
private:
	int speed = 10; //�ӵ��ٶ�
	int owner = 0; //Ĭ��Ϊ�ѷ�
	bool TARGET = false;//�Ƿ������ӥ
public:
	Point_Image point;
	Direction dir;
	int status = 0; //�ӵ�״̬
	int width = 10; //�ӵ��Ĵ�С
	int height = 10;
	virtual void Move(); //�ӵ��ƶ�
	virtual bool Collide(Rect& rect); //�ӵ�����ײ
	void Update(); //�ӵ�����
	void SetOwner(int owner) { this->owner = owner; }; //�����ӵ���𣬱�������
	void HitTarget() { TARGET = TRUE; }; //�ӵ�����Ŀ��
	bool GetTarget() { return TARGET; };//�Ƿ����Ŀ��
};