#pragma once
#include"include.h"
#include"player.h"

const int WindowWidth = 1280;
const int WindowHeight = 720;
const int ID_BUTTON_START = 1;
const int ID_BUTTON_SETTING = 2;
const int ID_BUTTON_END = 3;
//typedef struct tagWNDCLASSA {
//	UINT style;
//	WNDPROC lpfnWndProc;
//	int cbClsExtra;
//	int cbWndExtra;
//	HINSTANCE hInstance;
//	HICON hIcon;
//	HCURSOR hCursor;
//	HBRUSH hbrBackground;
//	LPCSTR lpszMenuName;
//	LPCSTR lpszClassName;
//}WNDCLASSA, *PWNDCLASSA, *NPWNDCLASSA, *LPWNDCLASSA;

HWND set_window(HINSTANCE hInst);
long long WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
void ToggleView();
void PaintView(HBITMAP hBitmap, HWND hwnd, int width, int height);
void WindowChange(HWND hwnd, int &width, int &height);

//设立物体枚举及物体的状态和位置信息
enum Subject { eagle, wall, sail, food };
struct object {
	double x;
	double y;
	int maprow;
	int mapcol;
	int life;
};

//设计一个Draw类来绘制窗口，主要用来渲染
class Draw {
private:
	HBITMAP hBitmap;
	HWND hwnd;
	HDC hdc;
	int ImageWidth;
	int ImageHeight;
	int NowWidth = WindowWidth;
	int NowHeight = WindowHeight;
	int ButtonCount = 3;
	BOOL CALLBACK EnumChildProc(HWND hwndChild, LPARAM lParam);
public:
	Draw(HBITMAP hBit, HWND hw, int width, int height);
	Draw(HBITMAP hBit, HWND hw);
	Draw(const Draw& draw);
	Draw() {};
	void DrawBackground(); //加载开始界面背景
	void InitBackGround(); //加载游戏界面背景
	void initworld(); //游戏内容初=初始化
	void DrawTank(TANK*tank); //绘制坦克
	void ClearTank(); //删除坦克
	template<typename T1, typename T2> void Drawob(T1* b, HDC& hdc, HBITMAP h2, T2 xlength, T2 ylength, int x1 = 220, int y1 = 0, int w1 = 110, int h1 = 120);
	bool GetImage();
	bool GetImage(HBITMAP hBlt);
	~Draw();
};



#define rows 16
#define cols 16


