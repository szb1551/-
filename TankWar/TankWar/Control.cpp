#pragma  once
#include "stdafx.h"
//�߼���  ����̹�ˡ��ӵ�
#include "Control.h"
#include "Union.h"

// 
// //�о����ӵ����� ����HP�����¼Ʒְ�
// void Control::enemyBeAttack(int posX, int posY)
// {
// 	int tank = CData::GetTypeOfMap(posX, posY);
// 	VTank[tank + 2].clearTank();
// 	VTank[tank + 2].setnMaxHP(VTank[tank + 2].getMaxHP() - 1);
// 	updateTableau();
// }

//���ܣ����̹���Ƿ����ͨ��
//������̹�˷���x�� y ����
//����ֵ����ͨ������true,���򷵻�false

//���ܰ���   �ƶ�̹�˻����һ���ӵ�
void Control::moveTankORBullet(char ch ,int player)
{
	if (player == 1 && CUnion::VTank[0].getValid())
	{
		switch (ch)
		{
		case 'w':
		case 'W':
			CUnion::VTank[0].move(UP);
			break;
		case 'a':
		case 'A':
			CUnion::VTank[0].move(LEFT);
			break;
		case 's':
		case 'S':
			CUnion::VTank[0].move(DOWN);
			break;
		case 'd':
		case 'D':
			CUnion::VTank[0].move(RIGHT);
			break;
		case 32:
			sendBullet(CUnion::VTank[0]);
			break;
		}
	}
	else if (CUnion::VTank[1].getValid()) //�ж����2�İ���
	{
		switch (ch)
		{
		case 72:
			CUnion::VTank[1].move(UP);
			break;
		case 75:
			CUnion::VTank[1].move(LEFT);
			break;
		case 80:
			CUnion::VTank[1].move(DOWN);
			break;
		case 77:
			CUnion::VTank[1].move(RIGHT);
			break;
		case 'j':
		case 'J':
			sendBullet(CUnion::VTank[1]);
			break;
		}
	}
}
//ѭ������ӵ���������ӵ�
void Control::moveBulletAuto()
{
	list<CBullet>::iterator itr;
	itr = CUnion::ListBullet.begin();

	while (itr != CUnion::ListBullet.end())
	{
		
		//����ӵ��������ƶ�
		if (itr->getIsValid())
		{
			itr->move(itr->getDirection());
			++itr;
		}
		else
		{
			itr = CUnion::ListBullet.erase(itr);
		}
	}
}
//===================================================================
//�ƶ����ез�̹��
void Control::moveAllTankAuto()
{
	for (int i = 0; i < countEnemyTank; i++)
	{
		if (CUnion::VTank[i + 2].isValid)
		{
			moveAuto(CUnion::VTank[i + 2]);
		}
	}
}

void Control::sendBullet()
{
// 	����һ���ӵ�
// 		clock_t firstTime = clock();
// 		switch (this->Direction)
// 		{
// 		case UP:
// 			bullet = { this->TankID, this->TankX + 1, this->TankY - 1, this->Direction, true, firstTime, this->TankX + 1, this->TankY - 1 };
// 			break;
// 		case DOWN:
// 			bullet = { this->TankID, this->TankX + 1, this->TankY + 3, this->Direction, true, firstTime, this->TankX + 1, this->TankY + 3 };
// 			break;
// 		case LEFT:
// 			bullet = { this->TankID, this->TankX - 1, this->TankY + 1, this->Direction, true, firstTime, this->TankX - 1, this->TankY + 1 };
// 			break;
// 		case RIGHT:
// 			bullet = { this->TankID, this->TankX + 3, this->TankY + 1, this->Direction, true, firstTime, this->TankX + 3, this->TankY + 1 };
// 			break;
// 		}
// 		//���ӵ�����VBullet����
// 		ListBullet.push_back(bullet);
// 		//�ƶ���һ��
// 		bullet.move(this->Direction);
}

