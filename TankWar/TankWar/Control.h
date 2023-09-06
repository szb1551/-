
//#include "Bullet.h"
//#include "Tank.h"
#include "Union.h"

class  Control : virtual public CTank, virtual public CBullet
{
public: 
	static   char isThrough(  int posX,  int posY);
	//̹���Ƿ����ͨ����ͼs
	

	//static void enemyBeAttack(int posX, int posY);
	

	//̹���Ƿ�����̹��
	
	static void moveTankORBullet(char ch ,int player);
	static char bulletIsThrough(  int posX,  int posY);
	static void  moveBulletAuto();

	//-------------------------------------
	void gameStart(int);
	void init();
	static void moveAuto(CTank& tank);

	//���¼Ƿְ�
	static void updateMyTableau();
	static void updateTableau();
	static void drawTableau();
	 void drawTank();

	static void sendBullet();
	static void sendBullet(CTank& tank);
	static void moveAllTankAuto();

private:
	int gameStatus;


	clock_t playStart = clock();
	clock_t playEnd;
	clock_t	bulletStartTime = clock();
	clock_t bulletEndTime;
	clock_t enemyTankStartTime = clock();
	clock_t enemyTankEndTime;

	static CBullet bullet;
	CTank myTank1;
	CTank myTank2;

	CTank enemyTank1;
	CTank enemyTank2;
	CTank enemyTank3;
	CTank enemyTank4;
	
};