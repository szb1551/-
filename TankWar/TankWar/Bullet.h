#pragma once
#include "Draw.h"
class CBullet:virtual public Draw
{
public:
	CBullet();
	~CBullet() ;
	//CBullet();
	void InitBullet(int tankID, int bulletX, int bulletY, int direction, bool isValid, clock_t sTime, int oldX, int oldY);
	bool printBullet( );
	void move(int direction);
	void moveBulletAuto();
	void loopMove();
	void clearBullet();
	 int getBulletX();
	 int getBulletY();
	 int getDirection();
	bool getIsValid();
	void setIsValid(bool valid);
	void setsTime(clock_t c);
	clock_t getsTime();
	
//private:
	 int BulletID;			//�ӵ����
	 int TankID;			//̹��ID
	 int BulletX;			//�ӵ�x����
	 int BulletY;			//�ӵ�y����
	 int Direction;		    //�ӵ�����
	bool isValid;			//�ӵ��Ƿ���Ч
	 int oldBulletX;
	 int oldBulletY;
	clock_t sendTime;					//�ӵ������ʱ��
	 int nLevel;			//�ӵ��ȼ�
protected:
	//static list<CBullet> ListBullet;

};

