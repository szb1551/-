#pragma once
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <list>
using std::vector;
using std::list;

#pragma region ȫ�ֲ�������

#define SPEEDDISTANTBULLET	1200	    //�з������ӵ��ļ��ʱ��

//���ڴ�С
#define WINDOWS_WIDTH 120   
#define WINDOWS_HIGH  41

//��ͼ��С
#define MAP_WIDTH 45					//��ͼ��
#define MAP_HIGH  40					//��ͼ��


#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3

#pragma endregion

#pragma region ����ͼ��

#define WALL__      0x00  // "  " �յ��������ƻ���  ��ͨ����				
#define WALL_A      0x01  // "��" ��ǽ��  ���ƻ�������ͨ����		
#define WALL_B      0x02  // "�d" ��ǽ��  ���ƻ�, ����ͨ������ǽ���ƻ���̬��
#define WALL_C      0x03  // "��" ��ǽ (�����ƻ�, ����ͨ��)
#define WALL_D      0x04  // "��" �����������ƻ�,   �ӵ���ͨ����̹�˲���ͨ����
#define WALL_E      0x05  // "��" ���֣������ƻ���  ��ͨ������������	
#define WALL_G      0x06  // "��" ���ӣ������ƻ���  ��ʰȡ�������ԣ�
#define WALL_H      0x07  // "��" ���أ�  ���ƻ�������ͨ��)

#define TANK_C       0x10  //  "��"	//�ҷ�̹��1
#define TANK_B1      0x11  //  "��"	//�з�̹��1
#define TANK_B2      0x12  //  "��"	//�з�̹��2
#define TANK_B3      0x13  //  "��"	//�з�̹��3
#define TANK_B4      0x14  //  "��"	//�з�̹��4
#define TANK_B5      0x15  //  "��"	//�з�̹��5
#define TANK_B6      0x16  //  "��"	//�з�̹��6
#define TANK_A       0x19  //  "��" //�ҷ�̹��2
#define TANK_D       0x18  //  "��"
#define TANK_E       0x17  //  "��"

#define BLOOD_0     0x20   //  "  "
#define BLOOD_1     0x21   //  "��"
#define BLOOD_2     0x22   //  "��"
#define BLOOD_3     0x23   //  "��"
#define BLOOD_4     0x24   //  "��"
#define BLOOD_5     0x25   //  "��"
#define BLOOD_6     0x26   //  "��"
#define BLOOD_7     0x27   //  "��"
#define BLOOD_8     0x28   //  "��"
#define BLOOD_9     0x29   //  "��"

#define MISSIL_0    0x30   //  "  "
#define MISSIL_1    0x31   //  "��"
#define MISSIL_2    0x32   //  "��"
#define MISSIL_3    0x33   //  "��"
#define MISSIL_4    0x34   //  "��"
#define MISSIL_5    0x35   //  "��"
#define MISSIL_6    0x36   //  "��"
#define MISSIL_7    0x37   //  "��"
#define MISSIL_8    0x38   //  "��"
#define MISSIL_9    0x39   //  "��"
#pragma endregion

class CData
{
public:
	static int GetTypeOfMap(int x, int y);
	static void SetTypeOfMap(int x, int y, int type);

	static int g_sysMap00[MAP_HIGH][MAP_WIDTH];

};

#pragma region ��ͼ
extern int g_sysMap01[MAP_HIGH][MAP_WIDTH];

#pragma endregion