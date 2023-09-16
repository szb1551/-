#include"manage.h"
#include "collide.h"
//#include"map.h"

extern AllObjects All_Ob; //外部引用范例
Player* PA = new Player(rows - 1, 4, up);
ManageWindow::ManageWindow(HWND hwnd, HBITMAP hBitmap, int width, int height)
{
	this->hwnd = hwnd;
	this->hBitmap = hBitmap;
	this->NowWindowWidth = width;
	this->NowWindowHeight = height;
}

ManageWindow::ManageWindow(HWND hwnd, HBITMAP hBitmap)
{
	this->hwnd = hwnd;
	this->hBitmap = hBitmap;
}


BOOL CALLBACK ManageWindow::EnumChildProc(HWND hwndChild, LPARAM lParam)
{
	if (IsWindow(hwndChild) && (GetWindowLong(hwndChild, GWL_STYLE) & BS_PUSHBUTTON)) {
		// 找到一个按钮，增加计数
		ButtonCount++;
	}
	return TRUE;
}

void ManageWindow::PaintView()
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	cout << NowWindowWidth << " " << NowWindowHeight << endl;
	draw = new Draw(hBitmap, hwnd, hdc, NowWindowWidth, NowWindowHeight);
	if (windowstate == background)
		draw->DrawBackground();
	else if (windowstate == WindowState::begin)
	{
		draw->BeginBufferHdc();
		draw->InitBackGround();
		draw->InitWorld();
		All_Ob.show();
		draw->DrawTank(PA);
		draw->EndBufferHdc();
		windowstate = game;
	}
	else if (windowstate == WindowState::game)
	{
		draw->BeginBufferHdc();
		draw->InitBackGround();
		draw->ChangeWorld();
		draw->DrawTank(PA);
		draw->EndBufferHdc();
	}
	delete draw;
	EndPaint(hwnd, &ps);
}

void ManageWindow::ChangeWorld(Direction dir)
{
	if (dir != PA->direction)
	{
		PA->direction = dir;
		PA->change_dir = true;
	}
	else
		PA->change_dir = false;
	PA->Update();
	InvalidateRect(hwnd, NULL, TRUE);
}

void ManageWindow::ChangeWorld_Fire()
{
	if (PA->Get_Bullet_state() == 0)
	{
		if (PA->button_fire == false)
		{
			PA->button_fire = true;
			SetTimer(hwnd, 1, 50, NULL);
		}
		else
		{
			PA->button_fire = false;
			KillTimer(hwnd, 1);
		}	
	}
	InvalidateRect(hwnd, NULL, TRUE);
}

void ManageWindow::Update()
{
	RECT rc;
	GetWindowRect(hwnd, &rc);
	NowWindowWidth = rc.right - rc.left;
	NowWindowHeight = rc.bottom - rc.top;
}

void ManageWindow::WindowChange()
{
	Update();
	InvalidateRect(hwnd, NULL, TRUE);
}

void ManageWindow::ToggleBeginView()
{
	MessageBox(hwnd, L"开始按钮被点击了", L"按钮点击事件", MB_ICONINFORMATION);
	windowstate = WindowState::begin;
	PaintView();
}

void ManageWindow::ToggleSetView()
{
	windowstate = WindowState::set;
	MessageBox(hwnd, L"设置按钮被点击了", L"按钮点击事件", MB_ICONINFORMATION);
}

void ManageWindow::ToggleEndView()
{
	windowstate = WindowState::end;
	MessageBox(hwnd, L"结束按钮被点击了", L"按钮点击事件", MB_ICONINFORMATION);
	DestroyWindow(hwnd);
}