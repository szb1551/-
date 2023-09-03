#include "manage.h"
//#include "map.h"

//HBITMAP hBitmap;
//int width = WindowWidth;
//int height = WindowHeight;

int mapIndex[rows][cols] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2,
						   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2,
						   2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 2, 3, 2,
						   2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 2, 3, 2,
						   2, 3, 3, 3, 2, 3, 1, 3, 2, 3, 3, 3, 2, 2, 3, 2,
						   2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 2, 3, 2,
						   2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 2, 3, 2,
						   2, 3, 3, 3, 2, 3, 1, 3, 2, 3, 3, 3, 2, 2, 3, 2,
						   2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 2, 3, 2,
						   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2,
						   1, 2, 2, 2, 2, 3, 2, 3, 2, 2, 2, 2, 1, 2, 3, 2,
						   2, 3, 2, 3, 2, 3, 3, 3, 2, 3, 2, 3, 2, 2, 3, 2,
						   2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 2, 3, 2,
						   2, 3, 3, 3, 2, 2, 2, 2, 2, 3, 3, 3, 2, 2, 3, 2,
						   2, 3, 2, 3, 2, 3, 3, 3, 2, 3, 2, 3, 2, 2, 3, 2,
						   2, 2, 2, 2, 2, 3, 0, 3, 2, 2, 2, 2, 2, 2, 3, 2
};


Draw::Draw(HBITMAP hBit, HWND hw)
{
	hBitmap = hBit;
	hwnd = hw;
}
Draw::Draw(HBITMAP hBit, HWND hw, int width, int height)
{
	hBitmap = hBit;
	hwnd = hw;
	NowWidth = width;
	NowHeight = height;
}
Draw::Draw(const Draw& draw)
{
	hBitmap = draw.hBitmap;
	hwnd = draw.hwnd;
	NowWidth = draw.NowWidth;
	NowHeight = draw.NowHeight;
	hdc = draw.hdc;
	ImageWidth = draw.ImageWidth;
	ImageHeight = draw.ImageHeight;
}

BOOL CALLBACK Draw::EnumChildProc(HWND hwndChild, LPARAM lParam)
{
	if (IsWindow(hwndChild) && (GetWindowLong(hwndChild, GWL_STYLE) & BS_PUSHBUTTON)) {
		// 找到一个按钮，增加计数
		ButtonCount++;
	}
	return TRUE;
}

void Draw::DrawBackground()
{
	PAINTSTRUCT ps;
	hdc = BeginPaint(hwnd, &ps);
	//创建内存设备上下文
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hBitmap);

	// 绘制按钮
	cout << "绘制按钮" << endl;
	for (int i = 1; i <= ButtonCount; i++)
	{
		int buttonx = NowWidth / 2 - 50;
		int buttony = NowHeight * 0.8 - 15 + (30 * (i - 1));
		SetWindowPos(GetDlgItem(hwnd, i), NULL, buttonx, buttony, 100, 30, SWP_SHOWWINDOW);
	}

	//读取图像
	if (GetImage())
	{
		cout << "读取图像成功" << endl;
		StretchBlt(hdc, 0, 0, NowWidth, NowHeight, hdcMem, 0, 0, ImageWidth, ImageHeight, SRCCOPY);
	}
	//绘制图像
	//BitBlt(hdc, 0, 0, 1284, 588, hdcMem, 0, 0, SRCCOPY);
	//清理资源
	SelectObject(hdcMem, hOldBitmap);
	DeleteDC(hdcMem);
	EndPaint(hwnd, &ps);
}

