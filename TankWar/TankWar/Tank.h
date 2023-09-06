#pragma once
#include "Draw.h"

class CTank :virtual public Draw
{
public:
	CTank();
	CTank(int tankID, int tankX, int tankY, char dire,int nMaxHP);
	void printTank();
	
	void move(int direction);
	
	
	void clearTank();
	int getId();
	char getDirection();
	int getPosX();
	int getPosY();	
	int getMaxHP();
	 bool getValid();
	void setnMaxHP(int maxHP);
	void setValid(bool valid);
	//����������Ƿ���ĳ̹��
	static bool isTank(int x, int y, CTank & tank);

	//static bool tankIsThroughTank(int posX, int posY, int direction);//----------------
	static  bool tankIsThrough(int posX, int  posY, int  direction);
//protected:
	 int TankID;     //̹�˱�� ���0��1Ϊ���̹��
	 int TankX;		 //x����
	 int TankY;
	 int Direction; //̹�˷���
	int nMaxHP;				//̹�����Ѫ��
	clock_t TankTime1;		//���ڿ���̹���ƶ��ٶ�
	clock_t TankTime2;		//���ڿ���̹�˷����ӵ����ٶ�
	clock_t TankTime3;
	 int nLevel;	 //̹�˵ȼ�
	int nCurHP;				//̹�˵�ǰѪ��
	int nOriginSpeed;		//̹��ԭʼ�ٶ�
	int nSpeed;				//̹�˵�ǰ�ٶ�
	int nGoDirection;		//̹����Ҫ�ı�ķ���
	int nKill;				//̹��ɱ����
	int nDie;				//̹����������
	bool isValid;			//̹���Ƿ�����/
protected:
	//static vector<CTank> VTank;
	
};