void Control::sendBullet(CTank& tank)
{
	//����һ���ӵ�
	clock_t firstTime = clock();
	switch (tank.Direction)
	{
	case UP:
		bullet.InitBullet( tank.TankID, tank.TankX + 1, tank.TankY - 1, tank.Direction, true, firstTime, tank.TankX + 1, tank.TankY - 1 );
		break;
	case DOWN:
		bullet.InitBullet(tank.TankID, tank.TankX + 1, tank.TankY + 3, tank.Direction, true, firstTime, tank.TankX + 1, tank.TankY + 3);
		break;
	case LEFT:
		bullet.InitBullet(tank.TankID, tank.TankX - 1, tank.TankY + 1, tank.Direction, true, firstTime, tank.TankX - 1, tank.TankY + 1);
		break;
	case RIGHT:
		bullet.InitBullet(tank.TankID, tank.TankX + 3, tank.TankY + 1, tank.Direction, true, firstTime, tank.TankX + 3, tank.TankY + 1 );
		break;
	}
	//���ӵ�����VBullet����
	CUnion::ListBullet.push_back(bullet);
	//�ƶ���һ��
	bullet.move(tank.Direction);
}

//��ʼ��Ϸ
//��������Ϸ����
void Control::gameStart(int n1)
{
	countMyTank = n1;
	system("cls");
	drawTank();
	drawTableau();
	Draw::DrawMap(CData::g_sysMap00);
	while (true)
	{
		char ch;
		//�ƶ��ҷ�̹��
		playEnd = clock();
		if (playEnd - playStart > 20)
		{
			if (_kbhit())
			{
				ch = _getch();
				playStart = playEnd;
				Control::moveTankORBullet(ch, 1);
				//��������2
				if (countMyTank == 2)
				{
					Control::moveTankORBullet(ch, 2);
				}
				//��esc��Ϸ ���ز˵�
				if (ch == 27)
				{
					gameStatus = 1;
					return;
				}
			}
		}
		//�ƶ��ӵ�
		bulletEndTime = clock();
		if (bulletEndTime - bulletStartTime > (200 - speedMoveBullet))
		{
			bulletStartTime = bulletEndTime;
			Control::moveBulletAuto();
		}
		//�ƶ��з�̹��
		enemyTankEndTime = clock();
		if (enemyTankEndTime - enemyTankStartTime > speedMoveTank)
		{
			enemyTankStartTime = enemyTankEndTime;
			moveAllTankAuto();
		}
	}
}

