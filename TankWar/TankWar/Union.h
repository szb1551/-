#pragma once
#include "Bullet.h"
#include "Tank.h"

class CUnion
{
public:

	//�о����ӵ����� ����HP�����¼Ʒְ�
	void CUnion::enemyBeAttack(int posX, int posY);

	static void attackSomeThing(int mapType, CBullet& tank);

	static vector<CTank> VTank;
	static list<CBullet> ListBullet;

};

