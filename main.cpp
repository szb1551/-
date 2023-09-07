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
			MW->ToggleBeginView();
		else if (wp == ID_BUTTON_SETTING)
			MW->ToggleSetView();
		else if (wp == ID_BUTTON_END)
			MW->ToggleEndView();
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
	case WM_KEYDOWN:
		switch (wp)
		{
		case VK_UP:
			//MessageBox(NULL, L"点击了", L"上建", NULL);
			MW->ChangeWorld(up);
			/*if (!ON2) {
				change(&g_tank, 0, 0 - g_tank.yverb, 0);
				hdc1 = GetDC(hWnd);
				DRAWONE(&g_tank, hdc1, 0);
				ReleaseDC(hWnd, hdc1);
			}*/
			//if(g_tank.maprow==rows-1)MessageBox(hh,L"pa",L"sd",NULL);
			break;
		case VK_DOWN:
			MW->ChangeWorld(down);
			break;
		case VK_LEFT:
			MW->ChangeWorld(Direction::left);
			break;
		case VK_RIGHT:
			MW->ChangeWorld(Direction::right);
			break;
		case VK_SPACE:
			/*if (!ON2) {
				timer[count] = count;
				count++;
				bx[count - 1] = g_tank.x;
				by[count - 1] = g_tank.y;
				init2(&bb[count - 1], g_tank.hurt2, g_tank.x, g_tank.y, g_tank.direction, count - 1);
				bb[count - 1].source = &g_tank;
				bb[count - 1].group = mtank;
				c101[count - 1] = g_tank.direction;
				SetTimer(hWnd, timer[count - 1], 50, NULL);
				hdc1 = GetDC(hWnd);
				DRAWONE(&g_tank, hdc1, 0);
				ReleaseDC(hWnd, hdc1);
			}*/
			break;
		}
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