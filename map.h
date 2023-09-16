#pragma once
#include"include.h"
#include"player.h"
#include "Structs.h"
#include "enemy.h"

//��������ö�ټ������״̬��λ����Ϣ
enum Subject { eagle, iron, sail, wall };



const int WindowWidth = 1280;
const int WindowHeight = 765;
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



//���һ��Draw�������ƴ��ڣ���Ҫ������Ⱦ
class Draw {
private:
	HBITMAP hBitmap;
	HWND hwnd;
	HDC hdc;
	HDC hdc2; //����˫���弼��
	int ImageWidth;
	int ImageHeight;
	int NowWidth = WindowWidth;
	int NowHeight = WindowHeight;
	int ButtonCount = 3;
	BOOL CALLBACK EnumChildProc(HWND hwndChild, LPARAM lParam);
public:
	Draw(HBITMAP hBit, HWND hw, HDC hdc, int width, int height);
	Draw(HBITMAP hBit, HWND hw);
	Draw(const Draw& draw);
	Draw() {};
	void DrawBackground(); //���ؿ�ʼ���汳��
	void InitBackGround(); //������Ϸ���汳��
	void InitWorld(); //��Ϸ���ݳ�=��ʼ��
	void ChangeWorld(); //��Ϸ���ݽ���ʱ����
	void DrawTank(TANK*tank); //����̹��
	void ClearTank(); //ɾ��̹��
	void DrawBullet(Bullet* bullet);//�����ӵ�
	void DeleteBullet(Bullet* bullet);//ɾ���ӵ�
	void BeginBufferHdc();
	void EndBufferHdc();//˫����ʵ��
	template<typename T1, typename T2> void Drawob(T1* b, HDC& hdc, HBITMAP h2, T2 xlength, T2 ylength, int x1 = 220, int y1 = 0, int w1 = 110, int h1 = 120);
	bool GetImage();
	bool GetImage(HBITMAP hBlt);
	~Draw();
};



#define rows 16
#define cols 16


