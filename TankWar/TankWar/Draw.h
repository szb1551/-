#pragma once
#include "Data.h"


  class Draw :public CData
{
public:
	static void writeChar(int x, int y, char * pszChar, char wArr);
	static bool SetWindowSize(char* pszWindowTitle, int nX, int nY);
	static void DrawMap(int nMap[][MAP_WIDTH]);
	//��ӡ�Ƿְ�
	
	
	//��ʾѡ��
	static int showOption();
	static void showConfig();
	static void clearConsole(int x);
	static void help();
	static void editMap();
protected:
	static int countEnemyTank;	//�з�̹��������
	static int countMyTank;   //�ҷ�̹��������
	static int speedMoveTank;	//�з�̹���ƶ��ٶ�
	static int speedMoveBullet;	//�ӵ������ٶ�
	static int enemyTankHP;	//�з�̹��Ѫֵ
	static int myTankHP;		//�ҷ�̹��Ѫֵ

};

 