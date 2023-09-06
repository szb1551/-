#include "stdafx.h"
#include "Union.h"
#include "Control.h"
#include "Draw.h"



//�о����ӵ����� ����HP�����¼Ʒְ�
void CUnion::enemyBeAttack(int posX, int posY)
{
	int tank = CData::GetTypeOfMap(posX, posY);
	VTank[tank + 2].clearTank();
	VTank[tank + 2].setnMaxHP(VTank[tank + 2].getMaxHP() - 1);
	Control::updateTableau();
}


//���ܣ������ӵ������ϰ���
//����������λ�õ���������
void CUnion::attackSomeThing(int mapType, CBullet& bullet)
{
	//�������λ���ǵз�̹�˲������ҷ������ӵ��ӵ���������
	if (mapType >= TANK_B1&& mapType <= TANK_B6 && bullet.TankID < 2)
	{
		int enemyTankID = mapType - 0x10 + 1;
		VTank[enemyTankID].clearTank();
		VTank[enemyTankID].setnMaxHP(VTank[enemyTankID].getMaxHP() - 1);
		Control::updateTableau();
		bullet.setIsValid(false);
	}
	//�������λ�����ҷ�̹�˲����ǵз�������ӵ�
	else if ((mapType == TANK_C || mapType == TANK_A) && bullet.TankID >= 2)
	{
		if (mapType == TANK_C)
		{
			VTank[0].setnMaxHP(VTank[0].getMaxHP() - 1);
			Control::updateMyTableau();
			bullet.setIsValid(false);
		}
		else
		{
			VTank[1].setnMaxHP(VTank[1].getMaxHP() - 1);
			Control::updateMyTableau();
			bullet.setIsValid(false);
		}

	}
	//����ǿ��ƻ���ǽ��ݻ�
	else if (mapType == WALL_A || mapType == WALL_H)
	{
		CData::SetTypeOfMap(bullet.BulletX, bullet.BulletY, WALL__);
		Draw::writeChar(bullet.BulletX, bullet.BulletY, "  ", 0);
		bullet.setIsValid(false);
	}
	bullet.setIsValid(false);

}

list<CBullet> CUnion::ListBullet;

vector<CTank> CUnion::VTank;
