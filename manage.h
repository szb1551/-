#pragma once
#include "map.h"

enum WindowState { background, begin, game, set, end };

#define IDC_WINDOWSPROJECT1 109

//设立一个Manage类来管理窗口
class ManageWindow
{
private:
	HWND hwnd;
	int ImageWidth;
	int ImageHeight;
	HBITMAP hBitmap;
	int NowWindowWidth = WindowWidth;
	int NowWindowHeight = WindowHeight;
	int ButtonCount = 3;//窗口内按钮的数量
	void Update();//更新Window窗口大小
	BOOL CALLBACK EnumChildProc(HWND hwndChild, LPARAM lParam); //检查是否有子窗口，按钮数量增加
	Draw* draw=nullptr; //定义Draw类变量
	WindowState windowstate=background;
public:
	ManageWindow(HWND hwnd, HBITMAP hBitmap, int width, int height);
	ManageWindow(HWND hwnd, HBITMAP hBitmap);
	void PaintView(); //窗口改变时更改背景图片大小
	void ToggleBeginView();//开始游戏时，渲染物体
	void ToggleSetView();//点击设置按钮
	void ToggleEndView();//点击结束按钮
	void ToggleView();//TODO
	void WindowChange();//改变窗口大小时，更改其它物体坐标
	void ChangeWorld(Direction dir);//改变世界，移动等操作
	void ChangeWorld_Fire();//发射子弹等操作
};