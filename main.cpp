#include "player.h"
#include "bullet.h"
#include "manage.h"

HBITMAP hBitmap;
ManageWindow* MW;
//int width = WindowWidth;
//int height = WindowHeight;

long long WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_COMMAND:
		if (wp == ID_BUTTON_START)
		{
			MW->ToggleBeginView();
			
		}
		else if (wp == ID_BUTTON_SETTING)
		{
			MW->ToggleSetView();
			
		}
		else if (wp == ID_BUTTON_END)
		{
			MW->ToggleEndView();
		}
		break;
		//TODO
	case WM_SIZE:
		cout << "调用WM_SIZE";
		//当窗口大小发生改变时，更新图片的大小和位置
		//MW.WindowChange();
		if(MW!=nullptr)
			MW->WindowChange();
		//WindowChange(hwnd, width, height);
		break;
	case WM_PAINT:
		cout << "调用WM_PAINT";
		//MW.PaintView();
		if (MW != nullptr)
			MW->PaintView();
		//PaintView(hBitmap, hwnd, width, height);
		break;
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
	case WM_QUIT:
		exit(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wp, lp);
	}
}

int main()
{
	hBitmap = (HBITMAP)LoadImage(NULL, L"image/mypaper_title.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HINSTANCE hInst = 0;
	HWND hwnd = set_window(hInst);
	MW = new ManageWindow(hwnd, hBitmap);
	//ShowWindow(hwnd, SW_SHOW);
	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);
	MSG msg;
	while (true) if (GetMessage(&msg, NULL, 0, 0))
	{
		//cout << msg.message;
		if (msg.message == WM_QUIT) {
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}