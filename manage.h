#pragma once
#include "map.h"

enum WindowState { background, begin, game, set, end };

#define IDC_WINDOWSPROJECT1 109

//����һ��Manage����������
class ManageWindow
{
private:
	HWND hwnd;
	int ImageWidth;
	int ImageHeight;
	HBITMAP hBitmap;
	int NowWindowWidth = WindowWidth;
	int NowWindowHeight = WindowHeight;
	int ButtonCount = 3;//�����ڰ�ť������
	void Update();//����Window���ڴ�С
	BOOL CALLBACK EnumChildProc(HWND hwndChild, LPARAM lParam); //����Ƿ����Ӵ��ڣ���ť��������
	Draw* draw=nullptr; //����Draw�����
	WindowState windowstate=background;
public:
	ManageWindow(HWND hwnd, HBITMAP hBitmap, int width, int height);
	ManageWindow(HWND hwnd, HBITMAP hBitmap);
	void PaintView(); //���ڸı�ʱ���ı���ͼƬ��С
	void ToggleBeginView();//��ʼ��Ϸʱ����Ⱦ����
	void ToggleSetView();//������ð�ť
	void ToggleEndView();//���������ť
	void ToggleView();//TODO
	void WindowChange();//�ı䴰�ڴ�Сʱ������������������
	void ChangeWorld(Direction dir);//�ı����磬�ƶ��Ȳ���
	void ChangeWorld_Fire();//�����ӵ��Ȳ���
};