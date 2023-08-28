#include "map.h"

HBITMAP hBitmap;
int width= WindowWidth;
int height = WindowHeight;

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
void Draw::DrawBackground()
{
	PAINTSTRUCT ps;
	hdc = BeginPaint(hwnd, &ps);
	//创建内存设备上下文
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hBitmap);

	//读取图像
	if (GetImage())
	{
		StretchBlt(hdc, 0, 0, NowWidth, NowHeight, hdcMem, 0, 0, ImageWidth, ImageHeight, SRCCOPY);
	}
	//绘制图像
	//BitBlt(hdc, 0, 0, 1284, 588, hdcMem, 0, 0, SRCCOPY);
	//清理资源
	SelectObject(hdcMem, hOldBitmap);
	DeleteDC(hdcMem);
	EndPaint(hwnd, &ps);
}

//void initworld() {
//	//GetClientRect(hh, &worldre);
//	HBITMAP map[4];
//	for (int i = 0; i < 4; i++)
//	{
//		string filename = "image/myobject" + (i+'0') + "_66.bmp";
//		//filename = L"image/myobject%d_66.bmp" % (i);
//		//wsprintf(filename, "%d", i);//格式化写入map0/1/2/3.bmp
//		map[i] = (HBITMAP)LoadImage(gg, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//加载图片的函数
//	}
//	xlength = (double)(worldre.right) / (4 * cols);
//	ylength = (double)worldre.bottom / (2 * rows);
//	int x, y;
//	hdc4 = GetDC(hh);
//	for (int rowNum = 0; rowNum < rows; rowNum++) {
//		//MessageBox(hh,L"S",L"S",NULL);
//		for (int colNum = 0; colNum < cols; colNum++) {
//			x = (2 * colNum + 1) * xlength;//贴图所在横坐标			
//			y = (2 * rowNum + 1) * ylength;//贴图所在纵坐标	
//			if (mapIndex[rowNum][colNum] == 1) {
//				init3(&ob[obcount++], x, y, colNum, rowNum);
//				ob[obcount - 1].mapcol = colNum;
//				ob[obcount - 1].maprow = rowNum;
//				ob[obcount - 1].subject = wall;
//				ob[obcount - 1].life = 1;
//			}
//			if (mapIndex[rowNum][colNum] == 3) {
//				init3(&ob[obcount++], x, y, colNum, rowNum);
//				ob[obcount - 1].mapcol = colNum;
//				ob[obcount - 1].maprow = rowNum;
//				ob[obcount - 1].subject = soil;
//				ob[obcount - 1].life = 1;
//			}
//			if (mapIndex[rowNum][colNum] == 0) {
//				init3(&ob[obcount++], x, y, colNum, rowNum);
//				ob[obcount - 1].mapcol = colNum;
//				ob[obcount - 1].maprow = rowNum;
//				ob[obcount - 1].subject = eagle;
//				ob[obcount - 1].life = 1;
//			}
//
//			if (mapIndex[rowNum][colNum] != 2)
//				Drawob(&ob[obcount - 1], hdc4, map[mapIndex[rowNum][colNum]]);
//		}
//	}
//	Deletob(&ob[0], hdc4);    ReleaseDC(hh, hdc4);
//	//object b;
//}

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

long long WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_COMMAND:
		if (wp == ID_BUTTON_START)
		{
			ToggleView();
			MessageBox(hwnd, L"开始按钮被点击了", L"按钮点击事件", MB_ICONINFORMATION);
		}
		else if (wp == ID_BUTTON_SETTING)
		{
			ToggleView();
			MessageBox(hwnd, L"设置按钮被点击了", L"按钮点击事件", MB_ICONINFORMATION);
		}
		else if (wp == ID_BUTTON_END)
		{
			ToggleView();
			MessageBox(hwnd, L"结束按钮被点击了", L"按钮点击事件", MB_ICONINFORMATION);
			DestroyWindow(hwnd);
		}
		break;
		//TODO
	case WM_SIZE:
		//当窗口大小发生改变时，更新图片的大小和位置
		WindowChange(hwnd);
		break;
	case WM_PAINT:
		PaintView(hBitmap, hwnd, width, height);
		//cout << "hello" << endl;
		break;
	case WM_CLOSE:
	case WM_DESTROY:
		cout << "someting";
		PostQuitMessage(0);
	case WM_QUIT:
		exit(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wp, lp);
	}
}

void PaintView(HBITMAP hBitmap, HWND hwnd, int width, int height)
{
	Draw draw(hBitmap, hwnd, width, height);
	draw.DrawBackground();
	draw.~Draw();
}

void WindowChange(HWND hwnd)
{
	RECT rc;
	GetWindowRect(hwnd, &rc);
	width = rc.right - rc.left;
	height = rc.bottom - rc.top;
	int buttonx = width / 2 - 50;
	int buttony = height * 0.8 - 15;
	SetWindowPos(GetDlgItem(hwnd, ID_BUTTON_START), NULL, buttonx, buttony, 100, 30, SWP_SHOWWINDOW);
	SetWindowPos(GetDlgItem(hwnd, ID_BUTTON_SETTING), NULL, buttonx, buttony+30, 100, 30, SWP_SHOWWINDOW);
	SetWindowPos(GetDlgItem(hwnd, ID_BUTTON_END), NULL, buttonx, buttony+60, 100, 30, SWP_SHOWWINDOW);
	InvalidateRect(hwnd, NULL, TRUE);
}

void ToggleView()
{

}

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
	hBitmap = (HBITMAP)LoadImage(NULL, L"image/mypaper_title.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	Draw draw(hBitmap, hwnd, width, height);
	HWND hButton1 = CreateWindow(L"Button", L"开始游戏", WS_CHILD | WS_VISIBLE, width*0.45, height*0.8, 100, 30, hwnd, (HMENU)ID_BUTTON_START, NULL, NULL);
	HWND hButton2 = CreateWindow(L"Button", L"设置", WS_CHILD | WS_VISIBLE, width * 0.45, height * 0.8+30, 100, 30, hwnd, (HMENU)ID_BUTTON_SETTING, NULL, NULL);
	HWND hButton3 = CreateWindow(L"Button", L"退出游戏", WS_CHILD | WS_VISIBLE, width * 0.45, height * 0.8+60, 100, 30, hwnd, (HMENU)ID_BUTTON_END, NULL, NULL);

	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);

	MSG msg;
	while (true) if (GetMessage(&msg, NULL, 0, 0))
	{
		cout << msg.message;
		if (msg.message == WM_QUIT) {
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}