void Draw::initworld() {
	//GetClientRect(hh, &worldre);
	//隐藏按钮
	for (int i = 1; i <= ButtonCount; i++)
	{
		ShowWindow(GetDlgItem(hwnd, i), SW_HIDE);
	}
	HBITMAP map[4];
	PAINTSTRUCT ps;
	hdc = BeginPaint(hwnd, &ps);
	for (int i = 0; i < 4; i++)
	{
		int filenamesize = swprintf(NULL, 0, L"image/myobject%d_66.bmp", i);
		WCHAR* filename = new WCHAR[filenamesize+1];
		//filename = L"image/myobject%d_66.bmp" % (i);
		wsprintf(filename, L"image/myobject%d_66.bmp", i);//格式化写入map0/1/2/3.bmp
		map[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//加载图片的函数
		delete[]filename;
	}
	int xlength = (double)NowWidth/(cols);
	int ylength = (double)NowHeight/(rows+1);
	int x, y;
	HDC hdc = GetDC(hwnd);
	object ob;
	cout << "进入创建世界了" << endl;
	for (int rowNum = 0; rowNum < rows; rowNum++) {
		//MessageBox(hwnd,L"S",L"S",NULL);
		for (int colNum = 0; colNum < cols; colNum++) {
			x = (colNum) * xlength;//贴图所在横坐标			
			y = (rowNum) * ylength;//贴图所在纵坐标	
			int thing = mapIndex[rowNum][colNum];
			if (thing == wall) {
				ob.life = 4;
 			}
			else if (thing == food) {
				ob.life = 1;
			}
			else if (thing == eagle) {
				ob.life = 1;
			}
			ob.x = x;
			ob.y = y;
			ob.mapcol = colNum;
			ob.maprow = rowNum;
			Drawob(&ob, hdc, map[thing], xlength, ylength);
		}
	}
	DeleteDC(hdc);
	//Deletob(&ob[0], hdc4);   
	//ReleaseDC(hwnd, hdc);
	EndPaint(hwnd, &ps);
}

void Draw::Drawob(object* b, HDC hdc, HBITMAP h2, int xlength, int ylength) {
	HDC hmemdc = CreateCompatibleDC(hdc);
	SelectObject(hmemdc, h2);
	//StretchBlt(hdc, b->x, b->y, 2 * xlength, 2 * ylength, hmemdc, 290, 0, 60, 60, SRCCOPY);
	StretchBlt(hdc, b->x, b->y, xlength, ylength, hmemdc, 220, 0, 100, 120, SRCCOPY);
	DeleteObject(hmemdc);
}

bool Draw::GetImage() 
{
	BITMAP bmp;
	GetObject(hBitmap, sizeof(BITMAP), &bmp);

	ImageWidth = bmp.bmWidth;
	ImageHeight = bmp.bmHeight;
	if (ImageWidth == 0 || ImageHeight == 0)
		return false;
	return true;
}

Draw::~Draw()
{
}



//void PaintView(HBITMAP hBitmap, HWND hwnd, int width, int height)
//{
//	Draw draw(hBitmap, hwnd, width, height);
//	draw.DrawBackground();
//	draw.~Draw();
//}
//
//void WindowChange(HWND hwnd, int &width, int &height)
//{
//	RECT rc;
//	GetWindowRect(hwnd, &rc);
//	width = rc.right - rc.left;
//	height = rc.bottom - rc.top;
//	int buttonx = width / 2 - 50;
//	int buttony = height * 0.8 - 15;
//	SetWindowPos(GetDlgItem(hwnd, ID_BUTTON_START), NULL, buttonx, buttony, 100, 30, SWP_SHOWWINDOW);
//	SetWindowPos(GetDlgItem(hwnd, ID_BUTTON_SETTING), NULL, buttonx, buttony+30, 100, 30, SWP_SHOWWINDOW);
//	SetWindowPos(GetDlgItem(hwnd, ID_BUTTON_END), NULL, buttonx, buttony+60, 100, 30, SWP_SHOWWINDOW);
//	InvalidateRect(hwnd, NULL, TRUE);
//}


HWND set_window(HINSTANCE hInst)
{
	WNDCLASSEXW wc;
	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = L"WindowClassName";
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;
	RegisterClassExW(&wc);
	HWND hwnd = CreateWindowW(L"WindowClassName", L"你好", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 100, 100, WindowWidth, WindowHeight, NULL, NULL, hInst, NULL);
	if (hwnd == NULL) return (HWND) - 1;
	/*Draw draw(hBitmap, hwnd, WindowWidth, WindowHeight);
	draw.DrawBackground();
	draw.~Draw();*/
	HWND hButton1 = CreateWindow(L"Button", L"开始游戏", WS_CHILD | WS_VISIBLE, WindowWidth *0.45, WindowHeight *0.8, 100, 30, hwnd, (HMENU)ID_BUTTON_START, NULL, NULL);
	HWND hButton2 = CreateWindow(L"Button", L"设置", WS_CHILD | WS_VISIBLE, WindowWidth * 0.45, WindowHeight * 0.8+30, 100, 30, hwnd, (HMENU)ID_BUTTON_SETTING, NULL, NULL);
	HWND hButton3 = CreateWindow(L"Button", L"退出游戏", WS_CHILD | WS_VISIBLE, WindowWidth * 0.45, WindowHeight * 0.8+60, 100, 30, hwnd, (HMENU)ID_BUTTON_END, NULL, NULL);

	//ShowWindow(hwnd, SW_SHOWDEFAULT);
	//UpdateWindow(hwnd);

	return hwnd;
	//MSG msg;
	//while (true) if (GetMessage(&msg, NULL, 0, 0))
	//{
	//	//cout << msg.message;
	//	if (msg.message == WM_QUIT) {
	//		break;
	//	}
	//	TranslateMessage(&msg);
	//	DispatchMessage(&msg);
	//}
}