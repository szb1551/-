#include"manage.h"
//#include"map.h"

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
	cout << NowWindowWidth << " " << NowWindowHeight << endl;
	draw = new Draw(hBitmap, hwnd, NowWindowWidth, NowWindowHeight);
	if (windowstate == background)
		draw->DrawBackground();
	else if (windowstate == WindowState::begin)
	{
		draw->initworld();
	}
	delete draw;
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