void Control::init()
{
	system("cls");
	Draw::SetWindowSize("̹�˴�ս v1.0 ", WINDOWS_WIDTH, WINDOWS_HIGH);
	Draw::writeChar(15, 11, "̹�˴�ս v1.0", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	//����Ĭ�ϲ���
	gameStatus = 0;
	countEnemyTank = 1;
	speedMoveTank = 300;
	enemyTankHP = 10;
	speedMoveBullet = 50;
}
//̹���Զ��ƶ�
void Control::moveAuto(CTank& tank)
{
	clock_t time1_end;
	time1_end = clock();
	tank.move(tank.Direction);
	if (time1_end - tank.TankTime1 > SPEEDDISTANTBULLET)		//�����ӵ����ٶ�
	{
		sendBullet(tank);
		tank.TankTime1 = time1_end;
	}

}
// ���Ʒְ�
void Control::drawTableau()
{

	writeChar(45, 3, "  ���1  Ѫ����", FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	writeChar(53, 3, "10", FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	if (countMyTank == 2)
	{
		writeChar(45, 4, "  ���2  Ѫ����", FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		writeChar(53, 4, "10", FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}

	for (int i = 1; i <= countEnemyTank; i++)
	{
		char * enemyHP = new char[4];
		char setPlayer[50];
		_itoa_s(CUnion::VTank[1 + i].getMaxHP(), enemyHP, 4, 10);

		sprintf_s(setPlayer, "�з�̹��%dѪ����", i);
		writeChar(45, 5 + i, setPlayer, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		writeChar(53, 5 + i, enemyHP, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		delete enemyHP;
	}
}
//�����ҷ��Ʒְ�
void Control::updateMyTableau()
{
	char * enemyHP = new char[4];
	char * enemyHP2 = new char[4];
	_itoa_s(CUnion::VTank[0].getMaxHP(), enemyHP, 4, 10);
	writeChar(53, 3, "  ", FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	writeChar(53, 3, enemyHP, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	//���Ѫ��С��0 
	if (CUnion::VTank[0].getMaxHP() <= 0)
	{
		CUnion::VTank[0].setValid(false);
		CUnion::VTank[0].clearTank();
	}

	if (countMyTank == 2)
	{
		_itoa_s(CUnion::VTank[1].getMaxHP(), enemyHP2, 4, 10);
		writeChar(53, 4, "  ", FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		writeChar(53, 4, enemyHP2, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		if (CUnion::VTank[1].getMaxHP() <= 0)
		{
			CUnion::VTank[1].setValid(false);
			CUnion::VTank[1].clearTank();
		}
	}
	//�������Ѫ����С��0 ��Ϸ����
	if (CUnion::VTank[0].getMaxHP() <= 0 && countMyTank == 1)
	{
		writeChar(50, 16, "�����ˣ�", FOREGROUND_RED | FOREGROUND_INTENSITY);
	}
	else if (CUnion::VTank[0].getMaxHP() <= 0 && CUnion::VTank[1].getMaxHP() <= 0 && countMyTank == 2)
	{
		writeChar(50, 16, "�����ˣ�", FOREGROUND_RED | FOREGROUND_INTENSITY);
	}

	delete enemyHP;
	delete enemyHP2;
}
//���µз��Ʒְ�
void Control::updateTableau()
{
	int sumSocre = 0;
	//�з���Ϣ
	for (int i = 1; i <= countEnemyTank; i++)
	{
		sumSocre += CUnion::VTank[1 + i].getMaxHP();
		char * enemyHP = new char[4];
		_itoa_s(CUnion::VTank[1 + i].getMaxHP(), enemyHP, 4, 10);
		writeChar(53, 5 + i, "  ", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		writeChar(53, 5 + i, enemyHP, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		if (CUnion::VTank[1 + i].getMaxHP() <= 0)
		{
			CUnion::VTank[1 + i].clearTank();
			CUnion::VTank[1 + i].setValid(false);
		}

		delete enemyHP;
	}
	if (sumSocre == 0)
	{
		writeChar(50, 15, "��Ӯ�ˣ�", FOREGROUND_RED | FOREGROUND_INTENSITY);
	}

}
// ��ӡ��ʼ��̹��
void Control::drawTank()
{
	myTank1 = CTank(0, 5, 36, UP, 10);
	CUnion::VTank.push_back(myTank1);
	myTank2 = CTank(1, 35, 36, UP, 10);
	CUnion::VTank.push_back(myTank2);
	enemyTank1 = CTank(2, 16, 1, DOWN, enemyTankHP);
	enemyTank2 = CTank(3, 26, 1, DOWN, enemyTankHP);
	enemyTank3 = CTank(4, 6, 1, DOWN, enemyTankHP);
	enemyTank4 = CTank(5, 35, 1, DOWN, enemyTankHP);

	CUnion::VTank[0].printTank();

	if (countMyTank == 2)
	{
		CUnion::VTank[1].printTank();
	}

	if (countEnemyTank == 1)
	{
		CUnion::VTank.push_back(enemyTank1);
		CUnion::VTank[2].printTank();
	}
	else if (countEnemyTank == 2)
	{
		CUnion::VTank.push_back(enemyTank1);
		CUnion::VTank.push_back(enemyTank2);
		CUnion::VTank[2].printTank();
		CUnion::VTank[3].printTank();
	}
	else if (countEnemyTank == 3)
	{
		CUnion::VTank.push_back(enemyTank1);
		CUnion::VTank.push_back(enemyTank2);
		CUnion::VTank.push_back(enemyTank3);
		CUnion::VTank[2].printTank();
		CUnion::VTank[3].printTank();
		CUnion::VTank[4].printTank();
	}
	else if (countEnemyTank == 4)
	{
		CUnion::VTank.push_back(enemyTank1);
		CUnion::VTank.push_back(enemyTank2);
		CUnion::VTank.push_back(enemyTank3);
		CUnion::VTank.push_back(enemyTank4);
		CUnion::VTank[2].printTank();
		CUnion::VTank[3].printTank();
		CUnion::VTank[4].printTank();
		CUnion::VTank[5].printTank();
	}
}

CBullet Control::bullet;
