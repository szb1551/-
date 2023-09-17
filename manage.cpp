#include"manage.h"
#include "collide.h"
#include "include.h"
//#include"map.h"

extern AllObjects All_Ob; //外部引用范例
Player* PA = new Player(rows - 1, 4, up);
vector<TANK*> EM;
int Timer_Bullet_Count = 1;
int Timer_Enemy_Count = 10;


ManageWindow::ManageWindow(HWND hwnd, HBITMAP hBitmap, int width, int height)
{
	this->hwnd = hwnd;
	this->hBitmap = hBitmap;
	this->NowWindowWidth = width;
	this->NowWindowHeight = height;
	//PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	draw = new Draw(hBitmap, hwnd, hdc, NowWindowWidth, NowWindowHeight);
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
	HDC hdc = BeginPaint(hwnd, &ps);
	draw = new Draw(hBitmap, hwnd, hdc, NowWindowWidth, NowWindowHeight);
	if (windowstate == background)
		draw->DrawBackground();
	else if (windowstate == WindowState::begin)
	{
		draw->BeginBufferHdc();
		draw->InitBackGround();
		draw->InitWorld();
		All_Ob.show();
		draw->EndBufferHdc();
		windowstate = game;
		SetTimer(hwnd, 0, 20, WorldTimerProc);
		SetTimer(hwnd, Timer_Bullet_Count, 400, EnemyTankTimerProc);
		SetTimer(hwnd, Timer_Enemy_Count, 1000, EnemyTankDirectionProc);
	}
	else if (windowstate == WindowState::game)
	{
		draw->BeginBufferHdc();
		draw->InitBackGround();
		draw->ChangeWorld();
		if (PA)
		{
			draw->DrawTank(PA);
			if (PA->GetTarget())
			{
				cout << "自杀" << endl;
				windowstate = lose;
			}
		}
		for (int i = 0; i < min(ENEMY_EXIST_NUM,EM.size()); i++)
		{
			if (dynamic_cast<Enemy*>(EM[i]))
			{
				Enemy* temp = dynamic_cast<Enemy*>(EM[i]);
				temp->show = true;
			}
			draw->DrawTank(EM[i]);
			if (EM[i]->GetTarget())
			{
				cout << " 它杀" << endl;
				windowstate = lose;
			}
		}
		draw->EndBufferHdc();
		if (PA == nullptr)
		{
			windowstate = lose;	
		}
		else if (EM.size() == 0)
		{
			windowstate = win;
		}
	}
	else if (windowstate == win)
	{
		cout << "赢了" << endl;
		KillAllTimer(hwnd);
		draw->DrawWinGround();
	}
	else if (windowstate == lose)
	{
		cout << "输了" << endl;
		KillAllTimer(hwnd);
		draw->DrawLoseGround();
	}
	delete draw;
	EndPaint(hwnd, &ps);
}

void ManageWindow::ChangeWorld(Direction dir)
{
	if (PA)
	{
		if (dir != PA->direction)
		{
			PA->direction = dir;
			PA->change_dir = true;
		}
		else
			PA->change_dir = false;
		PA->Update();
	}
}


void KillAllTimer(HWND hwnd)
{
	KillTimer(hwnd, 0);
	KillTimer(hwnd, Timer_Bullet_Count);
	KillTimer(hwnd, Timer_Enemy_Count);
}

void CALLBACK WorldTimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	InvalidateRect(hwnd, NULL, TRUE);
}

void CALLBACK BulletTimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	PA->bullet.Update();
}

void CALLBACK EnemyTankDirectionProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	for (int i = 0; i < min(ENEMY_EXIST_NUM,EM.size()); i++)
	{
		Enemy* temp = dynamic_cast<Enemy*>(EM[i]);
		if (i % 2 == 0&&PA)
			temp->direction = temp->EnemyDirection(PA->GetImagePoint());
		else
			temp->direction = temp->EnemyDirection(Point(15, 6));
		
	}
}

void CALLBACK EnemyTankTimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	for (int i = 0; i < min(ENEMY_EXIST_NUM, EM.size()); i++)
	{
		EM[i]->Update();
	}
}

void ManageWindow::ChangeWorld_Fire()
{
	if (PA&&PA->Get_Bullet_state() == 0)
	{
		if (PA->button_fire == false)
		{
			PA->button_fire = true;
		}
		else
		{
			PA->button_fire = false;
			
		}	
	}
	//InvalidateRect(hwnd, NULL, TRUE);
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