#include "stdafx.h"
#include "Bullet.h"
#include "Union.h"
using  namespace std;

#pragma region  
CBullet::CBullet() :isValid(true)
{

}

CBullet::~CBullet()
{
	
}
 int CBullet::getBulletX()
{
	return BulletX;
}
 int CBullet::getBulletY()
{
	return BulletY;
}
 int CBullet::getDirection()
{
	return Direction;
}
void  CBullet::setsTime(clock_t c)
{
	sendTime = c;
}
clock_t CBullet::getsTime()
{
	return sendTime;
}

bool CBullet::getIsValid()
{
	return isValid;
}
void CBullet::setIsValid(bool valid)
{
	isValid = valid;
}
#pragma endregion 

//����ӵ�
void CBullet::clearBullet()
{
	int bOldIsThrough = CData::GetTypeOfMap(this->oldBulletX, this->oldBulletY);
	//Ϊ�˷�ֹ��ǽ���ӵ��������ǽ
	if (bOldIsThrough == WALL__ || bOldIsThrough == WALL_A
		|| bOldIsThrough == WALL_H || bOldIsThrough == MISSIL_1
		|| bOldIsThrough == MISSIL_2)
	{
		CData::SetTypeOfMap(this->oldBulletX, this->oldBulletY, WALL__);
		Draw::writeChar(this->oldBulletX, this->oldBulletY, "  ", 0);
	}

}

//���ܣ��ӵ���ָ���ķ����ƶ�һ��
//�������ƶ��ķ���
//����ֵ����
void CBullet::move(int direction)
{
	this->clearBullet();
	if (this->printBullet())
	{
		this->oldBulletY = BulletY;
		this->oldBulletX = BulletX;
		switch (direction)
		{
		case UP:
			--BulletY;
			break;
		case DOWN:
			++BulletY;
			break;
		case LEFT:
			--BulletX;
			break;
		case RIGHT:
			++BulletX;
			break;
		}
	}
}

//��ӡ�ӵ�����ǿյ��Ŵ�ӡ����true,���򷵻�false,Ȼ�����attackSomeThing()
bool CBullet::printBullet()
{
	int mapType = CData::GetTypeOfMap(this->BulletX, this->BulletY);
	//��������յ�����û������̹�����ӡ�ӵ�
	if (mapType == WALL__)
	{
		if (TankID < 2)
		{
			CData::SetTypeOfMap(this->BulletX, this->BulletY, MISSIL_1);
			Draw::writeChar(BulletX, BulletY, "��", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		}
		else    //��ӡ�з��ӵ�
		{
			CData::SetTypeOfMap(this->BulletX, this->BulletY, MISSIL_2);
			Draw::writeChar(BulletX, BulletY, "��", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		}
		return true;
	}
	else
	{
		CUnion::attackSomeThing(mapType,*this);
		return false;
	}

}

//std::vector<CTank>::iterator itr;



void CBullet::InitBullet(int tankID, int bulletX, int bulletY, int direction, bool isValid, clock_t sTime, int oldX, int oldY)
{
	TankID = tankID; 
	BulletX = bulletX;
	BulletY = bulletY;
	Direction = direction;
	this->isValid = isValid; 
	this->sendTime = sTime;
	oldBulletX = oldX;
	oldBulletY = oldY;
}
