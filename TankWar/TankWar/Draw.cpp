#include "stdafx.h"
#include "Draw.h"
//���ÿ���̨����
 bool Draw::SetWindowSize(char* pszWindowTitle, int nX, int nY)
{
	char setConsole[30];
	sprintf_s(setConsole, "mode con cols=%d lines=%d", WINDOWS_WIDTH, WINDOWS_HIGH);
	system(setConsole);
	/*
	HANDLE hStdIn, hStdOut;
	hStdIn = GetStdHandle((STD_INPUT_HANDLE));
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//��ȡ������̨���ڴ�С
	COORD pos = GetLargestConsoleWindowSize(hStdOut);
	COORD bufferSize = { pos.X , pos.Y };

	if (!SetConsoleScreenBufferSize(hStdOut, bufferSize))
	{
	printf("buffer error(%d,%d)%d\n", pos.X , pos.Y, GetLastError());
	return false;
	}

	SMALL_RECT srctWindow = { 0, 0, nX*2+1, nY+1};
	if (!SetConsoleWindowInfo(hStdOut, true, &srctWindow))
	{
	printf("size error %d\n", GetLastError());
	return false;
	}

	COORD buffer = { nX + 1, nY + 1 };
	if (!SetConsoleScreenBufferSize(hStdOut, buffer))
	{
	printf("buffer error(%d,%d)%d\n", buffer.X, buffer.Y, GetLastError());
	return false;
	}*/
	SetConsoleTitleA(pszWindowTitle);
	return true;
}
//��ӡ��ͼ
void Draw::DrawMap(int nMap[][MAP_WIDTH])
{
	for (int i = 0; i <MAP_WIDTH; i++)
	{
		for (int j = 0; j <MAP_HIGH; j++)
		{
			if (nMap[j][i] == WALL_A)
				writeChar(i, j, "��", BACKGROUND_RED);
			else if (nMap[j][i] == WALL_B)
				writeChar(i, j, "��", BACKGROUND_RED  );
			else if (nMap[j][i] == WALL_C)
				writeChar(i, j, "��", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			else if (nMap[j][i] == WALL_D)
				writeChar(i, j, "��", FOREGROUND_GREEN);
			else if (nMap[j][i] == WALL_H)
				writeChar(i, j, "��", BACKGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
			else if (nMap[j][i] == WALL_G)
				writeChar(i, j, "��", FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
		}
	}
}
//��ӡ�ַ�
void Draw::writeChar(int x, int y, char * pszChar, char wArr)
{
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	COORD loc;
	loc.X = x * 2;
	loc.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wArr);

	std::cout<<pszChar;
}


//��һ�����棬��ʾ���˵�
int Draw::showOption()
{
	//����
	Draw::clearConsole(8);
	Draw::writeChar(15, 11, "̹�˴�ս v1.0", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	char  ch;
	int option = 0;
	
	writeChar(13, 13 , "��", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	char * options[] = { "������Ϸ", "˫����Ϸ", "�༭��ͼ", "��    ��", "��Ϸ����", "��    ��" };
	for (int i = 0; i < 6; i++)
	{
		writeChar(15, 13 + i, options[i], FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}


	while (true)
	{
		if (_kbhit())
		{
			ch = _getch();

			if (ch == 27)	//esc
			{
				return -1;
			}
			if (ch == 72 || ch == 80||ch == '\r')  //ֻ������¼�
			{

				if (ch == 72)	//UP
				{
					writeChar(12, 13 + option, "    ", 0);
					option--;
				}
				else if (ch == 80)	//DOWN
				{
					writeChar(12, 13 + option, "    ",0);
					option++;
				}
				if (option < 0)
				{
					option = 0;
				}
				else if (option >= 6)
				{
					option--;
				}
				//�������¼�֮�����ʾ
				writeChar(13, 13 + option, "                        ",0);
				Sleep(100);
				writeChar(13, 13 + option, "��", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				writeChar(15, 13 + option, options[option], FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				
				if (ch == '\r')
				{
					return option;
				}
			}
		
		}
	}
}
//���ý���
void Draw::showConfig()
{
	Draw::clearConsole(8);
	char  ch;
	int option = 0;
	int num;
	char * charNum = new char[4];
	writeChar(13, 13, "��", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	char * options[] = { "�з�̹������", "�з�̹�˹�����", "�з�̹��Ѫ��", "�з�̹���ƶ��ٶ�", "�з�̹���Զ�Ѱ·", "��    ��" };
	int optionsNum[] = { countEnemyTank,speedMoveBullet, enemyTankHP,speedMoveTank, 0 };

	//��ʾѡ��
	for (int i = 0; i < 6; i++)
	{
		writeChar(15, 13 + i, options[i], FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
	//��ʾѡ���Ĳ���
	for (int i = 0; i < 5; i++)
	{
		(char *)_itoa_s(optionsNum[i], charNum, 6, 10);
		writeChar(25, 13 + i, charNum, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}
	//���ܰ���
	while (true)
	{
		if (_kbhit())
		{
			ch = _getch();

			//����˳�
			if ((ch == '\r')|| ch == 27)
			{
				//�����ø���
				countEnemyTank = optionsNum[0];
				speedMoveBullet = optionsNum[1];
				enemyTankHP = optionsNum[2];
				speedMoveTank = optionsNum[3];
				return;
			}

			//ֻ������¼�
			if (ch == 72 || ch == 80 || ch == '\r')
			{

				if (ch == 72)	//UP
				{
					//�����ͷ
					writeChar(12, 13 + option, "    ", 0);
					option--;
				}
				else if (ch == 80)	//DOWN
				{
					writeChar(12, 13 + option, "    ", 0);
					option++;
				}
				//��ֹѡ�
				if (option < 0)
				{
					option = 0;
				}
				else if (option >= 6)
				{
					option--;
				}

			}
			//������Ҽ�
			if (ch == 75 || ch == 77)
			{
				if (ch == 75)  //LEFT
				{
					num = --optionsNum[option];
				}
				else if (ch = 77)   //RIGHT
				{
					num = ++optionsNum[option];
				}

				//��ֹ����������Χ
				if (optionsNum[option] <= 0)	//�������в�����СֵΪ1�����ĸ�����Ϊ0;
				{
					if (option != 4)
					{
						optionsNum[option] = 1;
					}
					else
					{
						optionsNum[option] = 0;
					}
				}
				else if (optionsNum[0] > 4)	 //���Ƶз�̹�˵����ֵΪ4
				{
					optionsNum[0] = 4;
				}
				else if (optionsNum[4] > 1)	//���Ƶ��ĸ����������ֵΪ1
				{
					optionsNum[4] = 1;
				}

				(char *)_itoa_s(num, charNum, 6, 10);

				writeChar(25, 13 + option, charNum, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

			}
			//�������¼�֮�����ʾ
			writeChar(25, 13 + option, "                ", 0);
			writeChar(13, 13 + option, "��", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			writeChar(15, 13 + option, options[option], FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			if (option < 5)
			{
				(char *)_itoa_s(optionsNum[option], charNum, 6, 10);
				writeChar(25, 13 + option, charNum, FOREGROUND_GREEN| FOREGROUND_INTENSITY);

			}
		}
	}
}


//���ָ���е�����
void Draw::clearConsole(int x)
{
	for (int i = 0; i < x;i++)
	{
		writeChar(0, 13+i, "                                                                                                     ", 0);
	}
	
}
//��ӡ����
void Draw::help()
{
	Draw::clearConsole(8);
	writeChar(15, 13, "���1 ͨ���������w�� s�� a�� d�ĸ�������̹�����ϡ��¡������ƶ���", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	writeChar(15, 14, "      ͨ������ո����ӵ���", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	writeChar(15, 15, "���2 ͨ��������̡��������������ĸ�������̹�����ϡ��¡������ƶ���", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	writeChar(15, 16, "      ͨ���������j�����ӵ���", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	while (true)
	{
		if (_kbhit())
		{
			char ch = _getch();
			if (ch == '\r')
			{
				return;
			}
		}
	}
	
}
void Draw::editMap()
{

}

int Draw::myTankHP;

int Draw::countMyTank;
int Draw::speedMoveBullet;

int Draw::speedMoveTank;

int Draw::countEnemyTank;
int Draw::enemyTankHP;	//�з�̹��Ѫֵ