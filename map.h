#pragma once
#include"include.h"

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

//��������ö�ټ������״̬��λ����Ϣ
enum Subject { eagle, sail, wall, food };
struct object {
	int x;
	int y;
	int maprow;
	int mapcol;
	int life;
};

//���һ��Draw�������ƴ��ڣ���Ҫ������Ⱦ
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
	void DrawBackground();
	void initworld();
	void Drawob(object* b, HDC hdc, HBITMAP h2, int xlength, int ylength);
	bool GetImage();
	~Draw();
};



#define rows 16
#define cols 16


