
#include "stdafx.h"
#include "Control.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Control con;
	con.init();
	while (true)
	{
		int option = Draw::showOption();
		switch (option)
		{
		case 0:con.gameStart(1);			 break;	 //������Ϸ
		case 1:con.gameStart(2);			 break;	 //˫����Ϸ
		case 2:Draw::editMap();      	 break;	 //�༭��ͼ
		case 3:Draw::showConfig();	     break;	 //����
		case 4:Draw::help();		     break;	 //��Ϸ����
		case 5:return 0;			     break;	 //�˳���Ϸ
		}
	}
	return 0;
}

